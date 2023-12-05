#include "paciente.h"

/// ---------------------------- FUNCIONES PACIENTE ----------------------------------------------- ///
void crearUsuarioPaciente(paciente pacienteUsu)
{
    UsuarioPaciente usuarioP;
    FILE* archiUsuarios=fopen("UsuariosPacientes.dat","ab");


    if(archiUsuarios)
    {
        strcpy(usuarioP.usuarioPaciente,pacienteUsu.dni);
        strcpy(usuarioP.contrasenia, pacienteUsu.dni);//contraseña por default
        usuarioP.nivel=0;//dejo el inicio en 0 aunque me llene con basura
        fwrite(&usuarioP,sizeof(UsuarioPaciente),1,archiUsuarios);

        fclose(archiUsuarios);
    }
}
void cambiarContraseniaPacientes(char archivoUsuPaciente[30], UsuarioPaciente usuPaciente)
{
    UsuarioPaciente registroPaciente;

    FILE *archiUsuaPaciente = fopen(archivoUsuPaciente, "r+b");

    if (archiUsuaPaciente != NULL)
    {
        char comprobacion[8];
        while (fread(&registroPaciente, sizeof(UsuarioPaciente), 1, archiUsuaPaciente))
        {
            if (strcmp(registroPaciente.usuarioPaciente, usuPaciente.usuarioPaciente) == 0)
            {
                printf("Ingrese nueva contrasenia:\n");
                fflush(stdin);
                gets(usuPaciente.contrasenia);
                printf("Ingrese nuevamente contrasenia:\n");
                fflush(stdin);
                gets(comprobacion);

                if (strcmp(usuPaciente.contrasenia, comprobacion) == 0)
                {
                    // Actualizar en archiUsuaPaciente
                    fseek(archiUsuaPaciente, -sizeof(UsuarioPaciente), SEEK_CUR);
                    fwrite(&usuPaciente, sizeof(UsuarioPaciente), 1, archiUsuaPaciente);

                    printf("Contrasenia actualizada exitosamente.\n");

                    break;  // Salir del bucle después de encontrar y actualizar el registro
                }
                else
                {
                    printf("Las contrasenias no coinciden, vuelva a intentarlo\n");
                    break;
                }
            }
        }

        fclose(archiUsuaPaciente);
    }
    else
    {
        printf("No se pudo abrir el archivo de usuarios de pacientes.\n");
    }
}
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
            if(!isalnum(direccion[i]) && direccion[i]!= ' ') // la funcion isalnum verifica que la direccion no tenga ningun caracter especial solo letras y numeros
            {
                flag=0;
            }
        }
    }

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
        persona=cargaPaciente(nombreArchivo);
        guardaUnaPersona(nombreArchivo,persona);

        printf("\n %cDesea cargar otro paciente? S/N " , 168);
        fflush(stdin);
        continuar=getch();
        printf("\n\n");
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

paciente cargaPaciente(char nombreArchivo[])
{
    paciente nuevoPaciente;
    int nombreOk=0;
    int edadOk=0;
    char entradaEdad[11];
    int i=0;
    int flag = 0;
    int dniOk=0;
    int existeDni=0;
    int direccionOk=0;
    int telOk=0;


        while(nombreOk!=1)
        {
            system("cls");
            printf("\n---------------Cargando datos del Paciente---------------\n");

            printf("\n Ingrese Nombre y Apellido: ");
            fflush(stdin);
            gets(nuevoPaciente.apellidoYnombre);
            nombreOk=verificaNombre(nuevoPaciente.apellidoYnombre);

            if(nombreOk!=1)
            {
                printf("\nEl nombre o apellido ingresado no es valido.\n\n");
                system("pause");
            }

        }

        while(edadOk!=1)
        {
            system("cls");
            printf("\n---------------Cargando datos del Paciente---------------\n");

            printf("\n Ingrese la Edad: ");
            scanf("%i",&nuevoPaciente.edad);

            edadOk=verificaEdad(nuevoPaciente.edad);

            if(edadOk!=1)
            {
                printf("\n Edad no valida, ingrese edad nuevamente.\n\n");
                system("pause");
            }
        }


        while(dniOk!=1 || existeDni==1)
        {
            system("cls");
            printf("\n---------------Cargando datos del Paciente---------------\n");

            printf("\n Ingrese el DNI: ");
            fflush(stdin);
            gets(nuevoPaciente.dni);

            existeDni=verificaExistenciaPaciente(nombreArchivo,nuevoPaciente.dni);
            dniOk=verificaDni(nuevoPaciente.dni);

            if(existeDni==1)
            {
                printf("\n DNI ya registrado.\n\n");
                system("pause");

            }
            else
            {
                existeDni=0;
            }
            if(dniOk!=1)
            {
                printf("\n El DNI ingresado no es valido.\n\n");
                system("pause");
            }

        }

        while(direccionOk!=1)
        {
            system("cls");
            printf("\n---------------Cargando datos del Paciente---------------\n");

            printf("\n Ingrese el domicilio: ");
            gets(nuevoPaciente.direccion);

            direccionOk= verificaDireccion(nuevoPaciente.direccion);

            if(direccionOk!=1)
            {
                printf("\n La direccion ingresada no es correcta. \n\n");
                system("pause");
            }
        }

        while(telOk!=1)
        {
            system("cls");
            printf("\n---------------Cargando datos del Paciente---------------\n");

            printf("\n Ingrese un telefono: ");
            gets(nuevoPaciente.telefono);

            telOk=verificaTelefono(nuevoPaciente.telefono);

            if(telOk!=1)
            {
                printf("\n El telefono ingresado no es correcto.\n\n");
                system("pause");
            }

        }

        nuevoPaciente.eliminados=1;
        crearUsuarioPaciente(nuevoPaciente);

    return nuevoPaciente;
}


void mostrarPaciente(paciente persona)
{
    printf("-----------------------------------------------------\n");
    printf(" Apellido y Nombre---------------: %s\n",persona.apellidoYnombre);
    printf(" Edad----------------------------: %d\n",persona.edad);
    printf(" DNI-----------------------------: %s\n",persona.dni);
    printf(" Direccion-----------------------: %s\n",persona.direccion);
    printf(" Telefono------------------------: %s\n",persona.telefono);
    printf("-----------------------------------------------------\n\n");
}

void mostrarArchPacientes(char nombreArchivo[])
{
    paciente aux;
    FILE *archi=fopen(nombreArchivo,"rb");

    if(archi)
    {
        while(fread(&aux,sizeof(paciente),1,archi)>0)
        {

            if(aux.eliminados==1)
            {
            mostrarPaciente(aux);
            }
        }
        fclose(archi);
    }
    else
    {
        printf("Error al querer leer el archivo.\n\n");
    }
}

void darBajaPacienteArch(char nombreArchivoPac[] , char dniPaciente[])
{
    paciente auxRegPac;
    ///paciente aux;
    int flag = 0;
    FILE* pArchivoPac = fopen(nombreArchivoPac , "r+b");

    if(pArchivoPac != NULL){
        while(fread(&auxRegPac , sizeof(paciente) , 1 , pArchivoPac) > 0)
        {
            if(strcmp(auxRegPac.dni , dniPaciente) == 0)
                {
                flag = 1;
                fseek(pArchivoPac , (-1) * sizeof(paciente) , SEEK_CUR);
                auxRegPac.eliminados = 0;
                fwrite(&auxRegPac , sizeof(paciente) , 1 , pArchivoPac);
                break;
            }
        }
        fclose(pArchivoPac);
    }

    if(flag == 0){
        printf(" El DNI ingresado es incorrecto o el paciente no se encuentra registrado. \n\n");
    }else{
        system("cls");
        printf("\n PACIENTE DADO DE BAJA CON %cXITO. \n\n" , 144);
        mostrarPaciente(auxRegPac);
    }
}

