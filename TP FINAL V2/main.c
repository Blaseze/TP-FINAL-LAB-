#include <stdio.h>
#include <stdlib.h>
#include "empleado.h"
#include "listaEmpleados.h"
#include "paciente.h"
#include "practicas.h"
#include "menuDios.h"

int main()
{
///VARIABLES PARA EMPLEADOS
    char archEmpleadosLab[] = {"empleadosLab.dat"};
    int totalRegistrosArchEmple = 0;
    int cantPerfilesEmpleados = 0;
    celdaPerfil *adlEmpleados = NULL;
    int valAdlEmpleados = 0;
    char dniEmpleado[9];


///VARIABLES PARA ARBOL Y PACIENTE
    char archPacientes[] = {"pacientes.dat"};
    int totalRegistrosArchPac = 0;
    nodoarbol* arbolPacientes;
    nodoListaPaciente* listaPaciente;

    arbolPacientes = inicArbol();

    listaPaciente = iniclistaPaciente();

///VARIABLES PARA PRACTICAS
    char archPracticas[] = {"practicasLab.dat"};
    int nroPracAModificar = 0;
    int nroPracAEliminar = 0;
    int nroPracADarAlta = 0;
    int totalPracticas = 0;
    nodoListaPracticas* listaPracticas;

    listaPracticas = inicListaPracticas();

///VARIABLES PARA INGRESOS
    char archIngresos[] = {"ingresosPacientes.dat"};
    int totalRegistrosArchIng = 0;
    nodoListaIngresos* listaIngresosPacientes;

  listaIngresosPacientes = inicListaIngresos();

///VARIABLES PARA PRAC. POR ING.
    char archPracXing[] = {"pracXing.dat"};
    int totalRegistrosArchPracXing = 0;

///VARIABLES PARA ADL
    nodoarbol* adlPacientes = inicArbol();

//    cargarArchEmpleados(archEmpleadosLab);

//    system("cls");
/*
    printf("\n EMPLEADOS CARGADOS: \n\n");
    mostrarArchEmpleados(archEmpleadosLab);

    totalRegistrosArchEmple = calculaCantRegistros(archEmpleadosLab , sizeof(empleados_laboratorio));
    printf(" Se han registrado un total de %d empleados. \n\n" , totalRegistrosArchEmple);

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
*/
/*
    printf("\n Ingresar DNI del empleado a modificar: ");
    fflush(stdin);
    gets(dniEmpleado);

    system("cls");

    modificarEmpleadoEnArchivo(archEmpleadosLab , dniEmpleado);
*/
/*
    arbolPacientes = cargaArbolPacientes(arbolPacientes);
    arbolPacientes->listaIngresosPac = altaIngreso(arbolPacientes , archPracticas);

    system("cls");

    printf("\n ARBOL DE PACIENTES CARGADO: \n\n");
    mostrarArbolInOrder(arbolPacientes);

    printf(" LISTA DE INGRESOS... \n\n");
    mostrarListaIngresos(arbolPacientes->listaIngresosPac);
*/
//    cargarArchPracticas(archPracticas);

//    system("cls");

/*
    printf("\n PR%cCTICAS REGISTRADAS: \n\n" , 181);
    mostrarArchPracticas(archPracticas);

    totalPracticas = calculaCantRegistros(archPracticas , sizeof(practicas));

    printf(" Se han registrado un total de %d pr%ccticas. \n\n" , totalPracticas , 160);

    system("pause");
    system("cls");
*/
/*
    printf("\n Ingreasar nro de practica a modificar: ");
    scanf("%d" , &nroPracAModificar);

    modificarPractica(archPracticas , nroPracAModificar);
*/
/*
    printf("\n Ingreasar nro de practica a ELIMINAR: ");
    scanf("%d" , &nroPracAEliminar);

    darBajaPrac(archPracticas , nroPracAEliminar);

    system("pause");
    system("cls");

    printf("\n REGISTRO DE PR%cCTICAS ACUTALIZADO: \n\n" , 181);
    mostrarArchPracticas(archPracticas);

    system("pause");
    system("cls");

    listaPracticas = pasarArchPracToListaPrac(archPracticas , listaPracticas);

    printf("\n LISTA DE PR%cCTICAS ORDENADA POR NOMBRE: \n\n" , 181);
    mostrarListaPractica(listaPracticas);

    system("pause");
    system("cls");

    printf("\n Ingreasar nro de practica a dar de ALTA: ");
    scanf("%d" , &nroPracADarAlta);

    darAltaPrac(archPracticas , nroPracADarAlta);

    system("pause");
    system("cls");

    printf("\n REGISTRO DE PR%cCTICAS ACUTALIZADO: \n\n" , 181);
    mostrarArchPracticas(archPracticas);

    system("pause");
    system("cls");
*/
/*
    listaPracticas = pasarArchPracToListaPrac(archPracticas , listaPracticas);

    printf("\n LISTA DE PR%cCTICAS DISPONIBLES: \n\n" , 181);
    mostrarListaPractica(listaPracticas);

    system("pause");
    system("cls");
*/
//    cargaEnArchivo(archPacientes);
//
//    system("cls");

/*
    printf("\n PACIENTES CARGADOS... \n\n");
    mostrarArchPacientes(archPacientes);

    totalRegistrosArchPac = calculaCantRegistros(archPacientes , sizeof(paciente));
    printf(" Se han registrado un total de %d pacientes. \n\n" , totalRegistrosArchPac);

    system("pause");
    system("cls");
*/
    arbolPacientes = pasarArchPacienteToArbol(archPacientes , arbolPacientes);

    printf("\n PACIENTES CARGADOS: \n\n");
    mostrarArbolInOrder(arbolPacientes);

    system("pause");
    system("cls");

/*
    listaPaciente = pasarArchPacToListaPac(archPacientes , listaPaciente);

    printf("\n LISTA DE PACIENTES ORDENADA POR NOMBRE \n\n");
    mostrarListaPaciente(listaPaciente);
*/

    agregarIngreso(archIngresos , arbolPacientes);

    system("cls");


    printf("\n INGRESOS CARGADOS: \n\n");
    mostrarArchIngresos(archIngresos);

    totalRegistrosArchIng = calculaCantRegistros(archIngresos , sizeof(ingresos));
    printf(" Se han registrado un total de %d ingresos. \n\n" , totalRegistrosArchIng);

    system("pause");
    system("cls");
/*

    listaIngresosPacientes = pasarArchToListaIng(archIngresos , listaIngresosPacientes);

    printf("\n LISTA DE INGRESOS DE PACIENTES: \n\n");
    mostrarListaIngresos(listaIngresosPacientes);


    system("pause");
    system("cls");
*/
/*
    agregarPracticasPorIngreso(archPracXing , listaIngresosPacientes , listaPracticas);

    printf("\n RESUTALDOS CARGADOS: \n\n");
    mostrarArchPracticasPorIngreso(archPracXing);

    totalRegistrosArchPracXing = calculaCantRegistros(archPracXing , sizeof(practicaXingreso));

    printf(" Se han cargado un total de %d resultados. \n\n" , totalRegistrosArchPracXing);

    system("pause");
    system("cls");
*/
    adlPacientes = cargaAdlPacientes(archPacientes , adlPacientes , archIngresos);

    system("cls");

    printf("\n ADL DE PACIENTES CARGADO: \n\n");
    mostrarAdlPacientes(adlPacientes);

//    menuPrintAdmin();

    return 0;
}
