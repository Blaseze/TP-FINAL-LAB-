#include "menuDios.h"

///FUNCIONES DE DISEÑO DEL MENÚ ADMIN

//portada del menú admin
void portadaMenuAdmin()
{

    gotoxy(33,5);
    printf(GREEN " ========================================== ");
    gotoxy(33,6);
    printf(RED " ***************** M E N %c **************** " , 233);
    gotoxy(33,7);
    printf(GREEN " ========================================== ");
    gotoxy(33,8);
    printf(CYAN " ||||||||||||                  |||||||||||| ");
    gotoxy(33,9);
    printf(" ||||||||||||                  |||||||||||| ");
    gotoxy(33,10);
    printf(" |||||||       ****     ****        |||||||  ");
    gotoxy(33,11);
    printf(" ||||||||||||       ***        |||||||||||| ");
    gotoxy(33,12);
    printf(" ||||||||||||       ***        ||||||||||||  ");
    gotoxy(33,13);
    printf(" ||||||          ||     ||           |||||| ");
    gotoxy(33,14);
    printf(" ||||||||||||    || === ||     |||||||||||| ");
    gotoxy(33,15);
    printf(" ||||||||||||    ||=====||     |||||||||||| ");
    gotoxy(33,16);
    printf(GREEN " ========================================== ");
    gotoxy(33,17);
    printf(RED " ******** A D M I N I S T R A D O R ******* ");
    gotoxy(33,18);
    printf(GREEN " ========================================== \n\n");
}

//barra de carga
void progressBar()
{
    int i, x, y;
    int c = 0;

    for(i = 10 ; i <= 109 ; i++)
    {

        c++;

        gotoxy(48 , 13);
        printf(GREEN " CARGANDO...(%d%%) \n\n", c);

        gotoxy(i, 15);
        printf(YELLOW "%c", 219);

        for(x = 36 ; x < 75 ; x++)
        {
            for(y = 47; y < 75 ; y++)
            {
                gotoxy(y, 0);
            }
        }
    }

    gotoxy(4, 18);
    printf(WHITE " CARGA COMPLETA \n\n");

    system("pause");
    system("cls");
}
/// ==================================================================================================================== ///

///FUNCIONES DEL MENÚ ADMIN

//menú principal de admin
void menuPrintAdmin()
{
    portadaMenuAdmin();

    gotoxy(46,20);
    printf(WHITE " 1. EMPLEADO \n");
    gotoxy(46,21);
    printf(" 2. PR%cCTICA LAB \n" , 181);
    gotoxy(46,22);
    printf(" 3. PACIENTE \n");
    gotoxy(46,23);
    printf(" 4. INGRESO \n");
    gotoxy(46,24);
    printf(" 5. CONSULTAS \n");
    gotoxy(46,25);
    printf(" 6. SALIR \n\n");

}

void menuAdmin()
{
    char archEmpleados[] = {"empleadosLab.dat"};
    char archPracticas[] = {"practicasLab.dat"};
    char archPacientes[] = {"pacientes.dat"};
    char archIngresos[] = {"ingresosPacientes.dat"};
    char archPxi[] = {"pracXingPacientes.dat"};
    int opcion = 0;

    nodoarbol* arbol=inicArbol();
    nodoListaIngresos* listaIngresos = inicListaIngresos();

    arbol = pasarArchPacienteToArbol(archPacientes , arbol);
    listaIngresos = pasarArchToListaIng(archIngresos , listaIngresos);

    system("cls");
    progressBar();

    do{
        system("cls");

        menuPrintAdmin();

        gotoxy(3,28);
        printf(" Ingresar opci%cn: " , 162);
        fflush(stdin);
        scanf("%i", &opcion);

        switch(opcion)
        {
        case 1:
            subMenuEmpleado(opcion , archEmpleados);
            system("cls");
            break;

        case 2:
            subMenuPractica(opcion , archPracticas);
            system("cls");
            break;

        case 3:
            subMenuPaciente(opcion , archPacientes);
            system("cls");
            break;

        case 4:
            subMenuIngreso(opcion , archIngresos , arbol , archPxi , archPacientes , archPracticas);
            system("cls");
            break;

        case 5:
            subMenuConsulas(opcion , arbol , archPacientes , listaIngresos , archPracticas);
            system("cls");
            break;

        case 6:
            printf("\n Saliendo del men%c administrador.... \n\n" , 163);
            break;

        default:
            printf("\n OPCI%cN NO V%cLIDA. \n\n" , 224 , 181);
            system("pause");
        }

    }while(opcion != 6);
}

// ----------------------------------------------- SUB-MENÚ EMPLEADO ----------------------------------------------- //
void subMenuPrintEmpleado()
{
    portadaMenuAdmin();

    gotoxy(43,20);
    printf(WHITE " 1. AGREGAR EMPLEADO \n");
    gotoxy(43,21);
    printf(" 2. DAR BAJA EMPLEADO \n");
    gotoxy(43,22);
    printf(" 3. DAR ALTA EMPLEADO \n");
    gotoxy(43,23);
    printf(" 4. EDITAR DATOS DEL EMPLEADO \n");
    gotoxy(43,24);
    printf(" 5. VER LISTA DE EMPLEADOS EN ALTA POR PERFILES \n");
    gotoxy(43,25);
    printf(" 6. VER LISTA COMPLETA DE EMPLEADOS \n");
    gotoxy(43,26);
    printf(" 7. VOLVER \n\n");
}