void darAltaPacienteArch(char nombreArchivoPac[] , char dniPaciente[])
{
    paciente auxRegPac;
    paciente aux;
    int flag = 0;
    FILE *pArchivoPac = fopen(nombreArchivoPac , "r+b");

    if(pArchivoPac != NULL){
        while(fread(&auxRegPac , sizeof(paciente) , 1 , pArchivoPac) > 0){
            if(strcmp(auxRegPac.dni , dniPaciente) == 0){
                flag = 1;
                fseek(pArchivoPac , (-1) * sizeof(paciente) , SEEK_CUR);

                auxRegPac.eliminados=1;
                fwrite(&auxRegPac , sizeof(paciente) , 1 , pArchivoPac);
                break;
            }
        }
        fclose(pArchivoPac);
    }

    if(flag == 0){
        printf(" El DNI ingresado es incorrecto o el paciente no se encuentra registrado. \n\n");
    }else{
        system("cls");
        printf("\n PACIENTE DADO DE ALTA CON %cXITO. \n\n" , 144);
        mostrarPaciente(auxRegPac);
    }

}

void modificaPaciente(char nombreArchivo[],char dni[])
{
    int opcion;
    char continuar = 's';
    int nombreOK=0;
    int edadOk=0;
    int direccionOk=0;
    int flag=0;
    int telOk=0;

    FILE *archi=fopen(nombreArchivo,"r+b");
    paciente nuevo;

    if(archi)
    {
        while((flag==0)&& (fread(&nuevo,sizeof(paciente),1,archi)>0))
        {
            if(strcmp(nuevo.dni,nuevo.dni)==0)
            {
                flag=1;
                fseek(archi,(-1*sizeof(paciente)),SEEK_CUR);
            }
        }

        if(flag == 1)
        {
            system("cls");

            printf("\n El paciente a modifiar es: \n\n");
            mostrarPaciente(nuevo);

            system("pause");

            do
            {
            system("cls");

            printf("\n Que desea modificar?\n\n");
            printf(" 1- Apellido y Nombre.\n");
            printf(" 2- Edad.\n");
            printf(" 3- Direccion.\n");
            printf(" 4- Telefono.\n");
            printf(" 5- Salir.\n\n");


            scanf("%d",&opcion);

            switch(opcion)
            {
                case 1:

                while(nombreOK!=1)
                {
                    system("cls");
                    printf("\n Ingrese el nuevo Apellido y Nombre: \n");
                    fflush(stdin);
                    gets(nuevo.apellidoYnombre);
                    nombreOK=verificaNombre(nuevo.apellidoYnombre);

                    if(nombreOK!=1)
                    {
                        printf("\n El nombre o apellido ingresado no es valido.\n");
                        system("pause");
                    }
                }
                    fseek(archi, (-1) * sizeof(paciente), SEEK_CUR);
                    fwrite(&nuevo,sizeof(paciente),1,archi);
                    break;

                case 2:
                    while(edadOk!=1)
                    {
                        system("cls");
                        printf("\n Ingrese la Edad: \n");
                        scanf("%d",&nuevo.edad);
                        edadOk=verificaEdad(nuevo.edad);

                        if(edadOk!=1)
                        {
                            printf("\n Edad no valida, ingrese edad nuevamente.\n");
                            system("pause");
                        }
                    }
                    fseek(archi, (-1) * sizeof(paciente), SEEK_CUR);
                    fwrite(&nuevo,sizeof(paciente),1,archi);

                    break;
                case 3:

                    while(direccionOk!=1)
                    {
                        system("cls");
                        printf("\n Ingrese el domicilio: \n");
                        fflush(stdin);
                        gets(nuevo.direccion);
                        direccionOk= verificaDireccion(nuevo.direccion);

                        if(direccionOk!=1)
                        {
                            printf("\n La direccion ingresada no es correcta.");
                            system("pause");
                        }
                    }
                    fseek(archi, (-1) * sizeof(paciente), SEEK_CUR);
                    fwrite(&nuevo,sizeof(paciente),1,archi);

                    break;
                case 4:
                    while(telOk!=1)
                    {
                        system("cls");
                        printf("\n Ingrese un telefono: \n");
                        fflush(stdin);
                        gets(nuevo.telefono);

                        telOk=verificaTelefono(nuevo.telefono);

                        if(telOk!=1)
                        {
                            printf("\n El telefono ingresado no es correcto.\n");
                            system("pause");
                        }
                    }
                    fseek(archi, (-1) * sizeof(paciente), SEEK_CUR);
                    fwrite(&nuevo,sizeof(paciente),1,archi);

                    break;
                case 5:
                    break;
                default:
                    printf("\n Opcion ingresada incorrecta. \n\n");
                    system("pause");
                    system("cls");

                }

                printf("\n %cQuieres modificar otro dato? s=SI / n=NO " , 168);
                fflush(stdin);
                continuar = getch();

            }
            while(opcion != 5 && continuar == 's');

        }
        fclose(archi);
    }

    system("cls");

    printf("\n CAMBIOS REALIZADO CON EXITO: \n\n");
    mostrarPaciente(nuevo);

    system("pause");

}
/// ---------------------------- FIN FUNCIONES VALIDACIONES - PACIENTES ---------------------------- ///

/// ----------------------------- FUNCIONES DE ÁRBOL - PACIENTE ------------------------------------ ///
nodoarbol* inicArbol()
{
    return NULL;
}

nodoarbol* crearNodoArbol(paciente persona)
{
    nodoarbol *aux= (nodoarbol*) malloc(sizeof(nodoarbol));

    aux->dato=persona;
    aux->izq= NULL;
    aux->der= NULL;
    aux->listaIng = inicListaIngresos();

    return aux;
}

nodoarbol* insertar(nodoarbol* arbol,paciente dato)
{
    if(arbol==NULL)
    {
        arbol= crearNodoArbol(dato);
    }
    else
    {
        if(strcmp(dato.dni,arbol->dato.dni)<0)
        {
            arbol->izq=insertar(arbol->izq,dato);
        }
        else
        {
            arbol->der=insertar(arbol->der,dato);
        }
    }

    return arbol;
}

void mostrarArbolInOrder(nodoarbol *arbol)
{
    if(arbol)
    {
        mostrarArbolInOrder(arbol->izq);
        mostrarPaciente(arbol->dato);
        mostrarArbolInOrder(arbol->der);
    }
}

nodoarbol* buscarPacienteArbol(nodoarbol* arbol , char dniPaciente[])
{
    nodoarbol* encontrado = NULL;

    if(arbol != NULL)
        {
        if(strcmp(dniPaciente , arbol->dato.dni) == 0){
            encontrado = arbol;
        }else{
            if(strcmp(dniPaciente, arbol->dato.dni) < 0){
                encontrado = buscarPacienteArbol(arbol->izq , dniPaciente);
            }else{
                encontrado = buscarPacienteArbol(arbol->der , dniPaciente);
            }
        }
    }

    return encontrado;
}

nodoarbol* pasarArchPacienteToArbol(char nombreArchivo[] , nodoarbol* arbol)
{
    paciente auxReg;
    FILE *pArchivo = fopen(nombreArchivo , "rb");

    if(pArchivo != NULL)
        {
        while(fread(&auxReg , sizeof(paciente) , 1 , pArchivo) > 0)
        {
            if(existePaciente(arbol,auxReg.dni)==0)
            {
            arbol = insertar(arbol , auxReg);
            }
        }
        fclose(pArchivo);
    }else{
        printf(" ERROR en la lectura del archivo. \n\n");
    }

    return arbol;
}
int existePaciente(nodoarbol* arbol, char dni[])
{
    if (arbol == NULL)
        {
    return 0;  // No existe en el árbol
    }

    if (strcmp(dni, arbol->dato.dni) < 0)
        {
        return existePaciente(arbol->izq, dni);
    }
    else if (strcmp(dni, arbol->dato.dni) > 0)
        {
        return existePaciente(arbol->der, dni);
    }
    else
        {
        return 1;  // El paciente ya existe en el árbol
    }
}

