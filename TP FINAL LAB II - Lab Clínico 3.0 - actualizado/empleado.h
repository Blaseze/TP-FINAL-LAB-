#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>

#ifndef EMPLEADO_H_INCLUDED
#define EMPLEADO_H_INCLUDED

///STRUCT para la creación de usuario tipo empleado
typedef struct
{
    char usuarioEmpleado[9];
    char contraEmpleado[9];
    int nivel;

}UsuarioEmpleado;

///STRUCT para almacenar los datos del empleado
typedef struct
{
    char dni[9];
    char apeYnombre[40];
    char userEmpleado[20];
    char passEmpleado[9];
    char perfil[30];
    int estado;
}empleados_laboratorio;

///FUNCIONES DE USUARIO
void crearUsuarioEmpleado(char dni[],char contra[],char perfil[]);
void cambiarContraseniaEmpleados(char archivoUsu[30], char archivoEmple[30], UsuarioEmpleado empleado);

///FUNCIONES DE ARCHIVOS - EMPLEADO
void cargarArchEmpleados(char nombreArchivo[]);
void cambiarContraseniaEmpleados(char archivoUsu[30], char archivoEmple[30], UsuarioEmpleado empleado);
void guardarUnEmpleado(char nombreArchivo[] , empleados_laboratorio emple);
void mostrarArchEmpleados(char nombreArchivo[]);
void agregarEmpleados(char nombreArchivo[] , empleados_laboratorio nuevo);
void modificarEmpleadoEnArchivo(char nombreArchivo[] , char dniEmpleado[]);
void darBajaEmpleadoArch(char nombreArchivo[] , char dniEmpleado[]);
void darAltaEmpleadoArch(char nombreArchivo[] , char dniEmpleado[]);

///FUNCIONES AUXILIARES - EMPLEADO
empleados_laboratorio cargaDatosEmpleado(char nombreArchivo[] , empleados_laboratorio emple);
void mostrarUnEmpleado(empleados_laboratorio emple);
int menuEdicionDatosEmpleado();
empleados_laboratorio editarDatosEmpleado(char nombreArchivo[] , empleados_laboratorio emple);

///FUNCIONES DE VERFICIACIONES - EMPLEADO
int verificarApeYNombre(char apeYnombreEmpleado[]);
int verificarExistenciaEmpleado(char nombreArchivo[] , char dniEmpleado[]);
int verificarDni(char dniEmple[]);
int verficarPassEmpleado(char passEmple[]);
int verificarPerfilEmpleado(char perfilEmpleado[]);

///FUNCIONES EXTRAS
int calculaCantRegistros(char nombreArchivo[] , int tamDato);

#endif // EMPLEADO_H_INCLUDED
