#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef PRACTICAS_H_INCLUDED
#define PRACTICAS_H_INCLUDED

///PRACTICAS DEL PACIENTE
typedef struct
{
    int nroPractica;
    char nombrePractica[100];
    int eliminado;
}practicas;

typedef struct nodoListaPracticas
{
    practicas datosPracticas;
    struct nodoListaPracticas *siguiente;
}nodoListaPracticas;

///FUNCIONES PRACTICAS - ARCHIVO
void cargarArchPracticas(char nombreArchivo[]);
practicas cargaDatosPrac(practicas prac);
void guardarUnaPractica(char nombreArchivo[] , practicas prac);
void mostrarUnaPractica(practicas prac);
void mostrarArchPracticas(char nombreArchivo[]);
int ultimoNumPracCargada(char nombreArchivo[]);
void modificarPractica(char nombreArchivo[] , int nroPrac);
void darBajaPrac(char nombreArchivo[] , int nroPrac);
void darAltaPrac(char nombreArchivo[] , int nroPrac);

///FUNCIONES DE LISTA - PRACTICAS
nodoListaPracticas* inicListaPracticas();
nodoListaPracticas* crearNodoPractica(practicas pracPaciente);
nodoListaPracticas* agregarInicioListaPractica(nodoListaPracticas* listaPrac , nodoListaPracticas* nuevoNodoPrac);
nodoListaPracticas* agregarEnOrdenListaPracticas(nodoListaPracticas* listaPrac , nodoListaPracticas* nuevoNodoPrac);
nodoListaPracticas* pasarArchPracToListaPrac(char nombreArchivo[] , nodoListaPracticas* listaPrac);
void mostrarListaPractica(nodoListaPracticas *listaPrac);
nodoListaPracticas* buscarPractica(nodoListaPracticas* listaPrac , int nroPrac);

#endif // PRACTICAS_H_INCLUDED
