#include <stdio.h>
#include <stdlib.h>
#include "funcionesauxiliares.h"


#define DIM_PAC 100
#define archi "nombreArchivo.dat" /** ACOMODAR ARCHIVO */

/** FUNCION PARA PASAR DE ARCHIVO A UN ARREGLO EN ORDEN POR APELLIDO **/
/*******************//**
Funcion que pasa del archivo de clientes a un Array
**************************/
int archivoAArregloAltas(paciente a[], int dim)
{
    int v = 0;///creo los validos del arreglo recibido
    paciente p;

    FILE *fp = fopen(archi, "rb");///abro el archivo en modo lectura

    if(fp)
    {
        while(fread(&p, sizeof(paciente),1, fp) > 0)///recorro todo el archivo
        {
            if((p.eliminados == 0) && v<dim)///controlo que el archivo no tenga mas datos de los que soporta el arreglo
            {
                a[v] = p;///igualo el dato de ese archivo al arreglo en su posicion correspondiente
                v++;///incremento su posicion
            }

        }

        fclose(fp);///cierro el archivo
    }

    return v;///retorno los validos
}


/*******************//**
* \ Funcion que busca el menor apellido de un arreglo
* \param Validos, array, posicion de inicio
* \return Posicion del menor apellido
**************************/
int buscaMenorApellidoArreglo(int v, paciente a[], int pos)
{
    int posmenor = pos;///toma como posicion menor el valor de pos
    int i = pos + 1;///al arreglo se empieza a recorrer una posicion mas adelante que posmenos


    while(i<v)///se recorre todo el arreglo
    {
        ///res = strcmpi(a[i], a[posmenor]);
        if(strcmpi(a[i].apellidoYnombre, a[posmenor].apellidoYnombre) < 0)///compara el valor de i con el de posmenor
        {
            posmenor = i;///si es menor posmenor toma el valor de i
        }
        i++;
    }

    return posmenor;///retorna el valor de la posicion menor
}

/*******************//**
* \ Funcion de ordenamiento por seleccion de apellido de un arreglo
* \param Validos, arreglo
* \return Void
**************************/
void ordenamientoSeleccionAregloApellido(int v, paciente a[])
{
    int posmenor = 0;///recibe lo que retorna la busqueda de la posicion menor
    int i = 0;

    while(i<v)///recorre todo el arreglo
    {
        posmenor = buscaMenorApellidoArreglo(v, a, i);///posmenor almacena lo que retorna la funcion aneterior

        intercambio(&a[i], &a[posmenor]);

        i++;
    }

}

/*******************//**
* \brief Funcion de ordenamiento por Seleccion del archivo por apellido (pasa los datos a un array)
* \param None
* \return Void
**************************/
void ordenacionSeleccionArchivoApellido()
{
    paciente ordenacion[DIM_PAC];///este arreglo almacena los clientes del archivo para luego ser ordenado
    int vOrdenacion = 0;

    vOrdenacion = archivoAArregloAltas(ordenacion, DIM_PAC);///paso el archivo al arreglo

    ordenamientoSeleccionAregloApellido(vOrdenacion, ordenacion);///ordeno el arreglo

    muestraArreglo(vOrdenacion, ordenacion);

}

void intercambio(paciente *i, paciente *menor)
{
    paciente aux;

    aux = *menor;
    *menor = *i;
    *i = aux;
}

void muestraArreglo(int v, paciente a[])
{
    int i;
    for(i = 0; i<v; i++)
    {
        muestraUnPaciente(a[i]);
    }

}


/**********************************************
MUESTRO UN CLIENTE.
**********************************************/
void muestraUnPaciente(paciente p)
{
    printf("------------------------------------------------- \n");
    printf("Apellido y Nombre......: %s\n", p.apellidoYnombre);
    printf("Edad...................: %d\n", p.edad);
    printf("Dni....................: %s\n", p.dni);
    printf("Direccion..............: %s \n", p.direccion);
    printf("Telefono...............: %s \n", p.telefono);
    printf("Baja s/n...............: %d \n", p.eliminados);
    printf("------------------------------------------------- \n");
}
