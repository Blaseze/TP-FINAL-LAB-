#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>

#include "practicas.h"
#include "ingresoSistema.h"

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
    nodoListaPracticas* listaPrac;
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
    nodoListaIngresos* listaIng;
}nodoarbol;


///***************************************************///

///STRUCT AUXILIAR - LISTA PACIENTE
typedef struct
{
    paciente datosPac;
    struct nodoListaPaciente *siguiente;
}nodoListaPaciente;

///***************************************************///
///***************************************************///

///STRUCT CREACION USUARIOS
typedef struct
{
    char usuarioPaciente[8];
    char contrasenia[8];
    int nivel;

}UsuarioPaciente;


///***************************************************///

///  FUNCIONES CREACION USUARIO
void crearUsuarioPaciente(paciente pacienteUsu);
void cambiarContraseniaPacientes(char archivoUsuPaciente[30], UsuarioPaciente usuPaciente);
///FUNCIONES - PACIENTES
paciente cargaPaciente(char nombreArchivo[]);
void mostrarArchPacientes(char nombreArchivo[]);
void mostrarPaciente(paciente persona);
void cargaEnArchivo(char nombreArchivo[]);
void guardaUnaPersona(char nombreArchivo[],paciente perso);

///FUNCIONES VALIDACIONES - PACIENTES
int verificaNombre(char nombre[]);
int verificaEdad(int edad);
int verificaExistenciaPaciente(char nombreArchivo[],char dniPaciente[]);
int verificaDni(char dniP[]);
int verificaDireccion(char direccion[]);
int verificaTelefono(char telefono[]);

///FUNCIONES DE ÁRBOL - PACIENTES
nodoarbol* inicArbol();
nodoarbol* crearNodoArbol(paciente persona);
nodoarbol *insertar(nodoarbol *arbol,paciente dato);
void mostrarArbolInOrder(nodoarbol *arbol);
nodoarbol* buscarPacienteArbol(nodoarbol* arbol , char dniPaciente[]);
nodoarbol* pasarArchPacienteToArbol(char nombreArchivo[] , nodoarbol* arbol);
nodoarbol* tomar_nodo_mayor_valor (nodoarbol* arbol);
nodoarbol* tomar_nodo_menor_valor (nodoarbol* arbol);
nodoarbol* eliminar_nodo_de_arbol (nodoarbol* arbol, char dni[8]);

///FUNCIONES DE LISTA - PACIENTES
nodoListaPaciente* iniclistaPaciente();
nodoListaPaciente* crearNodoPaciente(paciente pac);
nodoListaPaciente* agregarInicioListaPaciente(nodoListaPaciente* listaPac , nodoListaPaciente* nuevoNodoPac);
nodoListaPaciente* agregarEnOrdenListaPaciente(nodoListaPaciente* listaPac , nodoListaPaciente* nuevoNodoPac);
void mostrarListaPaciente(nodoListaPaciente* listaPac);
nodoListaPaciente* pasarArchPacToListaPac(char nombreArchivo[] , nodoListaPaciente* listaPac);

///FUNCIONES DE ARCHIVOS INGRESOS - PACIENTES
void guardarUnIngreso(char nombreArchivo[] , ingresos ingPac);
int ultimoIngresoArch(char nombreArchivo[]);
void mostrarUnIngreso(ingresos ingresoPaciente);
void agregarIngreso(char nombreArchivo[] , nodoarbol* arbol);
void mostrarArchIngresos(char nombreArchivo[]);

///FUNCIONES DE LISTA INGRESOS - PACIENTES
nodoListaIngresos* inicListaIngresos();
nodoListaIngresos* crearNodoIngreso(ingresos ingresoPac);
nodoListaIngresos* agregarEnOrdenListaIngresos(nodoListaIngresos* listaIngresos , nodoListaIngresos* nuevoNodoIngreso);
void mostrarListaIngresos(nodoListaIngresos* listaIngresos);
nodoListaIngresos* buscarIngresoPorNumIngreso(nodoListaIngresos* listaIng , int numIngreso);
ingresos buscarIngresoPorDni(nodoListaIngresos* listaIng , char dniPac[]);
nodoListaIngresos* pasarArchToListaIng(char nombreArchivo[] , nodoListaIngresos* listaIng);

///FUNCIONES AUXILIARES INGRESOS - PACIENTES
ingresos cargaDatosIngresos(nodoarbol* arbol , ingresos ingresoPaciente);
nodoListaIngresos* agregarInicioListaIngresos(nodoListaIngresos* listaIngresos , nodoListaIngresos* nuevoNodoIngreso);
//void mostrarUnIngreso(ingresos ingresoPaciente);

///FUNCIONES DE LISTA - PARACTICAS POR INGRESO - PACIENTES
nodoListaPracXingreso* inicListaPracPorIngreso();
nodoListaPracXingreso* crearNodoPracPorIngreso(practicaXingreso prac);
nodoListaPracXingreso* agregarEnOrdenListaPracPorIngreso(nodoListaPracXingreso* listaPracPorIngreso , nodoListaPracXingreso* nuevoNodoPracPorIngreso);
void mostrarListaPracPorIngreso(nodoListaPracXingreso* listaPracPorIngreso);

///FUNCIONES AUXILIARES - PARACTICAS POR INGRESO - PACIENTES
nodoListaPracXingreso* agregarInicioListaPracPorIngreso(nodoListaPracXingreso* listaPracPorIngreso , nodoListaPracXingreso* nuevoNodoPracPorIngreso);
void mostrarUnaPracticaPorIngreso(practicaXingreso prac);

///FUNCIONES ARCHIVO - PRACTICAS POR INGRESO - PACIENTES
practicaXingreso cargaDatosPracticaPorIngreso(practicaXingreso pracPorIng , nodoListaPracticas* listaPrac , nodoListaIngresos* listaIng);
void guardarUnaPracticaPorIngreso(char nombreArchivo[] , practicaXingreso pracXing);
void mostrarArchPracticasPorIngreso(char nombreArchivo[]);
void agregarPracticasPorIngreso(char nombreArchivo[] , nodoListaIngresos* listaIng, nodoListaPracticas* listaPrac);

///FUNCIONES ADL
nodoarbol* altaAdl(nodoarbol* adl , paciente pac , ingresos ingPac);
void mostrarAdlPacientes(nodoarbol* adl);
nodoarbol* cargaAdlPacientes(char nombreArchPac[] , nodoarbol* adl , char nombreArchIng[]);

///FUNCIONES MENU
void mostrarEstudioPaciente(nodoarbol* arbol, UsuarioPaciente usuario);

#endif // PACIENTE_H_INCLUDED
