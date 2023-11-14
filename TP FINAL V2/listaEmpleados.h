#include "empleado.h"

#ifndef LISTAEMPLEADOS_H_INCLUDED
#define LISTAEMPLEADOS_H_INCLUDED

typedef struct nodoListaEmpleados
{
    empleados_laboratorio dato;
    struct nodoListaEmpleados *siguiente;

}nodoListaEmpleados;

typedef struct
{
    char perfilEmpleado[20];
    nodoListaEmpleados *lista;

}celdaPerfil;

///FUNCIONES DE LISTA EMPLEADOS
nodoListaEmpleados* inicListaEmpleados();
nodoListaEmpleados* crearNodoEmpleado(empleados_laboratorio emple);
nodoListaEmpleados* agregarEnOrdenListaEmpleados(nodoListaEmpleados* lista , nodoListaEmpleados* nuevoNodo);
void mostrarListaEmpleados(nodoListaEmpleados* lista);
nodoListaEmpleados* buscarEmpleadoLista(nodoListaEmpleados* lista , char dniEmpleado[]);

///FUNCIONES ESTRUCTURAS COMPUESTA - ADL EMPLEADOS
int agregarPerfil(celdaPerfil adl[] , int validos , char perfil[]);
int altaAdlEmpleados(celdaPerfil adl[] , int validos , char perfil[] , empleados_laboratorio emple);
int pasarArchivoEmpladosToAdl(char nombreArchivo[] , celdaPerfil adl[] , int dimension);
void mostrarAdlEmpleados(celdaPerfil adl[] , int validos);

///FUNCIONES AUXILIARES
nodoListaEmpleados* agregarInicioListaEmpleados(nodoListaEmpleados* lista , nodoListaEmpleados* nuevoNodo);
int buscarPerfil(celdaPerfil adl[] , int validos , char perfil[]);

#endif // LISTAEMPLEADOS_H_INCLUDED
