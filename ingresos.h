#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#ifndef INGRESOS_H_INCLUDED
#define INGRESOS_H_INCLUDED

typedef struct
{
    int nroIngreso;
    char fechaIngreso[11]; //por default es la actual
    char fechaRetiro[11];
    int dniPaciente;
    int matriculaProfesional;
    int eliminado;
    //nodoArbol* arbolPaciente;

}ingresos;

void fGetNow(char date[]);

#endif // INGRESOS_H_INCLUDED
