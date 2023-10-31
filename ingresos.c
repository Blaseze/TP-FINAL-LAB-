#include "ingresos.h"

void fGetNow(char date[]) //se obtiene la fecha actual. Ej: 30-10-2023
{
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    strftime(date,128,"%d-%m-%Y",tlocal);
}
