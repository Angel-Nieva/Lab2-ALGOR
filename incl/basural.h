#ifndef BASURAL_H
#define BASURAL_H
#include "../incl/basural.h"
#include "../incl/lista.h"

typedef struct lista movimiento;
typedef struct basural{ 
    int distancia; // Distancia al centro de la ciudad 
    int basura;    // Toneladas de basura
} basural;

int basuraPorMover(basural *centros,int numCentros,int incineradores);
movimiento *mejorCandidato(basural *centros,int numCentros,float descuento);

#endif