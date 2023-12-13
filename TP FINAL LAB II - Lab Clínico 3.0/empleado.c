#include "empleado.h"

//crea un usuario empleado
void crearUsuarioEmpleado(char dni[],char contra[],char perfil[])
{
    UsuarioEmpleado aux;
    FILE* archiEmpleados = fopen("UsuariosEmpleados.dat", "ab");

    if(archiEmpleados)
    {
        if(strcmpi(perfil,"administrativo")==0)
        {
            strcpy(aux.usuarioEmpleado,dni);
            strcpy(aux.contraEmpleado,contra);
            aux.nivel=1;

            fwrite(&aux,sizeof(UsuarioEmpleado),1,archiEmpleados);
        }
        else
        {
            strcpy(aux.usuarioEmpleado,dni);
            strcpy(aux.contraEmpleado,contra);
            aux.nivel=2;

            fwrite(&aux,sizeof(UsuarioEmpleado),1,archiEmpleados);
        }


        fclose(archiEmpleados);
    }

}
//cambia la contraseña del usuario empleado
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
                printf(" Ingrese nueva contrasenia: ");
                fflush(stdin);
                gets(empleado.contraEmpleado);
                printf(" Ingrese nuevamente contrasenia: ");
                fflush(stdin);
                gets(comprobacion);

                // Verifica que las contraseñas coincidan
                if (strcmp(empleado.contraEmpleado, comprobacion) == 0)
                {
                    usuarioEncontrado = 1;  // Marcar que se encontró el usuario
                    // Actualizar en archiUsua
                    fseek(archiUsua, (-1) * sizeof(UsuarioEmpleado), SEEK_CUR);
                    fwrite(&empleado, sizeof(UsuarioEmpleado), 1, archiUsua);

                    // No salimos del bucle aquí para seguir con la actualización del archivo de empleados
                }
                else
                {
                    printf("\n Las contrasen%cas no coinciden, vuelva a intentarlo. \n\n" , 164);
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

                    fseek(archiEmpledo, (-1) * sizeof(empleados_laboratorio), SEEK_CUR);
                    strcpy(registroEmple.passEmpleado,empleado.contraEmpleado);
                    fwrite(&registroEmple, sizeof(empleados_laboratorio), 1, archiEmpledo);
                    break;  // Salir del bucle después de encontrar y actualizar el registro
                }
            }

            printf("\n Contrase%ca actualizada exitosamente.\n\n" , 164);
        }

        fclose(archiUsua);
        fclose(archiEmpledo);
    }
    else
    {
        printf("No se pudieron abrir los archivos. \n\n");
    }
}

//============================================================================================================================//

/// --------------------------------------- FUNCIONES DE ARCHIVOS (EMPLEADO) --------------------------------------- ///

//carga el archivo de empleados
void cargarArchEmpleados(char nombreArchivo[])
{
    empleados_laboratorio emple;

    agregarEmpleados(nombreArchivo , emple);
}

//muestra todos los empleados del archivo
void mostrarArchEmpleados(char nombreArchivo[])
{
    empleados_laboratorio aux;
    FILE *pArchivo = fopen(nombreArchivo , "rb");

    if(pArchivo != NULL){
        while(fread(&aux , sizeof(empleados_laboratorio) , 1 , pArchivo) > 0){
            mostrarUnEmpleado(aux);
        }
        fclose(pArchivo);
    }else{
        printf(" ERROR en la lectura del archivo. \n\n");
    }
}

void mostrarArchEmpleadosSinContra(char nombreArchivo[])
{
    empleados_laboratorio aux;
    FILE *pArchivo = fopen(nombreArchivo, "rb");

    if(pArchivo != NULL)
    {
        while(fread(&aux, sizeof(empleados_laboratorio), 1, pArchivo) > 0)
        {
            mostrarUnEmpleadoSinContra(aux);
        }
        fclose(pArchivo);
    }
    else
    {
        printf(" ERROR en la lectura del archivo. \n\n");
    }
}

//modifica un empleado
void modificarEmpleadoEnArchivo(char nombreArchivo[] , char dniEmpleado[])
{
    empleados_laboratorio auxReg;
    int flag = 0;
    FILE *pArchivo = fopen(nombreArchivo , "r+b");

    if(pArchivo != NULL){
        while((flag == 0) && (fread(&auxReg , sizeof(empleados_laboratorio) , 1 , pArchivo) > 0)){
            if(strcmp(auxReg.dni , dniEmpleado) == 0){
                flag = 1;
                fseek(pArchivo , (-1) * sizeof(empleados_laboratorio) , SEEK_CUR);
                auxReg = editarDatosEmpleado(nombreArchivo , auxReg);
                fwrite(&auxReg , sizeof(empleados_laboratorio) , 1 , pArchivo);
            }
        }

        fclose(pArchivo);

        if(flag == 0){
            printf("\n El DNI %s no se encuentra registrado o no es v%clido. \n" , dniEmpleado , 160);
        }
    }
}

