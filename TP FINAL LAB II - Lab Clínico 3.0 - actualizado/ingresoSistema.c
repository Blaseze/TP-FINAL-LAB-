#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "paciente.h"
#include "empleado.h"
#include "ingresoSistema.h"
#include "menuDios.h"

UsuarioPaciente ingresarUsuarioPaciente()
{
    UsuarioPaciente usuarioP;
    UsuarioPaciente aux;
    int i = 3;
    FILE *archi = fopen("UsuariosPacientes.dat" , "rb");
    int flag = 0;

    if(archi)
    {
        while(flag == 0 && i >=0 && i<=3)
        {
            system("cls");

            printf("\n INICIO DE SESI%cN PACIENTE\n ", 224);
            printf(" -------------------------\n ");
            printf(" USUARIO: ");
            fflush(stdin);
            gets(aux.usuarioPaciente);

            printf(" CONTRASE%cA: ", 165);
            fflush(stdin);
            leerPassword(aux.contrasenia);
            printf("\n------------------------- \n\n");

            while(fread(&usuarioP,sizeof(UsuarioPaciente),1,archi) > 0)
            {
                if((strcmp(aux.usuarioPaciente,usuarioP.usuarioPaciente) == 0) && (strcmp(aux.contrasenia,usuarioP.contrasenia) == 0))
                {
                    flag = 1;
                    break;
                }
            }

            if (flag==0)
            {
                system("cls");
                printf(" LA CONTRASE%cA O EL USUARIO ES INV%cLIDO, INTENTE DE NUEVO...\n", 165, 181);
                printf(" TE QUEDAN %i INTENTOS \n\n",i);
                flag = 0;
                i--;
                rewind(archi);
                system("pause");
            }
        }

        fclose(archi);
    }

    if (flag == 1)
    {
        return aux;
    }
    else
    {
        printf("\n Inicio de sesi%cn fallido. Cerrando el programa...\n\n", 162);
        exit(EXIT_FAILURE);
    }
}

UsuarioEmpleado ingresarUsuarioEmpleado()
{
    UsuarioEmpleado aux;
    UsuarioEmpleado usuarioE;
    int i = 3;
    FILE *archi = fopen("UsuariosEmpleados.dat", "rb");
    int flag = 0;

    if(archi)
    {
        while(i > 0 && flag == 0)
        {
            rewind(archi);
            flag = 0;
            system("cls");

            printf("\n INICIO DE SESI%cN EMPLEADO \n ", 224);
            printf("-------------------------\n");
            printf(" USUARIO: ");
            fflush(stdin);
            gets(aux.usuarioEmpleado);

            printf("CONTRASE%cA: " , 165);
            fflush(stdin);
            leerPassword(aux.contraEmpleado);
            printf("\n-------------------------\n\n");

            while(fread(&usuarioE, sizeof(UsuarioEmpleado), 1, archi) > 0)
            {
                if ((strcmp(aux.usuarioEmpleado, usuarioE.usuarioEmpleado) == 0) && (strcmp(aux.contraEmpleado, usuarioE.contraEmpleado) == 0))
                {
                    flag = 1;
                    aux=usuarioE;
                }
            }

            if (flag == 0)
            {
                system("cls");
                printf(" LA CONTRASE%cA O EL USUARIO ES INV%cLIDO, INTENTE DE NUEVO...\n\n", 165, 181);
                printf(" TE QUEDAN %i INTENTOS \n\n", (i-1));
                i--;
                rewind(archi);
                system("pause");
            }
        }
        fclose(archi);
    }

    if (flag == 1)
    {
        return aux;
    }
    else
    {
        printf("\n Inicio de sesi%cn fallido. Cerrando el programa...\n\n", 162);
        exit(EXIT_FAILURE);
    }
}