nodoarbol* tomar_nodo_mayor_valor (nodoarbol* arbol)
{
    nodoarbol* mayorValor = NULL;

    if (arbol)
        {
        mayorValor = tomar_nodo_mayor_valor(arbol->der);

        if (!mayorValor)
            {
            mayorValor = arbol;
            }
        }

    return mayorValor;
}

nodoarbol* tomar_nodo_menor_valor (nodoarbol* arbol)
{
    nodoarbol* menorValor = NULL;

    if (arbol)
        {
        menorValor = tomar_nodo_menor_valor(arbol->der);

        if (!menorValor)
            {
            menorValor = arbol;
            }
        }

    return menorValor;
}

nodoarbol* eliminar_nodo_de_arbol (nodoarbol* arbol, char dni[8])
{

    if (arbol)
        {

        if (strcmpi(arbol->dato.dni,dni)==0)
            {

            if (arbol->izq)
                {

                nodoarbol* basura = tomar_nodo_mayor_valor(arbol->izq);


                arbol->der = eliminar_nodo_de_arbol(arbol->der, basura->dato.dni);


                free(basura);
                }

            else
                {

                if (arbol->der)
                {



                    nodoarbol* basura = tomar_nodo_menor_valor(arbol->der);


                    arbol->der = eliminar_nodo_de_arbol(arbol->der, arbol->dato.dni);


                    free(basura);
                    }

                else
                    {

                    free(arbol);


                    arbol = NULL;
                    }
                }
            }

        else
            {

            if (strcmpi(dni,arbol->dato.dni)>0)
                {

                arbol->der = eliminar_nodo_de_arbol(arbol->der, dni);
                }

            else
                {

                arbol->izq = eliminar_nodo_de_arbol(arbol->izq, dni);
                }
            }
        }

    return arbol;
}

/// ----------------------------- FIN FUNCIONES DE ÁRBOL - PACIENTE -------------------------------- ///

/// ----------------------------- FUNCIONES DE LISTA - PACIENTE ------------------------------------ ///

nodoListaPaciente* iniclistaPaciente()
{
    return NULL;
}

nodoListaPaciente* crearNodoPaciente(paciente pac)
{
    nodoListaPaciente* auxNodoPac = (nodoListaPaciente *)malloc(sizeof(nodoListaPaciente));

    auxNodoPac->datosPac = pac;
    auxNodoPac->siguiente = NULL;

    return auxNodoPac;
}

nodoListaPaciente* agregarInicioListaPaciente(nodoListaPaciente* listaPac , nodoListaPaciente* nuevoNodoPac)
{
    if(listaPac == NULL){
        listaPac = nuevoNodoPac;
    }else{
        nuevoNodoPac->siguiente = listaPac;
        listaPac = nuevoNodoPac;
    }

    return listaPac;
}

nodoListaPaciente* agregarEnOrdenListaPaciente(nodoListaPaciente* listaPac , nodoListaPaciente* nuevoNodoPac)
{
    if(listaPac == NULL){
        listaPac = nuevoNodoPac;
    }else{
        if(strcmpi(nuevoNodoPac->datosPac.apellidoYnombre , listaPac->datosPac.apellidoYnombre) < 0){
            listaPac = agregarInicioListaPaciente(listaPac , nuevoNodoPac);
        }else{
            nodoListaPaciente* ante = listaPac;
            nodoListaPaciente* seg = listaPac->siguiente;

            while((seg != NULL) && (strcmpi(nuevoNodoPac->datosPac.apellidoYnombre , seg->datosPac.apellidoYnombre) > 0)){
                ante = seg;
                seg = seg->siguiente;
            }

            ante->siguiente = nuevoNodoPac;
            nuevoNodoPac->siguiente = seg;
        }
    }

    return listaPac;
}

void mostrarListaPaciente(nodoListaPaciente* listaPac)
{
    nodoListaPaciente* seg = listaPac;

    if(seg != NULL){
        while(seg != NULL)
            {
                if(seg->datosPac.eliminados==1)
                {
                    mostrarPaciente(seg->datosPac);
                }
            seg = seg->siguiente;
        }
    }
}

nodoListaPaciente* pasarArchPacToListaPac(char nombreArchivo[] , nodoListaPaciente* listaPac)
{
    paciente auxRegPac;
    FILE *pArchivo = fopen(nombreArchivo , "rb");

    if(pArchivo != NULL){
        nodoListaPaciente* nodoPaciente;
        while(fread(&auxRegPac , sizeof(paciente) , 1 , pArchivo) > 0){
            nodoPaciente = crearNodoPaciente(auxRegPac);
            listaPac = agregarEnOrdenListaPaciente(listaPac , nodoPaciente);
        }
        fclose(pArchivo);
    }

    return listaPac;
}

/// ------------------------------ FIN FUNCIONES DE LISTA - PACIENTE ------------------------------ ///

/// ----------------------------- FUNCIONES DE INGRESOS PACIENTE ----------------------------------- ///
ingresos cargaDatosIngresos(nodoarbol* arbol , ingresos ingresoPaciente)
{
    int fechaIngresoValida = 0;
    int fechaRetiroValida = 0;
    nodoarbol* encontrado;
    int matriculaValida = 0;

    while(fechaIngresoValida != 1){
        system("cls");

        printf("\n CARGANDO INGRESO... \n\n");

        printf(" Ingresar fecha de ingreso: ");
        fflush(stdin);
        gets(ingresoPaciente.fechaIngreso);

        fechaIngresoValida = validarFecha(ingresoPaciente.fechaIngreso);

        if(fechaIngresoValida != 1){
            printf("\n La fecha ingresada no es v%clida. \n\n" , 160);
            system("pause");
        }
    }

    while(fechaRetiroValida != 1){
        system("cls");

        printf("\n CARGANDO INGRESO... \n\n");

        printf(" Ingresar fecha de retiro: ");
        fflush(stdin);
        gets(ingresoPaciente.fechaRetiro);

        fechaRetiroValida = validarFecha(ingresoPaciente.fechaRetiro);

        if(fechaRetiroValida != 1){
            printf("\n La fecha ingresada no es v%clida. \n\n" , 160);
            system("pause");
        }
    }

    do{
        system("cls");

        printf("\n CARGANDO INGRESO... \n\n");

        printf(" Ingresar DNI del paciente: ");
        fflush(stdin);
        gets(ingresoPaciente.dniPaciente);

        encontrado = buscarPacienteArbol(arbol , ingresoPaciente.dniPaciente);

        if(encontrado == NULL){
            printf("\n El DNI ingresado no se encuentra registrado o no es v%clido. \n\n" , 160);
            system("pause");
        }

    }while(encontrado == NULL);

    while(matriculaValida != 1){
        system("cls");

        printf("\n CARGANDO INGRESO... \n\n");

        printf(" Ingresar matr%ccula del profesional: " , 161);
        fflush(stdin);
        gets(ingresoPaciente.matriculaProfesional);

        matriculaValida = validarMatricula(ingresoPaciente.matriculaProfesional);

        if(matriculaValida != 1){
            printf("\n La matr%ccula ingresada no es v%clida. \n\n" , 161 , 160);
            system("pause");
        }
    }

    ingresoPaciente.eliminado =0;



    return ingresoPaciente;
}

