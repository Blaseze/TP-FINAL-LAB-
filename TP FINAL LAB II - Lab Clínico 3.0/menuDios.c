#include "menuDios.h"

///FUNCIONES DE DISEÑO DEL MENÚ ADMIN
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

///FUNCIONES DEL MENU ADMIN
void menuPrintAdmin()
{
    int opcion = 0;

    portadaMenuAdmin();

    gotoxy(46,20);
    printf(WHITE " 1. EMPLEADO \n");
    gotoxy(46,21);
    printf(" 2. PR%cCTICA \n" , 181);
    gotoxy(46,22);
    printf(" 3. PACIENTE \n");
    gotoxy(46,23);
    printf(" 4. INGRESO \n");
    gotoxy(46,24);
    printf(" 5. RESUTADO DE PR%cCTICA \n" , 181);
    gotoxy(46,25);
    printf(" 6. CONSULTA \n");
    gotoxy(46,26);
    printf(" 0. SALIR \n\n");

}

void menuAdmin()
{
    int opcion = 0;
    char archEmpleados[] = {"empleadosLab.dat"};
    char archPracticas[] = {"practicasLab.dat"};
    char archPacientes[] = {"pacientes.dat"};
    char archIngresos[] = {"ingresosPacientes.dat"};
    char archPxi[] = {"pracXing.dat"};
    nodoarbol* arbol=inicArbol();
    arbol=pasarArchPacienteToArbol(archPacientes,arbol);

    nodoListaPracticas* listaPracticas = inicListaPracticas();
    nodoListaIngresos* listaIngresos = inicListaIngresos();

    do{
        menuPrintAdmin();

        gotoxy(3,30);
        printf(" Ingresar opci%cn: " , 162);
        scanf("%d", &opcion);

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
            subMenuIngreso(opcion , archIngresos , arbol);
            system("cls");
            break;

        case 5:
            listaPracticas = pasarArchPracToListaPrac(archPracticas , listaPracticas);
            listaIngresos = pasarArchToListaIng(archIngresos , listaIngresos);
            subMenuResultadoPractica(opcion , archPxi , listaPracticas , listaIngresos);
            break;

        case 0:
            break;

        default:
            printf("\n OPCI%cN NO V%cLIDA. \n\n" , 224 , 181);
        }

    }while(opcion != 0);

}

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
    printf(" 0. VOLVER \n\n");
}

///SUB MENÚ EMPLEADO
void subMenuEmpleado(int opcion , char nombreArchEmpleados[])
{

    do{
        system("cls");

        subMenuPrintEmpleado();

        gotoxy(3,29);
        printf(" Ingresar opci%cn: " , 162);
        scanf("%d" , &opcion);

        switch(opcion)
        {
        case 1:
            resSubMenuEmpleadoCase1(nombreArchEmpleados);
            system("pause");
            break;

        case 2:
            resSubMenuEmpleadoCase2(nombreArchEmpleados);
            system("pause");
            break;

        case 3:
            resSubMenuEmpleadoCase3(nombreArchEmpleados);
            system("pause");
            break;

        case 4:
            system("cls");
            resSubMenuEmpleadoCase4(nombreArchEmpleados);
            system("pause");
            break;

        case 5:
            system("cls");
            resSubMenuEmpleadoCase5(nombreArchEmpleados);
            system("pause");
            break;

        case 6:
            system("cls");
            resSubMenuEmpleadoCase6(nombreArchEmpleados);
            system("pause");
            break;

        case 0:
            break;

        default:
            printf("\n OPCI%cN NO V%cLIDA. \n\n" , 224 , 181);
            system("pause");
            break;
        }

    }while(opcion != 0);
}

///FUNCIONES DEL SWITCH SUB MENÚ EMPLEADO
void resSubMenuEmpleadoCase1(char nombreArchEmpleados[])
{
    empleados_laboratorio nuevoEmpleado;
    int totalRegistrosArchEmple = 0;

    agregarEmpleados(nombreArchEmpleados , nuevoEmpleado);

    system("cls");

    printf(" EMPLEADOS CARGADOS: \n\n");
    mostrarArchEmpleados(nombreArchEmpleados);

    totalRegistrosArchEmple = calculaCantRegistros(nombreArchEmpleados , sizeof(empleados_laboratorio));

    printf(" Se han registrado un total de %d empleados. \n\n" , totalRegistrosArchEmple);
}

