#include <stdio.h>
#include <stdlib.h>
#include "../incl/lista.h"

movimiento *crearNodo(movimiento *nuevo,int partida,int llegada,float c )
{
	nuevo = (movimiento*)malloc(sizeof(movimiento));
	nuevo->centroInicio = partida;
    nuevo->centroFinal = llegada;
    nuevo->costo = c;
	nuevo->sig = NULL;
	return nuevo;
}

void ingresar(movimiento **inicio,movimiento *nuevo)
{	
	movimiento *auxiliar = (*inicio);
    if(auxiliar != NULL)
    {
        while(auxiliar->sig != NULL){ 
            auxiliar = auxiliar->sig;
        }
        auxiliar->sig = nuevo;	
    }
    else{
        (*inicio) = nuevo;
    }    
	return;
}

void freeLista(movimiento **inicio)
{
	movimiento *auxiliar;
	while(*inicio != NULL){
		auxiliar = *inicio;
		*inicio = (*inicio)->sig;
		free(auxiliar);
	}
	return;
}