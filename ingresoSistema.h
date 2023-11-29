#ifndef INGRESOSISTEMA_H_INCLUDED
#define INGRESOSISTEMA_H_INCLUDED
#include "paciente.h"
#include "empleado.h"
typedef struct
{
    char dniPaciente[30];
    char contrasenia[10];
    int nivel;

}UsuarioPaciente;

typedef struct
{
    char usuarioAdmin[10];///default Admin1234
    char contraAdmin[10];///default Dios1234
}UsuarioAdmin;

typedef struct
{
    char usuarioEmpleado[10];
    char contraEmpleado[10];
     int nivel;//
}UsuarioEmpleado;

void crearUsuarioPaciente(paciente paciente);
void crearUsuarioEmpleado(empleados_laboratorio empleados);
void cambiarContraseņaPacientes(char archivoP[30]);
void cambiarContraseņaEmpleados(char archivoP[30]);
int ingresarUsuarioPaciente();
int ingresarUsuarioEmpleado();
void menuPaciente();
void menuEmpleado();
void menu();


#endif // INGRESOSISTEMA_H_INCLUDED