void resSubMenuEmpleadoCase2(char nombreArchEmpleados[])
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

void resSubMenuEmpleadoCase3(char nombreArchEmpleados[])
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

void resSubMenuEmpleadoCase4(char nombreArchEmpleados[])
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

void resSubMenuEmpleadoCase5(char nombreArchEmpleados[])
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

void resSubMenuEmpleadoCase6(char nombreArchEmpleados[])
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
///FIN FUNCIONES DEL SWITCH SUB MENÚ EMPLEADO

void subMenuPrintPractica()
{
    portadaMenuAdmin();

    gotoxy(40,20);
    printf(WHITE " 1. AGREGAR PR%cCTICA \n" , 181);
    gotoxy(40,21);
    printf(" 2. DAR BAJA PR%cCTICA \n" , 181);
    gotoxy(40,22);
    printf(" 3. DAR ALTA PR%cCTICA \n" , 181);
    gotoxy(40,23);
    printf(" 4. EDITAR DATOS DE LA PR%cCTICA \n" , 181);
    gotoxy(40,24);
    printf(" 5. VER LISTA DE PR%cCTICAS \n" , 181);
    gotoxy(40,25);
    printf(" 0. VOLVER \n\n");
}

///FUNCIONES DEL SWITCH SUB MENÚ PRACTICA
void subMenuPractica(int opcion , char nombreArchPracticas[])
{
    do{
        system("cls");

        subMenuPrintPractica();

        gotoxy(3,29);
        printf(" Ingresar opci%cn: " , 162);
        scanf("%d" , &opcion);

        switch(opcion)
        {
        case 1:
            resSubMenuPracticaCase1(nombreArchPracticas);
            system("pause");
            break;

        case 2:
            resSubMenuPracticaCase2(nombreArchPracticas);
            system("pause");
            break;

        case 3:
            resSubMenuPracticaCase3(nombreArchPracticas);
            system("pause");
            break;

        case 4:
            resSubMenuPracticaCase4(nombreArchPracticas);
            system("pause");
            break;
        case 5:
            system("cls");
            resSubMenuPracticaCase5(nombreArchPracticas);
            system("pause");
            break;

        case 0:
            break;

        default:
            printf("\n OPCI%cN NO V%cLIDA. \n\n" , 224 , 181);
            system("pause");
            break;
        }

    }while(opcion != 0);
}

void resSubMenuPracticaCase1(char nombreArchPracticas[])
{
    int totalRegistrosArchPrac = 0;

    cargarArchPracticas(nombreArchPracticas);

    system("cls");

    printf(" PR%cCTICAS CARGADAS: \n\n" , 181);
    mostrarArchPracticas(nombreArchPracticas);

    totalRegistrosArchPrac = calculaCantRegistros(nombreArchPracticas , sizeof(practicas));

    printf(" Se han registrado un total de %d pr%ccticas. \n\n" , totalRegistrosArchPrac , 160);
}

void resSubMenuPracticaCase2(char nombreArchPracticas[])
{
    int nroPractica = 0;

    printf("\n Ingresar nro. de pr%cctica:" , 160);
    scanf("%d" , &nroPractica);

    darBajaPrac(nombreArchPracticas , nroPractica);
}

void resSubMenuPracticaCase3(char nombreArchPracticas[])
{
    int nroPractica = 0;

    printf("\n Ingresar nro. de pr%cctica:" , 160);
    scanf("%d" , &nroPractica);

    darAltaPrac(nombreArchPracticas , nroPractica);
}

void resSubMenuPracticaCase4(char nombreArchPracticas[])
{
    int nroPracticaAMod = 0;

    printf("\n Ingresar nro. de pr%cctica: " , 160);
    scanf("%d" , &nroPracticaAMod);

    modificarPractica(nombreArchPracticas , nroPracticaAMod);
}

void resSubMenuPracticaCase5(char nombreArchPracticas[])
{
    nodoListaPracticas* listaPracticas = inicListaPracticas();

    listaPracticas = pasarArchPracToListaPrac(nombreArchPracticas , listaPracticas);

    printf("\n LISTA DE PR%cCTICAS DISPONIBLES: \n\n" , 181);
    mostrarListaPractica(listaPracticas);
}
///FIN FUNCIONES DEL SWITCH SUB MENÚ PRACTICA

