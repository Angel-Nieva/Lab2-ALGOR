#include<stdio.h>
#include<stdlib.h>
#include "../incl/goloso.h"
#include "../incl/basural.h"
#include "../incl/lista.h"
#include "../incl/utility.h"

/**
 * @brief Mienstras quede basura por mover, busca el mejor movimiento para transferir basura y lo almacena
 * O(N^3) -> T(N) = 3c + N( 2c+N^2) = 3c + 2cN + N^3 -> T(N) = N^3
 * @param centros Lista con los centros de acopio
 * @param numCentros Cantidad de basurales
 * @param incineradores Cantidad de incineradores
 * @param subsidio  Subsidio del gobierno
 * @param inicio Lista enlazada para almacenar los movimientos que lleven a la solucion
 */ 
void goloso(basural *centros,int numCentros,int incineradores,float subsidio,movimiento **inicio)
{
    float descuento = (1 - (1/subsidio));
    while ( basuraPorMover(centros,numCentros,incineradores) )
    {        
        movimiento *candidato = mejorCandidato(centros,numCentros,descuento);
        ingresar(inicio,candidato);
    }

}
