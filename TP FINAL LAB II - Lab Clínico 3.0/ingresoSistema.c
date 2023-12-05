#include <stdlib.h>
#include <stdio.h>
#include "paciente.h"
#include "empleado.h"
#include "ingresoSistema.h"
#include "string.h"
#include "menuDios.h"


UsuarioPaciente ingresarUsuarioPaciente()
{
    UsuarioPaciente usuarioP;
    UsuarioPaciente aux;
    int i=3;
    FILE*archi=fopen("UsuariosPacientes.dat","rb");
    int flag = 0;
    char dni[8];

    if(archi)
    {

        while(flag == 0 && i >=0 && i<=3)
        {
            system("cls");

            printf("\n INICIO DE SESI%cN PACIENTE\n " , 224);
            printf(" -------------------------\n ");
            printf(" USUARIO: ");
            fflush(stdin);
            gets(aux.usuarioPaciente);

            printf(" CONTRASE%cA: " , 165);
            fflush(stdin);
            gets(aux.contrasenia);
            printf("-------------------------\n ");

            while(fread(&usuarioP,sizeof(UsuarioPaciente),1,archi))
            {
                if(strcmp(aux.usuarioPaciente,usuarioP.usuarioPaciente) == 0 && strcmp(aux.contrasenia,usuarioP.contrasenia)==0)
                {

                    flag = 1;

                    break;

                }
            }
            if (flag==0)
            {
                printf("TE QUEDAN %i INTENTOS\n",i);
                printf("LA CONTRASE%cA O EL USUARIO ES INV%cLIDO, INTENTE DE NUEVO...\n\n" , 165 , 181);
                flag = 0;
                i--;
                rewind(archi);
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
        printf(" Inicio de sesi%cn fallido. Cerrando el programa...\n\n" , 162);
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

    if (archi)
    {
        while (i > 0 && flag == 0)
        {
            printf("\n INICIO DE SESI%cN EMPLEADO\n " , 224);
            printf("-------------------------\n ");
            printf(" USUARIO: ");
            fflush(stdin);
            gets(aux.usuarioEmpleado);

            printf("CONTRASE%cA: " , 165);
            fflush(stdin);
            gets(aux.contraEmpleado);
            printf("-------------------------\n ");

            fseek(archi, 0, SEEK_SET);

            while (fread(&usuarioE, sizeof(UsuarioEmpleado), 1, archi) && flag == 0)
            {
                if (strcmp(aux.usuarioEmpleado, usuarioE.usuarioEmpleado) == 0 && strcmp(aux.contraEmpleado, usuarioE.contraEmpleado) == 0)
                {
                    flag = 1;
                    aux=usuarioE;
                }
            }

            if (flag == 0)
            {
                printf(" TE QUEDAN %i INTENTOS\n", (i-1));
                printf(" LA CONTRASE%cA O EL USUARIO ES INV%cLIDO, INTENTE DE NUEVO...\n\n" , 165 , 181);
                i--;
                rewind(archi);
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
        printf("Inicio de sesi%cn fallido. Cerrando el programa...\n\n" , 162);
        exit(EXIT_FAILURE);
    }
}
void menuPaciente()
{

    UsuarioPaciente usuario=ingresarUsuarioPaciente();
    int eleccion=0;
    const char dniAux[9];

    do
    {

        system("cls");

        if(usuario.nivel !=2 && usuario.nivel!=1)///por las dudas que no puedan entrar empleados
        {
            system("cls");
            printf("\n MEN%c PACIENTE.-\n\n" , 233);
            printf(" 1:VER INGRESOS.-\n");
            printf(" 2:CAMBIAR CONTRASE%cA.-\n") , 165;
            printf(" 3:SALIR.-\n\n");

            printf(" Seleccione la opci%cn que desea utilizar.\n\n" , 162);
            fflush(stdin);
            scanf("%i",&eleccion);

            system("cls");

            switch(eleccion)
            {
            case 1:
                printf("\n Ingresar DNI: ");
                fflush(stdin);
                gets(dniAux);

                system("cls");

                printf("\n INGRESOS DEL PACIENTE CON EL DNI %s: \n\n" , dniAux);
                mostrarArchIngresosPaciente("ingresosPacientes.dat" ,dniAux);
                system("pause");
                system("cls");
                printf("\n PRACTICAS DEL PACIENTE CON EL DNI %s: \n\n" , dniAux);
                mostrarArchRegPracPaciente("pracXingPacientes.dat" , dniAux);
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
    }while(eleccion !=3);
}
void menuEmpleado(nodoarbol*arbol)
{
    UsuarioEmpleado empleado = ingresarUsuarioEmpleado();
    int eleccion = 0;
    paciente pacienteBusqueda;
    int numIng = 0;
    int numPrac = 0;

    arbol=pasarArchPacienteToArbol("pacientes.dat",arbol);

    do
    {
        if (empleado.nivel == 1) ///administrativo
        {
            system("cls");
            printf("\n Tareas administrativas.\n\n");
            printf(" 1: CARGAR PACIENTE.-\n");
            printf(" 2: CARGAR INGRESO.-\n");
            printf(" 3: MODIFICAR PRACTICAS.-\n");
            printf(" 4: MOSTRAR EMPLEADOS LABORATORIO.-\n");
            printf(" 5: MOSTRAR PACIENTES LABORATORIO.-\n");
            printf(" 6: CAMBIAR CONTRASENIA.-\n");
            printf(" 7: SALIR.-\n\n");
            printf(" Seleccione la opci%cn que desea utilizar: " , 162);

            fflush(stdin);
            scanf("%i",&eleccion);
            system("cls");

            switch (eleccion)
            {
            case 1:

                cargaEnArchivo("pacientes.dat");
                arbol=pasarArchPacienteToArbol("pacientes.dat",arbol);
                system("pause");

                break;
            case 2:
               agregarIngreso("ingresosPacientes.dat",arbol);

                break;

            case 3:

                break;
            case 4:

                mostrarArchEmpleados("empleadosLab.dat");
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
                printf("Saliendo del men%c paciente.-\n\n" , 163);
                system("pause");
                return; // Salir del bucle y la función
            }
        }
        else if (empleado.nivel == 2) ///nivel 2 tecnico bioquimico
        {
            system("cls");
            printf("\n Tareas de laboratorio.\n");
            printf(" 1: CARGAR RESULTADO\n");
            printf(" 2: MODIFICAR RESULTADO\n");
            printf(" 3: VER PR%cCTICAS\n" , 181);
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
                mostrarArchRegPracPaciente("pracXingPacientes.dat");
                system("pause");
                system("cls");

                printf("\n Ingresar nro de practica: ");
                scanf("%d" , &numPrac);

                cargarResultadoPractica("pracXingPacientes.dat" , numPrac);

                break;
            case 2:
                //MODIFCIAR RESULTADO
                break;
            case 3:
                mostrarArchPracticas("practicasLab.dat");
                system("pause");
                break;
            case 4:
                cambiarContraseniaEmpleados("UsuariosEmpleados.dat","empleadosLab.dat", empleado);
                break;
            case 5:
                printf(" Saliendo del men%c paciente.-\n\n" , 163);
                system("pause");
                return; // Salir del bucle y la función
            }
        }
        else
        {
            break;
        }

    } while (1);
}

void menu()
{
    int eleccion = 0;
    empleados_laboratorio empleado;
    nodoarbol* arbol=inicArbol();


    do
    {
        system("cls");

        printf("\n Laboratorio de an%clisis cl%cnico\n\n" , 160 , 161);
        printf(" ------------------------------------\n");
        printf("\t 1: Iniciar sesi%cn.\n" , 162);
        printf("\t 2: Crear usuario.\n");
        printf("\t 3: Salir.\n");
        printf(" ------------------------------------\n\n");
        printf(" Seleccione la opci%cn que desea utilizar: " , 162);

        fflush(stdin);
        scanf("%i", &eleccion);
        system("cls");
        switch (eleccion)
        {
        case 1:
        {
            int eleccion2 = 0;
            printf("\n ------------------------------------\n");
            printf(" 1: Iniciar sesi%cn paciente.\n" , 162);
            printf(" 2: Iniciar sesi%cn empleado.\n" , 162);
            printf(" 3: Salir.\n");
            printf(" ------------------------------------\n\n");
            printf(" Seleccione la opci%cn que desea utilizar: " , 162);

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
                printf("\n Elecci%cn no v%clida. Intente de nuevo.\n" , 162 , 160);
                system("pause");

            }
        }
        break;
        case 2:
            printf("\n Ingrese contrase%ca del laboratorio.\n\n" , 164);
            fflush(stdin);
            char contra[8];
            gets(contra);

            if(strcmp(contra,"labcom7")==0)
            {
                agregarEmpleados("empleadosLab.dat",empleado);
                break;
            }else
            {
                printf("\n Contrase%ca del laboratorio incorrecta.\n\n" , 164);
                system("pause");
                system("cls");
            break;

            }
        case 3:
            printf("\n Cerrando programa, hasta pronto.-\n\n");

            break;
        case 99:
            menuAdmin();
            system("pause");
            system("cls");

            break;
        default:
            printf("\n Elecci%cn no v%clida. Intente de nuevo. \n\n" , 162 , 160);
            system("pause");
        }

    }
    while (eleccion!=3);
}
//
///