void subMenuEmpleado(int opcion , char nombreArchEmpleados[])
{

    do{
        system("cls");

        subMenuPrintEmpleado();

        gotoxy(3,29);
        printf(" Ingresar opci%cn: " , 162);
        fflush(stdin);
        scanf(" %i" , &opcion);

        switch(opcion)
        {
        case 1:
            subMenuEmpleadoCase1(nombreArchEmpleados);
            system("pause");
            break;

        case 2:
            subMenuEmpleadoCase2(nombreArchEmpleados);
            system("pause");
            break;

        case 3:
            subMenuEmpleadoCase3(nombreArchEmpleados);
            system("pause");
            break;

        case 4:
            system("cls");
            subMenuEmpleadoCase4(nombreArchEmpleados);
            system("pause");
            break;

        case 5:
            system("cls");
            subMenuEmpleadoCase5(nombreArchEmpleados);
            system("pause");
            break;

        case 6:
            system("cls");
            subMenuEmpleadoCase6(nombreArchEmpleados);
            system("pause");
            break;

        case 7:
            break;

        default:
            printf("\n OPCI%cN NO V%cLIDA. \n\n" , 224 , 181);
            system("pause");
        }

    }while(opcion != 7);
}

// --------------------------------------- FUNCIONES DEL SUB-MENÚ EMPLEADO --------------------------------------- //
void subMenuEmpleadoCase1(char nombreArchEmpleados[])
{
    empleados_laboratorio nuevoEmpleado;
    int totalRegistrosArchEmple = 0;

    agregarEmpleados(nombreArchEmpleados , nuevoEmpleado);

    system("cls");

    printf("\n EMPLEADOS CARGADOS: \n\n");
    mostrarArchEmpleados(nombreArchEmpleados);

    totalRegistrosArchEmple = calculaCantRegistros(nombreArchEmpleados , sizeof(empleados_laboratorio));

    printf(" Se han registrado un total de %d empleados. \n\n" , totalRegistrosArchEmple);
}

void subMenuEmpleadoCase2(char nombreArchEmpleados[])
{
    char dniEmpleado[9];
    int dniValido = 0;
    int existeEmpleado = 0;

    while(existeEmpleado != 1 || dniValido == 1){
        system("cls");

        printf("\n Ingresar DNI del empleado: ");
        fflush(stdin);
        gets(dniEmpleado);

        dniValido = verificarDni(dniEmpleado);
        existeEmpleado = verificarExistenciaEmpleado(nombreArchEmpleados , dniEmpleado);

        if(dniValido == 0 && existeEmpleado == 0){
            printf("\n El DNI ingresado no es v%clido o no se encuentra registrado. \n\n" , 160);
            system("pause");
        }else{
            existeEmpleado = 1;
            dniValido = 0;
        }
    }

    darBajaEmpleadoArch(nombreArchEmpleados , dniEmpleado);
}

void subMenuEmpleadoCase3(char nombreArchEmpleados[])
{
    char dniEmpleado[9];
    int dniValido = 0;
    int existeEmpleado = 0;

    while(existeEmpleado != 1 || dniValido == 1){
        system("cls");

        printf("\n Ingresar DNI del empleado: ");
        fflush(stdin);
        gets(dniEmpleado);

        dniValido = verificarDni(dniEmpleado);
        existeEmpleado = verificarExistenciaEmpleado(nombreArchEmpleados , dniEmpleado);

        if(dniValido == 0 && existeEmpleado == 0){
            printf("\n El DNI ingresado no es v%clido o no se encuentra registrado. \n\n" , 160);
            system("pause");
        }else{
            existeEmpleado = 1;
            dniValido = 0;
        }
    }

    darAltaEmpleadoArch(nombreArchEmpleados , dniEmpleado);
}

void subMenuEmpleadoCase4(char nombreArchEmpleados[])
{
    char dniEmpleado[9];
    int dniValido = 0;
    int existeEmpleado = 0;

    while(existeEmpleado != 1 || dniValido == 1){
        system("cls");

        printf("\n Ingresar DNI del empleado: ");
        fflush(stdin);
        gets(dniEmpleado);

        dniValido = verificarDni(dniEmpleado);
        existeEmpleado = verificarExistenciaEmpleado(nombreArchEmpleados , dniEmpleado);

        if(dniValido == 0 && existeEmpleado == 0){
            printf("\n El DNI ingresado no es v%clido o no se encuentra registrado. \n\n" , 160);
            system("pause");
        }else{
            existeEmpleado = 1;
            dniValido = 0;
        }
    }

    modificarEmpleadoEnArchivo(nombreArchEmpleados , dniEmpleado);
}

