#include<stdio.h>
#include<stdlib.h>
#include "../incl/lista.h"
#include "../incl/goloso.h"
#include "../incl/utility.h"
#include "../incl/basural.h"

int main(int argc, char const *argv[])
{
    if(argc !=3){ // Modificar a 3  <-----
        return 0;
    }
    int numCentros,incineradores;
    float subsidio;
    basural *centros = openFile(argv[1],&numCentros,&incineradores,&subsidio); // Lista con los basurales

    if(centros != NULL){

        movimiento *inicio = NULL;
        goloso(centros,numCentros,incineradores,subsidio,&inicio);
        writeFile(centros,inicio,argv[2],numCentros);
        free(centros);
        freeLista(&inicio);
    }
    return 0;
}