/// --------------------------------------- FIN FUNCIONES DE ARCHIVOS (EMPLEADO) --------------------------------------- ///

//============================================================================================================================//

/// ----------------------------------- FUNCIONES AUXILIARES DE ARCHIVOS (EMPLEADO) ------------------------------------ ///

empleados_laboratorio cargaDatosEmpleado(char nombreArchivo[] , empleados_laboratorio emple)
{
    int verificacionApeYnombre = 0;
    int verificacionDni = 0;
    int existeDni = 0;
    int passValido = 0;
    int verficacionPerfil = 0;

    while(verificacionApeYnombre != 1){
        system("cls");

        printf("\n CARGANDO DATOS DEL EMPLEADO.... \n");

        printf("\n Ingresar apellido y nombre: ");
        fflush(stdin);
        gets(emple.apeYnombre);

        verificacionApeYnombre = verificarApeYNombre(emple.apeYnombre);

        if(verificacionApeYnombre != 1){
            printf("\n El apellido o nombre ingresado no es v%clido. " , 160);
            printf("\n\n");
            system("pause");
        }
    }

    while(verificacionDni != 1 || existeDni == 1){
        system("cls");

        printf("\n CARGANDO DATOS DEL EMPLEADO.... \n");

        printf("\n Ingresar DNI: ");
        fflush(stdin);
        gets(emple.dni);

        existeDni = verificarExistenciaEmpleado(nombreArchivo , emple.dni);
        verificacionDni = verificarDni(emple.dni);

        if(existeDni == 1){
            printf("\n El DNI ya se encuentra registrado.");
            printf("\n\n");
            system("pause");
        }else{
            existeDni = 0;
        }

        if(verificacionDni != 1){
            printf("\n El DNI ingresado no es v%clido." , 160);
            printf("\n\n");
            system("pause");
        }
    }

    strcpy(emple.userEmpleado , emple.dni);

    while(passValido != 1){
        system("cls");

        printf("\n CARGANDO DATOS DEL EMPLEADO.... \n");

        printf("\n Ingresar contrase%ca (Max 8 caracteres): " , 164);
        fflush(stdin);
        gets(emple.passEmpleado);

        passValido = verficarPassEmpleado(emple.passEmpleado);

        if(passValido != 1){
            printf("\n Has ingresado una contrase%ca inv%clida o has superado el l%cmite de caracteres permitido. " , 164 , 160 , 161);
            printf("\n\n");
            system("pause");
        }
    }

    while(verficacionPerfil != 1){
        system("cls");

        printf("\n CARGANDO DATOS DEL EMPLEADO.... \n");

        printf("\n Ingresar perfil: ");
        fflush(stdin);
        fgets(emple.perfil , sizeof(emple.perfil) , stdin);
        emple.perfil[strcspn(emple.perfil , "\n")] = 0;

        verficacionPerfil = verificarPerfilEmpleado(emple.perfil);

        if((verficacionPerfil != 1) || (emple.perfil == 32)){
            printf("\n El perfil ingresado no es v%clido. " , 160);
            printf("\n\n");
            system("pause");
        }
    }

    emple.estado = 1;

    crearUsuarioEmpleado(emple.dni,emple.passEmpleado,emple.perfil);

    return emple;
}

//guarda el tipo de dato empleado en el archivo
void guardarUnEmpleado(char nombreArchivo[] , empleados_laboratorio emple)
{
    FILE *pArchivo = fopen(nombreArchivo , "ab");

    if(pArchivo != NULL){
        fwrite(&emple , sizeof(empleados_laboratorio) , 1 , pArchivo);
        fclose(pArchivo);

        printf("\n DATOS DEL EMPLEADO: \n\n");
        mostrarUnEmpleado(emple);

        printf("\n EMPLEADO CARGADO CON %cXITO \n\n" , 144);

    }else{
        printf(" ERROR en la apertura del archivo. \n\n");
    }
}

//carga un nuevo empleado en el archivo
void agregarEmpleados(char nombreArchivo[] , empleados_laboratorio nuevo)
{
    char continuar = 's';

    while(continuar == 's' || continuar == 'S'){
        system("cls");

        nuevo = cargaDatosEmpleado(nombreArchivo , nuevo);

        system("cls");

        guardarUnEmpleado(nombreArchivo , nuevo);

        printf("\n %cQuires agregar un nuevo empleado? s=SI / n=NO " , 168);
        fflush(stdin);
        continuar = getch();
        printf("\n\n");
    }
}