void mostrarUnIngreso(ingresos ingresoPaciente)
{
    printf("======================================================= \n");
    printf(" N%c Ingreso.......................: %d \n" , 248 , ingresoPaciente.nroIngreso);
    printf(" Fecha de ingreso.................: %s \n" , ingresoPaciente.fechaIngreso);
    printf(" Fecha de retiro..................: %s \n" , ingresoPaciente.fechaRetiro);
    printf(" DNI del paciente.................: %s \n" , ingresoPaciente.dniPaciente);
    printf(" Matr%cula del profesional.........: %s \n" , 161 , ingresoPaciente.matriculaProfesional);
    if(ingresoPaciente.eliminado == 0){
        printf(" Estado...........................: ALTA \n");
    }else{
        printf(" Estado...........................: BAJA \n");
    }
    printf("======================================================= \n\n");
}

///FUNCIONES DE VALIDACIONES DE INGRESOS - PACIENTE
int validarFecha(char fecha[])
{
    int fechaValida = 1;
    int exitoConversionFecha = 0;
    int longitudFecha = strlen(fecha);
    int i = 0;

    if(longitudFecha == 0 || longitudFecha < 6 || longitudFecha > 11 || fecha[0] == 32){  //verifico que no se ingrese una
                                                                                          //fecha "en blanco" y que la cantidad
                                                                                          //de caracteres sea el correcto
        fechaValida = 0;
    }else{
        while((i < longitudFecha) && (fechaValida == 1)){
            if((fecha[i] >= 48 && fecha[i] <= 57) || (fecha[i] == 47) || (fecha[i] == 45)){
                i++;
            }else{
                fechaValida = 0;
            }
        }
    }

    if(longitudFecha != 0){
        exitoConversionFecha = convertirFecha(fecha); //verifico que la fecha tenga el formato correcto:
                                                      //dd/mm/aaaa ; d/m/aa ; dd/mm/aa ó dd-mm-aaaa ; dd-mm-aa ; d-m-aa

        if(exitoConversionFecha == 1){
            fechaValida = 1;
        }else{
            fechaValida = 0;
        }
    }

    return fechaValida;
}

int convertirFecha(char fecha[])
{
    int fechaValida = 0;
    int dia = 0;
    int mes = 0;
    int year = 0;

    if(sscanf(fecha , "%d/%d/%d" , &dia , &mes , &year) == 3){ // Intenta convertir la fecha en formato dd/mm/aaaa
        if((dia >= 1 && dia <= 31) && (mes >= 1 && mes <= 12) && ((year >= 2023 && year <= 2033) || (year >= 23 && year <= 33))){
            fechaValida = 1;
        }
    }

    if(sscanf(fecha , "%d-%d-%d" , &dia , &mes , &year) == 3){ // Intenta convertir la fecha en formato dd-mm-aaaa
        if((dia >= 1 && dia <= 31) && (mes >= 1 && mes <= 12) && ((year >= 2023 && year <= 2033) || (year >= 23 && year <= 33))){
            fechaValida = 1;
        }
    }

    return fechaValida;
}

int validarMatricula(char matriculaProf[])
{
    int matriculaValida = 1;
    int longitudMatricula = strlen(matriculaProf);
    int i = 0;

    if(longitudMatricula == 0 || matriculaProf[0] == 32 || longitudMatricula > 11){
        matriculaValida = 0;
    }else{
        while((i < longitudMatricula) && (matriculaValida == 1)){
            if((matriculaProf[i] >= 40 && matriculaProf[i] <= 57) || //numeros del 0 - 9
               (matriculaProf[i] >= 65 && matriculaProf[i] <= 90) || //letras mayúsculas A-Z
               (matriculaProf[i] >= 97 && matriculaProf[i] <= 122) || //letras minúsculas a-z
               matriculaProf[i] == 32 || matriculaProf[i] == 46){ // espacio y '.'

                i++;
            }else{
               matriculaValida = 0;
            }
        }
    }

    return matriculaValida;
}
///FIN FUNCIONES DE VALIDACIONES DE INGRESOS - PACIENTE

///FUNCIONES ARCHIVO INGRESOS
void agregarIngreso(char nombreArchivo[] , nodoarbol* arbol)
{

    nodoListaIngresos* listaIngresos=inicListaIngresos();
    char continuar = 's';
    ingresos ingPaciente;

    while(continuar == 's' || continuar == 'S')
    {
        ingPaciente = cargaDatosIngresos(arbol , ingPaciente);
        ingPaciente.nroIngreso = 1 + ultimoIngresoArch(nombreArchivo);

        guardarUnIngreso(nombreArchivo , ingPaciente);

        nodoListaIngresos*nuevoNodoIngreso=crearNodoIngreso(ingPaciente);
        listaIngresos=agregarInicioListaIngresos(listaIngresos,nuevoNodoIngreso);

        listaIngresos=cargarPractica(listaIngresos,ingPaciente.nroIngreso,"practicasLab.dat");

        pasarListaIngresoToArchivo(listaIngresos , "pracXingPacientes.dat");

        printf("\n %cQuires agregar otro ingreso? s=SI / n=NO " , 168);
        fflush(stdin);
        continuar = getch();
    }
}

void pasarListaIngresoToArchivo(nodoListaIngresos* listaIng , char nombreArch[])
{
    regPracticasPacientes auxRegPac;
    nodoListaIngresos* segIng = listaIng;
    nodoListaPracXingreso *segPxi = listaIng->listaPrac;
    FILE* pArchivo = fopen(nombreArch , "ab");

    if(pArchivo != NULL)
    {
        while(segIng != NULL)
        {
            while(segPxi != NULL)
            {
                auxRegPac.nroIngreso = segIng->datosIngresoPac.nroIngreso;
                strcpy(auxRegPac.fechaIngreso , segIng->datosIngresoPac.fechaIngreso);
                strcpy(auxRegPac.fechaRetiro , segIng->datosIngresoPac.fechaRetiro);
                strcpy(auxRegPac.dniPaciente , segIng->datosIngresoPac.dniPaciente);
                strcpy(auxRegPac.matriculaProfesional , segIng->datosIngresoPac.matriculaProfesional);
                auxRegPac.nroPractica = segPxi->datos.nroPractica;
                strcpy(auxRegPac.nombrePractica , segPxi->datos.nombrePractica);
                strcpy(auxRegPac.resultado , segPxi->datos.resultado);

                fwrite(&auxRegPac , sizeof(regPracticasPacientes) , 1 , pArchivo);

                segPxi = segPxi->siguiente;
            }

            segIng = segIng->siguiente;
        }
        fclose(pArchivo);
    }
}

void mostrarUnRegPaciente(regPracticasPacientes regPracPaciente)
{
    printf("//////////////////////////////////////////////////////////////// \n");
    printf(" Nro. de ingreso.................: %d \n" , regPracPaciente.nroIngreso);
    printf(" Fecha de ingreso................: %s \n" , regPracPaciente.fechaIngreso);
    printf(" Fecha de retiro.................: %s \n" , regPracPaciente.fechaRetiro);
    printf(" DNI del paciente................: %s \n" , regPracPaciente.dniPaciente);
    printf(" Matr%ccula del profesional.......: %s \n" , 161 , regPracPaciente.matriculaProfesional);
    printf(" Nro. de pr%cctica................: %d \n" , 160 , regPracPaciente.nroPractica);
    printf(" Nombre de la pr%cctica...........: %s \n" , 160 , regPracPaciente.nombrePractica);
    printf(" Resultado.......................: %s \n" , regPracPaciente.resultado);
    printf("//////////////////////////////////////////////////////////////// \n\n");
}

void mostrarArchRegPracPaciente(char nombreArchivo[])
{
    regPracticasPacientes auxReg;
    FILE* pArchivo = fopen(nombreArchivo , "rb");

    if(pArchivo != NULL)
    {
        while(fread(&auxReg , sizeof(regPracticasPacientes) , 1 , pArchivo) > 0)
        {
            mostrarUnRegPaciente(auxReg);
        }
        fclose(pArchivo);
    }
}

