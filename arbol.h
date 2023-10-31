#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "Pacientes.h"


typedef struct nodoarbol
{
    paciente dato;
    struct nodoarbol *izq;
    struct nodoarbol *der;

}nodoarbol;



nodoarbol* inicArbol();
nodoarbol* crearNodoArbol(paciente persona);
nodoarbol *insertar(nodoarbol *arbol,paciente dato);
void mostrarArbolPreOrder(nodoarbol *arbol);
void mostrarArbolInOrder(nodoarbol *arbol);
void mostrarArbolPosOrder(nodoarbol *arbol);
nodoarbol *pasarArchivoToArbol(char nombreArchivo[],nodoarbol *arbol);


#endif // ARBOL_H_INCLUDED