//muestra un empleado
void mostrarUnEmpleado(empleados_laboratorio emple)
{
    printf("===========================================================\n");
    printf(" Apellido y nombre..........: %s \n" , emple.apeYnombre);
    printf(" DNI........................: %s \n" , emple.dni);
    printf(" Usuario....................: %s \n" , emple.userEmpleado);
    printf(" Password...................: %s \n" , emple.passEmpleado);
    printf(" Perfil.....................: %s \n" , emple.perfil);

    if(emple.estado == 1){
        printf(" Estado.....................: ALTA \n");
    }else{
        printf(" Estado.....................: BAJA \n");
    }
    printf("===========================================================\n\n");
}

void mostrarUnEmpleadoSinContra(empleados_laboratorio emple)
{
    printf("===========================================================\n");
    printf(" Apellido y nombre..........: %s \n", emple.apeYnombre);
    printf(" DNI........................: %s \n", emple.dni);
    printf(" Usuario....................: %s \n", emple.userEmpleado);
    printf(" Password...................: ******** \n");
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

/// ---------------------------------- FIN FUNCIONES AUXILIARES DE ARCHIVOS (EMPLEADO) ---------------------------------- ///

//============================================================================================================================//

/// ------------------------------------- FUNCIONES DE VERIFICACIONES - EMPLEADO ------------------------------------- ///

//verifica si ya se encuentra registrado un empelado en el archivo
int verificarExistenciaEmpleado(char nombreArchivo[] , char dniEmpleado[])
{
    int existeEmple = 0;
    empleados_laboratorio auxEmple;
    FILE *pArchivo = fopen(nombreArchivo , "rb");

    if(pArchivo != NULL){
        while((fread(&auxEmple , sizeof(empleados_laboratorio) , 1 , pArchivo) > 0) && (existeEmple == 0)){
            if(strcmpi(auxEmple.dni , dniEmpleado) == 0){
                existeEmple = 1;
            }
        }
        fclose(pArchivo);
    }

    return existeEmple;
}

//verifica que el nombre y el apellido del empelado no contenga algún caracter especial o número
int verificarApeYNombre(char apeYnombreEmpleado[])
{
    int apeYnombreValido = 1;
    int longitud = strlen(apeYnombreEmpleado); //obtengo la longitud del nombre y el apellido

    if((longitud == 0) || (apeYnombreEmpleado[0] == 32) || (longitud < 3) || (longitud > 30)){
        apeYnombreValido = 0;
    }else{
        int i = 0;

        while((i < longitud) && (apeYnombreValido == 1)){
            //utilizo el código ascii para verificar que no ingrese algún caracter especial o número
            if((apeYnombreEmpleado[i] >= 65 && apeYnombreEmpleado[i] <= 90) || (apeYnombreEmpleado[i] == -91) || (apeYnombreEmpleado[i] >= 97 && apeYnombreEmpleado[i] <= 122) || (apeYnombreEmpleado[i] == -92 ) || (apeYnombreEmpleado[i] == 32)){
                i++;
            }else{
                apeYnombreValido = 0;
            }
        }
    }

    return apeYnombreValido;
}

//verifica que el DNI sea de la longintud correcta y no tenga ningun caracter especial o letra
int verificarDni(char dniEmple[])
{
    int dniValido = 1; //arranco en 1 porque supongo que el dni ingresado es válido
    int longitud = strlen(dniEmple);
    int i = 0;

    if((longitud < 7 || longitud > 7) && (longitud < 8 || longitud > 8)){ // verificamos que el dni tenga una longitud de 7 u 8
        dniValido = 0;
    }else{
        while((i < longitud) && (dniValido == 1)){
            if((dniEmple[i] >= 48 && dniEmple[i] <= 57) && (dniEmple[0] != '0')){ //utilizo el código ascii para verificar que solo se ingrese números
                i++;
            }else{
                dniValido = 0;
            }
        }
    }

    return dniValido;
}

//verifica que el password no este registrado
int verficarPassEmpleado(char passEmple[])
{
    int longitudPass = strlen(passEmple);
    int passValido = 1;
    int i = 0;

    if(longitudPass < 4 || longitudPass > 8 || longitudPass == 0){
        passValido = 0;
    }else{
        while((i < longitudPass) && (passValido == 1)){
            if(passEmple[i] == 32){
                passValido = 0;
            }else{
                i++;
            }
        }
    }

    return passValido;
}

//verifica que el perfil asignado al empleado sea el correcto (administrativo , técnico o bioquímico)
int verificarPerfilEmpleado(char perfilEmpleado[])
{
    int perfilValido = 0;
    int longitudPerfil = strlen(perfilEmpleado);
    char *perfilMin = (char*)malloc(sizeof(char) * longitudPerfil + 1); //le sumo 1 para agregar el caracter nulo

    if(perfilMin != NULL){
        int i;

        for(i=0 ; perfilEmpleado[i] ; i++){
            perfilMin[i] = tolower(perfilEmpleado[i]); //convierto toda la cadena a minúscula
        }

        perfilMin[strlen(perfilEmpleado)] = '\0'; //agrego el caracter para indicar el final del string

        if((strcmp(perfilMin , "administrativo") == 0) ||
            (strcmp(perfilMin , "tecnico") == 0) ||
            (strcmp(perfilMin , "bioquimico") == 0)){

            perfilValido = 1;
        }
    }else{
        printf(" ERROR. No es posible asignar memoria. \n\n");
    }

    return perfilValido;
}

//verifica la si existe el usuario tipo empleado
int verificarExistenciaUsuarioEmpleado(char nombreArchivo[] , char usuarioEmpleado[])
{
    int existeUsuarioEmpleado = 0;
    empleados_laboratorio aux;
    FILE *pArchivo = fopen(nombreArchivo , "rb");

    if(pArchivo != NULL){
        while((fread(&aux , sizeof(empleados_laboratorio) , 1 , pArchivo) > 0) && (existeUsuarioEmpleado == 0)){
            if(strcmpi(aux.userEmpleado , usuarioEmpleado) == 0){
                existeUsuarioEmpleado = 1;
            }
        }
        fclose(pArchivo);
    }

    return existeUsuarioEmpleado;
}
/// ------------------------------------ FIN FUNCIONES DE VERIFICACIONES - EMPLEADO ------------------------------------ ///

//============================================================================================================================//

/// ------------------------------------- FUNCIONES DE EDICION DE DATOS - EMPLEADO ------------------------------------- ///

//menú que muestra por patalla las opciones para editar los datos de un empleado
int menuEdicionDatosEmpleado()
{
    int opcion;

    printf("\n EDICION DE DATOS DEL EMPLEADO: \n\n");

    printf(" 1. Editar apellido y nombre \n");
    printf(" 2. Editar DNI \n");
    printf(" 3. Editar contrase%ca \n" , 164);
    printf(" 4. Editar perfil \n");
    printf(" 0. Salir \n\n");

    printf(" Ingresar opci%cn: " , 162);
    scanf("%d" , &opcion);

    return opcion;
}

//edita los datos del empleado
empleados_laboratorio editarDatosEmpleado(char nombreArchivo[] , empleados_laboratorio emple)
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

    while((continuar == 's' || continuar == 'S') && (opcionEditarDatos != 0)){
        system("cls");

        opcionEditarDatos = menuEdicionDatosEmpleado();

        if(opcionEditarDatos == 1){
            while(verifApeYnombreNuevo != 1){
                system("cls");

                printf("\n Ingresar apellido y nombre: ");
                fflush(stdin);
                gets(aux.apeYnombre);

                verifApeYnombreNuevo = verificarApeYNombre(aux.apeYnombre);

                if(verifApeYnombreNuevo != 1){
                    printf("\n El apellido o nombre ingresado no es v%clido. " , 160);
                    printf("\n\n");
                    system("pause");
                }
            }
        }else if(opcionEditarDatos == 2){
            while(verifDniNuevo != 1 || existeNuevoDni == 1){
                system("cls");

                printf("\n Ingresar DNI: ");
                fflush(stdin);
                gets(aux.dni);

                existeNuevoDni = verificarExistenciaEmpleado(nombreArchivo , aux.dni);
                verifDniNuevo = verificarDni(aux.dni);

                if(existeNuevoDni == 1){
                    printf("\n El DNI ya se encuentra registrado.");
                    printf("\n\n");
                    system("pause");
                }

                if(verifDniNuevo != 1){
                    printf("\n El DNI ingresado no es v%clido." , 160);
                    printf("\n\n");
                    system("pause");
                }
            }

            strcpy(aux.userEmpleado , aux.dni);

        }else if(opcionEditarDatos == 3){
            while(verifPassNuevo != 1){
                system("cls");

                printf("\n Ingresar contrase%ca (Max 8 caracteres): " , 164);
                fflush(stdin);
                gets(aux.passEmpleado);

                verifPassNuevo = verficarPassEmpleado(aux.passEmpleado);

                if(verifPassNuevo != 1){
                    printf("\n Has ingresado una contrase%ca inv%clida o has superado el l%cmite de caracteres permitido. " , 164 , 160 , 161);
                    printf("\n\n");
                    system("pause");
                }
            }
        }else if(opcionEditarDatos == 4){
            while(verifPerfilNuevo != 1){
                system("cls");

                printf("\n Ingresar perfil: ");
                fflush(stdin);
                fgets(aux.perfil , sizeof(aux.perfil) , stdin);
                aux.perfil[strcspn(aux.perfil , "\n")] = 0;

                verifPerfilNuevo = verificarPerfilEmpleado(aux.perfil);

                if((verifPerfilNuevo != 1) || (aux.perfil == 32)){
                    printf("\n El perfil ingresado no es v%clido. " , 160);
                    printf("\n\n");
                    system("pause");
                }
            }

        }else if(opcionEditarDatos != 0){
            printf("\n OPCI%cN NO V%cLIDA. \n\n" , 224 , 181);
            system("pause");
        }

        if(opcionEditarDatos >= 1 && opcionEditarDatos <= 4){
            printf("\n %cQuieres modificar otro dato del empleado? s= SI / n=NO " , 168);
            fflush(stdin);
            continuar = getch();
        }
    }

    if(opcionEditarDatos == 0){
        system("cls");
        printf(" \n CAMBIO/S REALIZADO CON %cXITO: \n\n" , 144);
        mostrarUnEmpleado(aux);
        system("pause");
    }

    return aux;
}