void subMenuEmpleadoCase5(char nombreArchEmpleados[])
{
    int cantPerfilesEmpleados = 0;
    celdaPerfil *adlEmpleados = NULL;
    int valAdlEmpleados = 0;

    cantPerfilesEmpleados = contarPerfiles(nombreArchEmpleados);
    adlEmpleados = (celdaPerfil*)malloc((sizeof(celdaPerfil) * cantPerfilesEmpleados));

    if(adlEmpleados != NULL){
        valAdlEmpleados = pasarArchivoEmpladosToAdl(nombreArchEmpleados , adlEmpleados , cantPerfilesEmpleados + 1);

        printf("\n\t\t\t Actualemente se encuentra %d perfiles de empleados registrados: \n" , cantPerfilesEmpleados);
        printf("\n\n LISTA DE EMPLEADOS EN ALTA POR PERFILES: \n\n");
        mostrarAdlEmpleados(adlEmpleados , valAdlEmpleados);
    }else{
        printf(" ERROR al reservar espacio de memoria. \n\n");
    }
}

void subMenuEmpleadoCase6(char nombreArchEmpleados[])
{
    empleados_laboratorio auxRegEmpleado;
    nodoListaEmpleados* listaCompletaEmpleados = inicListaEmpleados();
    FILE *pArchivoEmpleados = fopen(nombreArchEmpleados , "rb");

    if(pArchivoEmpleados != NULL){
        while(fread(&auxRegEmpleado , sizeof(empleados_laboratorio) , 1 , pArchivoEmpleados) > 0){
            nodoListaEmpleados* nuevoEmpleado = crearNodoEmpleado(auxRegEmpleado);
            listaCompletaEmpleados = agregarEnOrdenListaEmpleados(listaCompletaEmpleados , nuevoEmpleado);
        }
        fclose(pArchivoEmpleados);
    }else{
        printf(" A%cn no se han registrado empleados. \n\n" , 163);
    }

    if(listaCompletaEmpleados != NULL){
        printf("\n LISTA COMPLETA DE EMPLEADOS: \n\n");
        mostrarListaEmpleadosCompleta(listaCompletaEmpleados);
    }else{
        printf(" A%cn no se han registrado empleados. \n\n" , 163);
    }

}
// --------------------------------------- FIN FUNCIONES DEL SUB-MENÚ EMPLEADO --------------------------------------- //

/// ===================================================================================================================== ///

// ------------------------------------------------ SUB-MENÚ PRÁCTICA ------------------------------------------------ //
void subMenuPrintPractica()
{
    portadaMenuAdmin();

    gotoxy(40,20);
    printf(WHITE " 1. AGREGAR PR%cCTICA LAB \n" , 181);
    gotoxy(40,21);
    printf(" 2. DAR BAJA PR%cCTICA LAB \n" , 181);
    gotoxy(40,22);
    printf(" 3. DAR ALTA PR%cCTICA LAB \n" , 181);
    gotoxy(40,23);
    printf(" 4. EDITAR DATOS DE LA PR%cCTICA LAB \n" , 181);
    gotoxy(40,24);
    printf(" 5. VER LISTA DE PR%cCTICAS LAB \n" , 181);
    gotoxy(40,25);
    printf(" 6. VOLVER \n\n");
}

void subMenuPractica(int opcion , char nombreArchPracticas[])
{

    do{
        system("cls");

        subMenuPrintPractica();

        gotoxy(3,29);
        printf(" Ingresar opci%cn: " , 162);
        fflush(stdin);
        scanf("%i" , &opcion);

        switch(opcion)
        {
        case 1:
            subMenuPracticaCase1(nombreArchPracticas);
            system("pause");
            break;

        case 2:
            subMenuPracticaCase2(nombreArchPracticas);
            system("pause");
            break;

        case 3:
            subMenuPracticaCase3(nombreArchPracticas);
            system("pause");
            break;

        case 4:
            subMenuPracticaCase4(nombreArchPracticas);
            system("pause");
            break;
        case 5:
            system("cls");
            subMenuPracticaCase5(nombreArchPracticas);
            system("pause");
            break;

        case 6:
            break;

        default:
            printf("\n OPCI%cN NO V%cLIDA. \n\n" , 224 , 181);
            system("pause");
        }

    }while(opcion != 6);
}

// --------------------------------------- FUNCIONES DEL SUB-MENÚ PRÁCTICA --------------------------------------- //
void subMenuPracticaCase1(char nombreArchPracticas[])
{
    int totalRegistrosArchPrac = 0;

    cargarArchPracticas(nombreArchPracticas);

    system("cls");

    printf(" PR%cCTICAS DE LABORATORIO CARGADAS: \n\n" , 181);
    mostrarArchPracticas(nombreArchPracticas);

    totalRegistrosArchPrac = calculaCantRegistros(nombreArchPracticas , sizeof(practicas));

    printf(" Se han registrado un total de %d pr%ccticas. \n\n" , totalRegistrosArchPrac , 160);
}

void subMenuPracticaCase2(char nombreArchPracticas[])
{
    int nroPractica = 0;

    printf("\n Ingresar nro. de pr%cctica de laboratorio:" , 160);
    scanf("%d" , &nroPractica);

    darBajaPrac(nombreArchPracticas , nroPractica);
}

