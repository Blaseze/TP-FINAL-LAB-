#include "paciente.h"

/// ---------------------------- FUNCIONES CREACION USUARIO --------------------------------------- ///
void crearUsuarioPaciente(paciente pacienteUsu)
{
    UsuarioPaciente usuarioP;
    FILE* archiUsuarios=fopen("UsuariosPacientes.txt","a+");


    if(archiUsuarios)
    {
        strcpy(usuarioP.usuarioPaciente,pacienteUsu.dni);
        strcpy(usuarioP.contrasenia,pacienteUsu.dni);
        usuarioP.nivel=0;//dejo el inicio en 0 aunque me llene con basura
    fwrite(&usuarioP,sizeof(UsuarioPaciente),1,archiUsuarios);

        fclose(archiUsuarios);
    }
}
void cambiarContraseniaPacientes(char archivoUsuPaciente[30], UsuarioPaciente usuPaciente)
{
    UsuarioPaciente registroPaciente;

    FILE *archiUsuaPaciente = fopen(archivoUsuPaciente, "r+");

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
/// ---------------------------- FUNCIONES PACIENTE ----------------------------------------------- ///
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
    FILE *archi= fopen(nombreArchivo,"r+");

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

        printf("\n %cDesea cargar otro paciente? S/N ", 168);
        fflush(stdin);
        continuar=getch();
        printf("\n\n");
    }
}

