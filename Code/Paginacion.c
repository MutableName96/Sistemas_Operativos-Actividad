#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h> 
#include <stdbool.h>

/****************************************
 *         		Struct's                *
 ****************************************/
 
typedef struct TablePage{
	int indice;
	int marcoAsignado;
	int cargada;
	
}TablePage;

typedef struct pagina{
	int numPagina;
	int size;
	
	}pagina;
	
typedef struct proceso{
	int cantidadPaginas;
	int size;
	
	}proceso;
	
typedef struct MarcoMem{
	int numeroMarco;
	int paginaAsignada;
	}MarcoMem;
	
/****************************************
 *        Variables Globales            *
 ****************************************/
#define SizeMemoryFisic 64 
#define SizePage 4

int totalMarcos = SizeMemoryFisic / SizePage;
MarcoMem memoriaFisica[SizeMemoryFisic/SizePage];
	
/****************************************
 *         		Funciones               *
 ****************************************/
 


int NumRandom(){
	return (rand() %totalMarcos);
	
	}
	
void printfTablasProcesos(){
	
	}
	
void printfMemFisica(){
	for(int i = 0; i < totalMarcos;i++){
		printf("|Numero de Marco|: %d ", memoriaFisica[i].numeroMarco);
		printf("-> Libre \n");
		
		}
	
	}

int numeroPaginas(int * tam){
	int totpagina = 0;
	totpagina = (int)ceil( *tam / SizePage);
	
	return totpagina;
	}
	
void crearProceso(){
	int tam = 0;
	printf("Elige el tamaño del proceso (KB): ");
	scanf("%d",&tam);
	printf("%d \n",numeroPaginas(&tam));
	}
	
	



int main()
{
	for(int i = 0; i < totalMarcos ;i++){
			memoriaFisica[i].numeroMarco = i;
			memoriaFisica[i].paginaAsignada = -1;
		}
	printfMemFisica();
	int opc = 0;
	do{
		printf("------------- Menu -------------\n");
		printf("1.- Crear Proceso\n");
		printf("2.- Asignar Paginas\n");
		printf("3.- Liberar Paginas\n");
		printf("4.- Mostrar procesos\n");
		printf("5.- Mostrar Memoria Fisica\n");
		printf("6.- Salir\n");
		printf("--------------------------------\n");
		scanf("%d",&opc);
		switch(opc){
			case 1:
				crearProceso();
			
				break;
				
			case 2:
			
				break;
				
			case 3:
			
				break;
				
			case 4:
			
				break;
				
			case 5:
			
				
				break;
			case 6:
				return 0;
				break;
				
			default:
			printf("Opcion invalida");
				
			
			}
		
		
		
		
		
	}while(true);

	

	


	srand(time(NULL));
	printf("%d",NumRandom());

	

    
  return 0 ;
 }
