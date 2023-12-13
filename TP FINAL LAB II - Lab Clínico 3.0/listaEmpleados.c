#include "listaEmpleados.h"

/// --------------------------------------- FUNCIONES DE LISTAS - EMPLEADO ------------------------------------------ ///

//inicializa la lista de empleados
nodoListaEmpleados* inicListaEmpleados()
{
    return NULL;
}

//crea un nodo empleado
nodoListaEmpleados* crearNodoEmpleado(empleados_laboratorio emple)
{
    nodoListaEmpleados* auxNodoEmple = (nodoListaEmpleados*)malloc(sizeof(nodoListaEmpleados));

    auxNodoEmple->dato = emple;
    auxNodoEmple->siguiente = NULL;

    return auxNodoEmple;
}

//agrega en orden por apellido y nombre en la lista
nodoListaEmpleados* agregarEnOrdenListaEmpleados(nodoListaEmpleados* lista , nodoListaEmpleados* nuevoNodo)
{
    if(lista == NULL){
        lista = nuevoNodo;
    }else{
        if(strcmpi(nuevoNodo->dato.apeYnombre , lista->dato.apeYnombre) < 0){
            lista = agregarInicioListaEmpleados(lista , nuevoNodo);
        }else{
            nodoListaEmpleados* ante = lista;
            nodoListaEmpleados* seg = lista->siguiente;

            while((seg != NULL) && (strcmpi(nuevoNodo->dato.apeYnombre , seg->dato.apeYnombre) > 0)){
                ante = seg;
                seg = seg->siguiente;
            }

            ante->siguiente = nuevoNodo;
            nuevoNodo->siguiente = seg;
        }
    }

    return lista;
}

//muestra los empleados solo en ALTA
void mostrarListaEmpleadosEnAlta(nodoListaEmpleados* lista) //solo va a mostrar los empleados en ALTA
{
    nodoListaEmpleados* seg = lista;

    if(seg != NULL){
        while(seg != NULL){
            if(seg->dato.estado == 1){
                mostrarUnEmpleado(seg->dato);
            }

            seg = seg->siguiente;
        }
    }
}

//muestra todos los empleados
void mostrarListaEmpleadosCompleta(nodoListaEmpleados* lista)
{
    nodoListaEmpleados* seg = lista;

    if(seg != NULL){
        while(seg != NULL){
            mostrarUnEmpleado(seg->dato);
            seg = seg->siguiente;
        }
    }
}

//busca un empleado en la lista por DNI
nodoListaEmpleados* buscarEmpleadoLista(nodoListaEmpleados* lista , char dniEmpleado[])
{
    nodoListaEmpleados* encontrado = NULL;
    nodoListaEmpleados* seg = lista;

    if(seg != NULL){
        while((encontrado == NULL) && (seg != NULL)){
            if(strcmp(seg->dato.dni , dniEmpleado) == 0){
                encontrado = seg;
            }else{
                seg = seg->siguiente;
            }
        }
    }

    return encontrado;
}

/// --------------------------------------- FIN FUNCIONES DE LISTAS - EMPLEADO ------------------------------------------ ///

//============================================================================================================================//

/// --------------------------------------- FUNCIONES AUXILIARES - LISTA ------------------------------------------ ///

//agrega al inicio de la lista un empleado
nodoListaEmpleados* agregarInicioListaEmpleados(nodoListaEmpleados* lista , nodoListaEmpleados* nuevoNodo)
{
    if(lista == NULL){
        lista = nuevoNodo;
    }else{
        nuevoNodo->siguiente = lista;
        lista = nuevoNodo;
    }

    return lista;
}
/// --------------------------------------- FIN FUNCIONES AUXILIARES - LISTA ------------------------------------------ //

//============================================================================================================================//

/// ------------------------------------- FUNCIONES DE ARREGLO DE LISTAS - EMPLEADO --------------------------------------- ///

