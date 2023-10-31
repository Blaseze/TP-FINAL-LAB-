#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "listaEmpleados.h"
#include "ingresos.h"

int main()
{
    char archEmpleadosLab[] = {"empleadosLab.dat"};
    int totalRegistrosArch = 0;
    int cantPerfilesEmpleados = 0;
    celdaPerfil *adlEmpleados = NULL;
    int valAdlEmpleados = 0;
    char dniEmpleado[9];


    cargarArchEmpleados(archEmpleadosLab);

    system("cls");

    printf("\n EMPLEADOS CARGADOS: \n\n");
    mostrarArchEmpleados(archEmpleadosLab);

    totalRegistrosArch = calculaCantRegistros(archEmpleadosLab , sizeof(empleados_laboratorio));
    printf(" Se han registrado un total de %d empleados. \n\n" , totalRegistrosArch);

    system("pause");
    system("cls");

    cantPerfilesEmpleados = contarPerfiles(archEmpleadosLab);
    adlEmpleados = (celdaPerfil*)malloc((sizeof(celdaPerfil) * cantPerfilesEmpleados));

    if(adlEmpleados != NULL){
        valAdlEmpleados = pasarArchivoEmpladosToAdl(archEmpleadosLab , adlEmpleados , cantPerfilesEmpleados + 1);

        printf("\n\t\t\t Actualemente se encuentra %d perfiles de empleados registrados: \n" , cantPerfilesEmpleados);
        printf("\n\n LISTA DE EMPLEADOS EN ALTA POR PERFILES: \n\n");
        mostrarAdlEmpleados(adlEmpleados , valAdlEmpleados);
    }else{
        printf(" ERROR al reservar espacio de memoria. \n\n");
    }

    system("pause");
    system("cls");

    printf("\n Ingresar DNI del empleado a modificar: ");
    fflush(stdin);
    gets(dniEmpleado);

    system("cls");

    modificarEmpleadoEnArchivo(archEmpleadosLab , dniEmpleado);

    return 0;
}
