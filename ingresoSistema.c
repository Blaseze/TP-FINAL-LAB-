+#include <stdlib.h>
#include <stdio.h>
#include "empleado.h"
#include "ingresoSistema.h"
#include "string.h"

/** \brief esta funcion la llama el administrativo que crea un paciente
 *
 * \param Paciente paciente
 *
 *
 *
 */
void crearUsuarioPaciente(Paciente paciente)
{
    UsuarioPaciente usuarioP;
    FILE* archiUsuarios=fopen("UsuariosPacientes.dat","ab");


    if(archiUsuarios)
    {
           strcpy(usuarioP.dniPaciente,paciente.DNI);
           strcpy(usuarioP.contrasenia,paciente.DNI);
           fwrite(&usuarioP,sizeof(UsuarioPaciente),1,archiUsuarios);
           usuarioP.nivel=0;
           fclose(archiUsuarios);
    }
}
void crearUsuarioEmpleado(empleados_laboratorio empleados)
{
    UsuarioAdministrativo usuarioA;
    UsuarioTecnico usuarioT;
    FILE* archiEmpleados=fopen("UsuariosEmpleados.dat","ab");


    if(archiEmpleados)
    {
        if(strcmpy(empleados.perfil,"administrativo")==0)
        {
            strcpy(usuarioA.usuarioAdministrativo,empleados.dni);
           usuarioA.contraAdministrativo=empleados.passEmpleado;
           usuarioA.nivel=1;
           fwrite(&usuarioA,sizeof(usuarioAdministrativo),1,archiEmpleados);
        }
        else {
           strcpy(usuarioT.usuarioTecnico,empleados.dni);
           usuarioT.contraTecnico=empleados.passEmpleado;
           usuarioT.nivel=2;
           fwrite(&usuarioT,sizeof(UsuarioTecnico),1,archiEmpleados);
        }        

           fclose(archiEmpleados);
    }
}
///Primera vez que entra al sistema generar nueva clave antes de seguir a ver los estudios

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
///