void menuPaciente()
{

    UsuarioPaciente usuario=ingresarUsuarioPaciente();
    int eleccion=0;

    do
    {
        system("cls");

        if(usuario.nivel != 2 && usuario.nivel!= 1)///por las dudas que no puedan entrar empleados
        {
            system("cls");

            printf("\n MEN%c PACIENTE.-\n\n", 233);
            printf(" 1: VER INGRESOS.-\n");
            printf(" 2: CAMBIAR CONTRASE%cA.-\n", 165);
            printf(" 3: SALIR.-\n\n");

            printf(" Seleccione la opci%cn que desea utilizar: ", 162);
            fflush(stdin);
            scanf("%i",&eleccion);

            system("cls");

            switch(eleccion)
            {
            case 1:
                printf("\n INGRESOS DEL PACIENTE CON EL DNI %s: \n\n", usuario.usuarioPaciente);
                mostrarArchIngresosPaciente("ingresosPacientes.dat",usuario.usuarioPaciente);
                system("pause");
                system("cls");
                printf("\n PRACTICAS DEL PACIENTE CON EL DNI %s: \n\n", usuario.usuarioPaciente);
                mostrarArchRegPracPorPaciente("pracXingPacientes.dat", usuario.usuarioPaciente);
                system("pause");
                break;

            case 2:
                cambiarContraseniaPacientes("UsuariosPacientes.dat",usuario);
                break;

            case 3:
                printf("\n Saliendo del menu paciente.-\n\n");
                system("pause");
                break;
            }
        }
        else
        {
            printf(" Error al ingresar el usuario.\n\n");
            break;
        }
    }
    while(eleccion != 3);
}

void menuEmpleado(nodoarbol*arbol)
{
    UsuarioEmpleado empleado = ingresarUsuarioEmpleado();
    int eleccion = 0;
    int dniPac[9];
    int dniValido = 0;
    int numIngreso = 0;
    int numPractica = 0;

    arbol=pasarArchPacienteToArbol("pacientes.dat",arbol);

    do
    {
        if (empleado.nivel == 1) ///administrativo
        {
            system("cls");
            printf("\n Tareas administrativas.\n\n");
            printf(" 1: CARGAR PACIENTE.-\n");
            printf(" 2: CARGAR INGRESO.-\n");
            printf(" 3: MODIFICAR PRACTICAS DE PACIENTES.-\n");
            printf(" 4: MOSTRAR EMPLEADOS LABORATORIO.-\n");
            printf(" 5: MOSTRAR PACIENTES LABORATORIO.-\n");
            printf(" 6: CAMBIAR CONTRASENIA.-\n");
            printf(" 7: SALIR.-\n\n");
            printf(" Seleccione la opci%cn que desea utilizar: ", 162);

            fflush(stdin);
            scanf("%i",&eleccion);
            system("cls");

            switch (eleccion)
            {
            case 1:
                cargaEnArchivo("pacientes.dat");
                system("pause");
                break;

            case 2:
                agregarIngreso("ingresosPacientes.dat",arbol);
                break;

            case 3:
                system("cls");
                printf("\n PRACTICAS DE PACIENTES: \n\n");
                mostrarArchRegPracCompleta("pracXingPacientes.dat");

                while(dniValido != 1){
                    printf("\n Ingresar DNI del paciente: ");
                    fflush(stdin);
                    gets(dniPac);

                    dniValido = verificaDni(dniPac);

                    if(dniValido == 1){
                        modificarPxi("pracXingPacientes.dat" , dniPac , "practicasLab.dat");
                        system("pause");
                    }else{
                        printf("\n El DNI ingresado no es v%clido o no se encuentra registrado. \n\n" , 160);
                        system("pause");
                    }
                }
                dniValido = 0; //reinicio la variable
                break;

            case 4:
                mostrarArchEmpleadosSinContra("empleadosLab.dat");
                system("pause");
                break;

            case 5:
                mostrarArchPacientes("pacientes.dat");
                system("pause");
                break;

            case 6:
                cambiarContraseniaEmpleados("UsuariosEmpleados.dat","empleadosLab.dat", empleado);
                break;

            case 7:
                printf("Saliendo del men%c paciente.-\n\n", 163);
                system("pause");
                return; // Salir del bucle y la función
            }
        }
        else if (empleado.nivel == 2) ///nivel 2 tecnico bioquimico
        {
            system("cls");

            printf("\n Tareas de laboratorio.\n\n");
            printf(" 1: CARGAR RESULTADO\n");
            printf(" 2: MODIFICAR RESULTADO\n");
            printf(" 3: VER PR%cCTICAS\n", 181);
            printf(" 4: CAMBIAR CONTRASENIA\n");
            printf(" 5: SALIR\n");
            printf("Seleccione la opcion que desea utilizar.\n");

            fflush(stdin);
            scanf("%i", &eleccion);
            system("cls");

            switch (eleccion)
            {
            case 1:
                printf("\n PRACTICAS DE PACIENTES: \n\n");
                mostrarArchRegPracCompleta("pracXingPacientes.dat");
                system("pause");
                system("cls");
                cargarResultadoPxi("pracXingPacientes.dat");
                break;

            case 2:
                system("cls");
                printf("\n PRACTICAS DE PACIENTES: \n\n");
                mostrarArchRegPracCompleta("pracXingPacientes.dat");

                while(dniValido != 1){
                    printf("\n Ingresar DNI del paciente: ");
                    fflush(stdin);
                    gets(dniPac);

                    dniValido = verificaDni(dniPac);

                    if(dniValido == 1){
                        printf(" Ingresar nro. de ingreso: ");
                        scanf("%d" , &numIngreso);

                        printf(" Ingresar nro. de pr%cctica: " , 160);
                        scanf("%d" , &numPractica);

                        modificarResultado("pracXingPacientes.dat" , dniPac , numIngreso , numPractica);
                        system("pause");
                    }else{
                        printf("\n El DNI ingresado no es v%clido o no se encuentra registrado. \n\n" , 160);
                        system("pause");
                    }
                }
                dniValido = 0; //reinicio la variable

                break;

            case 3:
                mostrarArchPracticas("practicasLab.dat");
                system("pause");
                break;

            case 4:
                cambiarContraseniaEmpleados("UsuariosEmpleados.dat","empleadosLab.dat", empleado);
                break;

            case 5:
                printf(" Saliendo del men%c paciente.- \n\n", 163);
                system("pause");
                return; // Salir del bucle y la función
            }
        }
        else
        {
            break;
        }

    }
    while (1);
}