void subMenuPracticaCase3(char nombreArchPracticas[])
{
    int nroPractica = 0;

    printf("\n Ingresar nro. de pr%cctica de laboratorio:" , 160);
    scanf("%d" , &nroPractica);

    darAltaPrac(nombreArchPracticas , nroPractica);
}

void subMenuPracticaCase4(char nombreArchPracticas[])
{
    int nroPracticaAMod = 0;

    printf("\n Ingresar nro. de pr%cctica de laboratorio: " , 160);
    scanf("%d" , &nroPracticaAMod);

    modificarPractica(nombreArchPracticas , nroPracticaAMod);
}

void subMenuPracticaCase5(char nombreArchPracticas[])
{
    nodoListaPracticas* listaPracticas = inicListaPracticas();

    listaPracticas = pasarArchPracToListaPrac(nombreArchPracticas , listaPracticas);

    printf("\n LISTA DE PR%cCTICAS DE LABORATORIO DISPONIBLES: \n\n" , 181);
    mostrarListaPractica(listaPracticas);
}
// ------------------------------------- FIN FUNCIONES DEL SUB-MENÚ PRÁCTICA ------------------------------------- //

/// ===================================================================================================================== ///

// ------------------------------------------------ SUB-MENÚ PACIENTE ------------------------------------------------ //
void subMenuPrintPaciente()
{
    portadaMenuAdmin();

    gotoxy(42,20);
    printf(WHITE " 1. AGREGAR PACIENTE \n");
    gotoxy(42,21);
    printf(" 2. DAR BAJA PACIENTE \n");
    gotoxy(42,22);
    printf(" 3. DAR ALTA PACIENTE \n");
    gotoxy(42,23);
    printf(" 4. EDITAR DATOS DEL PACIENTE \n");
    gotoxy(42,24);
    printf(" 5. VER LISTA DE PACIENTES \n");
    gotoxy(42,25);
    printf(" 6. VOLVER \n\n");
}

void subMenuPaciente(int opcion , char nombreArchPaciente[])
{
    do{
        system("cls");

        subMenuPrintPaciente();

        gotoxy(3,28);
        printf(" Ingresar opci%cn: " , 162);
        fflush(stdin);
        scanf("%i" , &opcion);

        switch(opcion)
        {
        case 1:
            subMenuPacienteCase1(nombreArchPaciente);
            system("pause");
            break;

        case 2:
            system("cls");
            subMenuPacienteCase2(nombreArchPaciente);
            system("pause");
            break;

        case 3:
            system("cls");
            subMenuPacienteCase3(nombreArchPaciente);
            system("pause");
            break;

        case 4:
            system("cls");
            subMenuPacienteCase4(nombreArchPaciente);
            break;

        case 5:
            system("cls");
            subMenuPacienteCase5(nombreArchPaciente);
            system("pause");
            break;

        case 6:
            break;

        default:
            printf("\n OPCI%cN NO V%cLIDA. \n\n" , 224 , 181);
            system("pause");
        }

    }while(opcion != 6);
}

// --------------------------------------- FUNCIONES DEL SUB-MENÚ PACIENTE --------------------------------------- //
void subMenuPacienteCase1(char nombreArchPaciente[])
{
    int totalRegistrosArchPacientes = 0;

    cargaEnArchivo(nombreArchPaciente);

    system("cls");

    printf(" PACIENTES CARGADOS: \n\n");
    mostrarArchPacientes(nombreArchPaciente);

    totalRegistrosArchPacientes = calculaCantRegistros(nombreArchPaciente , sizeof(paciente));

    printf(" Se han registrado un total de %d pacientes. \n\n" , totalRegistrosArchPacientes);
}

void subMenuPacienteCase2(char nombreArchPaciente[])
{
    char dniPac[9];
    int dniValido = 0;
    int existePaciente = 0;

    printf("\n Ingresar DNI del paciente: ");
    fflush(stdin);
    gets(dniPac);

    dniValido = verificaDni(dniPac);
    existePaciente = verificaExistenciaPaciente(nombreArchPaciente , dniPac);

    if(dniValido == 0 && existePaciente == 0){
        printf("\n El DNI ingresado no es v%clido o no se encuentra registrado. \n\n" , 160);
        system("pause");
    }else{
        existePaciente = 1;
        dniValido = 0;
    }

    darBajaPacienteArch(nombreArchPaciente , dniPac);
}

void subMenuPacienteCase3(char nombreArchPaciente[])
{
    char dniPac[9];
    int dniValido = 0;
    int existePaciente = 0;

    printf("\n Ingresar DNI del paciente: ");
    fflush(stdin);
    gets(dniPac);

    dniValido = verificaDni(dniPac);
    existePaciente = verificaExistenciaPaciente(nombreArchPaciente , dniPac);

    if(dniValido == 0 && existePaciente == 0){
        printf("\n El DNI ingresado no es v%clido o no se encuentra registrado. \n\n" , 160);
        system("pause");
    }else{
        existePaciente = 1;
        dniValido = 0;
    }

    darAltaPacienteArch(nombreArchPaciente , dniPac);
}