void subMenuPrintPaciente()
{
    portadaMenuAdmin();

    gotoxy(40,20);
    printf(WHITE " 1. AGREGAR PACIENTE \n");
    gotoxy(40,21);
    printf(" 2. DAR BAJA PACIENTE \n");
    gotoxy(40,22);
    printf(" 3. DAR ALTA PACIENTE \n");
    gotoxy(40,23);
    printf(" 4. EDITAR DATOS DEL PACIENTE \n");
    gotoxy(40,24);
    printf(" 5. VER LISTA DE PACIENTES \n");
    gotoxy(40,25);
    printf(" 0. VOLVER \n\n");
}

///FUNCIONES DEL SWITCH SUB MENÚ PACIENTE
void subMenuPaciente(int opcion , char nombreArchPaciente[])
{
    do{
        system("cls");

        subMenuPrintPaciente();

        gotoxy(3,28);
        printf(" Ingresar opci%cn: " , 162);
        scanf("%d" , &opcion);

        switch(opcion)
        {
        case 1:
            resSubMenuPacienteCase1(nombreArchPaciente);
            system("pause");
            break;

        case 2:
            system("cls");
            resSubMenuPacienteCase2(nombreArchPaciente);
            system("pause");
            break;

        case 3:
            system("cls");
            resSubMenuPacienteCase3(nombreArchPaciente);
            system("pause");
            break;

        case 4:
            system("cls");
            resSubMenuPacienteCase4(nombreArchPaciente);
            break;

        case 5:
            system("cls");
            resSubMenuPacienteCase5(nombreArchPaciente);
            system("pause");
            break;

        case 0:
            break;

        default:
            printf("\n OPCI%cN NO V%cLIDA. \n\n" , 224 , 181);
            system("pause");
            break;
        }

    }while(opcion != 0);
}

void resSubMenuPacienteCase1(char nombreArchPaciente[])
{
    int totalRegistrosArchPacientes = 0;

    cargaEnArchivo(nombreArchPaciente);

    system("cls");

    printf(" PACIENTES CARGADOS: \n\n" , 181);
    mostrarArchPacientes(nombreArchPaciente);

    totalRegistrosArchPacientes = calculaCantRegistros(nombreArchPaciente , sizeof(paciente));

    printf(" Se han registrado un total de %d pacientes. \n\n" , totalRegistrosArchPacientes);
}

void resSubMenuPacienteCase2(char nombreArchPaciente[])
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

void resSubMenuPacienteCase3(char nombreArchPaciente[])
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

void resSubMenuPacienteCase4(char nombreArchPaciente[])
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
        modificaPaciente(nombreArchPaciente , dniPac);
    }
}

void resSubMenuPacienteCase5(char nombreArchPaciente[])
{
    nodoListaPaciente* listaPacietes = iniclistaPaciente();

    listaPacietes = pasarArchPacToListaPac(nombreArchPaciente , listaPacietes);

    printf("\n LISTA DE PACIENTES: \n\n");
    mostrarListaPaciente(listaPacietes);

}
/// FIN FUNCIONES DEL SWITCH SUB MENÚ PACIENTE

void subMenuPrintIngreso()
{
    portadaMenuAdmin();

    gotoxy(40,20);
    printf(WHITE " 1. AGREGAR INGRESO \n");
    gotoxy(40,21);
    printf(" 2. DAR BAJA INGRESO \n");
    gotoxy(40,22);
    printf(" 3. DAR ALTA INGRESO \n");
    gotoxy(40,23);
    printf(" 4. EDITAR DATOS DEL INGRESO \n");
    gotoxy(40,24);
    printf(" 5. VER LISTA DE INGRESOS \n");
    gotoxy(40,25);
    printf(" 0. VOLVER \n\n");
}

