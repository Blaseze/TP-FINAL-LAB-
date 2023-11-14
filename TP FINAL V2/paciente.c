#include "paciente.h"

/// ---------------------------- FUNCIONES PACIENTE ----------------------------------------------- ///
paciente cargaPaciente(nodoarbol* arbol , paciente nuevoPaciente)
{
    int nombreOk=0;
    int edadOk=0;
    int dniOk=0;
    int existeDni = 0;
    int direccionOk=0;
    int telOk=0;


        while(nombreOk!=1)
        {
            system("cls");
            printf("\n ---------------Cargando datos del paciente---------------\n\n");
            printf("Ingrese Nombre y Apellido: ");
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
            printf("\n ---------------Cargando datos del paciente---------------\n\n");
            printf("Ingrese la Edad: ");
            scanf("%i",&nuevoPaciente.edad);
            edadOk=verificaEdad(nuevoPaciente.edad);

            if(edadOk!=1)
            {
                printf("\nEdad no valida, ingrese edad nuevamente.\n\n");
                system("pause");

            }
        }

        while(dniOk!=1 || existeDni==1)
        {

            system("cls");
            printf("\n ---------------Cargando datos del paciente---------------\n\n");
            printf("Ingrese el DNI: ");
            fflush(stdin);
            gets(nuevoPaciente.dni);

            existeDni=buscarPacienteArbol(arbol , nuevoPaciente.dni);
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
            printf("\n ---------------Cargando datos del paciente---------------\n\n");
            printf("Ingrese el domicilio: ");
            gets(nuevoPaciente.direccion);

            direccionOk= verificaDireccion(nuevoPaciente.direccion);

            if(direccionOk!=1)
            {
                printf("\nLa direccion ingresada no es correcta. \n\n");
                system("pause");
            }
        }

        while(telOk!=1)
        {
            system("cls");
            printf("\n ---------------Cargando datos del paciente---------------\n\n");
            printf("Ingrese un telefono: ");
            gets(nuevoPaciente.telefono);

            telOk=verificaTelefono(nuevoPaciente.telefono);

            if(telOk!=1)
            {
                printf("\nEl telefono ingresado no es correcto.\n\n");
                system("pause");

            }

        }

        nuevoPaciente.eliminados=0;

    return nuevoPaciente;
}

int verificaExistenciaPaciente(nodoarbol* arbol , char dniPaciente[])
{
    int existe=0;

    if(arbol != NULL && existe == 0)
    {
        if(strcmpi(arbol->dato.dni , dniPaciente) == 0){
            existe = 1;
        }else{
            if(strcmpi(arbol->dato.dni , dniPaciente) < 0){
                existe = verificaExistenciaPaciente(arbol->izq , dniPaciente);
            }else{
                existe = verificaExistenciaPaciente(arbol->der , dniPaciente);
            }
        }
    }

    return existe;
}

void mostrarPaciente(paciente persona)
{
    printf("--------------------------------------------------------\n");
    printf(" Apellido y Nombre---------------: %s\n",persona.apellidoYnombre);
    printf(" Edad----------------------------: %d\n",persona.edad);
    printf(" DNI-----------------------------: %s\n",persona.dni);
    printf(" Direccion-----------------------: %s\n",persona.direccion);
    printf(" Telefono------------------------: %s\n",persona.telefono);
    printf("--------------------------------------------------------\n\n");
}
/// ---------------------------- FIN FUNCIONES PACIENTE ------------------------------------------- ///

/// ---------------------------- FUNCIONES DE VALIDACIONES - PACIENTES ---------------------------- ///
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
    aux->listaIngresosPac = inicListaIngresos();

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

nodoarbol* buscarPacienteArbol(nodoarbol* arbol , char dniPaciente[])
{
    nodoarbol* encontrado = NULL;

    if(arbol != NULL){
        if(strcmpi(dniPaciente , arbol->dato.dni) < 0){
            encontrado = buscarPacienteArbol(arbol->izq , dniPaciente);
        }else{
             encontrado = buscarPacienteArbol(arbol->der , dniPaciente);
        }
    }

    return encontrado;
}

nodoarbol* cargaArbolPacientes(nodoarbol* arbol)
{
    paciente nuevoPac;
    nodoarbol* nodoPac;
    char continuar = 's';

    while(continuar == 's' || continuar == 'S'){
        system("cls");

        printf(" CARGANDO PACIENTES... \n\n");

        nuevoPac = cargaPaciente(arbol , nuevoPac);
        arbol = insertar(arbol , nuevoPac);

        printf("\n %cQuieres cargar otro paciente? s=SI / n=NO ");
        fflush(stdin);
        continuar = getch();
        printf("\n\n");
    }

    return arbol;
}
/// ----------------------------- FIN FUNCIONES DE ÁRBOL - PACIENTE -------------------------------- ///

