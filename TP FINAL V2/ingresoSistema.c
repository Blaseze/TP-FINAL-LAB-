#include <stdlib.h>
#include <stdio.h>
#include "empleado.h"
#include "ingresoSistema.h"
#include "string.h"

void crearUsuarioPaciente(paciente pacienteUsu)
{
    UsuarioPaciente usuarioP;
    FILE* archiUsuarios=fopen("UsuariosPacientes.dat","ab");


    if(archiUsuarios)
    {
           strcpy(usuarioP.dniPaciente,pacienteUsu.dni);
           strcpy(usuarioP.contrasenia,pacienteUsu.dni);
           fwrite(&usuarioP,sizeof(UsuarioPaciente),1,archiUsuarios);
           usuarioP.nivel=0;
           fclose(archiUsuarios);
    }
}
void crearUsuarioEmpleado(empleados_laboratorio empleados)
{
    UsuarioEmpleado aux;
    FILE* archiEmpleados=fopen("UsuariosEmpleados.dat","ab");


    if(archiEmpleados)
    {
        if(strcmpy(empleados.perfil,"administrativo")==0)
        {
           strcpy(aux.usuarioEmpleado,empleados.dni);
           strcpy(aux.contraEmpleado,empleados.passEmpleado);
           aux.nivel=1;
           fwrite(&aux,sizeof(UsuarioEmpleado),1,archiEmpleados);
        }
        else {
           strcpy(aux.usuarioEmpleado,empleados.dni);
           strcpy(aux.contraEmpleado,empleados.passEmpleado);
           aux.nivel=2;
           fwrite(&aux,sizeof(UsuarioEmpleado),1,archiEmpleados);
        }

           fclose(archiEmpleados);
    }
}
///Primera vez que entra al sistema generar nueva clave antes de seguir a ver los estudios
void cambiarContraseniaPacientes(char archivoP[30], UsuarioPaciente usuario)///archivo de pacientes
{
UsuarioPaciente registro;
int i=0;
int j=3;
char comprobacion[10];
int flag=0;
FILE*archi=fopen(archivoP,"r+b");
if(archi)
{
    while ((fread(&registro,sizeof(UsuarioPaciente),1,archi)) && flag==0)
    {
        while(!feof(archi) && usuario.dniPaciente==registro.dniPaciente && j>0)
        {
            printf("Ingrese nueva contrasenia:\n");
            fflush(stdin);
            gets(usuario.contrasenia);
            printf("Ingrese nuevamente la contrasenia:\n");
            fflush(stdin);
            gets(comprobacion);
            if(strcmp(usuario.contrasenia,comprobacion)==0)
            {
                flag=1;
                fseek(archi,sizeof(UsuarioPaciente)*(i-1),SEEK_SET);
                strcpy(registro.contrasenia,usuario.contrasenia);
                fwrite(&registro,sizeof(UsuarioPaciente),1,archi);
            }
            else
            {
                printf("Las contrasenias no coinciden, vuelva a intentarlo\n");
                j--;
                if(j==0)
                {
                    printf("Realizaste demasiados intentos\n");
                    break;
                }
            }
        }
        i++;
    }
    fclose(archi);
}
}

void cambiarContraseniaEmpleados(char archivoP[30],UsuarioEmpleado empleado)///archivo de empleados
{
UsuarioEmpleado registro;
int i=0;
int j=3;
char comprobacion[10];
int flag=0;
FILE*archi=fopen(archivoP,"r+b");
if(archi)
{
    while ((fread(&registro,sizeof(UsuarioEmpleado),1,archi)) && flag==0)
    {
        while(!feof(archi) && registro.usuarioEmpleado==empleado.usuarioEmpleado && j>0)
        {
            printf("Ingrese nueva contrasenia:\n");
            fflush(stdin);
            gets(empleado.contraEmpleado);
            printf("Ingrese nuevamente contrasenia:\n");
            fflush(stdin);
            gets(comprobacion);
            if(strcmp(empleado.contraEmpleado,comprobacion)==0)
            {
                flag=1;
                fseek(archi,sizeof(UsuarioEmpleado)*(i-1),SEEK_SET);
                strcpy(registro.contraEmpleado,empleado.contraEmpleado);
                fwrite(&registro,sizeof(UsuarioEmpleado),1,archi);
            }
            else
            {
                printf("Las contrasenias no coinciden, vuelva a intentarlo\n");
                j--;
                if(j==0)
                {
                    printf("Realizaste demasiados intentos\n");
                }
            }
        }
        i++;
    }
    fclose(archi);
}

}
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
            fread(&usuarioP,sizeof(UsuarioPaciente),1,archi);

            if(strcmp(aux.dniPaciente,usuarioP.dniPaciente) == 0 && strcmp(aux.contrasenia,usuarioP.contrasenia))
            {

                flag = 1;
                return aux;

            }
            else
            {
                printf("TE QUEDAN %i INTENTOS\n",i);
                printf("LA CONTRASENIA O EL USUARIO ES INVALIDO, INTENTE DE NUEVO...\n");
                flag = 0;
                i--;
            }
        }
        fclose(archi);
    }

    return break;
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
            fread(&usuarioE,sizeof(UsuarioEmpleado),1,archi);


            if(strcmp(aux.usuarioEmpleado,usuarioE.usuarioEmpleado) == 0 && strcmp(aux.contraEmpleado,usuarioE.contraEmpleado))
            {
                flag = 1;
                return aux;

            }
            else
            {
                printf("TE QUEDAN %i INTENTOS\n",i);
                printf("LA CONTRASENIA O EL USUARIO ES INVALIDO, INTENTE DE NUEVO...\n");
                flag = 0;
                i--;
            }
        }
        fclose(archi);
    }

