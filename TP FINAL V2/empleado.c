#include "empleado.h"

void crearUsuarioEmpleado(empleados_laboratorio empleados)
{
    UsuarioEmpleado aux;
    FILE* archiEmpleados=fopen("UsuariosEmpleados.txt","ab");


    if(archiEmpleados)
    {
        if(strcmpi(empleados.perfil,"administrativo")==0)
        {
            strcpy(aux.usuarioEmpleado,empleados.dni);
            strcpy(aux.contraEmpleado,empleados.passEmpleado);
            aux.nivel=1;
            fwrite(&aux,sizeof(UsuarioEmpleado),1,archiEmpleados);
        }
        else
        {
            strcpy(aux.usuarioEmpleado,empleados.dni);
            strcpy(aux.contraEmpleado,empleados.passEmpleado);
            aux.nivel=2;
            fwrite(&aux,sizeof(UsuarioEmpleado),1,archiEmpleados);
        }

        fclose(archiEmpleados);
    }

}
void cambiarContraseniaEmpleados(char archivoUsu[30], char archivoEmple[30], UsuarioEmpleado empleado)
{
    UsuarioEmpleado registroUsu;
    empleados_laboratorio registroEmple;
 char comprobacion[8];
    FILE *archiUsua = fopen(archivoUsu, "r+b");
    FILE *archiEmpledo = fopen(archivoEmple, "r+b");

    if ((archiUsua != NULL) && (archiEmpledo != NULL))
    {
        int usuarioEncontrado = 0;  // Variable para indicar si se encontró el usuario

        while (fread(&registroUsu, sizeof(UsuarioEmpleado), 1, archiUsua))
        {
            if (strcmp(registroUsu.usuarioEmpleado, empleado.usuarioEmpleado) == 0)
            {
                printf("Ingrese nueva contrasenia:\n");
                fflush(stdin);
                gets(empleado.contraEmpleado);
                printf("Ingrese nuevamente contrasenia:\n");
                fflush(stdin);

                gets(comprobacion);

                // Verifica que las contraseñas coincidan
                if (strcmp(empleado.contraEmpleado, comprobacion) == 0)
                {
                    // Actualizar en archiUsua
                    fseek(archiUsua, -sizeof(UsuarioEmpleado), SEEK_CUR);
                    fwrite(&empleado, sizeof(UsuarioEmpleado), 1, archiUsua);

                    usuarioEncontrado = 1;  // Marcar que se encontró el usuario

                    // No salimos del bucle aquí para seguir con la actualización del archivo de empleados
                }
                else
                {
                    printf("Las contrasenias no coinciden, vuelva a intentarlo\n");
                    break;  // Si las contraseñas no coinciden, salimos del bucle
                }
            }
        }

        if (usuarioEncontrado==1)
        {
            // Actualizar en archiEmpledo
            rewind(archiEmpledo);

            while (fread(&registroEmple, sizeof(empleados_laboratorio), 1, archiEmpledo))
            {
                if (strcmp(registroEmple.userEmpleado, empleado.usuarioEmpleado) == 0)
                {

                    fseek(archiEmpledo, -sizeof(empleados_laboratorio), SEEK_CUR);
                     strcpy(registroEmple.passEmpleado,empleado.contraEmpleado);
                    fwrite(&registroEmple, sizeof(empleados_laboratorio), 1, archiEmpledo);
                    break;  // Salir del bucle después de encontrar y actualizar el registro
                }
            }

            printf("Contraseña actualizada exitosamente.\n");
        }

        fclose(archiUsua);
        fclose(archiEmpledo);
    }
    else
    {
        printf("No se pudieron abrir los archivos\n");
    }
}

void cargarArchEmpleados(char nombreArchivo[])
{
    empleados_laboratorio emple;

    agregarEmpleados(nombreArchivo, emple);
}

void guardarUnEmpleado(char nombreArchivo[], empleados_laboratorio emple)
{
    FILE *pArchivo = fopen(nombreArchivo, "ab");

    if(pArchivo != NULL)
    {
        fwrite(&emple, sizeof(empleados_laboratorio), 1, pArchivo);
        fclose(pArchivo);

        printf("\n DATOS DEL EMPLEADO: \n\n");
        mostrarUnEmpleado(emple);

        printf("\n EMPLEADO CARGADO CON %cXITO \n\n", 144);

    }
    else
    {
        printf(" ERROR en la apertura del archivo. \n\n");
    }
}

