#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "gotoxy.h"
#include "colors.h"
#include "listaEmpleados.h"
#include "paciente.h"

#ifndef MENUDIOS_H_INCLUDED
#define MENUDIOS_H_INCLUDED

typedef struct {
    int dia;
    int mes;
    int anio;
}Fecha;


///FUNCIONES DE DISEÑO DEL MENÚ ADMIN
void progressBar();
void portadaMenuAdmin();

///************************************************************************* ///

///MENÚ PRINCIPAL ADMIN
void menuPrintAdmin();
void menuAdmin();

///************************************************************************* ///

///SUB-MENÚ EMPLEADO
void subMenuPrintEmpleado();
void subMenuEmpleado(int opcion , char nombreArchEmpleados[]);

///FUNCIONES DEL SUB-MENÚ EMPLEADO
void subMenuEmpleadoCase1(char nombreArchEmpleados[]);
void subMenuEmpleadoCase2(char nombreArchEmpleados[]);
void subMenuEmpleadoCase3(char nombreArchEmpleados[]);
void subMenuEmpleadoCase4(char nombreArchEmpleados[]);
void subMenuEmpleadoCase5(char nombreArchEmpleados[]);
void subMenuEmpleadoCase6(char nombreArchEmpleados[]);

///************************************************************************* ///

///SUB-MENÚ PRÁCTICA
void subMenuPrintPractica();
void subMenuPractica(int opcion , char nombreArchPracticas[]);

///FUNCIONES DEL SUB-MENÚ PRÁCTICA
void subMenuPracticaCase1(char nombreArchPracticas[]);
void subMenuPracticaCase2(char nombreArchPracticas[]);
void subMenuPracticaCase3(char nombreArchPracticas[]);
void subMenuPracticaCase4(char nombreArchPracticas[]);
void subMenuPracticaCase5(char nombreArchPracticas[]);

///************************************************************************* ///

///SUB-MENÚ PACIENTE
void subMenuPrintPaciente();
void subMenuPaciente(int opcion , char nombreArchPaciente[]);

///FUNCIONES DEL SUB-MENÚ PACIENTE
void subMenuPacienteCase1(char nombreArchPaciente[]);
void subMenuPacienteCase2(char nombreArchPaciente[]);
void subMenuPacienteCase3(char nombreArchPaciente[]);
void subMenuPacienteCase4(char nombreArchPaciente[]);
void subMenuPacienteCase5(char nombreArchPaciente[]);

///************************************************************************* ///

///SUB-MENÚ INGRESO
void subMenuPrintIngreso();
void subMenuIngreso(int opcion , char nombreArchIngresos[] , nodoarbol* arbolPacientes , char nombreArchPxi[] , char nombreArchPac[] , char nombreArchPrac[]);

///FUNCIONES DEL SUB-MENÚ INGRESO
void subMenuIngresoCase1(char nombreArchIngresos[] , nodoarbol* arbolPacientes);
void subMenuIngresoCase2(char nombreArchIngresos[]);
void subMenuIngresoCase3(char nombreArchIngresos[]);
void subMenuIngresoCase4(char nombreArchIngresos[]);
void subMenuIngresoCase5(char nombreArchPac[] , char nombreArchIngresos[] , nodoarbol* arbolPacientes);
void subMenuIngresoCase6(char nombreArchIngresos[] , char dniPac[]);
void subMenuIngresoCase7(char nombreArchPxi[] , char dniPac[]);
void subMenuIngresoCase8(char nombreArchPxi[]);

///************************************************************************* ///

///SUB-MENÚ CONSULTAS
void subMenuPrintConsultas();
void subMenuConsulas(int opcion , nodoarbol* arbol , char nombreArchPac[] , nodoListaIngresos* listaIng , char nombreArchPractica[]);

///FUNCIONES DEL SUB-MENÚ CONSULTAS
void subMenuConsultasCase1(nodoarbol* arbol , char dniPac[]);
void subMenuConsultasCase2(char nombreArchPacientes[] , char apeyNombreA[]);
void subMenuConsultasCase3(nodoListaIngresos* listaIng , char dniPac[]);
void subMenuConsultasCase4(nodoListaIngresos* listaIng, char fechaDesde[], char fechaHasta[]);
void subMenuConsultasCase5(char nombreArchPrac[] , char nombrePrac[]);

#endif // MENUDIOS_H_INCLUDED
