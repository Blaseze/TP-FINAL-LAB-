#include "practicas.h"

///FUNCIONES ARCHIVO - PRACTICAS
void cargarArchPracticas(char nombreArchivo[])
{
    char continuar = 's';
    practicas prac;

    while(continuar == 's' || continuar == 'S'){
        system("cls");

        printf("\n CARGANDO PRACTICAS.... \n\n");

        prac.nroPractica = ultimoNumPracCargada(nombreArchivo);

        prac.nroPractica++;

        prac = cargaDatosPrac(prac);

        guardarUnaPractica(nombreArchivo , prac);

        printf("\n %cQuieres ingresar una nueva pr%cctica? s=SI / n=NO " , 168 , 160);
        fflush(stdin);
        continuar = getch();
        printf("\n\n");
    }

}

practicas cargaDatosPrac(practicas prac)
{
    printf("\n Ingresar nombre de la pr%cctica: " , 160);
    fflush(stdin);
    gets(prac.nombrePractica);

    prac.eliminado = 0;

    return prac;
}

void guardarUnaPractica(char nombreArchivo[] , practicas prac)
{
    FILE *pArchivo = fopen(nombreArchivo , "ab");

    if(pArchivo != NULL){
        fwrite(&prac , sizeof(practicas) , 1 , pArchivo);
        fclose(pArchivo);
    }else{
        printf(" ERROR en la apertura del archivo. \n\n");
    }
}

void mostrarUnaPractica(practicas prac)
{
    printf("------------------------------------------------------------ \n");
    printf(" N%c de Pr%cctica...............: %d \n" , 248 , 160 , prac.nroPractica);
    printf(" Nombre de pr%cctica...........: %s \n" , 160 , prac.nombrePractica);
    if(prac.eliminado == 0){
        printf(" Estado.......................: ALTA \n");
    }else{
        printf(" Estado.......................: BAJA \n");
    }
    printf("------------------------------------------------------------ \n\n");
}

void mostrarArchPracticas(char nombreArchivo[])
{
    practicas auxPrac;
    FILE *pArchivo = fopen(nombreArchivo , "rb");

    if(pArchivo != NULL){
        while((fread(&auxPrac , sizeof(practicas) , 1 , pArchivo) > 0)){
            mostrarUnaPractica(auxPrac);
        }
        fclose(pArchivo);
    }else{
        printf(" ERROR en la lectura del achivo. \n\n");
    }
}

int ultimoNumPracCargada(char nombreArchivo[])
{
    int ultimoNumPrac = 0;
    practicas auxPrac;
    FILE *pArchivo = fopen(nombreArchivo , "rb");

    if(pArchivo != NULL){
        fseek(pArchivo , (-1) * sizeof(practicas) , SEEK_END);

        if(fread(&auxPrac , sizeof(practicas) , 1 , pArchivo) > 0){
            ultimoNumPrac = auxPrac.nroPractica;
        }
        fclose(pArchivo);
    }

    return ultimoNumPrac;
}

void modificarPractica(char nombreArchivo[] , int nroPrac)
{
    practicas auxReg;
    int flag = 0;
    char nuevoNombrePrac[100];
    FILE *pArchivo = fopen(nombreArchivo , "r+b");

    if(pArchivo != NULL){
        while((flag == 0) && (fread(&auxReg , sizeof(practicas) , 1 , pArchivo) > 0)){
            if(auxReg.nroPractica == nroPrac){
                flag = 1;

                fseek(pArchivo , (-1) * sizeof(practicas) , SEEK_CUR);

                system("cls");
                printf("\n El nro. de pr%cctica %d corresponde a: \n\n" , 160 , nroPrac);
                mostrarUnaPractica(auxReg);

                printf(" Ingresar nuevo nombre de la pr%cctica: " , 160);
                fflush(stdin);
                gets(nuevoNombrePrac);

                strcpy(auxReg.nombrePractica , nuevoNombrePrac);

                fwrite(&auxReg , sizeof(practicas) , 1 , pArchivo);

            }
        }

        if(flag == 0){
            printf("\n El nro. de pr%cctica ingresado es incorrecto. \n\n" , 160);
        }else{
            system("cls");
            printf("\n Pr%cctica actualizada: \n\n" , 160);
            mostrarUnaPractica(auxReg);
        }

        fclose(pArchivo);
    }
}

void darBajaPrac(char nombreArchivo[] , int nroPrac)
{
    practicas auxReg;
    int flag = 0;
    FILE *pArchivo = fopen(nombreArchivo , "r+b");

    if(pArchivo != NULL){
        while((flag == 0) && (fread(&auxReg , sizeof(practicas) , 1 , pArchivo) > 0)){
            if(auxReg.nroPractica == nroPrac){
                flag = 1;

                fseek(pArchivo , (-1) * sizeof(practicas) , SEEK_CUR);
                auxReg.eliminado = 1;

                fwrite(&auxReg , sizeof(practicas) , 1 , pArchivo);
            }
        }

        fclose(pArchivo);

        if(flag == 0){
            printf("\n El nro. de pr%cctica ingresado es incorrecto. \n\n" , 160);
        }else{
            printf("\n LA PRACTICA SE HA DADO DE BAJA CORRECTAMENTE... \n\n");
            mostrarUnaPractica(auxReg);
        }
    }
}