void mostrarArchEmpleados(char nombreArchivo[])
{
    empleados_laboratorio aux;
    FILE *pArchivo = fopen(nombreArchivo, "rb");

    if(pArchivo != NULL)
    {
        while(fread(&aux, sizeof(empleados_laboratorio), 1, pArchivo) > 0)
        {
            mostrarUnEmpleado(aux);
        }
        fclose(pArchivo);
    }
    else
    {
        printf(" ERROR en la lectura del archivo. \n\n");
    }
}

void agregarEmpleados(char nombreArchivo[], empleados_laboratorio nuevo)
{
    char continuar = 's';
    int existeEmpleado = 0;

    while(continuar == 's' || continuar == 'S')
    {
        system("cls");

        nuevo = cargaDatosEmpleado(nombreArchivo, nuevo);

        system("cls");

        guardarUnEmpleado(nombreArchivo, nuevo);

        printf("\n %cQuires agregar un nuevo empleado? s=SI / n=NO ", 168);
        fflush(stdin);
        continuar = getch();
        printf("\n\n");
    }
}

int contarPerfiles(char nombreArchivo[])
{
    empleados_laboratorio auxReg;
    int numPerfilesUnicos = 0;
    FILE *pArchivo = fopen(nombreArchivo, "rb");

    if(pArchivo != NULL)
    {
        char **perfilesUnicos = NULL;
        int existePerfil = 0;
        int i = 0;

        while(fread(&auxReg, sizeof(empleados_laboratorio), 1, pArchivo) > 0)
        {
            i = 0;
            existePerfil = 0;
            while((i < numPerfilesUnicos) && (existePerfil == 0))  //busco si ya existe el perfil en el arreglo
            {
                if(strcmpi(perfilesUnicos[i], auxReg.perfil) == 0)
                {
                    existePerfil = 1;
                }
                i++;
            }

            if(existePerfil == 0)
            {
                char *perfilNuevo = (char *)malloc(strlen(auxReg.perfil) + 1); //asigno memoria al nuevo perfil
                strcpy(perfilNuevo, auxReg.perfil);

                perfilesUnicos = (char **)realloc(perfilesUnicos, (numPerfilesUnicos + 1) * (sizeof(char *)));  //aumento la capacidad del arreglo

                perfilesUnicos[numPerfilesUnicos] = perfilNuevo; //guardo el perfil nuevo
                numPerfilesUnicos++;
            }
        }
        fclose(pArchivo);
    }
    else
    {
        printf(" ERROR en la lectura del archivo. \n\n");
    }

    return numPerfilesUnicos;
}

void modificarEmpleadoEnArchivo(char nombreArchivo[], char dniEmpleado[])
{
    empleados_laboratorio auxReg;
    int flag = 0;
    FILE *pArchivo = fopen(nombreArchivo, "r+b");

    if(pArchivo != NULL)
    {
        while((flag == 0) && (fread(&auxReg, sizeof(empleados_laboratorio), 1, pArchivo) > 0))
        {
            if(strcmp(auxReg.dni, dniEmpleado) == 0)
            {
                flag = 1;
                fseek(pArchivo, (-1) * sizeof(empleados_laboratorio), SEEK_CUR);
                auxReg = editarDatosEmpleado(nombreArchivo, auxReg);
                fwrite(&auxReg, sizeof(empleados_laboratorio), 1, pArchivo);
            }
        }

        fclose(pArchivo);

        if(flag == 0)
        {
            printf("\n El DNI %s no se encuentra registrado o no es v%clido. \n", dniEmpleado, 160);
        }
    }
}

