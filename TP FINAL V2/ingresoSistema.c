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
    int i=5;
    FILE*archi=fopen("UsuariosPacientes.dat","r+b");
    int flag = 0;
    char dni[8];

    if(archi)
    {
        while(flag == 0 && i >=0 && i<=3)
        {
            printf("INICIO DE SESION\n ");
            printf("-------------------------\n ");
            printf("USUARIO: ");
            fflush(stdin);
            gets(aux.dniPaciente);

            printf("CONTRASENIA: ");
            fflush(stdin);
            gets(aux.contrasenia);
            printf("-------------------------\n ");

            while(fread(&usuarioP,sizeof(UsuarioPaciente),1,archi))
            {
            if(strcmp(aux.dniPaciente,usuarioP.dniPaciente) == 0 && strcmp(aux.contrasenia,usuarioP.contrasenia))
            {

                flag = 1;
                break;

            }
            }
            if (flag==0)
            {
                printf("TE QUEDAN %i INTENTOS\n",i);
                printf("LA CONTRASENIA O EL USUARIO ES INVALIDO, INTENTE DE NUEVO...\n");
                flag = 0;
                i--;
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
        printf("Inicio de sesion fallido. Cerrando el programa...\n");
        exit(EXIT_FAILURE);
    }
}

UsuarioEmpleado ingresarUsuarioEmpleado()
{
    UsuarioEmpleado aux;
    UsuarioEmpleado usuarioE;
    int i=5;
    FILE*archi=fopen("UsuariosEmpleados.dat","r+b");
    int flag = 0;

    if(archi)
    {
        while(flag == 0 && i >=0 && i<=3)
        {
            printf("INICIO DE SESION\n ");
            printf("-------------------------\n ");
            printf("USUARIO: ");
            fflush(stdin);
            gets(aux.usuarioEmpleado);

            printf("CONTRASENIA: ");
            fflush(stdin);
            gets(aux.contraEmpleado);
            printf("-------------------------\n ");

            while(fread(&usuarioE,sizeof(UsuarioEmpleado),1,archi))
            {
                if(strcmp(aux.usuarioEmpleado,usuarioE.usuarioEmpleado) == 0 && strcmp(aux.contraEmpleado,usuarioE.contraEmpleado))
                {
                    flag = 1;
                    break;
                }
            }

            if(flag==0)
            {
                printf("TE QUEDAN %i INTENTOS\n",i);
                printf("LA CONTRASENIA O EL USUARIO ES INVALIDO, INTENTE DE NUEVO...\n");
                flag = 0;
                i--;
            }
        }
    }
    fclose(archi);


if (flag == 1)
    {
        return aux;
    }
    else
    {
        printf("Inicio de sesion fallido. Cerrando el programa...\n");
        exit(EXIT_FAILURE);
    }
}
void menuPaciente()
{
    UsuarioPaciente usuario = ingresarUsuarioPaciente();
    int eleccion = 0;

    do
    {
         if (usuario.nivel==0)
        {
            printf("1: VER ESTUDIOS\n");
            printf("2: CAMBIAR CONTRASENIA\n");
            printf("3: SALIR\n");
            fflush(stdin);
            scanf("%i", &eleccion);

            switch (eleccion)
            {
//            case 1:
//                mostrarEstudioPaciente(arbol, usuario);

//                break;
            case 2:
                cambiarContraseniaPacientes("UsuariosPacientes.dat", usuario);
                break;
            case 3:
                break;
            default:
                printf("Opción no válida. Intente de nuevo.\n");
            }
        }
        else
        {
            printf("Error al ingresar el usuario.\n");
            break;
        }
} while (eleccion != 3);
}


void menuEmpleado()
{
    UsuarioEmpleado empleado = ingresarUsuarioEmpleado();
    int eleccion = 0;

    do
    {
        if (empleado.nivel == 1) ///administrativo
        {
            printf("1: CARGAR PACIENTE\n");
            printf("2: CARGAR PRACTICAS\n");
            printf("3: MODIFICAR PRACTICAS\n");
            printf("4: MOSTRAR EMPLEADOS LABORATORIO\n");
            printf("5: MOSTRAR PACIENTES LABORATORIO\n");
            printf("6: CAMBIAR CONTRASENIA\n");
            printf("7: SALIR\n");
            printf("Seleccione la opción que desea utilizar.\n");

            fflush(stdin);
            scanf("%i", &eleccion);

            switch (eleccion)
            {
            case 1:
                // cargar paciente arboles
                break;
            case 2:
                // cargar practica arboles y listas
                break;
            case 3:
                // modificar practicas
                break;
            case 4:
                // Mostrar empleados laboratorio archivo(ADENTRO DE ESTA PODER BUSCAR POR DNI)
                break;
            case 5:
                // Mostrar pacientes laboratorio archivo(adentro de esta funcion mostrar ingresos y poder seleccionar 1)
                break;
            case 6:
                cambiarContraseniaEmpleados("UsuariosEmpleados.dat", empleado);
                break;
            case 7:
                break;
            }
        }
        else if (empleado.nivel == 2) ///nivel 2 tecnico bioquimico
        {
            printf("1: CARGAR RESULTADO\n");
            printf("2: MODIFICAR RESULTADO\n");
            printf("3: VER PRACTICAS\n");
            printf("4: CAMBIAR CONTRASENIA\n");
            printf("5: SALIR\n");
            printf("Seleccione la opción que desea utilizar.\n");

            fflush(stdin);
            scanf("%i", &eleccion);

            switch (eleccion)
            {
            case 1:
                // cargar RESULTADO
                break;
            case 2:
                // MODIFICAR RESULTADO
                break;
            case 3:
                mostrarArchPracticas("practicasLab.dat");
                break;
            case 4:
                cambiarContraseniaEmpleados("UsuariosEmpleados.dat", empleado);
                break;
            case 5:
                break;
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
nodoarbol* adl=inicArbol();

    do
    {
        printf("Laboratorio de analisis clinico\n\n\n");
        printf("------------------------------------\n");
        printf("1: Iniciar sesion.\n");
        printf("2: Crear usuario.\n");
        printf("3: Salir.\n");

        printf("Seleccione la opcion que desea utilizar.\n");

        fflush(stdin);
        scanf("%i", &eleccion);
        system("cls");
        switch (eleccion)
        {
        case 1:
            {
                int eleccion2 = 0;
                printf("1: Iniciar sesion paciente.\n");
                printf("2: Iniciar sesion empleado.\n");
                printf("3: Salir.\n");
                printf("Seleccione la opcion que desea utilizar.\n");

                fflush(stdin);
                scanf("%i", &eleccion2);
                system("cls");

                switch (eleccion2)
                {
                case 1:
                    menuPaciente();
                    break;
                case 2:
                    menuEmpleado();
                    break;
                case 3:
                    break;
                default:
                    printf("Elección no válida. Intente de nuevo.\n");
                }
            }
            break;
        case 2:

            break;
        case 3:
            break;
        case 99:
            menuDios();
            break;
        default:
            printf("Elección no válida. Intente de nuevo.\n");
        }

    } while (eleccion!=3);
}
//
///
