#include "menuDios.h"
#include "paciente.h"
#include "ingresoSistema.h"
#include "empleado.h"
#include "listaEmpleados.h"
#include "string.h"
#include "practicas.h"

void menuDios()
{
    int eleccion=0;
    printf("MODO ADMINISTRADOR.\n\n");
    printf("Todas las opciones del sistema habilitadas.\n")
    printf("---------------------------n");

    do {
        printf("1:Cargar nuevo paciente.\n");
        printf("2:Mostrar pacientes.\n");
        printf("3:Modificar paciente.\n");
        printf("4:Cambiar contrasenia paciente.\n");
        printf("5:Ingresar practica paciente.\n");
        printf("6:Modificar practica paciente.\n");
        printf("7:Cargar resultados practicas.\n");
        printf("8:Mostrar practicas.\n");
        printf("9:Modificar practicas.\n")
        printf("10:Agregar practicas.\n");;
        printf("11:Mostrar ingresos.\n");
        printf("12:Crear empleado.\n");
        printf("13:Mostrar empleado.\n");
        printf("14:Cambiar contrasenia empleado.\n");
        printf("15:Modificar empleados.\n");
        printf("16:Borrar empleado.\n");
        printf("17:Borrar paciente.\n");
        printf("18:Salir del sistema.\n");




        printf("Ingrese el número de la opción deseada: ");
        scanf("%i", &eleccion);

        switch (eleccion) {
            case 1:

                break;
            case 2:
                mostrarAdlPacientes(arbol),
                break;
            case 3:

                break;
                case 4:
                cambiarContraseniaPacientes("UsuariosPacientes.dat",usuarioP);
                break;
                case 5:
            cargaDatosPrac
                break;
                case 6:
                modificarPractica()
                break;
                case 7:
                car
                break;
                case 8:

                break;
                case 9:

                break;
                case 10:

                break;
                case 11:
                    mostrarArchIngresos

                break;
                case 12:

                break;
                case 13:
mostrarAdlEmpleados(adl)
                break;
                case 14:
cambiarContraseniaEmpleados("UsuariosEmpleados.dat",usuarioE)
                break;
                case 15:
modificarEmpleadoEnArchivo()
                break;
                case 16:

                break;
                case 17:
                    mostrarAdlPacientes(adl);
                    char dni[8];
                    printf("Ingrese el dni del paciente que desea borrar.\n")
                    fflush(stdin);
                    gets(dni);
                   eliminar_nodo_de_arbol(adl,dni);
                break;
            case 18:
                printf("Saliendo del programa. ¡Hasta luego!\n");
                break;
            default:
                printf("Opción no válida. Por favor, elija nuevamente.\n");
        }
    } while (opcion != 18);


}