///FUNCIONES AUXILIARES
empleados_laboratorio cargaDatosEmpleado(char nombreArchivo[], empleados_laboratorio emple)
{
    int verificacionApeYnombre = 0;
    int verificacionDni = 0;
    int existeDni = 0;
    int passValido = 0;
    int verficacionPerfil = 0;

    while(verificacionApeYnombre != 1)
    {
        system("cls");

        printf("\n CARGANDO DATOS DEL EMPLEADO.... \n");

        printf("\n Ingresar apellido y nombre: ");
        fflush(stdin);
        gets(emple.apeYnombre);

        verificacionApeYnombre = verificarApeYNombre(emple.apeYnombre);

        if(verificacionApeYnombre != 1)
        {
            printf("\n El apellido o nombre ingresado no es v%clido. ", 160);
            printf("\n\n");
            system("pause");
        }
    }

    while(verificacionDni != 1 || existeDni == 1)
    {
        system("cls");

        printf("\n CARGANDO DATOS DEL EMPLEADO.... \n");

        printf("\n Ingresar DNI: ");
        fflush(stdin);
        gets(emple.dni);

        existeDni = verificarExistenciaEmpleado(nombreArchivo, emple.dni);
        verificacionDni = verificarDni(emple.dni);

        if(existeDni == 1)
        {
            printf("\n El DNI ya se encuentra registrado.");
            printf("\n\n");
            system("pause");
        }
        else
        {
            existeDni = 0;
        }

        if(verificacionDni != 1)
        {
            printf("\n El DNI ingresado no es v%clido.", 160);
            printf("\n\n");
            system("pause");
        }
    }

    strcpy(emple.userEmpleado, emple.dni);

    while(passValido != 1)
    {
        system("cls");

        printf("\n CARGANDO DATOS DEL EMPLEADO.... \n");

        printf("\n Ingresar contrase%ca (Max 8 caracteres): ", 164);
        fflush(stdin);
        gets(emple.passEmpleado);

        passValido = verficarPassEmpleado(emple.passEmpleado);

        if(passValido != 1)
        {
            printf("\n Has ingresado una contrase%ca inv%clida o has superado el l%cmite de caracteres permitido. ", 164, 160, 161);
            printf("\n\n");
            system("pause");
        }
    }

    while(verficacionPerfil != 1)
    {
        system("cls");

        printf("\n CARGANDO DATOS DEL EMPLEADO.... \n");

        printf("\n Ingresar perfil: ");
        fflush(stdin);
        fgets(emple.perfil, sizeof(emple.perfil), stdin);
        emple.perfil[strcspn(emple.perfil, "\n")] = 0;

        verficacionPerfil = verificarPerfilEmpleado(emple.perfil);

        if(verficacionPerfil != 1 || emple.perfil == 32)
        {
            printf("\n El perfil ingresado no es v%clido. ", 160);
            printf("\n\n");
            system("pause");
        }
    }

    crearUsuarioEmpleado(emple);
    emple.estado = 1;

    return emple;
}

void mostrarUnEmpleado(empleados_laboratorio emple)
{
    printf("===========================================================\n");
    printf(" Apellido y nombre..........: %s \n", emple.apeYnombre);
    printf(" DNI........................: %s \n", emple.dni);
    printf(" Usuario....................: %s \n", emple.userEmpleado);
   // printf(" Password...................: %s \n", emple.passEmpleado);
    printf(" Password...................:********\n");
    printf(" Perfil.....................: %s \n", emple.perfil);

    if(emple.estado == 1)
    {
        printf(" Estado.....................: ALTA \n");
    }
    else
    {
        printf(" Estado.....................: BAJA \n");
    }
    printf("===========================================================\n\n");
}

int calculaCantRegistros(char nombreArchivo[], int tamDato)
{
    int totalRegistros = 0;
    FILE *pArchivo = fopen(nombreArchivo, "rb");

    if(pArchivo != NULL)
    {
        fseek(pArchivo, tamDato - 1, SEEK_END);
        totalRegistros = ftell(pArchivo) / tamDato;
        fclose(pArchivo);
    }

    return totalRegistros;
}

/// FUNCIONES DE VERIFICACIONES
int verificarExistenciaEmpleado(char nombreArchivo[], char dniEmpleado[])
{
    int existeEmple = 0;
    empleados_laboratorio auxEmple;
    FILE *pArchivo = fopen(nombreArchivo, "rb");

    if(pArchivo != NULL)
    {
        while((fread(&auxEmple, sizeof(empleados_laboratorio), 1, pArchivo) > 0) && (existeEmple == 0))
        {
            if(strcmpi(auxEmple.dni, dniEmpleado) == 0)
            {
                existeEmple = 1;
            }
        }
        fclose(pArchivo);
    }

    return existeEmple;
}

