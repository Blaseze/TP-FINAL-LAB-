#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>

#ifndef PACIENTE_H_INCLUDED
#define PACIENTE_H_INCLUDED

///STRUCT PRÁCTICA POR INGRESO Y LISTA PRÁCTICA POR INGRESO
typedef struct
{
    int nroIngreso;
    int nroPractica;
    char resultado[40];
}practicaXingreso;

typedef struct nodoListaPracXingreso
{
    practicaXingreso datos;
    struct nodoListaPracXingreso *siguiente;

}nodoListaPracXingreso;

///***************************************************///

///STRUCT INGRESOS Y LISTA DE INGRESOS
typedef struct
{
    int nroIngreso;
    char fechaIngreso[11]; //por default es la actual
    char fechaRetiro[11];
    char dniPaciente[9];
    char matriculaProfesional[10];
    int eliminado;
}ingresos;

typedef struct nodoListaIngresos
{
    ingresos datosIngresoPac;
    struct nodoListaIngresos *siguiente;
    nodoListaPracXingreso *listaPracticasPorIngreso;

}nodoListaIngresos;

///***************************************************///

///STRUCT PACIENTE Y ÁRBOL PACIENTE
typedef struct
{
    char apellidoYnombre[40];
    int edad;
    char dni[9];
    char direccion[30];
    char telefono[20];
    int eliminados;
}paciente;

typedef struct nodoarbol
{
    paciente dato;
    struct nodoarbol *izq;
    struct nodoarbol *der;
    nodoListaIngresos *listaIngresosPac;
}nodoarbol;

///***************************************************///

///FUNCIONES - PACIENTES
paciente cargaPaciente(nodoarbol* arbol , paciente nuevoPaciente);
void mostrarPaciente(paciente persona);

///FUNCIONES VALIDACIONES - PACIENTES
int verificaNombre(char nombre[]);
int verificaEdad(int edad);
int verificaExistenciaPaciente(nodoarbol* arbol , char dniPaciente[]);
int verificaDni(char dniP[]);
int verificaDireccion(char direccion[]);
int verificaTelefono(char telefono[]);

///FUNCIONES DE ÁRBOL - PACIENTES
nodoarbol* inicArbol();
nodoarbol* crearNodoArbol(paciente persona);
nodoarbol *insertar(nodoarbol *arbol,paciente dato);
void mostrarArbolInOrder(nodoarbol *arbol);
nodoarbol* buscarPacienteArbol(nodoarbol* arbol , char dniPaciente[9]);
nodoarbol* cargaArbolPacientes(nodoarbol* arbol);

///FUNCIONES DE LISTA - INGRESOS
nodoListaIngresos* inicListaIngresos();
nodoListaIngresos* crearNodoIngreso(ingresos ingresoPac);
nodoListaIngresos* agregarEnOrdenListaIngresos(nodoListaIngresos* listaIngresos , nodoListaIngresos* nuevoNodoIngreso);
void mostrarListaIngresos(nodoListaIngresos* listaIngresos);

///FUNCIONES AUXILIARES - INGRESOS
ingresos cargaDatosIngresos(nodoarbol *arbol , ingresos ingresoPaciente);
nodoListaIngresos* agregarInicioListaIngresos(nodoListaIngresos* listaIngresos , nodoListaIngresos* nuevoNodoIngreso);
void mostrarUnaPracticaPorIngreso(practicaXingreso prac);

///FUNCIONES DE LISTA - PARACTICAS POR INGRESO
nodoListaPracXingreso* inicListaPracPorIngreso();
nodoListaPracXingreso* crearNodoPracPorIngreso(practicaXingreso prac);
nodoListaPracXingreso* agregarEnOrdenListaPracPorIngreso(nodoListaPracXingreso* listaPracPorIngreso , nodoListaPracXingreso* nuevoNodoPracPorIngreso);
void mostrarListaPracPorIngreso(nodoListaPracXingreso* listaPracPorIngreso);

///FUNCIONES AUXILIARES - PARACTICAS POR INGRESO
nodoListaPracXingreso* agregarInicioListaPracPorIngreso(nodoListaPracXingreso* listaPracPorIngreso , nodoListaPracXingreso* nuevoNodoPracPorIngreso);
void mostrarUnaPracticaPorIngreso(practicaXingreso prac);

#endif // PACIENTE_H_INCLUDED
