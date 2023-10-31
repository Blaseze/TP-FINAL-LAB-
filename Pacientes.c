#include "Pacientes.h"

int verificaNombre(char nombre[])
{
    int flag=1;
    int tamanio= strlen(nombre);

    if((tamanio==0)|| (nombre[0]== 32))
    {
        flag=0;
    }
    else
    {
        int i=0;
        while(i<tamanio && (flag==1))
        {
            if((nombre[i]>=65 && nombre[i]<=90)|| (nombre[i]>=97 && nombre[i]<=122)|| (nombre[i]==32))
            {
                i++;
            }
            else
            {
                flag=0;
            }
        }
    }
    return flag;
}


int verificaEdad(int edad)
{
    int flagEdad=1;

    if(edad<=0 || edad>=110)
    {
        flagEdad=0;
    }
    return flagEdad;
}

int verificaExistenciaPaciente(char nombreArchivo[],char dniPaciente[])
{
    int existe=0;
    paciente auxPaciente;
    FILE *archi= fopen(nombreArchivo,"rb");

    if(archi)
    {
        while((fread(&auxPaciente,sizeof(paciente),1,archi)>0)&& (existe==0))
        {
            if(strcmpi(auxPaciente.dni,dniPaciente)==0)
            {
                existe=1;
            }
        }
        fclose(archi);
    }
    return existe;
}

int verificaDni(char dniP[])
{
    int dniValido=1;
    int tamanio= strlen(dniP);
    int i=0;

    if((tamanio<7 || tamanio>7)&& (tamanio<8 || tamanio>8))
    {
        dniValido=0;
    }
    else
    {
        while((i<tamanio) && (dniValido==1))
        {
            if((dniP[i]>=48 && dniP[i]<=57)&& (dniP[0]!= '0'))
            {
                i++;
            }
            else
            {
                dniValido=0;
            }
        }
    }
    return dniValido;
}

int verificaDireccion(char direccion[])
{
    int flag=1;
    int tamanio= strlen(direccion);

    if(tamanio>30)
    {
        flag=0;
    }
    else
    {
        for(int i=0; i< tamanio; i++)
        {
            if(!isalnum(direccion[i])) // la funcion isalnum verifica que la direccion no tenga ningun caracter especial solo letras y numeros
            {
                flag=0;
            }
        }
    }
//    for(int i=0; i< strlen(direccion);i++)
//        {
//            if(isalnum((int)direccion))
//            {
//                flag=0;
//            }
//        }
    return flag;
}

int verificaTelefono(char telefono[])
{
    int tamanio=strlen(telefono);
    int flag=1;

    if(tamanio>20)
    {
        flag=0;
    }
    else
    {
        for(int i=0; i<tamanio; i++)
        {
            if(!isdigit(telefono[i]))
            {
                flag=0;
            }
        }
    }
    return flag;
}
void cargaEnArchivo(char nombreArchivo[])
{
    char continuar='s';
    paciente persona;

    while(continuar=='s'|| continuar=='S')
    {
        persona=cargaPaciente(nombreArchivo,persona);
        guardaUnaPersona(nombreArchivo,persona);

        system("cls");
        printf("¿Desea cargar otro paciente? S/N\n\n");
        fflush(stdin);
        continuar=getch();
    }
}

void guardaUnaPersona(char nombreArchivo[],paciente perso)
{
    FILE *archi=fopen(nombreArchivo,"ab");

    if(archi!= NULL)
    {
        fwrite(&perso,sizeof(paciente),1,archi);
        fclose(archi);
    }
    else
    {
        printf("Error en la apertura del archivo.\n\n");
    }
}

paciente cargaPaciente(char nombreArchivo[],paciente nuevoPaciente)
{
    int nombreOk=0;
    int edadOk=0;
    int dniOk=0;
    int existeDni=0;
    int direccionOk=0;
    int telOk=0;


    printf("---------------Cargando un Paciente---------------\n");

        while(nombreOk!=1)
        {
            system("cls");
            printf("Ingrese Nombre y Apellido: \n");
            fflush(stdin);
            gets(nuevoPaciente.apellidoYnombre);
            nombreOk=verificaNombre(nuevoPaciente.apellidoYnombre);

            if(nombreOk!=1)
            {
                printf("\nEl nombre o apellido ingresado no es valido.\n");
                system("pause");
            }

        }

        while(edadOk!=1)
        {
            printf("Ingrese la Edad: \n");
            scanf("%i",&nuevoPaciente.edad);
            edadOk=verificaEdad(nuevoPaciente.edad);

            if(edadOk!=1)
            {
                printf("\nEdad no valida, ingrese edad nuevamente.\n");

            }
        }

        while(dniOk!=1 || existeDni==1)
        {

            printf("Ingrese el DNI: \n");
            fflush(stdin);
            gets(nuevoPaciente.dni);

            existeDni=verificaExistenciaPaciente(nombreArchivo,nuevoPaciente.dni);
            dniOk=verificaDni(nuevoPaciente.dni);

            if(existeDni==1)
            {
                printf("\n DNI ya registrado.\n\n");

            }
            else
            {
                existeDni=0;
            }
            if(dniOk!=1)
            {
                printf("\n El DNI ingresado no es valido.\n");

            }

        }

        while(direccionOk!=1)
        {
            printf("Ingrese el domicilio: \n");
            gets(nuevoPaciente.direccion);

            direccionOk= verificaDireccion(nuevoPaciente.direccion);

            if(direccionOk!=1)
            {
                printf("\nLa direccion ingresada no es correcta.");
            }
        }

        while(telOk!=1)
        {
            printf("Ingrese un telefono: \n");
            gets(nuevoPaciente.telefono);

            telOk=verificaTelefono(nuevoPaciente.telefono);

            if(telOk!=1)
            {
                printf("\nEl telefono ingresado no es correcto.\n");

            }

        }

        nuevoPaciente.eliminados=0;

    return nuevoPaciente;
}


void mostrarPaciente(paciente persona)
{
    printf("-----------------------------------------\n\n");
    printf("Apellido y Nombre---------------: %s\n",persona.apellidoYnombre);
    printf("Edad----------------------------: %d\n",persona.edad);
    printf("DNI-----------------------------: %s\n",persona.dni);
    printf("Direccion-----------------------: %s\n",persona.direccion);
    printf("Telefono------------------------: %s\n",persona.telefono);
    printf("-----------------------------------------\n\n");
}


void mostrarArchPacientes(char nombreArchivo[])
{
    paciente aux;
    FILE *archi=fopen(nombreArchivo,"rb");

    if(archi)
    {
        while(fread(&aux,sizeof(paciente),1,archi)>0)
        {
            mostrarPaciente(aux);
        }
        fclose(archi);
    }
    else
    {
        printf("Error al querer leer el archivo.\n\n");
    }
}






