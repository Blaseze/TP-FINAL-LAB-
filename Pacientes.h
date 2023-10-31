#ifndef PACIENTES_H_INCLUDED
#define PACIENTES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

typedef struct
{
    char apellidoYnombre[40];
    int edad;
    char dni[9];
    char direccion[30];
    char telefono[20];
    int eliminados;
    //nodoLista *listaEstudios;
}paciente;



int verificaNombre(char nombre[]);
int verificaEdad(int edad);
int verificaExistenciaPaciente(char nombreArchivo[],char dniPaciente[]);
int verificaDni(char dniP[]);
int verificaDireccion(char direccion[]);
int verificaTelefono(char telefono[]);
paciente cargaPaciente(char nombreArchivo[],paciente nuevoPaciente);
void mostrarArchPacientes(char nombreArchivo[]);
void mostrarPaciente(paciente persona);
void cargaEnArchivo(char nombreArchivo[]);
void guardaUnaPersona(char nombreArchivo[],paciente perso);

#endif // PACIENTES_H_INCLUDED