void guardaUnaPersona(char nombreArchivo[],paciente perso)
{
    FILE *archi=fopen(nombreArchivo,"a+");

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

    nuevoPaciente.eliminados=0;
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
    FILE *archi=fopen(nombreArchivo,"r");

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

nodoarbol *insertar(nodoarbol *arbol,paciente dato)
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

nodoarbol* buscarPacienteArbol(nodoarbol* arbol, char dniPaciente[])
{
    nodoarbol* encontrado = NULL;

    if(arbol != NULL)
    {
        if(strcmp(dniPaciente, arbol->dato.dni) == 0)
        {
            encontrado = arbol;
        }
        else
        {
            if(strcmp(dniPaciente, arbol->dato.dni) < 0)
            {
                encontrado = buscarPacienteArbol(arbol->izq, dniPaciente);
            }
            else
            {
                encontrado = buscarPacienteArbol(arbol->der, dniPaciente);
            }
        }
    }

    return encontrado;
}

nodoarbol* pasarArchPacienteToArbol(char nombreArchivo[], nodoarbol* arbol)
{
    paciente auxReg;
    FILE *pArchivo = fopen(nombreArchivo, "r");

    if(pArchivo != NULL)
    {
        while(fread(&auxReg, sizeof(paciente), 1, pArchivo) > 0)
        {
            arbol = insertar(arbol, auxReg);
        }
        fclose(pArchivo);
    }
    else
    {
        printf(" ERROR en la lectura del archivo. \n\n");
    }

    return arbol;
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

nodoListaPaciente* agregarInicioListaPaciente(nodoListaPaciente* listaPac, nodoListaPaciente* nuevoNodoPac)
{
    if(listaPac == NULL)
    {
        listaPac = nuevoNodoPac;
    }
    else
    {
        nuevoNodoPac->siguiente = listaPac;
        listaPac = nuevoNodoPac;
    }

    return listaPac;
}

nodoListaPaciente* agregarEnOrdenListaPaciente(nodoListaPaciente* listaPac, nodoListaPaciente* nuevoNodoPac)
{
    if(listaPac == NULL)
    {
        listaPac = nuevoNodoPac;
    }
    else
    {
        if(strcmpi(nuevoNodoPac->datosPac.apellidoYnombre, listaPac->datosPac.apellidoYnombre) < 0)
        {
            listaPac = agregarInicioListaPaciente(listaPac, nuevoNodoPac);
        }
        else
        {
            nodoListaPaciente* ante = listaPac;
            nodoListaPaciente* seg = listaPac->siguiente;

            while((seg != NULL) && (strcmpi(nuevoNodoPac->datosPac.apellidoYnombre, seg->datosPac.apellidoYnombre) > 0))
            {
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

    if(seg != NULL)
    {
        while(seg != NULL)
        {
            mostrarPaciente(seg->datosPac);
            seg = seg->siguiente;
        }
    }
}

nodoListaPaciente* pasarArchPacToListaPac(char nombreArchivo[], nodoListaPaciente* listaPac)
{
    paciente auxRegPac;
    FILE *pArchivo = fopen(nombreArchivo, "r");

    if(pArchivo != NULL)
    {
        nodoListaPaciente* nodoPaciente;
        while(fread(&auxRegPac, sizeof(paciente), 1, pArchivo) > 0)
        {
            nodoPaciente = crearNodoPaciente(auxRegPac);
            listaPac = agregarEnOrdenListaPaciente(listaPac, nodoPaciente);
        }
        fclose(pArchivo);
    }

    return listaPac;
}

/// ------------------------------ FIN FUNCIONES DE LISTA - PACIENTE ------------------------------ ///

/// ----------------------------- FUNCIONES DE INGRESOS PACIENTE ----------------------------------- ///
ingresos cargaDatosIngresos(nodoarbol* arbol, ingresos ingresoPaciente)
{
    int fechaIngresoValida = 0;
    int fechaRetiroValida = 0;
    nodoarbol* encontrado;
    int matriculaValida = 0;
    nodoListaPracticas*aux=arbol->listaIng->listaPrac;
    practicas auxPracticas;

    while(fechaIngresoValida != 1)
    {
        system("cls");

        printf("\n CARGANDO INGRESO... \n\n");

        printf(" Ingresar fecha de ingreso: ");
        fflush(stdin);
        gets(ingresoPaciente.fechaIngreso);

        fechaIngresoValida = validarFecha(ingresoPaciente.fechaIngreso);

        if(fechaIngresoValida != 1)
        {
            printf("\n La fecha ingresa no es v%clida. \n\n", 160);
            system("pause");
        }
    }

    while(fechaRetiroValida != 1)
    {
        system("cls");

        printf("\n CARGANDO INGRESO... \n\n");

        printf(" Ingresar fecha de retiro: ");
        fflush(stdin);
        gets(ingresoPaciente.fechaRetiro);

        fechaRetiroValida = validarFecha(ingresoPaciente.fechaRetiro);

        if(fechaRetiroValida != 1)
        {
            printf("\n La fecha ingresa no es v%clida. \n\n", 160);
            system("pause");
        }
    }

    do
    {
        system("cls");

        printf("\n CARGANDO INGRESO... \n\n");

        printf(" Ingresar DNI del paciente: ");
        fflush(stdin);
        gets(ingresoPaciente.dniPaciente);

        encontrado = buscarPacienteArbol(arbol, ingresoPaciente.dniPaciente);

        if(encontrado == NULL)
        {
            printf("\n El DNI ingresado no se encuentra registrado o no es v%clido. \n\n", 160);
            system("pause");
        }

    }
    while(encontrado == NULL);

    while(matriculaValida != 1)
    {
        system("cls");

        printf("\n CARGANDO INGRESO... \n\n");

        printf(" Ingresar matr%ccula del profesional: ", 161);
        fflush(stdin);
        gets(ingresoPaciente.matriculaProfesional);

        matriculaValida = validarMatricula(ingresoPaciente.matriculaProfesional);

        if(matriculaValida != 1)
        {
            printf("\n La matr%ccula ingresada no es v%clida. \n\n", 161, 160);
            system("pause");
        }
    }

    ingresoPaciente.eliminado = 0;


    auxPracticas=cargaDatosPrac(auxPracticas);
    nodoListaPracticas*nuevaPractica=crearNodoPractica(auxPracticas);
    aux=agregarEnOrdenListaPracticas(aux,nuevaPractica);

    return ingresoPaciente;
}

void mostrarUnIngreso(ingresos ingresoPaciente)
{
    printf("======================================================= \n");
    printf(" N%c Ingreso.......................: %d \n", 248, ingresoPaciente.nroIngreso);
    printf(" Fecha de ingreso.................: %s \n", ingresoPaciente.fechaIngreso);
    printf(" Fecha de retiro..................: %s \n", ingresoPaciente.fechaRetiro);
    printf(" DNI del paciente.................: %s \n", ingresoPaciente.dniPaciente);
    printf(" Matr%cula del profesional.........: %s \n", 161, ingresoPaciente.matriculaProfesional);
    if(ingresoPaciente.eliminado == 0)
    {
        printf(" Estado...........................: ALTA \n");
    }
    else
    {
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

    if(longitudFecha == 0 || longitudFecha < 6 || longitudFecha > 11 || fecha[0] == 32)   //verifico que no se ingrese una
    {
        //fecha "en blanco" y que la cantidad
        //de caracteres sea el correcto
        fechaValida = 0;
    }
    else
    {
        while((i < longitudFecha) && (fechaValida == 1))
        {
            if((fecha[i] >= 48 && fecha[i] <= 57) || (fecha[i] == 47) || (fecha[i] == 45))
            {
                i++;
            }
            else
            {
                fechaValida = 0;
            }
        }
    }

    if(longitudFecha != 0)
    {
        exitoConversionFecha = convertirFecha(fecha); //verifico que la fecha tenga el formato correcto:
        //dd/mm/aaaa ; d/m/aa ; dd/mm/aa ó dd-mm-aaaa ; dd-mm-aa ; d-m-aa

        if(exitoConversionFecha == 1)
        {
            fechaValida = 1;
        }
        else
        {
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

    if(sscanf(fecha, "%d/%d/%d", &dia, &mes, &year) == 3)      // Intenta convertir la fecha en formato dd/mm/aaaa
    {
        if((dia >= 1 && dia <= 31) && (mes >= 1 && mes <= 12) && ((year >= 2023 && year <= 2033) || (year >= 23 && year <= 33)))
        {
            fechaValida = 1;
        }
    }

    if(sscanf(fecha, "%d-%d-%d", &dia, &mes, &year) == 3)      // Intenta convertir la fecha en formato dd-mm-aaaa
    {
        if((dia >= 1 && dia <= 31) && (mes >= 1 && mes <= 12) && ((year >= 2023 && year <= 2033) || (year >= 23 && year <= 33)))
        {
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

    if(longitudMatricula == 0 || matriculaProf[0] == 32 || longitudMatricula > 11)
    {
        matriculaValida = 0;
    }
    else
    {
        while((i < longitudMatricula) && (matriculaValida == 1))
        {
            if((matriculaProf[i] >= 40 && matriculaProf[i] <= 57) || //numeros del 0 - 9
                    (matriculaProf[i] >= 65 && matriculaProf[i] <= 90) || //letras mayúsculas A-Z
                    (matriculaProf[i] >= 97 && matriculaProf[i] <= 122) || //letras minúsculas a-z
                    matriculaProf[i] == 32 || matriculaProf[i] == 46)  // espacio y '.'
            {

                i++;
            }
            else
            {
                matriculaValida = 0;
            }
        }
    }

    return matriculaValida;
}
///FIN FUNCIONES DE VALIDACIONES DE INGRESOS - PACIENTE

///FUNCIONES ARCHIVO INGRESOS
void agregarIngreso(char nombreArchivo[], nodoarbol* arbol)
{
    char continuar = 's';
    ingresos ingPaciente;

    while(continuar == 's' || continuar == 'S')
    {
        system(" cls");

        ingPaciente.nroIngreso = ultimoIngresoArch(nombreArchivo);

        ingPaciente.nroIngreso++;

        ingPaciente = cargaDatosIngresos(arbol, ingPaciente);
        guardarUnIngreso(nombreArchivo, ingPaciente);

        printf("\n %cQuires agregar otro ingreso? s=SI / n=NO \n", 168);
        fflush(stdin);
        continuar = getch();
    }
}

void guardarUnIngreso(char nombreArchivo[], ingresos ingPac)
{
    FILE* pArchivo = fopen(nombreArchivo, "a+");

    if(pArchivo != NULL)
    {
        fwrite(&ingPac, sizeof(ingresos), 1, pArchivo);
        fclose(pArchivo);
    }
    else
    {
        printf(" ERROR en la apertura del archivo ingresos. \n\n");
    }
}

void mostrarArchIngresos(char nombreArchivo[])
{
    ingresos ingPac;
    FILE *pArchivo = fopen(nombreArchivo, "r");

    if(pArchivo != NULL)
    {
        while(fread(&ingPac, sizeof(ingresos), 1, pArchivo) > 0)
        {
            mostrarUnIngreso(ingPac);
        }
        fclose(pArchivo);
    }
    else
    {
        printf("\n NO hay ingresos registrados. \n\n");
    }
}

int ultimoIngresoArch(char nombreArchivo[])
{
    ingresos auxRegIng;
    int ultimoIng = 0;
    FILE *pArchivo = fopen(nombreArchivo, "r");

    if(pArchivo != NULL)
    {
        fseek(pArchivo, (-1) * sizeof(ingresos), SEEK_END);

        if(fread(&auxRegIng, sizeof(ingresos), 1, pArchivo) > 0)
        {
            ultimoIng = auxRegIng.nroIngreso;
        }

        fclose(pArchivo);
    }

    return ultimoIng;
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

nodoListaIngresos* agregarInicioListaIngresos(nodoListaIngresos* listaIngresos, nodoListaIngresos* nuevoNodoIngreso)
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

nodoListaIngresos* agregarEnOrdenListaIngresos(nodoListaIngresos* listaIngresos, nodoListaIngresos* nuevoNodoIngreso)
{
    if(listaIngresos == NULL)
    {
        listaIngresos = nuevoNodoIngreso;
    }
    else
    {
        if(strcmpi(nuevoNodoIngreso->datosIngresoPac.fechaIngreso, listaIngresos->datosIngresoPac.fechaIngreso) > 0)
        {
            listaIngresos = agregarInicioListaIngresos(listaIngresos, nuevoNodoIngreso);
        }
        else
        {
            nodoListaIngresos *ante = listaIngresos;
            nodoListaIngresos *seg = listaIngresos->siguiente;

            while((seg != NULL) && (strcmpi(nuevoNodoIngreso->datosIngresoPac.fechaIngreso, listaIngresos->datosIngresoPac.fechaIngreso) < 0))
            {
                ante = seg;
                seg = seg->siguiente;
            }

            ante->siguiente = nuevoNodoIngreso;
            nuevoNodoIngreso->siguiente = seg;
        }
    }

    return listaIngresos;
}

void mostrarListaIngresos(nodoListaIngresos* listaIngresos)
{
    nodoListaIngresos* seg = listaIngresos;

    if(seg != NULL)
    {
        while(seg != NULL)
        {
            mostrarUnIngreso(seg->datosIngresoPac);
            seg = seg->siguiente;
        }
    }
}

nodoListaIngresos* buscarIngresoPorNumIngreso(nodoListaIngresos* listaIng, int numIngreso)
{
    nodoListaIngresos* ingresoEncontrado = NULL;
    nodoListaIngresos* seg = listaIng;

    if(seg != NULL)
    {
        while((seg != NULL) && (ingresoEncontrado == NULL))
        {
            if(seg->datosIngresoPac.nroIngreso == numIngreso)
            {
                ingresoEncontrado = seg;
            }
            else
            {
                seg = seg->siguiente;
            }
        }
    }

    return ingresoEncontrado;
}

ingresos buscarIngresoPorDni(nodoListaIngresos* listaIng, char dniPac[])
{
    ingresos ingEncontrado;
    int flag = 0;
    nodoListaIngresos* seg = listaIng;

    if(seg != NULL)
    {
        while((seg != NULL) && (flag == 0))
        {
            if(strcmp(seg->datosIngresoPac.dniPaciente, dniPac) == 0)
            {
                flag = 1;
                ingEncontrado = seg->datosIngresoPac;
            }
            else
            {
                seg = seg->siguiente;
            }
        }
    }

    return ingEncontrado;
}

nodoListaIngresos* pasarArchToListaIng(char nombreArchivo[], nodoListaIngresos* listaIng)
{
    ingresos auxRegIng;
    FILE *pArchivo = fopen(nombreArchivo, "r");

    if(pArchivo != NULL)
    {
        nodoListaIngresos* nuevoIng;
        while(fread(&auxRegIng, sizeof(ingresos), 1, pArchivo) > 0)
        {
            nuevoIng = crearNodoIngreso(auxRegIng);
            listaIng = agregarEnOrdenListaIngresos(listaIng, nuevoIng);
        }
        fclose(pArchivo);
    }
    else
    {
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

nodoListaPracXingreso* crearNodoPracPorIngreso(practicaXingreso prac)
{
    nodoListaPracXingreso* auxNodoPracXingreso = (nodoListaPracXingreso *)malloc(sizeof(nodoListaPracXingreso));

    auxNodoPracXingreso->datos = prac;
    auxNodoPracXingreso->siguiente = NULL;

    return auxNodoPracXingreso;
}

nodoListaPracXingreso* agregarEnOrdenListaPracPorIngreso(nodoListaPracXingreso* listaPracPorIngreso, nodoListaPracXingreso* nuevoNodoPracPorIngreso)
{
    if(listaPracPorIngreso == NULL)
    {
        listaPracPorIngreso = nuevoNodoPracPorIngreso;
    }
    else
    {
        if(nuevoNodoPracPorIngreso->datos.nroIngreso < listaPracPorIngreso->datos.nroIngreso)
        {
            listaPracPorIngreso = agregarInicioListaPracPorIngreso(listaPracPorIngreso, nuevoNodoPracPorIngreso);
        }
        else
        {
            nodoListaPracXingreso* ante = listaPracPorIngreso;
            nodoListaPracXingreso* seg = listaPracPorIngreso->siguiente;

            while((seg != NULL) && (nuevoNodoPracPorIngreso->datos.nroIngreso > listaPracPorIngreso->datos.nroIngreso))
            {
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

    if(seg != NULL)
    {
        while(seg != NULL)
        {
            mostrarUnaPracticaPorIngreso(seg->datos);
            seg = seg->siguiente;
        }
    }
}

///FUNCIONES AUXILIARES - PRÁCTICAS POR INGRESO
nodoListaPracXingreso* agregarInicioListaPracPorIngreso(nodoListaPracXingreso* listaPracPorIngreso, nodoListaPracXingreso* nuevoNodoPracPorIngreso)
{
    if(listaPracPorIngreso == NULL)
    {
        listaPracPorIngreso = nuevoNodoPracPorIngreso;
    }
    else
    {
        nuevoNodoPracPorIngreso->siguiente = listaPracPorIngreso;
        listaPracPorIngreso = nuevoNodoPracPorIngreso;
    }

    return listaPracPorIngreso;
}

void mostrarUnaPracticaPorIngreso(practicaXingreso prac)
{
    printf("*********************************** \n");
    printf(" N%c de ingreso..............: %d \n", 248, prac.nroIngreso);
    printf(" N%c de practica.............: %d \n", 248, prac.nroPractica);
    printf(" Resultado..................: %s \n", prac.resultado);
    printf("*********************************** \n\n");
}

/// ----------------------------- FIN DE FUNCIONES DE LISTA - PRÁCTICAS POR INGRESO ---------------- ///

/// ----------------------------- FUNCIONES ARCHIVO - PRÁCTICAS POR INGRESOS ---------------------- ///
practicaXingreso cargaDatosPracticaPorIngreso(practicaXingreso pracPorIng, nodoListaPracticas* listaPrac, nodoListaIngresos* listaIng)
{
    nodoListaIngresos* ingresoEncontrado = 0;
    nodoListaPracticas* pracEncontrada = NULL;

    while(ingresoEncontrado == 0)
    {
        system("cls");

        printf("\n CARGANDO DATOS PR%cCTICAS POR INGRESO: \n\n", 181);

        printf(" Ingresar nro. de ingreso: ");
        scanf("%d", &pracPorIng.nroIngreso);

        ingresoEncontrado = buscarIngresoPorNumIngreso(listaIng, pracPorIng.nroIngreso);

        if(ingresoEncontrado == 0)
        {
            printf("\n El nro. de ingreso no se encuentra registrado. \n\n");
            system("pause");
        }
        else
        {
            system("cls");
            printf("\n El nro de ingreso %d corresponde a: \n\n", pracPorIng.nroIngreso);
            mostrarUnIngreso(ingresoEncontrado->datosIngresoPac);
            system("pause");
        }
    }

    while(pracEncontrada == NULL)
    {
        system("cls");

        printf("\n CARGANDO DATOS PR%cCTICAS POR INGRESO: \n\n", 181);

        printf(" Ingresar nro. de pr%cctica: ", 160);
        scanf("%d", &pracPorIng.nroPractica);

        pracEncontrada = buscarPractica(listaPrac, pracPorIng.nroPractica);

        if(pracEncontrada == NULL)
        {
            printf("\n El nro. de pr%cctica no se encuentra registrada. \n\n", 160);
            system("pause");
        }
        else
        {
            system("cls");
            printf("\n El nro. de pr%cctica %d corresponde a: \n\n", 160, pracPorIng.nroPractica);
            mostrarUnaPractica(pracEncontrada->datosPracticas);
        }
    }

    printf(" Ingresar resultado: ");
    fflush(stdin);
    gets(pracPorIng.resultado);

    return pracPorIng;
}

void guardarUnaPracticaPorIngreso(char nombreArchivo[], practicaXingreso pracXing)
{
    practicaXingreso auxRegPracXing;
    FILE *pArchivo = fopen(nombreArchivo,"a+");

    if(pArchivo != NULL)
    {
        fwrite(&pracXing, sizeof(practicaXingreso), 1, pArchivo);
        fclose(pArchivo);
    }
    else
    {
        printf(" ERROR en el archivo de prac. por ing. \n\n");
    }
}

void mostrarArchPracticasPorIngreso(char nombreArchivo[])
{
    practicaXingreso auxPracXing;
    FILE *pArchivo = fopen(nombreArchivo, "r");

    if(pArchivo != NULL)
    {
        while(fread(&auxPracXing, sizeof(practicaXingreso), 1, pArchivo) > 0)
        {
            mostrarUnaPracticaPorIngreso(auxPracXing);
        }
        fclose(pArchivo);
    }
    else
    {
        printf(" ERROR en la lectura del archivo prac. por ing. \n\n");
    }
}

void agregarPracticasPorIngreso(char nombreArchivo[], nodoListaIngresos* listaIng, nodoListaPracticas* listaPrac)
{
    char continuar = 's';
    practicaXingreso pracPorIng;

    while(continuar == 's' || continuar == 'S')
    {
        system("cls");

        pracPorIng = cargaDatosPracticaPorIngreso(pracPorIng, listaPrac, listaIng);
        guardarUnaPracticaPorIngreso(nombreArchivo, pracPorIng);

        printf("\n %cQuires cargar mas resultados? s=SI / n=NO ", 168);
        fflush(stdin);
        continuar = getch();
        printf("\n\n");
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

void mostrarAdlPacientes(nodoarbol* adl)
{
    if(adl != NULL)
    {
        mostrarAdlPacientes(adl->izq);
        mostrarPaciente(adl->dato);
        mostrarListaIngresos(adl->listaIng);
        mostrarAdlPacientes(adl->der);
    }
}

nodoarbol* cargaAdlPacientes(char nombreArchPac[], nodoarbol* adl, char nombreArchIng[])
{
    paciente auxRegPac;
    ingresos auxRegIng;

    FILE* pArchivoPac = fopen(nombreArchPac, "r");
    FILE* pArchivoIng = fopen(nombreArchIng, "r");

    if((pArchivoPac != NULL) && (pArchivoIng != NULL))
    {
        while(fread(&auxRegPac, sizeof(paciente), 1, pArchivoPac) > 0)
        {
            rewind(pArchivoIng);
            while(fread(&auxRegIng, sizeof(ingresos), 1, pArchivoIng) > 0)
            {
                if(strcmp(auxRegIng.dniPaciente, auxRegPac.dni) == 0)
                {
                    adl = altaAdl(adl, auxRegPac, auxRegIng);
                }
            }
        }
    }

    return adl;
}

/// -------------------------------------- FIN FUNCIONES ADL ------------------------------------ ///
/// Funciones extrasssssssssss
void mostrarEstudioPaciente(nodoarbol* arbol, UsuarioPaciente usuario)
{
    arbol = buscarPacienteArbol(arbol, usuario.usuarioPaciente);

    if (arbol)
    {
        nodoListaIngresos* aux = arbol->listaIng;


        while (aux)
        {
            mostrarUnIngreso(aux->datosIngresoPac);
            aux=aux->siguiente;
        }

        int i = 0;
        printf("Ponga el numero del ingreso que desea ver.\n");
        fflush(stdin);
        scanf("%i", &i);

        // Restaurar el puntero al comienzo de la lista de ingresos
        aux = arbol->listaIng;

        while (aux)
        {
            if (aux->datosIngresoPac.nroIngreso == i)
            {
                while (aux->listaPrac)
                {
                    mostrarUnaPractica(aux->listaPrac->datosPracticas);
                    aux->listaPrac = aux->listaPrac->siguiente;
                }
            }
            arbol->listaIng = arbol->listaIng->siguiente;
        }
    }
    else
    {
        printf("Numero de practica incorrecto.\nSaliendo del sistema.\n");
    }
}