void menu()
{
    int eleccion = 0;
    int eleccion2 = 0;
    empleados_laboratorio empleado;
    char codigoMenuAdm[] = {"adrian_crack"}; //codigo por default
    char ingresoCodigo[16];

    nodoarbol* arbol=inicArbol();

    system("cls");
    progressBar();
    portadaInicio();

    do
    {
        system("cls");

        portadaInicioEstatica();

        gotoxy(40 , 20);
        printf(WHITE " ------------------------------------------ ");
        gotoxy(51 , 21);
        printf(" 1: Iniciar sesi%cn.", 162);
        gotoxy(51 , 22);
        printf(" 2: Crear usuario.");
        gotoxy(51 , 23);
        printf(" 3: Salir.");
        gotoxy(40 , 24);
        printf(" ------------------------------------------ ");

        gotoxy(4 , 26);
        printf(" Seleccione una opci%cn: ", 162);
        fflush(stdin);
        scanf("%i", &eleccion);

        switch (eleccion)
        {
        case 1:
            do{
                system("cls");

                portadaInicioEstatica();

                gotoxy(40 , 20);
                printf( WHITE " ------------------------------------------ ");
                gotoxy(51 , 21);
                printf(" 1: Iniciar sesi%cn paciente.", 162);
                gotoxy(51 , 22);
                printf(" 2: Iniciar sesi%cn empleado.", 162);
                gotoxy(51 , 23);
                printf(" 3: Salir.");
                gotoxy(40 , 24);
                printf(" ------------------------------------------ ");

                gotoxy(4 , 26);
                printf(" Seleccione una opci%cn: " , 162);
                fflush(stdin);
                scanf("%i", &eleccion2);

                switch (eleccion2)
                {
                case 1:
                    system("cls");
                    menuPaciente(arbol);
                    break;
                case 2:
                    system("cls");
                    menuEmpleado(arbol);
                    break;
                case 3:
                    break;

                default:
                    printf("\n Elecci%cn no v%clida. Intente de nuevo. \n\n", 162, 160);
                    system("pause");
                }

            }while(eleccion2 != 3);
            break;

        case 2:
            printf("\n Ingrese contrase%ca del laboratorio: ", 164);
            fflush(stdin);
            char contra[8];
            leerPassword(contra);

            if(strcmp(contra,"labcom7")==0)
            {
                agregarEmpleados("empleadosLab.dat",empleado);
                break;
            }
            else
            {
                printf("\n Contrase%ca del laboratorio incorrecta. \n\n", 164);
                system("pause");
                system("cls");
                break;
            }

        case 3:
            printf(GRAY "\n\n\t\t |**********************************************************************************| \n");
            printf(ORANGE "\t\t |                %c%cCERRANDO EL PROGRAMA...  NOS VEMOS PRONTO!!                     | \n", 173, 173);
            printf(ORANGE "\t\t |      BY: FRANCO AGUSTIN - MEDINA GABRIEL - TU%cON FACUNDO - VELASQUEZ BLAS        | \n" , 165);
            printf(GRAY "\t\t |**********************************************************************************| \n\n\n" WHITE);
            break;

        case 99:
            printf("\n Ingresar c%cdigo: " , 162);
            fflush(stdin);
            gets(ingresoCodigo);

            if(strcmp(ingresoCodigo , codigoMenuAdm) == 0){
                menuAdmin();
                system("pause");
                system("cls");
            }else{
                printf("\n El c%cdigo ingresado es incorrecto \n\n" , 162);
                system("pause");
            }
            break;

        default:
            printf("\n Elecci%cn no v%clida. Intente de nuevo. \n\n", 162, 160);
            system("pause");
        }
    }
    while(eleccion != 3);
}

