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
           strcpy(usuarioP.dniPaciente,pacienteUsu.DNI);
           strcpy(usuarioP.contrasenia,pacienteUsu.DNI);
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
           aux.contraEmpleado=empleados.passEmpleado;
           aux.nivel=1;
           fwrite(&aux,sizeof(UsuarioEmpleado),1,archiEmpleados);
        }
        else {
           strcpy(aux.usuarioEmpleado,empleados.dni);
           aux.contraEmpleado=empleados.passEmpleado;
           aux.nivel=2;
           fwrite(&aux,sizeof(UsuarioEmpleado),1,archiEmpleados);
        }

           fclose(archiEmpleados);
    }
}
///Primera vez que entra al sistema generar nueva clave antes de seguir a ver los estudios
void cambiarContraseñaPacientes(char archivoP[30])///archivo de pacientes
{
UsuarioPaciente p;
UsuarioPaciente aux;
int i=0;
int j=3;
char comprobacion[10];
int flag=0;
FILE*archi=fopen(archivoP,"r+b");
if(archi)
{
    while ((fread(&p,sizeof(UsuarioPaciente)1,archi)>0) && flag==0)
    {
        while(!feof(archi) && aux.dniPaciente==p.dniPaciente && j>0)
        {
            printf("Ingrese nueva contrasenia:\n");
            fflush(stdin);
            gets(aux.contrasenia);
            printf("Ingrese nuevamente contrasenia:\n");
            fflush(stdin);
            gets(comprobacion);
            if(strcmp(aux.contrasenia,comprobacion)==0)
            {
                flag=1;
                fseek(archi,sizeof(UsuarioPaciente)*(i-1),SEEK_SET);
                strcpy(p.contrasenia,aux.contrasenia);
                fwrite(&p,sizeof(UsuarioPaciente),1,archi);
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
void cambiarContraseñaEmpleados(char archivoP[30])///archivo de empleados
{
UsuarioEmpleado e;
UsuarioEmpleado aux;
int i=0;
int j=3;
char comprobacion[10];
int flag=0;
FILE*archi=fopen(archivoP,"r+b");
if(archi)
{
    while ((fread(&e,sizeof(UsuarioEmpleado)1,archi)>0) && flag==0)
    {
        while(!feof(archi) && aux.usuarioEmpleado==e.usuarioEmpleado && j>0)
        {
            printf("Ingrese nueva contrasenia:\n");
            fflush(stdin);
            gets(aux.contraEmpleado);
            printf("Ingrese nuevamente contrasenia:\n");
            fflush(stdin);
            gets(comprobacion);
            if(strcmp(aux.contraEmpleado,comprobacion)==0)
            {
                flag=1;
                fseek(archi,sizeof(UsuarioEmpleado)*(i-1),SEEK_SET);
                strcpy(e.contraEmpleado,aux.contraEmpleado);
                fwrite(&p,sizeof(UsuarioEmpleado),1,archi);
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
}
int ingresarUsuarioPaciente()
{
   UsuarioPaciente usuarioP;
    UsuarioPaciente aux;
    int i=5;
    FILE*archi=fopen("UsuariosPacientes.dat","r+b");
    int flag = 0;

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

    return flag;
}
int ingresarUsuarioEmpleado()
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
            fread(&usuarioP,sizeof(UsuarioPaciente),1,archi);


            if(strcmp(aux.usuarioEmpleado,usuarioE.usuarioEmpleado) == 0 && strcmp(aux.contraEmpleado,usuarioE.contraEmpleado))
            {
                flag = 1;
                aux.nivel=usuarioE.nivel;
                if(aux.nivel==1)
                {
                    return 1;
                }
                else
                {
                    return 2;
                }
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

return 0;
}

void menuPaciente()
{
int flag=ingresarUsuarioPaciente();
int eleccion=0;

if(flag==1)
{
printf("1:VER ESTUDIOS\n");
printf("2:CAMBIAR CONTRASENIA\n");
printf("3:SALIR\n");
fflush(stdin);
scanf("%i",&eleccion);
switch(eleccion)
{
case 1:
//ver estudios
//break
case 2:
cambiarContraseñaPacientes("UsuariosPacientes.dat");
//break
case 3:
//return 0;
//break
}
}
}

void menuEmpleado()
{
int nivel=ingresarUsuarioEmpleado();
int eleccion=0;

if(nivel==1)///administrativo
{
printf("1:CARGAR PACIENTE\n");
printf("2:CARGAR PRACTICAS\n");
printf("3:MODIFICAR PRACTICAS\n");
printf("4:MOSTRAR EMPLEADOS LABORATORIO\n");
printf("5:CAMBIAR CONTRASENIA\n");
printf("6:SALIR\n");
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
//Mostrar empleados laboratorio archivo
//break
case 5:
cambiarContraseñaEmpleados("UsuariosEmpleados.dat");
//break
case 6:
//return 0;
//break
}
else if (nivel==2)///nivel 2 tecnico bioquimico
{
printf("1:CARGAR RESULTADO\n");
printf("2:MODIFICAR RESULTADO\n");
printf("3:CAMBIAR CONTRASENIA\n");
printf("4:SALIR\n");
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
cambiarContraseñaEmpleados("UsuariosEmpleados.dat");
break;
case 4:
return 0;
break;
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
