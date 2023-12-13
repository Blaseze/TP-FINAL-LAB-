#ifndef INGRESOSISTEMA_H_INCLUDED
#define INGRESOSISTEMA_H_INCLUDED

#include "empleado.h"
#include "paciente.h"

UsuarioPaciente ingresarUsuarioPaciente();
UsuarioEmpleado ingresarUsuarioEmpleado();
void menuPaciente();
void menuEmpleado(nodoarbol* arbol);
void menu();
void portadaInicio();
void portadaInicioEstatica();
void leerPassword(char pass[]);

#endif // INGRESOSISTEMA_H_INCLUDED
