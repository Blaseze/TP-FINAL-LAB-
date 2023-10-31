#include "arbol.h"
#include <stdio.h>
#include <stdlib.h>


nodoarbol* inicArbol()
{
    return NULL;
}

nodoarbol* crearNodoArbol(paciente persona)
{
    nodoarbol *aux= malloc(sizeof(nodoarbol));

    aux->dato=persona;
    aux->izq= NULL;
    aux->der= NULL;

    return aux;
}

nodoarbol *insertar(nodoarbol *arbol,paciente dato)
{
    if(arbol==NULL)
    {
        arbol= crearNodoArbol(dato);
    }
    else
    {
        if(strcmp(dato.dni,arbol->dato.dni)<0)
        {
            arbol->izq=insertar(arbol->izq,dato);
        }
        else
        {
            arbol->der=insertar(arbol->der,dato);
        }
    }

    return arbol;
}

void mostrarArbolPreOrder(nodoarbol *arbol)
{
    if(arbol)
    {
        mostrarPaciente(arbol->dato);
        mostrarArbolPreOrder(arbol->izq);
        mostrarArbolPreOrder(arbol->der);
    }
}

void mostrarArbolInOrder(nodoarbol *arbol)
{
    if(arbol)
    {
        mostrarArbolPreOrder(arbol->izq);
        mostrarPaciente(arbol->dato);
        mostrarArbolPreOrder(arbol->der);
    }
}

void mostrarArbolPosOrder(nodoarbol *arbol)
{
    if(arbol)
    {
        mostrarArbolPreOrder(arbol->izq);
        mostrarArbolPreOrder(arbol->der);
        mostrarPaciente(arbol->dato);
    }
}

nodoarbol *pasarArchivoToArbol(char nombreArchivo[],nodoarbol *arbol)
{
    paciente aux;
    FILE *archi=fopen(nombreArchivo,"rb");

    if(archi)
    {
        while(fread(&aux,sizeof(paciente),1,archi)>0)
        {
            arbol=insertar(arbol,aux);
        }
        fclose(archi);
    }
    else
    {
        printf("ERROR al leer el archivo.\n\n");
    }

    return arbol;

}


//void cargaArchivoArbol(char nombreArchivo[],nodoarbol*arbol)
//{
//    FILE *archi=fopen(nombreArchivo,"ab");
//
//    if(archi)
//    {
//        if(arbol)
//        {
//
//        }
//    }
//}





