#include<stdio.h>
#include<stdlib.h>
#include "../incl/basural.h"
#include "../incl/lista.h"
#include "../incl/utility.h"
/**
 * @brief Recorre una lista de basurales y cuenta la cantidad de centros de acopio con basura 
 * @param centros Lista con los centros de acopio
 * @param numCentros Cantidad de basurales
 * @param incineradores Cantidad de incineradores
 * @return 1 si queda basura por mover, 0 en caso contrario
 */ 
int basuraPorMover(basural *centros,int numCentros,int incineradores)
{
    int centrosConBasura = 0;
    for (size_t i = 0; i < numCentros; i++)
    {
        if (centros[i].basura != 0 )
            centrosConBasura += 1;
    }
    if( centrosConBasura > incineradores)
        return 1;
    else
        return 0;     
}

movimiento *mejorCandidato(basural *centros,int numCentros,float descuento)
{   
    float menorCosto = 9999999999;
    int distInicio,distLlegada,centroIni,centroFin;
    for (size_t i = 0; i < numCentros-1; i++)
    {
        for (size_t j = i+1; j < numCentros; j++)
        { 
            if ( centros[i].basura != 0 && centros[j].basura != 0)
            {    
                int distanciaEntreCentros = abs( centros[i].distancia - centros[j].distancia );

                float costo = (distanciaEntreCentros)*(centros[i].basura)*(descuento);
                if ( costo < menorCosto)
                {
                    menorCosto = costo;
                    distInicio = centros[i].distancia;
                    distLlegada = centros[j].distancia;
                    centroIni = i;
                    centroFin = j;
                }

                costo = (distanciaEntreCentros)*(centros[j].basura)*(descuento);
                if ( costo < menorCosto)
                {
                    menorCosto = costo;
                    distInicio = centros[j].distancia;
                    distLlegada = centros[i].distancia;
                    centroIni = j;
                    centroFin = i;
                }
            }                                                
        }                
    }
    centros[centroFin].basura += centros[centroIni].basura;
    centros[centroIni].basura = 0;
    movimiento *nuevo = crearNodo(nuevo,distInicio,distLlegada,menorCosto);
    #ifdef DEBUG

        printf("%s\n",movimientoToString(centros,nuevo,numCentros));

    #endif
    return nuevo;    
}