#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include "practicas.h"

#ifndef PACIENTE_H_INCLUDED
#define PACIENTE_H_INCLUDED

typedef struct
{
    int nroIngreso;
    char fechaIngreso[11]; //por default es la actual
    char fechaRetiro[11];
    char dniPaciente[9];
    char matriculaProfesional[10];
    int nroPractica;
    char nombrePractica[40];
    char resultado[40];

}regPracticasPacientes;

///STRUCT PRÁCTICA POR INGRESO Y LISTA PRÁCTICA POR INGRESO
typedef struct
{
    int nroIngreso;
    int nroPractica;
    char nombrePractica[40];
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
    nodoListaPracXingreso* listaPrac;
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

typedef struct
{
    char usuarioPaciente[9];
    char contrasenia[9];
    int nivel;

}UsuarioPaciente;

///***************************************************///

///FUNCIONES DE USUARIO - PACIENTE
void crearUsuarioPaciente(char dni[] , char contra[]);
void cambiarContraseniaPacientes(char archivoUsuPaciente[30], UsuarioPaciente usuPaciente);

/// **************************************************************************************************************** ///

///FUNCIONES DE VERIFICACIONES - PACIENTE
int verificaNombre(char nombre[]);
int verificaEdad(int edad);
int verificaExistenciaPaciente(char nombreArchivo[],char dniPaciente[]);
int verificaDni(char dniP[]);
int verificaDireccion(char direccion[]);
int verificaTelefono(char telefono[]);

/// **************************************************************************************************************** ///

///FUNCIONES DE ARCHIVO - PACIENTE
void cargaEnArchivo(char nombreArchivo[]);
void mostrarArchPacientes(char nombreArchivo[]);
void darBajaPacienteArch(char nombreArchivoPac[] , char dniPaciente[]);
void darAltaPacienteArch(char nombreArchivoPac[] , char dniPaciente[]);
void modificaPaciente(char nombreArchivo[],char dni[]);

///FUNCIONES AUXILIARES DE ARCHVIO - PACIENTE
paciente cargaPaciente(char nombreArchivo[]);
void guardaUnaPersona(char nombreArchivo[],paciente perso);
void mostrarPaciente(paciente persona);

/// **************************************************************************************************************** ///

///FUNCIONES DE ÁRBOL - PACIENTES
nodoarbol* inicArbol();
nodoarbol* crearNodoArbol(paciente persona);
nodoarbol* insertar(nodoarbol *arbol,paciente dato);
void mostrarArbolInOrder(nodoarbol *arbol);
nodoarbol* buscarPacienteArbol(nodoarbol* arbol , char dniPaciente[]);
nodoarbol* pasarArchPacienteToArbol(char nombreArchivo[] , nodoarbol* arbol);
nodoarbol* eliminar_nodo_de_arbol(nodoarbol* arbol, char dni[]);

///FUNCIONES AUXILIARES DE ÁRBOL - PACIENTES
nodoarbol* tomar_nodo_mayor_valor(nodoarbol* arbol);
nodoarbol* tomar_nodo_menor_valor(nodoarbol* arbol);

/// **************************************************************************************************************** ///

///FUNCIONES DE LISTA - PACIENTES
nodoListaPaciente* iniclistaPaciente();
nodoListaPaciente* crearNodoPaciente(paciente pac);
nodoListaPaciente* agregarEnOrdenListaPaciente(nodoListaPaciente* listaPac , nodoListaPaciente* nuevoNodoPac);
void mostrarListaPaciente(nodoListaPaciente* listaPac);
nodoListaPaciente* pasarArchPacToListaPac(char nombreArchivo[] , nodoListaPaciente* listaPac);

///FUNCIONES AUXILIARES DE LISTA - PACIENTE
nodoListaPaciente* agregarInicioListaPaciente(nodoListaPaciente* listaPac , nodoListaPaciente* nuevoNodoPac);

/// **************************************************************************************************************** ///

///FUNCIONES DE VALIDACIONES DE INGRESO
int validarFecha(char fecha[]);
int validarMatricula(char matriculaProf[]);

///FUNCIONES AUXILIARES DE INGRESOS
int convertirFecha(char fecha[]);
ingresos cargaDatosIngresos(nodoarbol* arbol , ingresos ingresoPaciente);
void mostrarUnIngreso(ingresos ingresoPaciente);

/// **************************************************************************************************************** ///

///FUNCIONES DE LISTA DE INGRESOS
nodoListaIngresos* inicListaIngresos();
nodoListaIngresos* crearNodoIngreso(ingresos ingresoPac);
nodoListaIngresos* agregarEnOrdenListaIngresos(nodoListaIngresos* listaIngresos , nodoListaIngresos* nuevoNodoIngreso);
void mostrarListaIngresos(nodoListaIngresos* listaIng);
nodoListaIngresos* buscarIngresoEnListaPorDni(nodoListaIngresos* listaIng , char dniPac[]);
ingresos buscarIngresoPorDni(nodoListaIngresos* listaIng , char dniPac[]);
nodoListaIngresos* pasarArchToListaIng(char nombreArchivo[] , nodoListaIngresos* listaIng);

///FUNCIONES AUXILIARES DE LISTA INGRESOS
nodoListaIngresos* agregarInicioListaIngresos(nodoListaIngresos* listaIngresos , nodoListaIngresos* nuevoNodoIngreso);
void mostrarUnIngreso(ingresos ingresoPaciente);

/// **************************************************************************************************************** ///

///FUNCIONES DE ARCHIVO DE INGRESOS
void agregarIngreso(char nombreArchivo[] , nodoarbol* arbol);
void mostrarArchIngresos(char nombreArchivo[]);
void darBajaIngresoArch(char nombreArchIng[] , int numIngreso);
void darAltaIngresoArch(char nombreArchIng[] , int numIngreso);
void modificarIngresoArch(char nombreArchivo[] , int numIngreso);

///FUNCIONES AUXILIARES DE ARCHIVO DE INGRESOS
void guardarUnIngreso(char nombreArchivo[] , ingresos ingPac);
int ultimoIngresoArch(char nombreArchivo[]);
int menuEdicionDatosIngresos();
ingresos editarDatosIngreso(char nombreArchivo[] , ingresos ingPaciente);

/// **************************************************************************************************************** ///

///FUNCIONES DE LISTA - PARACTICAS POR INGRESO
nodoListaPracXingreso* inicListaPracPorIngreso();
nodoListaPracXingreso* crearNodoPracPorIngreso(practicas prac,int nroIngreso , char resultado[]);
nodoListaPracXingreso* agregarEnOrdenListaPracPorIngreso(nodoListaPracXingreso* listaPracPorIngreso , nodoListaPracXingreso* nuevoNodoPracPorIngreso);
void mostrarListaPracPorIngreso(nodoListaPracXingreso* listaPracPorIngreso);
nodoListaPracXingreso* buscarPxiPorNumIngreso(nodoListaPracXingreso* listaPxi , int numIngreso);

///FUNCIONES AUXILIARES DE LISTA PARACTICAS POR INGRESO
nodoListaPracXingreso* agregarInicioListaPracPorIngreso(nodoListaPracXingreso* listaPracPorIngreso , nodoListaPracXingreso* nuevoNodoPracPorIngreso);
void mostrarUnaPracticaPorIngreso(practicaXingreso prac);
nodoListaIngresos* cargarPractica(nodoListaIngresos*arbol, int nroIngreso, char archiPracticas[]);

/// **************************************************************************************************************** ///

///FUNCIONES DE ARCHIVO - PRACTICAS POR INGRESO
regPracticasPacientes buscarPxiPorDni(char nombreArchPxi[] , char dniPac[]);
void cargarResultadoPxi(char nombreArchPxi[]);
void modificarResultado(char nombreArchPxi[] , char dniPac[] , int numIng , int numPrac);
void mostrarArchRegPracCompleta(char nombreArchivo[]);
void mostrarArchRegPracPorPaciente(char nombreArchivo[] , char dniPac[]);
void modificarPxi(char nombreArchPxi[] , char dniPac[] , char nombreArchPracticas[]);

/// **************************************************************************************************************** ///

///FUNCIONES ADL
nodoarbol* altaAdl(nodoarbol* adl, paciente pac, ingresos ingPac);
nodoarbol* cargaAdlPacientes(char nombreArchPac[], nodoarbol* adl, char nombreArchIng[]);
void mostrarAdlPacientes(nodoarbol* adl);

#endif // PACIENTE_H_INCLUDED
