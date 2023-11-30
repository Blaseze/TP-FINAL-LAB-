#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>

#ifndef EMPLEADO_H_INCLUDED
#define EMPLEADO_H_INCLUDED

typedef struct
{
    char dni[9];
    char apeYnombre[40];
    char userEmpleado[20];
    char passEmpleado[9];
    char perfil[30];
    int estado;
}empleados_laboratorio;

typedef struct
{
    char usuarioEmpleado[8];
    char contraEmpleado[8];
    int nivel;

}UsuarioEmpleado;

///FUNCIONES PRINCIPALES
void crearUsuarioEmpleado(empleados_laboratorio empleados);
void cambiarContraseniaEmpleados(char archivoUsu[30], char archivoEmple[30], UsuarioEmpleado empleado);
void cargarArchEmpleados(char nombreArchivo[]);
void guardarUnEmpleado(char nombreArchivo[] , empleados_laboratorio emple);
void mostrarArchEmpleados(char nombreArchivo[]);
void agregarEmpleados(char nombreArchivo[] , empleados_laboratorio nuevo);
void modificarEmpleadoEnArchivo(char nombreArchivo[] , char dniEmpleado[]);

///FUNCIONES AUXILIARES
empleados_laboratorio cargaDatosEmpleado(char nombreArchivo[] , empleados_laboratorio emple);
void mostrarUnEmpleado(empleados_laboratorio emple);
int contarPerfiles(char nombreArchivo[]);
int calculaCantRegistros(char nombreArchivo[] , int tamDato);
int menuEdicionDatosEmpleado();
empleados_laboratorio editarDatosEmpleado(char nombreArchivo[] , empleados_laboratorio emple);

///VALIDACIONES
int verificarApeYNombre(char apeYnombreEmpleado[]);
int verificarExistenciaEmpleado(char nombreArchivo[] , char dniEmpleado[]);
int verificarDni(char dniEmple[]);
int verficarPassEmpleado(char passEmple[]);
int verificarPerfilEmpleado(char perfilEmpleado[]);

#endif // EMPLEADO_H_INCLUDED