//da de baja un empleado
void darBajaEmpleadoArch(char nombreArchivo[] , char dniEmpleado[])
{
    empleados_laboratorio auxRegEmpleado;
    empleados_laboratorio emple;
    int flag = 0;
    FILE *pArchivoEmple = fopen(nombreArchivo , "r+b");

    if(pArchivoEmple != NULL){
        while((flag == 0) && (fread(&auxRegEmpleado , sizeof(empleados_laboratorio) , 1 , pArchivoEmple) > 0)){
            if(strcmp(auxRegEmpleado.dni , dniEmpleado) == 0){
                flag = 1;
                auxRegEmpleado.estado = 0;
                emple = auxRegEmpleado;
            }
        }
        fseek(pArchivoEmple , (-1) * sizeof(empleados_laboratorio) , SEEK_CUR);
        fwrite(&emple , sizeof(empleados_laboratorio) , 1 , pArchivoEmple);
        fclose(pArchivoEmple);
    }

    system("cls");
    printf("\n EMPLEADO DADO DE BAJA CON %cXITO. \n\n" , 144);
    mostrarUnEmpleado(emple);
}

//da de alta un empleado
void darAltaEmpleadoArch(char nombreArchivo[] , char dniEmpleado[])
{
    empleados_laboratorio auxRegEmpleado;
    empleados_laboratorio emple;
    int flag = 0;
    FILE *pArchivoEmple = fopen(nombreArchivo , "r+b");

    if(pArchivoEmple != NULL){
        while((flag == 0) && (fread(&auxRegEmpleado , sizeof(empleados_laboratorio) , 1 , pArchivoEmple) > 0)){
            if(strcmp(auxRegEmpleado.dni , dniEmpleado) == 0){
                flag = 1;
                auxRegEmpleado.estado = 1;
                emple = auxRegEmpleado;
            }
        }
        fseek(pArchivoEmple , (-1) * sizeof(empleados_laboratorio) , SEEK_CUR);
        fwrite(&emple , sizeof(empleados_laboratorio) , 1 , pArchivoEmple);
        fclose(pArchivoEmple);
    }

    system("cls");
    printf("\n EMPLEADO DADO DE ALTA CON %cXITO. \n\n" , 144);
    mostrarUnEmpleado(emple);
}

/// ----------------------------------- FIN FUNCIONES DE EDICION DE DATOS - EMPLEADO ----------------------------------- ///

//============================================================================================================================//

/// --------------------------------------- FUNCIONES EXTRAS --------------------------------------- ///

//retorna la cantidad total de registros de un archivo
int calculaCantRegistros(char nombreArchivo[] , int tamDato)
{
   int totalRegistros = 0;
   FILE *pArchivo = fopen(nombreArchivo , "rb");

   if(pArchivo != NULL){
        fseek(pArchivo , tamDato - 1 , SEEK_END);
        totalRegistros = ftell(pArchivo) / tamDato;
        fclose(pArchivo);
   }

   return totalRegistros;
}
/// ------------------------------------- FIN FUNCIONES EXTRAS ------------------------------------- ///