void mostrarArchRegPracPorUsuario(char nombreArchivo[] , char dniPac[])
{
    regPracticasPacientes auxReg;
    FILE* pArchivo = fopen(nombreArchivo , "rb");

    if(pArchivo != NULL){
        while(fread(&auxReg , sizeof(regPracticasPacientes) , 1 , pArchivo) > 0){
            if(strcmp(auxReg.dniPaciente , dniPac) == 0){
                mostrarUnRegPaciente(auxReg);
            }
        }
        fclose(pArchivo);
    }
}

void guardarUnIngreso(char nombreArchivo[] , ingresos ingPac)
{
    FILE* pArchivo = fopen(nombreArchivo , "ab");

    if(pArchivo != NULL)
        {
        fwrite(&ingPac , sizeof(ingresos) , 1 , pArchivo);
        fclose(pArchivo);
    }else{
        printf(" ERROR en la apertura del archivo ingresos. \n\n");
    }
}

void mostrarArchIngresos(char nombreArchivo[])
{
    ingresos ingPac;
    FILE *pArchivo = fopen(nombreArchivo , "rb");

    if(pArchivo != NULL){
        while(fread(&ingPac , sizeof(ingresos) , 1 , pArchivo) > 0){
            mostrarUnIngreso(ingPac);
        }
        fclose(pArchivo);
    }else{
        printf("\n NO hay ingresos registrados. \n\n");
    }
}

void mostrarArchIngresosPaciente(char nombreArchivo[] , char dniPac[])
{
    ingresos ingPac;
    FILE *pArchivo = fopen(nombreArchivo , "rb");

    if(pArchivo != NULL){
        while(fread(&ingPac , sizeof(ingresos) , 1 , pArchivo) > 0){
            if(strcmp(ingPac.dniPaciente , dniPac) == 0)
            {
                mostrarUnIngreso(ingPac);
            }

        }
        fclose(pArchivo);
    }else{
        printf("\n NO hay ingresos registrados. \n\n");
    }
}

int ultimoIngresoArch(char nombreArchivo[])
{
    ingresos auxRegIng;
    int ultimoIng = 0;
    FILE *pArchivo = fopen(nombreArchivo , "rb");

    if(pArchivo != NULL){
        fseek(pArchivo , (-1) * sizeof(ingresos) , SEEK_END);

        if(fread(&auxRegIng , sizeof(ingresos) , 1 , pArchivo) > 0){
            ultimoIng = auxRegIng.nroIngreso;
        }

        fclose(pArchivo);
    }

    return ultimoIng;
}

void darBajaIngresoArch(char nombreArchIng[] , int numIngreso)
{
    ingresos auxRegIng;
    int flag = 0;
    FILE *pArchivoIng = fopen(nombreArchIng , "r+b");

    if(pArchivoIng != NULL){
        while(fread(&auxRegIng , sizeof(paciente) , 1 , pArchivoIng) > 0){
            if(auxRegIng.nroIngreso == numIngreso){
                flag = 1;
                fseek(pArchivoIng , (-1) * sizeof(ingresos) , SEEK_CUR);
                auxRegIng.eliminado = 1;
                fwrite(&auxRegIng , sizeof(paciente) , 1 , pArchivoIng);
            }
        }
        fclose(pArchivoIng);
    }

    if(flag == 0){
        printf(" El nro. de  ingreso es incorrecto o no se encuentra registrado. \n\n");
    }else{
        system("cls");
        printf("\n INGRESO DADO DE BAJA CON %cXITO. \n\n" , 144);
        mostrarUnIngreso(auxRegIng);
    }
}

void darAltaIngresoArch(char nombreArchIng[] , int numIngreso)
{
    ingresos auxRegIng;
    int flag = 0;
    FILE *pArchivoIng = fopen(nombreArchIng , "r+b");

    if(pArchivoIng != NULL){
        while(fread(&auxRegIng , sizeof(paciente) , 1 , pArchivoIng) > 0){
            if(auxRegIng.nroIngreso == numIngreso){
                flag = 1;
                fseek(pArchivoIng , (-1) * sizeof(ingresos) , SEEK_CUR);
                auxRegIng.eliminado = 0;
                fwrite(&auxRegIng , sizeof(paciente) , 1 , pArchivoIng);
            }
        }
        fclose(pArchivoIng);
    }

    if(flag == 0){
        printf(" El nro. de  ingreso es incorrecto o no se encuentra registrado. \n\n");
    }else{
        system("cls");
        printf("\n INGRESO DADO DE BAJA CON %cXITO. \n\n" , 144);
        mostrarUnIngreso(auxRegIng);
    }
}

int menuEdicionDatosIngresos()
{
    int opcion;

    printf("\n EDICION DE DATOS DEL INGRESO: \n\n");

    printf(" 1. Editar fecha de ingreso \n");
    printf(" 2. Editar fecha de retiro \n");
    printf(" 3. Editar matr%ccula \n" , 161);
    printf(" 0. Salir \n\n");

    printf(" Ingresar opci%cn: " , 162);
    scanf("%d" , &opcion);

    return opcion;
}

ingresos editarDatosIngreso(char nombreArchivo[] , ingresos ingPaciente)
{
    ingresos auxIng = ingPaciente;
    int fechaIngresoValida = 0;
    int fechaRetiroValida = 0;
    int matriculaValida = 0;
    char continuar = 's';
    int opMenuEdicionDatosIngreso;

    system("cls");
    printf("\n El ingreso a modificar es: \n\n");
    mostrarUnIngreso(auxIng);
    system("pause");

    while((continuar == 's' || continuar == 'S') || (opMenuEdicionDatosIngreso != 0)){
        system("cls");

        opMenuEdicionDatosIngreso = menuEdicionDatosIngresos();

        if(opMenuEdicionDatosIngreso == 1){

            while(fechaIngresoValida != 1){
                system("cls");

                printf("\n Ingresar nueva fecha de ingreso: ");
                fflush(stdin);
                gets(auxIng.fechaIngreso);

                fechaIngresoValida = validarFecha(auxIng.fechaIngreso);

                if(fechaIngresoValida != 1){
                    printf("\n La fecha ingresada no es v%clida. \n\n" , 160);
                    system("pause");
                }
            }
        }else if(opMenuEdicionDatosIngreso == 2){
             while(fechaIngresoValida != 1){
                system("cls");

                printf("\n Ingresar nueva fecha de retiro: ");
                fflush(stdin);
                gets(auxIng.fechaRetiro);

                fechaRetiroValida = validarFecha(auxIng.fechaIngreso);

                if(fechaRetiroValida != 1){
                    printf("\n La fecha ingresada no es v%clida. \n\n" , 160);
                    system("pause");
                }
            }
        }else if(opMenuEdicionDatosIngreso == 3){
            while(matriculaValida != 1){
                system("cls");

                printf(" Ingresar nueva matr%ccula del profesional: " , 161);
                fflush(stdin);
                gets(auxIng.matriculaProfesional);

                matriculaValida = validarMatricula(auxIng.matriculaProfesional);

                if(matriculaValida != 1){
                    printf("\n La matr%ccula ingresada no es v%clida. \n\n" , 161 , 160);
                    system("pause");
                }
            }
        }else{
            if(opMenuEdicionDatosIngreso != 0){
                printf(" OPCI%cN NO V%cLIDA. \n\n") , 224 , 181;
            }
        }

        if(opMenuEdicionDatosIngreso >= 1 || opMenuEdicionDatosIngreso <= 3){
            printf("\n %cQuieres modificar otro dato del ingreso? s= SI / n=NO " , 168);
            fflush(stdin);
            continuar = getch();
        }
    }

    if(opMenuEdicionDatosIngreso != 0){
        system("cls");
        printf(" \n CAMBIO/S REALIZADO CON %cXITO: \n\n" , 144);
        mostrarUnIngreso(auxIng);
        system("pause");
    }

    return auxIng;
}