/// FUNCIONES DEL SWITCH SUB MENÚ INGRESO
void subMenuIngreso(int opcion , char nombreArchIngresos[] , nodoarbol* arbolPacientes)
{
    char dniPac[9];
    int dniValido = 0;

    do{
        system("cls");

        subMenuPrintIngreso();

        gotoxy(3,28);
        printf(" Ingresar opci%cn: " , 162);
        scanf("%d" , &opcion);

        switch(opcion)
        {
        case 1:
            resSubMenuIngresoCase1(nombreArchIngresos , arbolPacientes);
            system("pause");
            break;

        case 2:
            resSubMenuIngresoCase2(nombreArchIngresos);
            system("pause");
           break;

        case 3:
            resSubMenuIngresoCase3(nombreArchIngresos);
            system("pause");
            break;

        case 4:
            resSubMenuIngresoCase4(nombreArchIngresos);
            system("cls");
            break;

        case 5:

            while(dniValido != 1){
                printf("\n Ingresar DNI: ");
                fflush(stdin);
                gets(dniPac);

                dniValido = verificaDni(dniPac);

                if(dniValido == 1){
                    resSubMenuIngresoCase5(nombreArchIngresos , dniPac);
                    system("pause");
                }else{
                    printf("\n El DNI ingresado no es v%clido o no se encuentra registrado. \n\n" , 160);
                }
            }

            break;

        default:
            printf("\n OPCI%cN NO V%cLIDA. \n\n" , 224 , 181);
            system("pause");
        }

    }while(opcion != 0);
}

void resSubMenuIngresoCase1(char nombreArchIngresos[] , nodoarbol* arbolPacientes)
{
    int totalRegistrosArchIngresos = 0;

    agregarIngreso(nombreArchIngresos , arbolPacientes);

    system("cls");

    printf(" INGRESOS CARGADOS: \n\n" , 181);
    mostrarArchIngresos(nombreArchIngresos);

    totalRegistrosArchIngresos = calculaCantRegistros(nombreArchIngresos , sizeof(ingresos));

    printf(" Se han registrado un total de %d ingresos. \n\n" , totalRegistrosArchIngresos);

}

void resSubMenuIngresoCase2(char nombreArchIngresos[])
{
    int nroIngreso = 0;

    printf(" Ingresar nro. de ingreso: ");
    scanf("%d" , &nroIngreso);

    darBajaIngresoArch(nombreArchIngresos , nroIngreso);
}

void resSubMenuIngresoCase3(char nombreArchIngresos[])
{
    int nroIngreso = 0;

    printf(" Ingresar nro. de ingreso: ");
    scanf("%d" , &nroIngreso);

    darAltaIngresoArch(nombreArchIngresos , nroIngreso);
}

void resSubMenuIngresoCase4(char nombreArchIngresos[])
{
    int nroIngresoMod = 0;

    mostrarArchIngresos(nombreArchIngresos);

    printf("\n Ingresar nro. de ingreso a modificar: ");
    scanf("%d" , &nroIngresoMod);

    modificarIngresoArch(nombreArchIngresos , nroIngresoMod);
}

void resSubMenuIngresoCase5(char nombreArchIngresos[] , char dniPac[])
{
    mostrarArchIngresosPaciente(nombreArchIngresos , dniPac);
}
/// FIN FUNCIONES DEL SWITCH SUB MENÚ PACIENTE

void subMenuPrintResultadoDePractica()
{
    portadaMenuAdmin();

    gotoxy(40,20);
    printf(WHITE " 1. AGREGAR RESULTADO \n");
    gotoxy(40,21);
    printf(" 2. EDITAR NRO. PR%cCTICA / RESULTADO \n" , 181);
    gotoxy(40,22);
    printf(" 3. VER LISA DE RESULTADOS \n\n");
    gotoxy(40,23);
    printf(" 0. VOLVER \n\n");
}

///FUNCIONES DEL SWITCH SUB MENÚ RESULTADO PRÁCTICA
void subMenuResultadoPractica(int opcion , char nombreArchPxi[] , nodoListaPracticas* listPrac , nodoListaIngresos* listIng)
{

    do{
        system("cls");

        subMenuPrintResultadoDePractica();

        gotoxy(3,28);
        printf(" Ingresar opci%cn: " , 162);
        scanf("%d" , &opcion);

        switch(opcion)
        {
        case 1:
            resSubMenuResultadoPracticaCase1(nombreArchPxi , listPrac , listIng);
            system("pause");
            break;

        case 2:
            //resSubMenuResultadoPracticaCase2(nombreArchPxi , listPrac , listIng);
            //system("pause");
            break;

        case 3:
            resSubMenuResultadoPracticaCase3(nombreArchPxi);
            system("pause");
            break;

        case 0:
            break;

        default:
            printf("\n OPCI%cN NO V%cLIDA. \n\n" , 224 , 181);
            system("pause");
            break;
        }

    }while(opcion != 0);
}

