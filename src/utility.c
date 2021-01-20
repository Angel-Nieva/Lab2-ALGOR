#include <stdio.h>
#include <stdlib.h>
#include "../incl/utility.h"
#include "../incl/basural.h"
#include "../incl/lista.h"

/**
 * @brief Abre el archivo de entrada y crea un arreglo de basural con los centros de acopio
 * @param filename Nomrbre archivo de entrada
 * @param col Cantidad de columnas del arreglo
 * @param fil Cantidad de filas en el arreglo
 * @return Arreglo de basural
 */
basural * openFile(const char * filename,int *centros,int *incineradores,float *subsidio)
{
    FILE * f;
    f = fopen (filename, "r");
    if(f == NULL){
        fputs ("File error",stderr); 
		exit (1);
    }

    // Si el archivo no es NULL

    fscanf(f,"%d %d %f ",&(*centros),&(*incineradores),&(*subsidio));     // Se guardan los datos
    basural * b = (basural *)malloc((*centros)*sizeof(basural));          // Se reserva memoria para almacenar todos los centros

    for (size_t i = 0; i < (*centros); i++)
    {
        fscanf(f,"%d %d ",&(b[i].distancia),&(b[i].basura));
    }
    fclose(f);
	return b;    
}

/**
 * @brief Transforma los movimientos y resultados en un string posible de visualizar y guardar en un archivo de texto
 * @param aux auxiliar para la lista enlazada
 * @param costoTotal Costo total de los movimientos
 * @return char *String
 */
char * movimientoToString(basural *centros,movimiento *inicio,int numCentros){
    char *buffer = malloc(sizeof(char)*1000);
    int a = 0;

    movimiento *aux = inicio;
    float costoTotal = 0;
    while ( aux != NULL )
    {
        a +=snprintf(buffer+a,1000-a,"%d -> %d : %f\n",aux->centroInicio,aux->centroFinal,aux->costo);
        costoTotal+= aux->costo;
          aux = aux->sig;
      }

      for (size_t i = 0; i < numCentros; i++)
	{
        if ( centros[i].basura != 0 )
        {
            a += snprintf(buffer+a,1000-a,"centro %d: %d toneladas\n",centros[i].distancia,centros[i].basura);  //snprintf transforma a string
        }        
            
	}
    a += snprintf(buffer+a,1000-a,"costo: %f\n",costoTotal);
   
    return buffer;
}


/**
 * @brief Escribe un archivo con la solucion del problema
 * @param numCentros la cantidad de centros de basura
 * @param filename i.e salida.out
 */
void writeFile(basural *centros,movimiento *inicio,const char*filename,int numCentros)
{
    char *buffer = movimientoToString(centros,inicio,numCentros);
    FILE *fp;
    fp = fopen(filename, "w+");
    fputs(buffer,fp);
    fclose(fp);
    free(buffer);
}