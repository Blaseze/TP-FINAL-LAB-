#ifndef FUNCIONESAUXILIARES_H_INCLUDED
#define FUNCIONESAUXILIARES_H_INCLUDED

typedef struct
{
    char apellidoYnombre[40];
    int edad;
    char dni[9];
    char direccion[30];
    char telefono[20];
    int eliminados;
    //nodoLista *listaEstudios;
}paciente;

int archivoAArregloAltas(paciente a[], int dim);
int buscaMenorApellidoArreglo(int v, paciente a[], int pos);
void ordenamientoSeleccionAregloApellido(int v, paciente a[]);
void ordenacionSeleccionArchivoApellido();
void intercambio(paciente *i, paciente *menor);
void muestraArreglo(int v, paciente a[]);
void muestraUnPaciente(paciente p);
#endif // FUNCIONESAUXILIARES_H_INCLUDED