void modificarIngresoArch(char nombreArchivo[] , int numIngreso)
{
    ingresos auxRegIngreso;
    int flag = 0;
    FILE* pArchivo = fopen(nombreArchivo , "r+b");

    if(pArchivo != NULL){
        while((flag == 0) && (fread(&auxRegIngreso , sizeof(ingresos) , 1 , pArchivo) > 0)){
            if(auxRegIngreso.nroIngreso == numIngreso){
                flag = 1;
                fseek(pArchivo , (-1) * sizeof(ingresos) , SEEK_CUR);
                auxRegIngreso = editarDatosIngreso(nombreArchivo , auxRegIngreso);
                fwrite(&auxRegIngreso , sizeof(ingresos) , 1 , pArchivo);
            }
        }
        fclose(pArchivo);

        if(flag == 0){
            printf("\n El nro. de ingreso no se encuentra registrado o no es v%clido. \n" , 160);
        }
    }
}
///FIN FUNCIONES ARCHIVO INGRESOS

/// ----------------------------- FIN FUNCIONES DE INGRESOS PACIENTE ------------------------------- ///

/// ----------------------------- FUNCIONES DE LISTA - INGRESOS PACIENTE --------------------------- ///
nodoListaIngresos* inicListaIngresos()
{
    return NULL;
}

nodoListaIngresos* crearNodoIngreso(ingresos ingresoPac)
{
    nodoListaIngresos* auxNodoIngreso = (nodoListaIngresos *)malloc(sizeof(nodoListaIngresos));

    auxNodoIngreso->datosIngresoPac = ingresoPac;
    auxNodoIngreso->siguiente = NULL;
    auxNodoIngreso->listaPrac = inicListaPracticas();

    return auxNodoIngreso;
}

nodoListaIngresos* agregarInicioListaIngresos(nodoListaIngresos* listaIngresos , nodoListaIngresos* nuevoNodoIngreso)
{
    if(listaIngresos == NULL)
    {
        listaIngresos = nuevoNodoIngreso;
    }
    else
    {
        nuevoNodoIngreso->siguiente = listaIngresos;
        listaIngresos = nuevoNodoIngreso;
    }

    return listaIngresos;
}

nodoListaIngresos* agregarEnOrdenListaIngresos(nodoListaIngresos* listaIngresos , nodoListaIngresos* nuevoNodoIngreso)
{
    if(listaIngresos == NULL){
        listaIngresos = nuevoNodoIngreso;
    }else{
        if(strcmpi(nuevoNodoIngreso->datosIngresoPac.fechaIngreso , listaIngresos->datosIngresoPac.fechaIngreso) > 0){
            listaIngresos = agregarInicioListaIngresos(listaIngresos , nuevoNodoIngreso);
        }else{
            nodoListaIngresos *ante = listaIngresos;
            nodoListaIngresos *seg = listaIngresos->siguiente;

            while((seg != NULL) && (strcmpi(nuevoNodoIngreso->datosIngresoPac.fechaIngreso , listaIngresos->datosIngresoPac.fechaIngreso) < 0)){
                ante = seg;
                seg = seg->siguiente;
            }

            ante->siguiente = nuevoNodoIngreso;
            nuevoNodoIngreso->siguiente = seg;
        }
    }

    return listaIngresos;
}

void mostrarListaIngresos(nodoarbol* arbol)
{
    nodoListaIngresos* seg = arbol->listaIng;
    if(seg != NULL)
        {
        while(seg != NULL)
        {
            mostrarUnIngreso(seg->datosIngresoPac);
            seg = seg->siguiente;
        }
    }
}

nodoListaIngresos* buscarIngresoPorNumIngreso(nodoListaIngresos* listaIng , int numIngreso)
{
    nodoListaIngresos* ingresoEncontrado = NULL;
    nodoListaIngresos* seg = listaIng;

    if(seg != NULL){
        while((seg != NULL) && (ingresoEncontrado == NULL)){
            if(seg->datosIngresoPac.nroIngreso == numIngreso){
                ingresoEncontrado = seg;
            }else{
                seg = seg->siguiente;
            }
        }
    }

    return ingresoEncontrado;
}

ingresos buscarIngresoPorDni(nodoListaIngresos* listaIng , char dniPac[])
{
    ingresos ingEncontrado;
    int flag = 0;
    nodoListaIngresos* seg = listaIng;

    if(seg != NULL){
        while((seg != NULL) && (flag == 0)){
            if(strcmp(seg->datosIngresoPac.dniPaciente , dniPac) == 0){
                flag = 1;
                ingEncontrado = seg->datosIngresoPac;
            }else{
                seg = seg->siguiente;
            }
        }
    }

    return ingEncontrado;
}

nodoListaPracticas* cargaListaPracticaPaciente(nodoarbol* arbol , char dniPac[] , nodoListaPracticas* listaPrac)
{
    nodoarbol* pacienteEncontrado = buscarPacienteArbol(arbol , dniPac);
    practicas pracPaciente;
    char continuar = 's';
    int nroIngPaciente = 0;
    int nroPrac = 0;

    if(pacienteEncontrado != NULL){
        nodoListaIngresos* ingresoEncontrado;
        nodoListaPracticas* practicaEncontrada;

        while(continuar == 's' || continuar == 'S'){
            system("cls");

            printf("\n LISTA DE INGRESOS DEL PACIENTE: \n\n");
            mostrarListaIngresos(pacienteEncontrado->listaIng);

            printf("\n Ingresar nro. de ingreso del paciente: ");
            scanf("%d" , &nroIngPaciente);

            ingresoEncontrado = buscarIngresoPorNumIngreso(pacienteEncontrado->listaIng , nroIngPaciente);

            if(ingresoEncontrado != NULL){
                system("cls");

                printf("\n LISTA DE PR%cCTICAS DISPONIBLES: \n\n" , 181);
                mostrarListaPractica(listaPrac);

                printf("\n Ingresar nro. de pr%cctica: " , 160);
                scanf("%d" , &nroPrac);

                practicaEncontrada = buscarPractica(listaPrac , nroPrac);

                if(practicaEncontrada != NULL){
                    pracPaciente = practicaEncontrada->datosPracticas;
                    nodoListaPracticas* nuevaPracPaciente = crearNodoPractica(pracPaciente);
                    pacienteEncontrado->listaIng->listaPrac = agregarInicioListaPractica(pacienteEncontrado->listaIng->listaPrac , nuevaPracPaciente);
                }
            }
        }
    }

    return pacienteEncontrado->listaIng->listaPrac;
}

nodoListaIngresos* pasarArchToListaIng(char nombreArchivo[] , nodoListaIngresos* listaIng)
{
    ingresos auxRegIng;
    FILE *pArchivo = fopen(nombreArchivo , "rb");

    if(pArchivo != NULL){
        nodoListaIngresos* nuevoIng;
        while(fread(&auxRegIng , sizeof(ingresos) , 1 , pArchivo) > 0){
            nuevoIng = crearNodoIngreso(auxRegIng);
            listaIng = agregarEnOrdenListaIngresos(listaIng , nuevoIng);
        }
        fclose(pArchivo);
    }else{
        printf(" ERROR en la lectura del archivo ing. \n\n");
    }

    return listaIng;
}

/// ----------------------------- FIN FUNCIONES DE LISTA - INGRESOS PACIENTE ----------------------- ///

/// ----------------------------- FUNCIONES DE LISTA - PRÁCTICAS POR INGRESOS ---------------------- ///
nodoListaPracXingreso* inicListaPracPorIngreso()
{
    return NULL;
}