return break;
}

void menuPaciente()
{
   UsuarioPaciente usuario=ingresarUsuarioPaciente();
   int eleccion=0;

if(usuario!= NULL)
{
printf("1:VER ESTUDIOS\n");
printf("2:CAMBIAR CONTRASENIA\n");
printf("3:SALIR\n");
fflush(stdin);
scanf("%i",&eleccion);
switch(eleccion)
{
case 1:
mostrarEstudioPaciente(arbol,usuario);
break;
case 2:
cambiarContraseniaPacientes("UsuariosPacientes.dat",usuario);
break;
case 3:
return 0;
break;
}
}
}

void menuEmpleado()
{
UsuarioEmpleado empleado=ingresarUsuarioEmpleado();
int eleccion=0;

if(empleado.nivel==1)///administrativo
{
printf("1:CARGAR PACIENTE\n");
printf("2:CARGAR PRACTICAS\n");
printf("3:MODIFICAR PRACTICAS\n");
printf("4:MOSTRAR EMPLEADOS LABORATORIO\n");
printf("5:MOSTRAR PACIENTES LABORATORIO\n");
printf("6:CAMBIAR CONTRASENIA\n");
printf("7:SALIR\n");
fflush(stdin);
scanf("%i",&eleccion);
switch(eleccion)
{
case 1:
//cargar paciente arboles
//break
case 2:
//cargar practica arboles y listas
//break
case 3:
//modificar practicas
//break
case 4:
//Mostrar empleados laboratorio archivo(ADENTRO DE ESTA PODER BUSCAR POR DNI
//break
case 5:
    //Mostrar pacientes laboratorio archivo(adentro de esta funcion mostrar ingresos y poder selecionar 1
//break
case 6:
cambiarContraseniaEmpleados("UsuariosEmpleados.dat",empleado);
//break
case 7:
//return 0;
//break
}
}
else if (empleado.nivel==2)///nivel 2 tecnico bioquimico
{
printf("1:CARGAR RESULTADO\n");
printf("2:MODIFICAR RESULTADO\n");
printf("3:VER PRACTICAS\n");
printf("4:CAMBIAR CONTRASENIA\n");
printf("5:SALIR\n");
fflush(stdin);
scanf("%i",&eleccion);
switch(eleccion)
{
case 1:
//cargar RESULTADO
break;
case 2:
//MODIFIVAR RESULTADO
break;
case 3:
    // VER PRACTICAS(ADENTRO DE ESTO PERMITIR BUSQUEDA DE PRACTICAS POR TECLADO
case 4:
cambiarContraseniaEmpleados("UsuariosEmpleados.dat",empleado);
break;
case 5:
return 0;
break;
}
}
else
{
    break;
}


}

void menu()
{
    int eleccion=0;
    printf("1:Iniciar sesion");
    printf("2:crear usuario");
    fflush(stdin);
    scanf("%i",eleccion);
     if(eleccion==1)
     {
        int eleccion2=0;
        printf("1:Iniciar sesion paciente");
        printf("2:Iniciar sesion empleado");
        fflush(stdin);
     scanf("%i",eleccion2);
     if(eleccion2==1)
     {
        menuPaciente();
     }
     else if(eleccion2==2)
     {
        menuEmpleado();
     }
     else
     {
        printf("eleccion invalida");
        break;
     }
     }
     else if(eleccion==2)
     {
        ///crearempleado();
     }
     else if(eleccion==99)
     {
        menudios();
     }
     else
     {
        printf("eleccion invalida");
        break;
     }
}

///