int verificarApeYNombre(char apeYnombreEmpleado[])
{
    int apeYnombreValido = 1;
    int longitud = strlen(apeYnombreEmpleado); //obtengo la longitud del nombre y el apellido

    if((longitud == 0) || (apeYnombreEmpleado[0] == 32) || (longitud < 3) || (longitud > 30))
    {
        apeYnombreValido = 0;
    }
    else
    {
        int i = 0;

        while((i < longitud) && (apeYnombreValido == 1))
        {
            //utilizo el código ascii para verificar que no ingrese algún caracter especial o número
            if((apeYnombreEmpleado[i] >= 65 && apeYnombreEmpleado[i] <= 90) || (apeYnombreEmpleado[i] == -91) || (apeYnombreEmpleado[i] >= 97 && apeYnombreEmpleado[i] <= 122) || (apeYnombreEmpleado[i] == -92 ) || (apeYnombreEmpleado[i] == 32))
            {
                i++;
            }
            else
            {
                apeYnombreValido = 0;
            }
        }
    }

    return apeYnombreValido;
}

int verificarDni(char dniEmple[])
{
    int dniValido = 1; //arranco en 1 porque supongo que el dni ingresado es válido
    int longitud = strlen(dniEmple);
    int i = 0;

    if((longitud < 7 || longitud > 7) && (longitud < 8 || longitud > 8))  // verificamos que el dni tenga una longitud de 7 u 8
    {
        dniValido = 0;
    }
    else
    {
        while((i < longitud) && (dniValido == 1))
        {
            if((dniEmple[i] >= 48 && dniEmple[i] <= 57) && (dniEmple[0] != '0'))  //utilizo el código ascii para verificar que solo se ingrese números
            {
                i++;
            }
            else
            {
                dniValido = 0;
            }
        }
    }

    return dniValido;
}

int verificarExistenciaUsuarioEmpleado(char nombreArchivo[], char usuarioEmpleado[])
{
    int existeUsuarioEmpleado = 0;
    empleados_laboratorio aux;
    FILE *pArchivo = fopen(nombreArchivo, "rb");

    if(pArchivo != NULL)
    {
        while((fread(&aux, sizeof(empleados_laboratorio), 1, pArchivo) > 0) && (existeUsuarioEmpleado == 0))
        {
            if(strcmpi(aux.userEmpleado, usuarioEmpleado) == 0)
            {
                existeUsuarioEmpleado = 1;
            }
        }
        fclose(pArchivo);
    }

    return existeUsuarioEmpleado;
}

int verficarPassEmpleado(char passEmple[])
{
    int longitudPass = strlen(passEmple);
    int passValido = 1;
    int i = 0;

    if(longitudPass > 8 || longitudPass == 0)
    {
        passValido = 0;
    }
    else
    {
        while((i < longitudPass) && (passValido == 1))
        {
            if(passEmple[i] == 32)
            {
                passValido = 0;
            }
            else
            {
                i++;
            }
        }
    }

    return passValido;
}

int verificarPerfilEmpleado(char perfilEmpleado[])
{
    int perfilValido = 0;
    int longitudPerfil = strlen(perfilEmpleado);
    char *perfilMin = (char*)malloc(sizeof(char) * longitudPerfil + 1); //le sumo 1 para agregar el caracter nulo

    if(perfilMin != NULL)
    {
        int i;

        for(i=0 ; perfilEmpleado[i] ; i++)
        {
            perfilMin[i] = tolower(perfilEmpleado[i]); //convierto toda la cadena a minúscula
        }

        perfilMin[strlen(perfilEmpleado)] = '\0'; //agrego el caracter para indicar el final del string

        if((strcmp(perfilMin, "administrativo") == 0) ||
                (strcmp(perfilMin, "tecnico") == 0) ||
                (strcmp(perfilMin, "bioquimico") == 0))
        {

            perfilValido = 1;
        }
    }
    else
    {
        printf(" ERROR. No es posible asignar memoria. \n\n");
    }

    return perfilValido;
}

int menuEdicionDatosEmpleado()
{
    int opcion;

    printf("\n EDICION DE DATOS DEL EMPLEADO: \n\n");

    printf(" 1. Editar apellido y nombre \n");
    printf(" 2. Editar DNI \n");
    printf(" 3. Editar contrase%ca \n", 164);
    printf(" 4. Editar perfil \n");
    printf(" 5. Dar de BAJA al empleado \n");
    printf(" 6. Dar de ALTA al empleado \n");
    printf(" 0. Salir \n\n");

    printf(" Ingresar opci%cn: ", 162);
    scanf("%d", &opcion);

    return opcion;
}