nodoListaPracXingreso* crearNodoPracPorIngreso(practicas prac,int nroIngreso)
{
    nodoListaPracXingreso* auxNodoPracXingreso = (nodoListaPracXingreso *)malloc(sizeof(nodoListaPracXingreso));

    auxNodoPracXingreso->datos.nroIngreso=nroIngreso;
    auxNodoPracXingreso->datos.nroPractica=prac.nroPractica;
    strcpy(auxNodoPracXingreso->datos.nombrePractica,prac.nombrePractica);
    strcpy(auxNodoPracXingreso->datos.resultado," Esperando carga resultado");
    auxNodoPracXingreso->siguiente = NULL;

    return auxNodoPracXingreso;
}

nodoListaPracXingreso* agregarEnOrdenListaPracPorIngreso(nodoListaPracXingreso* listaPracPorIngreso , nodoListaPracXingreso* nuevoNodoPracPorIngreso)
{
    if(listaPracPorIngreso == NULL){
        listaPracPorIngreso = nuevoNodoPracPorIngreso;
    }else{
        if(nuevoNodoPracPorIngreso->datos.nroIngreso < listaPracPorIngreso->datos.nroIngreso){
            listaPracPorIngreso = agregarInicioListaPracPorIngreso(listaPracPorIngreso , nuevoNodoPracPorIngreso);
        }else{
            nodoListaPracXingreso* ante = listaPracPorIngreso;
            nodoListaPracXingreso* seg = listaPracPorIngreso->siguiente;

            while((seg != NULL) && (nuevoNodoPracPorIngreso->datos.nroIngreso > listaPracPorIngreso->datos.nroIngreso)){
                ante = seg;
                seg = seg->siguiente;
            }

            ante->siguiente = nuevoNodoPracPorIngreso;
            nuevoNodoPracPorIngreso->siguiente = seg;
        }
    }

    return listaPracPorIngreso;
}

void mostrarListaPracPorIngreso(nodoListaPracXingreso* listaPracPorIngreso)
{
    nodoListaPracXingreso* seg = listaPracPorIngreso;

    if(seg != NULL){
        while(seg != NULL){
            mostrarUnaPracticaPorIngreso(seg->datos);
            seg = seg->siguiente;
        }
    }
}

///FUNCIONES AUXILIARES - PRÁCTICAS POR INGRESO
nodoListaPracXingreso* agregarInicioListaPracPorIngreso(nodoListaPracXingreso* listaPracPorIngreso , nodoListaPracXingreso* nuevoNodoPracPorIngreso)
{
    if(listaPracPorIngreso == NULL){
        listaPracPorIngreso = nuevoNodoPracPorIngreso;
    }else{
        nuevoNodoPracPorIngreso->siguiente = listaPracPorIngreso;
        listaPracPorIngreso = nuevoNodoPracPorIngreso;
    }

    return listaPracPorIngreso;
}

void mostrarUnaPracticaPorIngreso(practicaXingreso prac)
{
    printf("*********************************** \n");
    printf(" N%c de ingreso..............: %d \n" , 248 , prac.nroIngreso);
    printf(" N%c de practica.............: %d \n" , 248 , prac.nroPractica);
    printf(" Nombre de la pr%cctica......: %s \n" , 160 , prac.nombrePractica);
    printf(" Resultado..................: %s \n" , prac.resultado);
    printf("*********************************** \n\n");
}

/// ----------------------------- FIN DE FUNCIONES DE LISTA - PRÁCTICAS POR INGRESO ---------------- ///

/// ----------------------------- FUNCIONES ARCHIVO - PRÁCTICAS POR INGRESOS ---------------------- ///
practicaXingreso cargaDatosPracticaPorIngreso(practicaXingreso pracPorIng , nodoListaPracticas* listaPrac , nodoListaIngresos* listaIng)
{
    nodoListaIngresos* ingresoEncontrado = 0;
    nodoListaPracticas* pracEncontrada = NULL;

    while(ingresoEncontrado == 0){
        system("cls");

        printf("\n CARGANDO DATOS PR%cCTICAS POR INGRESO: \n\n" , 181);

        printf(" Ingresar nro. de ingreso: ");
        scanf("%d" , &pracPorIng.nroIngreso);

        ingresoEncontrado = buscarIngresoPorNumIngreso(listaIng , pracPorIng.nroIngreso);

        if(ingresoEncontrado == 0){
            printf("\n El nro. de ingreso no se encuentra registrado. \n\n");
            system("pause");
        }else{
            system("cls");
            printf("\n El nro de ingreso %d corresponde a: \n\n" , pracPorIng.nroIngreso);
            mostrarUnIngreso(ingresoEncontrado->datosIngresoPac);
            system("pause");
        }
    }

    while(pracEncontrada == NULL){
        system("cls");

        printf("\n CARGANDO DATOS PR%cCTICAS POR INGRESO: \n\n" , 181);

        printf(" Ingresar nro. de pr%cctica: " , 160);
        scanf("%d" , &pracPorIng.nroPractica);

        pracEncontrada = buscarPractica(listaPrac , pracPorIng.nroPractica);

        if(pracEncontrada == NULL){
            printf("\n El nro. de pr%cctica no se encuentra registrada. \n\n" , 160);
            system("pause");
        }else{
            system("cls");
            printf("\n El nro. de pr%cctica %d corresponde a: \n\n" , 160 , pracPorIng.nroPractica);
            mostrarUnaPractica(pracEncontrada->datosPracticas);
        }
    }

    printf(" Ingresar resultado: ");
    fflush(stdin);
    gets(pracPorIng.resultado);

    return pracPorIng;
}

void guardarUnaPracticaPorIngreso(char nombreArchivo[] , practicaXingreso pracXing)
{
    practicaXingreso auxRegPracXing;
    FILE *pArchivo = fopen(nombreArchivo ,"ab");

    if(pArchivo != NULL){
        fwrite(&pracXing , sizeof(practicaXingreso) , 1 , pArchivo);
        fclose(pArchivo);
    }else{
        printf(" ERROR en el archivo de prac. por ing. \n\n");
    }
}

void mostrarArchPracticasPorIngreso(char nombreArchivo[])
{
    practicaXingreso auxPracXing;
    FILE *pArchivo = fopen(nombreArchivo , "rb");

    if(pArchivo != NULL){
        while(fread(&auxPracXing , sizeof(practicaXingreso) , 1 , pArchivo) > 0){
            mostrarUnaPracticaPorIngreso(auxPracXing);
        }
        fclose(pArchivo);
    }else{
        printf(" ERROR en la lectura del archivo prac. por ing. \n\n");
    }
}

void agregarPracticasPorIngreso(char nombreArchivo[] , nodoListaIngresos* listaIng, nodoListaPracticas* listaPrac)
{
    char continuar = 's';
    practicaXingreso pracPorIng;

    while(continuar == 's' || continuar == 'S'){
        system("cls");

        pracPorIng = cargaDatosPracticaPorIngreso(pracPorIng , listaPrac , listaIng);
        guardarUnaPracticaPorIngreso(nombreArchivo , pracPorIng);

        printf("\n %cQuires cargar mas resultados? s=SI / n=NO " , 168);
        fflush(stdin);
        continuar = getch();
        printf("\n\n");
    }
}

regPracticasPacientes buscarPracPacienteEnArch(char nombreArchivo[] , int nroPrac)
{
    regPracticasPacientes auxReg;
    regPracticasPacientes registroEncontrado;
    int flag = 0;
    FILE *pArchivo = fopen(nombreArchivo , "rb");

    if(pArchivo != NULL)
    {
        while(fread(&auxReg , sizeof(regPracticasPacientes) , 1 , pArchivo) > 0)
        {
            if(auxReg.nroPractica == nroPrac)
            {
                flag = 1;
                registroEncontrado = auxReg;
            }
        }
        fclose(pArchivo);
    }

    return registroEncontrado;
}