void resSubMenuResultadoPracticaCase1(char nombreArchPxi[] , nodoListaIngresos* listaIng , nodoListaPracticas* listaPrac)
{
    int totalRegistrosArchPxi = 0;
    regPracticasPacientes auxReg;

    agregarPracticasPorIngreso(nombreArchPxi , listaIng , listaPrac);

    system("cls");

    printf(" RESULTADOS CARGADOS: \n\n");
    mostrarArchPracticasPorIngreso(nombreArchPxi);

    totalRegistrosArchPxi = calculaCantRegistros(nombreArchPxi , sizeof(practicaXingreso));

    printf(" Se han registrado un total de %d resultados. \n\n" , totalRegistrosArchPxi);
}

//void resSubMenuResultadoPracticaCase2(char nombreArchPxi[] , nodoListaPracticas* listaPrac , nodoListaIngresos* listaIng)
//{
//    modificarPxi(nombreArchPxi , listaIng , listaPrac);
//}

void resSubMenuResultadoPracticaCase3(char nombreArchPxi[])
{
    system("cls");

    printf("\n RESULTADOS CARGADOS: \n\n");
    mostrarArchPracticasPorIngreso(nombreArchPxi);
}
///FIN FUNCIONES DEL SWITCH SUB MENÚ RESULTADO PRÁCTICA

void subMenuPrintConsulta()
{
    portadaMenuAdmin();

    gotoxy(40,20);
    printf(WHITE " 1. BUSCAR EMPLEADO \n");
    gotoxy(40,21);
    printf(" 2. BUSCAR PR%cCTICA \n" , 181);
    gotoxy(40,22);
    printf(" 3. BUSCAR PACIENTE \n");
    gotoxy(40,23);
    printf(" 4. BUSCAR INGRESO \n");
    gotoxy(40,24);
    printf(" 5. BUSCAR RESULTADO DE UNA PR%cCTICA \n" , 181);
    gotoxy(40,25);
    printf(" 0. VOLVER \n\n");
}

///FUNCIONES DEL SWITCH SUB MENÚ RESULTADO CONSULTA
void subMenuConsulta(int opcion , nodoListaEmpleados* listaEmpleados , nodoarbol* arbolPacientes , nodoListaPracticas* listaPrac ,nodoListaIngresos* listaIng , nodoListaPracXingreso* listaPxi)
{
    char dniEmpleado[9];
    char dniPaciente[9];
    nodoListaEmpleados* empleadoEncontrado;
    int nroPracAbuscar = 0;
    nodoListaPracticas* practicaEncontrada;

    do{
        system("cls");

        gotoxy(3,28);
        printf(" Ingresar opci%cn: " , 162);
        scanf("%d" , &opcion);

        switch(opcion)
        {
        case 1:
            printf(" Ingresar DNI del empleado: ");
            fflush(stdin);
            gets(dniEmpleado);

            empleadoEncontrado = buscarEmpleadoLista(listaEmpleados , dniEmpleado);

            if(empleadoEncontrado != NULL){
                system("cls");
                printf("\n El DNI %s pertenece a: \n\n" , dniEmpleado);
                mostrarUnEmpleado(empleadoEncontrado->dato);
            }else{
                printf(" El DNI ingresado es incorrecto o no se encuentra registrado. \n\n");
            }
            break;

        case 2:
            printf(" Ingresar nro. de pr%cctica: " , 160);
            gets(dniPaciente);

            practicaEncontrada = buscarPractica(listaPrac , nroPracAbuscar);

            if(practicaEncontrada != NULL){
                system("cls");
                printf("\n El nro. de pr%cctica pertenece a: \n\n" , 160 , nroPracAbuscar);
                mostrarUnaPractica(practicaEncontrada->datosPracticas);
            }else{
                printf(" El nro. de pr%cctica es incorrecto o no se encuentra registrado. \n\n" , 160);
            }
        }
    }while(opcion==1 || opcion==2);
}