empleados_laboratorio editarDatosEmpleado(char nombreArchivo[], empleados_laboratorio emple)
{
    empleados_laboratorio aux = emple;
    char continuar = 's';
    int opcionEditarDatos;
    int verifApeYnombreNuevo = 0;
    int verifDniNuevo = 0;
    int existeNuevoDni = 0;
    int verifPassNuevo = 0;
    int verifPerfilNuevo = 0;

    printf("\n El empleado a modificar es: \n\n");
    mostrarUnEmpleado(aux);

    system("pause");

    while((continuar == 's' || continuar == 'S') && opcionEditarDatos != 0)
    {
        system("cls");

        opcionEditarDatos = menuEdicionDatosEmpleado();

        if(opcionEditarDatos == 1)
        {
            while(verifApeYnombreNuevo != 1)
            {
                system("cls");

                printf("\n Ingresar apellido y nombre: ");
                fflush(stdin);
                gets(aux.apeYnombre);

                verifApeYnombreNuevo = verificarApeYNombre(aux.apeYnombre);

                if(verifApeYnombreNuevo != 1)
                {
                    printf("\n El apellido o nombre ingresado no es v%clido. ", 160);
                    printf("\n\n");
                    system("pause");
                }
            }
        }
        else if(opcionEditarDatos == 2)
        {
            while(verifDniNuevo != 1 || existeNuevoDni == 1)
            {
                system("cls");

                printf("\n Ingresar DNI: ");
                fflush(stdin);
                gets(aux.dni);

                existeNuevoDni = verificarExistenciaEmpleado(nombreArchivo, aux.dni);
                verifDniNuevo = verificarDni(aux.dni);

                if(existeNuevoDni == 1)
                {
                    printf("\n El DNI ya se encuentra registrado.");
                    printf("\n\n");
                    system("pause");
                }

                if(verifDniNuevo != 1)
                {
                    printf("\n El DNI ingresado no es v%clido.", 160);
                    printf("\n\n");
                    system("pause");
                }
            }

            strcpy(aux.userEmpleado, aux.dni);

        }
        else if(opcionEditarDatos == 3)
        {
            while(verifPassNuevo != 1)
            {
                system("cls");

                printf("\n Ingresar contrase%ca (Max 8 caracteres): ", 164);
                fflush(stdin);
                gets(aux.passEmpleado);

                verifPassNuevo = verficarPassEmpleado(aux.passEmpleado);

                if(verifPassNuevo != 1)
                {
                    printf("\n Has ingresado una contrase%ca inv%clida o has superado el l%cmite de caracteres permitido. ", 164, 160, 161);
                    printf("\n\n");
                    system("pause");
                }
            }
        }
        else if(opcionEditarDatos == 4)
        {
            while(verifPerfilNuevo != 1)
            {
                system("cls");

                printf("\n Ingresar perfil: ");
                fflush(stdin);
                fgets(aux.perfil, sizeof(aux.perfil), stdin);
                aux.perfil[strcspn(aux.perfil, "\n")] = 0;

                verifPerfilNuevo = verificarPerfilEmpleado(aux.perfil);

                if(verifPerfilNuevo != 1 || aux.perfil == 32)
                {
                    printf("\n El perfil ingresado no es v%clido. ", 160);
                    printf("\n\n");
                    system("pause");
                }
            }
        }
        else if(opcionEditarDatos == 5)
        {
            aux.estado = 0;
        }
        else if(opcionEditarDatos == 6)
        {
            aux.estado = 1;
        }
        else if(opcionEditarDatos != 0)
        {
            printf("\n OPCI%cN NO V%cLIDA. \n\n", 224, 181);
            system("pause");
        }

        if(opcionEditarDatos >= 1 && opcionEditarDatos <= 6)
        {
            printf("\n %cQuieres modificar otro dato del empleado? s= SI / n=NO ", 168);
            fflush(stdin);
            continuar = getch();
        }
    }

    if(opcionEditarDatos != 0)
    {
        system("cls");
        printf(" \n CAMBIO/S REALIZADO CON %cXITO: \n\n", 144);
        mostrarUnEmpleado(aux);
        system("pause");
    }

    return aux;
}
