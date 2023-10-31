#include "listaEmpleados.h"

nodoListaEmpleados* inicListaEmpleados()
{
    return NULL;
}

nodoListaEmpleados* crearNodoEmpleado(empleados_laboratorio emple)
{
    nodoListaEmpleados* auxNodoEmple = (nodoListaEmpleados*)malloc(sizeof(nodoListaEmpleados));

    auxNodoEmple->dato = emple;
    auxNodoEmple->siguiente = NULL;

    return auxNodoEmple;
}

nodoListaEmpleados* agregarEnOrdenListaEmpleados(nodoListaEmpleados* lista , nodoListaEmpleados* nuevoNodo)
{
    if(lista == NULL){
        lista = nuevoNodo;
    }else{
        if(strcmpi(nuevoNodo->dato.apeYnombre , lista->dato.apeYnombre) < 0){
            lista = agregarInicioListaEmpleados(lista , nuevoNodo);
        }else{
            nodoListaEmpleados* ante = lista;
            nodoListaEmpleados* seg = lista->siguiente;

            while((seg != NULL) && (strcmpi(nuevoNodo->dato.apeYnombre , seg->dato.apeYnombre) > 0)){
                ante = seg;
                seg = seg->siguiente;
            }

            ante->siguiente = nuevoNodo;
            nuevoNodo->siguiente = seg;
        }
    }

    return lista;
}

void mostrarListaEmpleados(nodoListaEmpleados* lista) //solo va a mostrar los empleados en ALTA
{
    nodoListaEmpleados* seg = lista;

    if(seg != NULL){
        while(seg != NULL){
            if(seg->dato.estado == 1){
                mostrarUnEmpleado(seg->dato);
            }

            seg = seg->siguiente;
        }
    }
}

nodoListaEmpleados* buscarEmpleadoLista(nodoListaEmpleados* lista , char dniEmpleado[])
{
    nodoListaEmpleados* encontrado = NULL;
    nodoListaEmpleados* seg = lista;

    if(seg != NULL){
        while((encontrado == NULL) && (seg != NULL)){
            if(strcmp(seg->dato.dni , dniEmpleado) == 0){
                encontrado = seg;
            }else{
                seg = seg->siguiente;
            }
        }
    }

    return encontrado;
}

/// --------------------------------- FUNCIONES ESTRUCTURAS COMPUESTAS --------------------------------- ///
int pasarArchivoEmpladosToAdl(char nombreArchivo[] , celdaPerfil adl[] , int dimension)
{
    empleados_laboratorio auxReg;
    int valEmpleados = 0;
    char perfilEmple[20];
    FILE *pArchivo = fopen(nombreArchivo , "rb");

    if(pArchivo != NULL){
        while((fread(&auxReg , sizeof(empleados_laboratorio) , 1 , pArchivo) > 0) && (valEmpleados < dimension)){
            strcpy(perfilEmple , auxReg.perfil);
            valEmpleados = altaAdlEmpleados(adl , valEmpleados , perfilEmple , auxReg);
        }
        fclose(pArchivo);
    }else{
        printf(" ERROR en la lectura del archivo. \n\n");
    }

    return valEmpleados;
}

void mostrarAdlEmpleados(celdaPerfil adl[] , int validos)
{
    int i;

    for(i=0 ; i<validos ; i++){
        printf("\t*************************************************** \n");
        printf("\t\t\t Perfil: %s \n" , adl[i].perfilEmpleado);
        printf("\t*************************************************** \n");

        mostrarListaEmpleados(adl[i].lista);
    }
}

///FUNCIONES AUXILIARES
nodoListaEmpleados* agregarInicioListaEmpleados(nodoListaEmpleados* lista , nodoListaEmpleados* nuevoNodo)
{
    if(lista == NULL){
        lista = nuevoNodo;
    }else{
        nuevoNodo->siguiente = lista;
        lista = nuevoNodo;
    }

    return lista;
}

int buscarPerfil(celdaPerfil adl[] , int validos , char perfil[])
{
    int pos = -1;
    int i = 0;

    while((i < validos) && (pos == -1)){
        if(strcmpi(adl[i].perfilEmpleado , perfil) == 0){
            pos = i;
        }else{
            i++;
        }
    }

    return pos;
}

int agregarPerfil(celdaPerfil adl[] , int validos , char perfil[])
{
    strcpy(adl[validos].perfilEmpleado , perfil);
    adl[validos].lista = inicListaEmpleados();

    validos++;

    return validos;
}

int altaAdlEmpleados(celdaPerfil adl[] , int validos , char perfil[] , empleados_laboratorio emple)
{
    nodoListaEmpleados* nuevoEmpleado = crearNodoEmpleado(emple);

    int pos = buscarPerfil(adl , validos , perfil);

    if(pos == -1){
        validos = agregarPerfil(adl , validos , perfil);
        pos = validos-1;
    }

    adl[pos].lista = agregarEnOrdenListaEmpleados(adl[pos].lista , nuevoEmpleado);

    return validos;
}