void subMenuPacienteCase4(char nombreArchPaciente[])
{
    char dniPac[9];
    int dniValido;
    int existePaciente = 0;

    printf("\n Ingresar DNI del paciente: ");
    fflush(stdin);
    gets(dniPac);

    dniValido = verificaDni(dniPac);
    existePaciente = verificaExistenciaPaciente(nombreArchPaciente , dniPac);

    if(dniValido == 0 && existePaciente == 0){
        printf("\n El DNI ingresado no es v%clido o no se encuentra registrado. \n\n" , 160);
        system("pause");
    }else{
        existePaciente = 1;
        dniValido = 0;
        modificaPaciente(nombreArchPaciente , dniPac);
    }
}

void subMenuPacienteCase5(char nombreArchPaciente[])
{
    nodoListaPaciente* listaPacietes = iniclistaPaciente();

    listaPacietes = pasarArchPacToListaPac(nombreArchPaciente , listaPacietes);

    printf("\n LISTA DE PACIENTES: \n\n");
    mostrarListaPaciente(listaPacietes);
}
// ------------------------------------- FIN FUNCIONES DEL SUB-MENÚ PACIENTE ------------------------------------- //

/// ===================================================================================================================== ///

// ------------------------------------------------ SUB-MENÚ INGRESO ------------------------------------------------ //
void subMenuPrintIngreso()
{
    portadaMenuAdmin();

    gotoxy(43,20);
    printf(WHITE "  1. AGREGAR INGRESO \n");
    gotoxy(43,21);
    printf("  2. DAR BAJA INGRESO \n");
    gotoxy(43,22);
    printf("  3. DAR ALTA INGRESO \n");
    gotoxy(43,23);
    printf("  4. EDITAR DATOS DEL INGRESO \n");
    gotoxy(43,24);
    printf("  5. VER PACIENTES E INGRESOS ASOCIADOS \n" , 181);
    gotoxy(43,25);
    printf("  6. VER LISTA DE INGRESOS DE UN PACIENTE \n");
    gotoxy(43,26);
    printf("  7. VER LISTA DE PR%cCTICAS DE UN PACIENTE \n" , 181);
    gotoxy(43,27);
    printf("  8. VER LISTA DE PR%cCTICAS COMPLETA \n" , 181);
    gotoxy(43,28);
    printf("  9. CARGAR RESULTADO DE UNA PR%cCTICA \n" , 181);
    gotoxy(43,29);
    printf(" 10. MODIFICAR RESULTADO DE UNA PR%cCTICA \n" , 181);
    gotoxy(43,30);
    printf(" 11. MODIFICAR UNA PR%cCTICA \n" , 181);
    gotoxy(43,31);
    printf(" 12. VOLVER \n\n");
}

void subMenuIngreso(int opcion , char nombreArchIngresos[] , nodoarbol* arbolPacientes , char nombreArchPxi[] , char nombreArchPac[] , char nombreArchPrac[])
{
    char dniPac[9];
    int dniValido = 0;
    int numIngreso = 0;
    int numPractica = 0;

    do{
        system("cls");

        subMenuPrintIngreso();

        gotoxy(3,34);
        printf(" Ingresar opci%cn: " , 162);
        fflush(stdin);
        scanf("%i" , &opcion);

        switch(opcion)
        {
        case 1:
            subMenuIngresoCase1(nombreArchIngresos , arbolPacientes);
            system("pause");
            break;

        case 2:
            subMenuIngresoCase2(nombreArchIngresos);
            system("pause");
           break;

        case 3:
            subMenuIngresoCase3(nombreArchIngresos);
            system("pause");
            break;

        case 4:
            system("cls");
            subMenuIngresoCase4(nombreArchIngresos);
            break;

        case 5:
            subMenuIngresoCase5(nombreArchPac , nombreArchIngresos  , arbolPacientes);
            system("pause");
            break;

        case 6:
            while(dniValido != 1){
                printf("\n Ingresar DNI: ");
                fflush(stdin);
                gets(dniPac);

                dniValido = verificaDni(dniPac);

                if(dniValido == 1){
                    subMenuIngresoCase6(nombreArchIngresos , dniPac);
                    system("pause");
                }else{
                    printf("\n El DNI ingresado no es v%clido o no se encuentra registrado. \n\n" , 160);
                }
            }
            dniValido = 0;
            break;

        case 7:
            while(dniValido != 1){
                printf("\n Ingresar DNI: ");
                fflush(stdin);
                gets(dniPac);

                dniValido = verificaDni(dniPac);

                if(dniValido == 1){
                    subMenuIngresoCase7(nombreArchPxi , dniPac);
                    system("pause");
                }else{
                    printf("\n El DNI ingresado no es v%clido o no se encuentra registrado. \n\n" , 160);
                }
            }
            dniValido = 0;
            break;

        case 8:
            subMenuIngresoCase8(nombreArchPxi);
            system("pause");
            break;

        case 9:
            cargarResultadoPxi(nombreArchPxi);
            system("pause");
            break;

        case 10:
            while(dniValido != 1){
                printf("\n Ingresar DNI: ");
                fflush(stdin);
                gets(dniPac);

                dniValido = verificaDni(dniPac);

                if(dniValido == 1){
                    system("cls");
                    printf("\n PR%cCTICAS DEL PACIENTE CON EL DNI: %s \n\n" , 181 , dniPac);
                    mostrarArchRegPracPorPaciente(nombreArchPxi , dniPac);
                    system("pause");
                    printf("\n Ingresar nro. de ingreso: ");
                    scanf("%d" , &numIngreso);
                    printf(" Ingresar nro. de pr%cctica: " , 160);
                    scanf("%d" , &numPractica);

                    modificarResultado(nombreArchPxi , dniPac , numIngreso , numPractica);
                    system("pause");
                }else{
                    printf("\n El DNI ingresado no es v%clido o no se encuentra registrado. \n\n" , 160);
                }
            }
            dniValido = 0;
            break;

        case 11:
            while(dniValido != 1){
                printf("\n Ingresar DNI: ");
                fflush(stdin);
                gets(dniPac);

                dniValido = verificaDni(dniPac);

                if(dniValido == 1){
                    modificarPxi(nombreArchPxi , dniPac , nombreArchPrac);
                    system("pause");
                }else{
                    printf("\n El DNI ingresado no es v%clido o no se encuentra registrado. \n\n" , 160);
                }
            }
            dniValido = 0;
            break;

        case 12:
            break;

        default:
            printf("\n OPCI%cN NO V%cLIDA. \n\n" , 224 , 181);
            system("pause");
        }

    }while(opcion != 12);
}

