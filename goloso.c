#include<stdio.h>
#include<stdlib.h>

typedef struct basural{ 
    int distancia; // Distancia al centro de la ciudad 
    int basura;    // Toneladas de basura
} basural;

typedef struct cola{
	int centroInicio;   // Centro de partida con la basura
    int centroFinal;    // Centro de llegada con la basura
    float costo;              // Costo de mover la basura
	struct cola * sig;
}movimiento;

basural * openFile(const char * filename,int *centros,int *incineradores,float *subsidio);

int basuraPorMover(basural *centros,int numCentros,int incineradores);
movimiento *mejorCandidato(basural *centros,int numCentros,float descuento);
void goloso(basural *centros,int numCentros,int incineradores,float subsidio,movimiento **inicio,movimiento **final);

movimiento *crearNodo(movimiento *nuevo,int partida,int llegada,float c );
void encolar(movimiento **inicio,movimiento **final,movimiento *nuevo);
void descolar(movimiento **inicio,movimiento **final);
void freeCola(movimiento **nodo);
char * movimientoToString(basural *centros,movimiento *inicio,int numCentros);
void writeFile(basural *centros,movimiento *inicio,const char * filename,int numCentros);
/*====================================== MAIN ===========================================================*/
int main(int argc, char const *argv[])
{
    if(argc !=2){ // Modificar a 3  <-----
        return 0;
    }
    int numCentros,incineradores;
    float subsidio;
    basural *centros = openFile(argv[1],&numCentros,&incineradores,&subsidio); // Lista con los basurales

    if(centros != NULL){

        movimiento *inicio = NULL;
        movimiento *final = NULL;
        goloso(centros,numCentros,incineradores,subsidio,&inicio,&final);

       /* movimiento *aux = inicio;

        float costoTotal = 0;
        while ( aux != NULL )
        {
            printf("%d -> %d : %f\n",aux->centroInicio,aux->centroFinal,aux->costo);
            costoTotal+= aux->costo;
            aux = aux->sig;
        }
        printf("Total: %f\n",costoTotal);

        */
        printf("voy aca\n");
        writeFile(centros,inicio,argv[2],numCentros);
        //writeFile(g,argv[2]); 
        free(centros);
        freeCola(&inicio);
    }
    return 0;
}

/* =========================== FUNCIONES LECTURA ============================*/

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

/* =========================== FUNCIONES CENTROS ==============================*/

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
    return nuevo;    
}

void goloso(basural *centros,int numCentros,int incineradores,float subsidio,movimiento **inicio,movimiento **final)
{
    float descuento = (1 - (1/subsidio));
    while ( basuraPorMover(centros,numCentros,incineradores) )
    {        
        movimiento *candidato = mejorCandidato(centros,numCentros,descuento);
        encolar(inicio,final,candidato);
    }

}

/* =========================== FUNCIONES COLA =================================*/
movimiento *crearNodo(movimiento *nuevo,int partida,int llegada,float c )
{
	nuevo = (movimiento*)malloc(sizeof(movimiento));
	nuevo->centroInicio = partida;
    nuevo->centroFinal = llegada;
    nuevo->costo = c;
	nuevo->sig = NULL;
	return nuevo;
}

void encolar(movimiento **inicio,movimiento **final,movimiento *nuevo)
{
	(*final) = nuevo;
	if((*inicio) == NULL){
		(*inicio) = nuevo;
	}else{
		movimiento *auxiliar = (*inicio);
		while(auxiliar->sig != NULL){ 
			auxiliar = auxiliar->sig;
		}
		auxiliar->sig = nuevo;
	}
	return;
}

void descolar(movimiento **inicio,movimiento **final)
{
	if((*inicio) == NULL){
		return;
	}else if((*inicio)->sig == NULL){
		free((*inicio));
		(*inicio) = NULL;
		(*final) = NULL;
	}else{
		movimiento *auxiliar = (*inicio);
		(*inicio) = (*inicio)->sig;
		free(auxiliar);
	}
	return;
}
/*============================================ FUNCIONES ESCRITURA====================================================*/

char * movimientoToString(basural *centros,movimiento *inicio,int numCentros){
    char *buffer = malloc(sizeof(char)*1000);
    int a = 0;

    movimiento *aux = inicio;
    printf("entroooooo\n");
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
    printf("%s \n",buffer);
   
    return buffer;
}



void writeFile(basural *centros,movimiento *inicio,const char*filename,int numCentros)
{
    printf("entrooooo23232o\n");
    char *buffer = movimientoToString(centros,inicio,numCentros);
    FILE *fp;
    fp = fopen(filename, "w+");
    fputs(buffer,fp);
    fclose(fp);
    free(buffer);
}




















/*
void front(cola *inicio){
	if(inicio == NULL){
		printf("Cola vacia\n");
	}else{
		printf("Inicio: %d\n",inicio->dato);
	}
	return;
}
void back(cola *final){
	if(final == NULL){
		printf("Cola vacia\n");
	}else{
		printf("Final: %d\n",final->dato);
	}
	return;
}
*/
void freeCola(movimiento **nodo)
{
	movimiento *auxiliar;
	while(*nodo != NULL){
		auxiliar = *nodo;
		*nodo = (*nodo)->sig;
		free(auxiliar);
	}
	return;
}
