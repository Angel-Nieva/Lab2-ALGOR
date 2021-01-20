#ifndef UTILITY_H
#define UTILITY_H
#include "../incl/utility.h"
#include "../incl/basural.h"

basural * openFile(const char * filename,int *centros,int *incineradores,float *subsidio);
char * movimientoToString(basural *centros,movimiento *inicio,int numCentros);
void writeFile(basural *centros,movimiento *inicio,const char * filename,int numCentros);

#endif