// --------------------------------------- FUNCIONES DEL SUB-MENÚ INGRESO --------------------------------------- //
void subMenuIngresoCase1(char nombreArchIngresos[] , nodoarbol* arbolPacientes)
{
    int totalRegistrosArchIngresos = 0;

    agregarIngreso(nombreArchIngresos , arbolPacientes);

    system("cls");

    printf(" INGRESOS CARGADOS: \n\n" , 181);
    mostrarArchIngresos(nombreArchIngresos);

    totalRegistrosArchIngresos = calculaCantRegistros(nombreArchIngresos , sizeof(ingresos));

    printf(" Se han registrado un total de %d ingresos. \n\n" , totalRegistrosArchIngresos);

}

void subMenuIngresoCase2(char nombreArchIngresos[])
{
    int nroIngreso = 0;

    printf(" Ingresar nro. de ingreso: ");
    scanf("%d" , &nroIngreso);

    darBajaIngresoArch(nombreArchIngresos , nroIngreso);
}

void subMenuIngresoCase3(char nombreArchIngresos[])
{
    int nroIngreso = 0;

    printf(" Ingresar nro. de ingreso: ");
    scanf("%d" , &nroIngreso);

    darAltaIngresoArch(nombreArchIngresos , nroIngreso);
}

void subMenuIngresoCase4(char nombreArchIngresos[])
{
    int nroIngresoMod = 0;

    printf("\n INGRESOS REGISTRADOS: \n\n");
    mostrarArchIngresos(nombreArchIngresos);

    printf("\n Ingresar nro. de ingreso a modificar: ");
    scanf("%d" , &nroIngresoMod);

    modificarIngresoArch(nombreArchIngresos , nroIngresoMod);
}

void subMenuIngresoCase5(char nombreArchPac[] , char nombreArchIngresos[] , nodoarbol* arbolPacientes)
{
    arbolPacientes = cargaAdlPacientes(nombreArchPac , arbolPacientes , nombreArchIngresos);

    if(arbolPacientes != NULL){
        system("cls");
        printf("\n LISTA DE PACIENTES CON SUS INGRESOS Y PR%cCTICAS: \n\n" , 181);
        mostrarAdlPacientes(arbolPacientes);
    }else{
        printf(" NO HAY DATOS CARGADOS. \n\n");
    }
}

void subMenuIngresoCase6(char nombreArchIngresos[] , char dniPac[])
{
    system("cls");
    printf("\n INGRESOS DEL PACIENTE CON EL DNI: %s \n\n" , dniPac);
    mostrarArchIngresosPaciente(nombreArchIngresos , dniPac);
}

void subMenuIngresoCase7(char nombreArchPxi[] , char dniPac[])
{
    system("cls");
    printf("\n PR%cCTICAS DEL PACIENTE CON EL DNI: %s \n\n" , 181 , dniPac);
    mostrarArchRegPracPorPaciente(nombreArchPxi , dniPac);
}

void subMenuIngresoCase8(char nombreArchPxi[])
{
    system("cls");
    printf("\n LISTA DE PR%cCTICAS \n\n" , 181);
    mostrarArchRegPracCompleta(nombreArchPxi);
}
// ------------------------------------- FIN FUNCIONES DEL SUB-MENÚ INGRESO ------------------------------------- //

/// ===================================================================================================================== ///

