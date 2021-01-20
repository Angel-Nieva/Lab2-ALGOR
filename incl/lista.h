#ifndef LISTA_H
#define LISTA_H
#include "../incl/lista.h"
#include "../incl/basural.h"

typedef struct lista{
	int centroInicio;   // Centro de partida con la basura
    int centroFinal;    // Centro de llegada con la basura
    float costo;        // Costo de mover la basura
	struct lista * sig;
}movimiento;

movimiento *crearNodo(movimiento *nuevo,int partida,int llegada,float c );
void ingresar(movimiento **inicio,movimiento *nuevo);
void freeLista(movimiento **nodo);

#endif