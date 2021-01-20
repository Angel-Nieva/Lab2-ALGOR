#include<stdio.h>
#include<stdlib.h>
#include "../incl/goloso.h"
#include "../incl/basural.h"
#include "../incl/lista.h"
#include "../incl/utility.h"

void goloso(basural *centros,int numCentros,int incineradores,float subsidio,movimiento **inicio)
{
    float descuento = (1 - (1/subsidio));
    while ( basuraPorMover(centros,numCentros,incineradores) )
    {        
        movimiento *candidato = mejorCandidato(centros,numCentros,descuento);
        ingresar(inicio,candidato);
    }

}