// --------------------------------------------- SUB-MENÚ CONSULTAS --------------------------------------------- //
void subMenuPrintConsultas()
{
    portadaMenuAdmin();

    gotoxy(40,20);
    printf(WHITE " 1. BUSCAR PACIENTE POR DNI \n");
    gotoxy(40,21);
    printf(" 2. BUSCAR PACIENTES POR NOMBRE \n");
    gotoxy(40,22);
    printf(" 3. BUSCAR INGRESO DE UN PACIENTE POR DNI \n");
    gotoxy(40,23);
    printf(" 4. BUSCAR INGRESOS POR RANGO DE FECHA \n");
    gotoxy(40,24);
    printf(" 5. BUSCAR PR%cCTICA DE LABORATORIO \n" , 181);
    gotoxy(40,25);
    printf(" 6. VOLVER \n\n");
}

void subMenuConsulas(int opcion , nodoarbol* arbol , char nombreArchPac[] , nodoListaIngresos* listaIng , char nombreArchPractica[])
{
    char dniPac[9];
    int dniValido;
    char apeYnombrePaciente[30];
    int nombreYapeValido;
    char fechaDesde[11];
    char fechaHasta[11];
    int fechaIngresoDesdeValida;
    int fechaIngresoHastaValida;
    char nombrePractica[50];

    do{
        system("cls");

        subMenuPrintConsultas();

        gotoxy(3,28);
        printf(" Ingresar opci%cn: " , 162);
        fflush(stdin);
        scanf("%i" , &opcion);

        switch(opcion)
        {
        case 1:
            while(dniValido != 1){
                system("cls");

                printf("\n Ingresar DNI: ");
                fflush(stdin);
                gets(dniPac);

                dniValido = verificaDni(dniPac);

                if(dniValido == 1){
                    system("cls");
                    subMenuConsultasCase1(arbol , dniPac);
                    system("pause");
                }else{
                    printf("\n El DNI ingresado no es v%clido o no se encuentra registrado. \n\n" , 160);
                }
            }
            dniValido = 0; //reinicio la variable para reutilizarla
            break;

        case 2:
            while(nombreYapeValido != 1){
                system("cls");

                printf("\n Ingresar apellido o nombre del paciente: ");
                fflush(stdin);
                gets(apeYnombrePaciente);

                nombreYapeValido = verificaNombre(apeYnombrePaciente);

                if(nombreYapeValido == 1){
                    system("cls");
                    printf("\n PACIENTES CON APELLIDO O NOMBRE O QUE COMIENCEN CON: %s \n\n" , apeYnombrePaciente);
                    subMenuConsultasCase2(nombreArchPac , apeYnombrePaciente);
                    system("pause");
                }else{
                    printf("\n El nombre ingresado no existe o es inv%clido. \n\n" , 160);
                    system("pause");
                }
            }
            nombreYapeValido = 0; //reinicio la variable para reutilizarla
            break;

        case 3:
            while(dniValido != 1){
                system("cls");

                printf("\n Ingresar DNI: ");
                fflush(stdin);
                gets(dniPac);

                dniValido = verificaDni(dniPac);

                if(dniValido == 1){
                    system("cls");
                    subMenuConsultasCase3(listaIng , dniPac);
                    system("pause");
                }else{
                    printf("\n El DNI ingresado no es v%clido o no se encuentra registrado. \n\n" , 160);
                    system("pause");
                }
            }
            dniValido = 0; //reinicio la variable para reutilizarla
            break;

        case 4:
            while((fechaIngresoDesdeValida != 1) && (fechaIngresoHastaValida != 1)){
                system("cls");

                printf("\n Ingresar rango de fecha (mismo formato - dd/mm/aaaa ; d/m/aa ; dd/mm/aa): \n\n");
                printf(" Fecha desde: ");
                fflush(stdin);
                gets(fechaDesde);

                printf(" Fecha hasta: ");
                fflush(stdin);
                gets(fechaHasta);

                fechaIngresoDesdeValida = validarFecha(fechaDesde);
                fechaIngresoHastaValida = validarFecha(fechaHasta);

                if(fechaIngresoDesdeValida == 1 && fechaIngresoHastaValida == 1){
                    system("cls");
                    printf("\n INGRESOS DE PACIENTES CON FECHA DESDE %s HASTA %s \n\n" , fechaDesde , fechaHasta);
                    subMenuConsultasCase4(listaIng , fechaDesde , fechaHasta);
                    system("pause");
                }else{
                    printf(" La/s fecha/s ingresada/s es/son inv%clida/s. \n\n" , 160);
                    system("pause");
                }
            }
            //reinicio ambas variables
            fechaIngresoDesdeValida = 0;
            fechaIngresoHastaValida = 0;
            break;

        case 5:
            system("cls");
            printf("\n Ingresar nombre de la pr%cctica de lab: " , 160);
            fflush(stdin);
            gets(nombrePractica);

            system("cls");
            printf("\n PR%cCTICAS DE LABORATORIOS CON EL NOMBRE O QUE COMIENZA CON: %s \n\n" , 181 , nombrePractica);
            subMenuConsultasCase5(nombreArchPractica , nombrePractica);
            system("pause");
            break;

        case 6:
            break;

        default:
            printf("\n OPCI%cN NO V%cLIDA. \n\n" , 224 , 181);
            system("pause");
        }

    }while(opcion != 6);
}