//pasa los datos del archivo al arreglo de lista
int pasarArchivoEmpladosToAdl(char nombreArchivo[] , celdaPerfil adl[] , int dimension)
{
    empleados_laboratorio auxReg;
    int valEmpleados = 0;
    char perfilEmple[20];
    FILE *pArchivo = fopen(nombreArchivo , "rb");

    if(pArchivo != NULL){
        while((fread(&auxReg , sizeof(empleados_laboratorio) , 1 , pArchivo) > 0) && (valEmpleados < dimension)){
            strcpy(perfilEmple , auxReg.perfil);
            valEmpleados = altaAdlEmpleados(adl , valEmpleados , perfilEmple , auxReg);
        }
        fclose(pArchivo);
    }else{
        printf(" ERROR en la lectura del archivo. \n\n");
    }

    return valEmpleados;
}

//muestra un perfil y la lista de empleados
void mostrarAdlEmpleados(celdaPerfil adl[] , int validos)
{
    int i;

    for(i=0 ; i<validos ; i++){
        printf("\t*************************************************** \n");
        printf("\t\t\t Perfil: %s \n" , adl[i].perfilEmpleado);
        printf("\t*************************************************** \n");

        mostrarListaEmpleadosEnAlta(adl[i].lista);
    }
}
/// ----------------------------------- FIN FUNCIONES DE ARREGLO DE LISTAS - EMPLEADO ------------------------------------- ///

//============================================================================================================================//

/// ---------------------------------------- FUNCIONES AUXILIARES (ADL) ------------------------------------------ ///

//cuenta los perfiles de empleados y retorna la cantidad de perfiles
int contarPerfiles(char nombreArchivo[])
{
    empleados_laboratorio auxReg;
    int numPerfilesUnicos = 0;
    FILE *pArchivo = fopen(nombreArchivo , "rb");

    if(pArchivo != NULL){
        char **perfilesUnicos = NULL;
        int existePerfil = 0;
        int i = 0;

        while(fread(&auxReg , sizeof(empleados_laboratorio) , 1 , pArchivo) > 0){
            i = 0;
            existePerfil = 0;
            while((i < numPerfilesUnicos) && (existePerfil == 0)){ //busco si ya existe el perfil en el arreglo
                if(strcmpi(perfilesUnicos[i] , auxReg.perfil) == 0){
                    existePerfil = 1;
                }
                i++;
            }

            if(existePerfil == 0){
                char *perfilNuevo = (char *)malloc(strlen(auxReg.perfil) + 1); //asigno memoria al nuevo perfil
                strcpy(perfilNuevo , auxReg.perfil);

                perfilesUnicos = (char **)realloc(perfilesUnicos , (numPerfilesUnicos + 1) * (sizeof(char *))); //aumento la capacidad del arreglo

                perfilesUnicos[numPerfilesUnicos] = perfilNuevo; //guardo el perfil nuevo
                numPerfilesUnicos++;
            }
        }
        fclose(pArchivo);
    }else{
        printf(" ERROR en la lectura del archivo. \n\n");
    }

    return numPerfilesUnicos;
}

//busca un perfil en el arreglo de lista y retorna la posición
int buscarPerfil(celdaPerfil adl[] , int validos , char perfil[])
{
    int pos = -1;
    int i = 0;

    while((i < validos) && (pos == -1)){
        if(strcmpi(adl[i].perfilEmpleado , perfil) == 0){
            pos = i;
        }else{
            i++;
        }
    }

    return pos;
}

//agrega el perfil en la posición correspondiente con sus respectivos empleados
int agregarPerfil(celdaPerfil adl[] , int validos , char perfil[])
{
    strcpy(adl[validos].perfilEmpleado , perfil);
    adl[validos].lista = inicListaEmpleados();

    validos++;

    return validos;
}

//función principal que llama a las funciones anteriores
int altaAdlEmpleados(celdaPerfil adl[] , int validos , char perfil[] , empleados_laboratorio emple)
{
    nodoListaEmpleados* nuevoEmpleado = crearNodoEmpleado(emple);

    int pos = buscarPerfil(adl , validos , perfil);

    if(pos == -1){
        validos = agregarPerfil(adl , validos , perfil);
        pos = validos-1;
    }

    adl[pos].lista = agregarEnOrdenListaEmpleados(adl[pos].lista , nuevoEmpleado);

    return validos;
}
/// ---------------------------------------- FIN FUNCIONES AUXILIARES (ADL) ------------------------------------------ ///