void portadaInicio()
{
    gotoxy(50,4);
    Sleep(170);
    printf(ORANGE " B I E N V E N I D O / A ");
    gotoxy(40,5);
    Sleep(175);
    printf(RED " ========================================== ");
    gotoxy(40,6);
    Sleep(180);
    printf(LBLUE " ************* LABORATORIO DE ************* ");
    gotoxy(40,7);
    Sleep(185);
    printf(RED " ========================================== ");
    gotoxy(40,8);
    Sleep(190);
    printf(LGREEN " ||||||||||||                  |||||||||||| ");
    gotoxy(40,9);
    Sleep(195);
    printf(" ||||||||||||                  |||||||||||| ");
    gotoxy(40,10);
    Sleep(200);
    printf(" |||||||       ****     ****        |||||||  ");
    gotoxy(40,11);
    Sleep(205);
    printf(" ||||||||||||       ***        |||||||||||| ");
    gotoxy(40,12);
    Sleep(210);
    printf(" ||||||||||||       ***        ||||||||||||  ");
    gotoxy(40,13);
    Sleep(215);
    printf(" |||||||         ||     ||          ||||||| ");
    gotoxy(40,14);
    Sleep(220);
    printf(" ||||||||||||    || === ||     |||||||||||| ");
    gotoxy(40,15);
    Sleep(225);
    printf(" ||||||||||||    ||=====||     |||||||||||| ");
    gotoxy(40,16);
    Sleep(230);
    printf(RED " ========================================== ");
    gotoxy(40,17);
    Sleep(235);
    printf(LBLUE " ************ AN%cLISIS CL%cNICO ************ " , 181 , 214);
    gotoxy(40,18);
    Sleep(240);
    printf(RED " ========================================== \n\n");
}

void portadaInicioEstatica()
{
    gotoxy(50,4);
    printf(ORANGE " B I E N V E N I D O / A ");
    gotoxy(40,5);
    printf(RED " ========================================== ");
    gotoxy(40,6);
    printf(LBLUE " ************* LABORATORIO DE ************* ");
    gotoxy(40,7);
    printf(RED " ========================================== ");
    gotoxy(40,8);
    printf(LGREEN " ||||||||||||                  |||||||||||| ");
    gotoxy(40,9);
    printf(" ||||||||||||                  |||||||||||| ");
    gotoxy(40,10);
    printf(" |||||||       ****     ****        |||||||  ");
    gotoxy(40,11);
    printf(" ||||||||||||       ***        |||||||||||| ");
    gotoxy(40,12);
    printf(" ||||||||||||       ***        ||||||||||||  ");
    gotoxy(40,13);
    printf(" |||||||         ||     ||          ||||||| ");
    gotoxy(40,14);
    printf(" ||||||||||||    || === ||     |||||||||||| ");
    gotoxy(40,15);
    printf(" ||||||||||||    ||=====||     |||||||||||| ");
    gotoxy(40,16);
    printf(RED " ========================================== ");
    gotoxy(40,17);
    printf(LBLUE " ************ AN%cLISIS CL%cNICO ************ " , 181 , 214);
    gotoxy(40,18);
    printf(RED " ========================================== \n\n");

}

void leerPassword(char pass[])
{
    int i = 0;

    fflush(stdout);

    while(pass[i-1] != 13)
    {
        pass[i] = (unsigned char)getch();

        if(pass[i] != 8)
        {
            printf("*");
            i++;
        }
        else if(i > 0)
        {
            printf("%c", 8);
            printf("%c", 32);
            printf("%c", 8);
            i--;
        }

        fflush(stdout);
    }
    pass[i-1] = NULL;

    printf("%c", 8);
    printf("%c", 32);
    printf("%c", 8);
}