/// ----------------------------- FUNCIONES DE INGRESOS PACIENTE ----------------------------------- ///
ingresos cargaDatosIngresos(nodoarbol *arbol , ingresos ingresoPaciente)
{
    int fechaIngresoValida = 0;
    int fechaRetiroValida = 0;
    nodoarbol* encontrado = NULL;
    int matriculaValida = 0;

    while(fechaIngresoValida != 1){
        printf(" \n Ingresar fecha de ingreso: ");
        fflush(stdin);
        gets(ingresoPaciente.fechaIngreso);

        fechaIngresoValida = validarFecha(ingresoPaciente.fechaIngreso);

        if(fechaIngresoValida != 1){
            printf("\n La fecha ingresa no es v%clida. \n\n" , 160);
            system("pause");
            system("cls");
        }
    }

    while(fechaRetiroValida != 1){
        printf(" \n Ingresar fecha de retiro: ");
        fflush(stdin);
        gets(ingresoPaciente.fechaRetiro);

        fechaRetiroValida = validarFecha(ingresoPaciente.fechaRetiro);

        if(fechaRetiroValida != 1){
            printf("\n La fecha ingresa no es v%clida. \n\n" , 160);
            system("pause");
            system("cls");
        }
    }

    while(encontrado == NULL){
        printf("\n Ingresar DNI del paciente: ");
        fflush(stdin);
        gets(ingresoPaciente.dniPaciente);

        encontrado = buscarPacienteArbol(arbol , ingresoPaciente.dniPaciente);

        if(encontrado == NULL){
            printf(" El DNI ingresado no se encuentra registrado o no es v%clido. \n\n" , 160);
            system("pause");
            system("cls");
        }
    }

    while(matriculaValida != 1){
        printf("\n Ingresar matr%ccula del profesional: " , 161);
        fflush(stdin);
        gets(ingresoPaciente.matriculaProfesional);

        matriculaValida = validarMatricula(ingresoPaciente.matriculaProfesional);

        if(matriculaValida != 1){
            printf(" La matr%ccula ingresada no es v%clida. \n\n" , 161 , 160);
        }
    }

    ingresoPaciente.eliminado = 0;

    return ingresoPaciente;
}

void mostrarUnIngreso(ingresos ingresoPaciente)
{
    printf("\n---------------------------------------------------- \n");
    printf(" N%c Ingreso......................: %d \n" , ingresoPaciente.nroIngreso);
    printf(" Fecha de ingreso.................: %s \n" , ingresoPaciente.fechaIngreso);
    printf(" Fecha de retiro..................: %s \n" , ingresoPaciente.fechaRetiro);
    printf(" DNI del paciente.................: %s \n" , ingresoPaciente.dniPaciente);
    printf(" Matr%cula del profesional........: %s \n" , 161 , ingresoPaciente.matriculaProfesional);
    if(ingresoPaciente.eliminado == 0){
        printf(" Estado...........................: ALTA \n" , ingresoPaciente.eliminado);
    }else{
        printf(" Estado...........................: BAJA \n" , ingresoPaciente.eliminado);
    }
    printf("---------------------------------------------------- \n\n");
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
        if((dia >= 1 && dia <= 31) && (mes >= 1 && mes <= 12) && ((year >= 1000 && year <= 9999) || (year >= 10 && year <= 99))){
            fechaValida = 1;
        }
    }

    if(sscanf(fecha , "%d-%d-%d" , &dia , &mes , &year) == 3){ // Intenta convertir la fecha en formato dd-mm-aaaa
        if((dia >= 1 && dia <= 31) && (mes >= 1 && mes <= 12) && ((year >= 1000 && year <= 9999) || (year >= 10 && year <= 99))){
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
    auxNodoIngreso->listaPracticasPorIngreso = inicListaPracPorIngreso();

    return auxNodoIngreso;
}

nodoListaIngresos* agregarInicioListaIngresos(nodoListaIngresos* listaIngresos , nodoListaIngresos* nuevoNodoIngreso)
{
    if(listaIngresos == NULL){
        listaIngresos = nuevoNodoIngreso;
    }else{
        nuevoNodoIngreso->siguiente = listaIngresos;
        listaIngresos = nuevoNodoIngreso;
    }

    return listaIngresos;
}

nodoListaIngresos* agregarEnOrdenListaIngreso(nodoListaIngresos* listaIngresos , nodoListaIngresos* nuevoNodoIngreso)
{
    if(listaIngresos == NULL){
        listaIngresos = nuevoNodoIngreso;
    }else{
        if(strcmp(nuevoNodoIngreso->datosIngresoPac.fechaIngreso , listaIngresos->datosIngresoPac.fechaIngreso) > 0){
            listaIngresos = agregarInicioListaIngresos(listaIngresos , nuevoNodoIngreso);
        }else{
            nodoListaIngresos *ante = listaIngresos;
            nodoListaIngresos *seg = listaIngresos->siguiente;

            while((seg != NULL) && (strcmp(nuevoNodoIngreso->datosIngresoPac.fechaIngreso , listaIngresos->datosIngresoPac.fechaIngreso) < 0)){
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

    if(seg != NULL){
        while(seg != NULL){
            mostrarUnIngreso(seg->datosIngresoPac);
            seg = seg->siguiente;
        }
    }
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
    printf(" Resultado...................: %s \n" , prac.resultado);
    printf("*********************************** \n\n");
}

/// ----------------------------- FIN DE FUNCIONES DE LISTA - PRÁCTICAS POR INGRESO ---------------- ///