void darAltaPrac(char nombreArchivo[] , int nroPrac)
{
    practicas auxReg;
    int flag = 0;
    FILE *pArchivo = fopen(nombreArchivo , "r+b");

    if(pArchivo != NULL){
        while((flag == 0) && (fread(&auxReg , sizeof(practicas) , 1 , pArchivo) > 0)){
            if(auxReg.nroPractica == nroPrac){
                flag = 1;

                fseek(pArchivo , (-1) * sizeof(practicas) , SEEK_CUR);
                auxReg.eliminado = 0;

                fwrite(&auxReg , sizeof(practicas) , 1 , pArchivo);
            }
        }

        fclose(pArchivo);

        if(flag == 0){
            printf("\n El nro. de pr%cctica ingresado es incorrecto. \n\n" , 160);
        }else{
            printf("\n LA PRACTICA SE HA DADO DE ALTA CORRECTAMENTE... \n\n");
            mostrarUnaPractica(auxReg);
        }
    }
}

///FUNCIONES DE LISTA - PRACTICAS
nodoListaPracticas* inicListaPracticas()
{
    return NULL;
}

nodoListaPracticas* crearNodoPractica(practicas pracPaciente)
{
    nodoListaPracticas* auxNodoPrac = (nodoListaPracticas *)malloc(sizeof(nodoListaPracticas));

    auxNodoPrac->datosPracticas = pracPaciente;
    auxNodoPrac->siguiente = NULL;

    return auxNodoPrac;
}

nodoListaPracticas* agregarInicioListaPractica(nodoListaPracticas* listaPrac , nodoListaPracticas* nuevoNodoPrac)
{
    if(listaPrac == NULL){
        listaPrac = nuevoNodoPrac;
    }else{
        nuevoNodoPrac->siguiente = listaPrac;
        listaPrac = nuevoNodoPrac;
    }

    return listaPrac;
}

nodoListaPracticas* agregarEnOrdenListaPracticas(nodoListaPracticas* listaPrac , nodoListaPracticas* nuevoNodoPrac)
{
    if(listaPrac == NULL){
        listaPrac = nuevoNodoPrac;
    }else{
        if(strcmpi(nuevoNodoPrac->datosPracticas.nombrePractica , listaPrac->datosPracticas.nombrePractica) < 0){
            listaPrac = agregarInicioListaPractica(listaPrac , nuevoNodoPrac);
        }else{
            nodoListaPracticas* ante = listaPrac;
            nodoListaPracticas* seg = listaPrac->siguiente;

            while((seg != NULL) && (strcmpi(nuevoNodoPrac->datosPracticas.nombrePractica , listaPrac->datosPracticas.nombrePractica) > 0)){
                ante = seg;
                seg = seg->siguiente;
            }

            ante->siguiente = nuevoNodoPrac;
            nuevoNodoPrac->siguiente = seg;
        }
    }

    return listaPrac;
}

nodoListaPracticas* pasarArchPracToListaPrac(char nombreArchivo[] , nodoListaPracticas* listaPrac)
{
    practicas auxReg;
    nodoListaPracticas* nuevoNodoPrac;
    FILE *pArchivo = fopen(nombreArchivo , "rb");

    if(pArchivo != NULL){
        while(fread(&auxReg , sizeof(practicas) , 1 , pArchivo) > 0){
            nuevoNodoPrac = crearNodoPractica(auxReg);
            listaPrac = agregarEnOrdenListaPracticas(listaPrac , nuevoNodoPrac);
        }
        fclose(pArchivo);
    }

    return listaPrac;
}

void mostrarListaPractica(nodoListaPracticas *listaPrac)
{
    nodoListaPracticas* seg = listaPrac;

    if(seg != NULL){
        while(seg != NULL){
            if(seg->datosPracticas.eliminado == 0){
                mostrarUnaPractica(seg->datosPracticas);
            }
            seg = seg->siguiente;
        }
    }
}

nodoListaPracticas* buscarPractica(nodoListaPracticas* listaPrac , int nroPrac)
{
    nodoListaPracticas* encontrada = NULL;
    nodoListaPracticas* seg = listaPrac;

    if(seg != NULL){
        while((seg != NULL) && (encontrada == NULL)){
            if(seg->datosPracticas.nroPractica == nroPrac){
                encontrada = seg;
            }
            seg = seg->siguiente;
        }
    }

    return encontrada;
}