// -------------------------------------- FUNCIONES DEL SUB-MENÚ CONSULTAS -------------------------------------- //
void subMenuConsultasCase1(nodoarbol* arbol , char dniPac[])
{
    nodoarbol* pacienteEncontrado = buscarPacienteArbol(arbol , dniPac);

    if(pacienteEncontrado != NULL){
        system("cls");
        printf("\n El paciente con el DNI %s pertenece a: \n\n" , dniPac);
        mostrarPaciente(pacienteEncontrado->dato);
    }else{
        printf("\n El DNI ingresado no es v%clido o no se encuentra registrado. \n\n" , 160);
    }
}

void subMenuConsultasCase2(char nombreArchPacientes[] , char apeyNombreA[])
{
    nodoListaPaciente* listaPacientes = iniclistaPaciente();
    listaPacientes = pasarArchPacToListaPac(nombreArchPacientes , listaPacientes);
    nodoListaPaciente* seg = listaPacientes;
    int rtaComparacionChars = 0;

    if(seg != NULL){
        while(seg != NULL){
            rtaComparacionChars = strncasecmp(seg->datosPac.apellidoYnombre , apeyNombreA , strlen(apeyNombreA));

            if(rtaComparacionChars == 0 || strcmpi(apeyNombreA , seg->datosPac.apellidoYnombre) == 0){ //la función strncasecmp no hace diferencia entre mayusculas y minúsuclas
                mostrarPaciente(seg->datosPac);
            }

            seg = seg->siguiente;
        }
    }
}

void subMenuConsultasCase3(nodoListaIngresos* listaIng , char dniPac[])
{
    ingresos ingresoEncontrado = buscarIngresoPorDni(listaIng , dniPac);

    if(strcmp(ingresoEncontrado.dniPaciente , dniPac) == 0){
        system("cls");
        printf("\n El ingreso con el DNI %s corresponde a: \n\n" , dniPac);
        mostrarUnIngreso(ingresoEncontrado);
    }else{
        printf("\n El DNI ingresado no es v%clido o no se encuentra registrado. \n\n" , 160);
    }
}

void subMenuConsultasCase4(nodoListaIngresos* listaIng, char fechaDesde[], char fechaHasta[])
{
    nodoListaIngresos* seg = listaIng;
    Fecha fechaDesdeStruct, fechaHastaStruct;
    obtenerFechaDesdeCadena(fechaDesde, &fechaDesdeStruct);
    obtenerFechaDesdeCadena(fechaHasta, &fechaHastaStruct);

    if (seg != NULL) {
        while (seg != NULL) {
            Fecha fechaIngresoStruct;
            obtenerFechaDesdeCadena(seg->datosIngresoPac.fechaIngreso, &fechaIngresoStruct);

            if (compararFechas(fechaIngresoStruct, fechaDesdeStruct) >= 0 &&compararFechas(fechaIngresoStruct, fechaHastaStruct) <= 0) {
                mostrarUnIngreso(seg->datosIngresoPac);
            }
            seg = seg->siguiente;
        }
    }
}

void subMenuConsultasCase5(char nombreArchPrac[] , char nombrePrac[])
{
    nodoListaPracticas* listaPracticas = inicListaPracticas();
    listaPracticas = pasarArchPracToListaPrac(nombreArchPrac , listaPracticas);
    nodoListaPracticas* seg = listaPracticas;
    int rtaComparacionChars = 0;

    if(seg != NULL){
        while(seg != NULL){
            rtaComparacionChars = strncasecmp(nombrePrac , seg->datosPracticas.nombrePractica , strlen(nombrePrac)); //la función strncasecmp no hace diferencia entre mayusculas y minúsuclas

            if((rtaComparacionChars == 0) || strcmpi(nombrePrac , seg->datosPracticas.nombrePractica) == 0){
                mostrarUnaPractica(seg->datosPracticas);
            }

            seg = seg->siguiente;
        }
    }else{
        printf("\n NO hay pr%ccticas cargadas o el nombre ingresado es incorrecto. \n\n" , 160);
    }
}
// ------------------------------------- FIN FUNCIONES DEL SUB-MENÚ CONSULTAS ------------------------------------- //

///FUNCIONES EXTRAS
void obtenerFechaDesdeCadena(char fechaStr[], Fecha *fecha) {
    sscanf(fechaStr, "%d/%d/%d", &fecha->dia, &fecha->mes, &fecha->anio);
}

int compararFechas(Fecha fecha1, Fecha fecha2) {
    struct tm tm1 = { .tm_year = fecha1.anio - 1900, .tm_mon = fecha1.mes - 1, .tm_mday = fecha1.dia };
    struct tm tm2 = { .tm_year = fecha2.anio - 1900, .tm_mon = fecha2.mes - 1, .tm_mday = fecha2.dia };

    time_t t1 = mktime(&tm1);
    time_t t2 = mktime(&tm2);

    if (t1 == -1 || t2 == -1) {
        // Error en la conversión
        return 0;
    }

    if (t1 < t2) {
        return -1;
    } else if (t1 > t2) {
        return 1;
    } else {
        return 0; // Fechas iguales
    }
}