regPracticasPacientes editarPracPaciente(char nombreArchivo[] , regPracticasPacientes regPracPaciente)
{
    regPracticasPacientes auxPxi;
    char continuar = 's';
    int opEditarDatosPxi = 0;

    auxPxi = buscarPracPacienteEnArch(nombreArchivo , regPracPaciente.nroPractica);

    if(auxPxi.nroPractica == regPracPaciente.nroPractica)
    {
        system("cls");

        printf("\n El resultado de la practica corresponde a: \n\n");
        mostrarUnRegPaciente(regPracPaciente);

        printf(" Ingresar  resultado: ");
        fflush(stdin);
        gets(auxPxi.resultado);

    }
    else
    {
        printf(" La pr%cctica aun no se encuentra registrada. o no existe. \n\n" , 160);
    }

    return auxPxi;
}

void cargarResultadoPractica(char nombreArchPracPaciente[] , int nroPrac)
{
    regPracticasPacientes auxRegPxi;
    int flag = 0;
    FILE* pArchivoPxi = fopen(nombreArchPracPaciente , "r+b");

    if(pArchivoPxi != NULL)
    {
        while((flag == 0) && (fread(&auxRegPxi , sizeof(practicaXingreso) , 1 , pArchivoPxi) > 0))
        {
            if(auxRegPxi.nroPractica == nroPrac)
            {
                flag = 1;
                fseek(pArchivoPxi , (-1) * sizeof(regPracticasPacientes) , SEEK_CUR);
                auxRegPxi = editarPracPaciente(nombreArchPracPaciente , auxRegPxi);
                fwrite(&auxRegPxi , sizeof(regPracticasPacientes) , 1 , pArchivoPxi);
            }
        }
        fclose(pArchivoPxi);
    }
}

void modificarPxi(char nombreArchivo[] , int nroPract)
{
    regPracticasPacientes auxRegPxi;
    int flag = 0;
    FILE *pArchivoPxi = fopen(nombreArchivo , "r+b");

    if(pArchivoPxi != NULL){
        while((flag == 0) && (fread(&auxRegPxi , sizeof(practicaXingreso) , 1 , pArchivoPxi) > 0)){
            if(auxRegPxi.nroPractica = nroPract){
                flag = 1;
                fseek(pArchivoPxi , (-1) * sizeof(regPracticasPacientes) , SEEK_CUR);
                auxRegPxi = editarPracPaciente(nombreArchivo , auxRegPxi);
                fwrite(&auxRegPxi , sizeof(regPracticasPacientes) , 1 , pArchivoPxi);
            }
        }
        fclose(pArchivoPxi);
    }
}

/// --------------------------- FIN FUNCIONES ARCHIVO - PRÁCTICAS POR INGRESOS -------------------- ///

/// ---------------------------------------- FUNCIONES ADL --------------------------------------- ///
nodoarbol* altaAdl(nodoarbol* adl, paciente pac, ingresos ingPac)
{
    nodoListaIngresos* nuevoIng = crearNodoIngreso(ingPac);
    nodoarbol* pacienteEncontrado = buscarPacienteArbol(adl, pac.dni);

    if(pacienteEncontrado == NULL)
    {
        adl = insertar(adl, pac);
        pacienteEncontrado = buscarPacienteArbol(adl, pac.dni);
    }

    pacienteEncontrado->listaIng = agregarEnOrdenListaIngresos(pacienteEncontrado->listaIng, nuevoIng);

    return adl;
}

nodoarbol* cargaAdlPacientes(char nombreArchPac[], nodoarbol* adl, char nombreArchIng[])
{
    paciente auxRegPac;
    ingresos auxRegIng;

    FILE* pArchivoPac = fopen(nombreArchPac, "rb");
    FILE* pArchivoIng = fopen(nombreArchIng, "rb");

    if((pArchivoPac != NULL) && (pArchivoIng != NULL)){
        while(fread(&auxRegPac , sizeof(paciente) , 1 , pArchivoPac) > 0){
            rewind(pArchivoIng);
            while(fread(&auxRegIng , sizeof(ingresos) , 1 , pArchivoIng) > 0){
                if(strcmp(auxRegIng.dniPaciente , auxRegPac.dni) == 0){
                    adl = altaAdl(adl , auxRegPac , auxRegIng);
                }
            }
        }
    }

    return adl;
}

void mostrarAdlPacientes(nodoarbol* adl)
{
    if(adl != NULL){
        mostrarAdlPacientes(adl->izq);
        mostrarPaciente(adl->dato);
        mostrarListaIngresos(adl->listaIng);
        //mostrarListaPractica(adl->listaIng->listaPrac);
        mostrarAdlPacientes(adl->der);
    }
}

/// -------------------------------------- FIN FUNCIONES ADL ------------------------------------ ///

nodoListaIngresos* cargarPractica(nodoListaIngresos* listaIngresos, int nroIngreso, char archiPracticas[])
{
    nodoListaIngresos* auxIngresos = listaIngresos;
    practicas regPractica;
    int eleccionPractica = 0;
    char eleccion = 's';
    printf("\n Agregue una practica\n\n");
    int flag = 0;

    FILE* archiPractica = fopen(archiPracticas, "rb");

    if (archiPractica != NULL)
    {
        while(auxIngresos != NULL && eleccion == 's')
        {
            flag = 0;
            rewind(archiPractica);
            printf(" LISTA DE PRACTICAS: \n\n");
            mostrarArchPracticas("practicasLab.dat");
            printf("\n Que practica desea agregar?\n");
            fflush(stdin);
            scanf("%i", &eleccionPractica);

            while ((flag == 0) && (fread(&regPractica, sizeof(practicas), 1, archiPractica) > 0))
            {
                if (eleccionPractica == regPractica.nroPractica)
                {
                    flag = 1;
                    nodoListaPracXingreso* nuevoNodo = crearNodoPracPorIngreso(regPractica, nroIngreso);
                    auxIngresos->listaPrac = agregarInicioListaPracPorIngreso(auxIngresos->listaPrac, nuevoNodo);
                }
            }
            printf("\n PR%cCTICA CARDA CON %cXITO: \n\n" , 181 , 144);
            mostrarUnaPracticaPorIngreso(auxIngresos->listaPrac->datos);

            printf("\n\n Desea cargar otra practica?s/n\n");
            fflush(stdin);
            scanf("%c", &eleccion);

        }

        fclose(archiPractica);
    }
    else
    {
        printf("Error al abrir el archivo de practicas.\n");
    }

    system("cls");
    printf("\n LISTA DE PRACTICAS CARGADAS: \n\n");
    mostrarListaPracPorIngreso(auxIngresos->listaPrac);
    system("pause");

    return auxIngresos;
}

void mostrarEstudioPaciente(nodoListaIngresos* listaIngresos, UsuarioPaciente usuario)
{

    nodoListaIngresos* auxIngresos = listaIngresos;
    nodoListaPracXingreso* auxPxi = listaIngresos->listaPrac;

    if (auxIngresos)
    {
        printf("Llego2\n");

        while (auxIngresos)
        {
            printf("Llego3\n");
            mostrarUnIngreso(auxIngresos->datosIngresoPac);
            auxIngresos=auxIngresos->siguiente;
        }

        printf("Llego4\n");
        int i = 0;
        printf("Ponga el numero del ingreso que desea ver.\n");
        fflush(stdin);
        scanf("%i", &i);

        // Restaurar el puntero al comienzo de la lista de ingresos
        auxIngresos = listaIngresos;

        if(auxIngresos->datosIngresoPac.nroIngreso == i)
        {
            auxPxi = auxIngresos->listaPrac;

            while(auxPxi != NULL)
            {
                mostrarUnaPracticaPorIngreso(auxPxi->datos);
                auxPxi = auxPxi->siguiente;
            }
        }
        else
        {
               auxIngresos = auxIngresos->siguiente;
        }

    }
    else
    {
        printf("Numero de practica incorrecto.\nSaliendo del sistema.\n");
    }
}
