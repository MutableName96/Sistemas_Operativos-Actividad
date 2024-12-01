#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

/****************************************
 *         		Struct's                *
 ****************************************/
 
typedef struct TablePage{
	int indicePagina;
	int marcoAsignado;
	int cargada;
	int ultimoUso;
	
}TablePage;

typedef struct pagina{
	int numPagina;
	int size;
	
	
	}pagina;
	
typedef struct proceso{
	int PID;
	int cantidadPaginas;
	int size;
	TablePage *tablaPaginas;
	struct proceso *siguiente;
	
	}proceso;
	
typedef struct MarcoMem{
	int numeroMarco;
	int paginaAsignada;
	int procesoId;
	}MarcoMem;
	
/****************************************
 *        Variables Globales            *
 ****************************************/
 
#define SizeMemoryFisic 8 
#define SizePage 4

int totalMarcos = SizeMemoryFisic / SizePage;
int contProceso = 1;
int contadorUso = 0;
MarcoMem memoriaFisica[SizeMemoryFisic/SizePage];

proceso *cabeza = NULL;
	
/****************************************
 *         		Funciones               *
 ****************************************/
 void LRU();
	
void printfTablasProcesos(){
	
if(cabeza==NULL){
	printf("No hay procesos creados\n");
	return;
	}
	proceso *nuevo = cabeza;
	printf("----------------------------------------\n");
	while(nuevo != NULL){
		printf("| PID: %d | Tamaño Proceso: %d (KB) | Paginas: %d |\n\n",nuevo->PID, nuevo->size, nuevo->cantidadPaginas);
		for(int i = 0; i < nuevo->cantidadPaginas;i++){
		printf("| pagina %d | Marco asignado %d | Cargado %d |\n", nuevo->tablaPaginas[i].indicePagina, nuevo->tablaPaginas[i].marcoAsignado, nuevo->tablaPaginas[i].cargada);
		}
		printf("----------------------------------------\n");

		
	nuevo = nuevo->siguiente;
	}
	}
	
void printfMemFisica() {
    printf("-- Memoria Fisica --\n");
        for (int i = 0; i < totalMarcos; i++) {
        if (memoriaFisica[i].paginaAsignada != -1) {
            int pidProceso = memoriaFisica[i].procesoId;
            proceso *aux = cabeza;
            while (aux != NULL && aux->PID != pidProceso) {
                aux = aux->siguiente;
            }

            if (aux != NULL) {
                for (int j = 0; j < aux->cantidadPaginas; j++) {
                    if (aux->tablaPaginas[j].marcoAsignado == i) {
                        printf("| Marco: %d | Página: %d | (Proceso ID: %d) | Último Uso: %d \n", 
                               i, aux->tablaPaginas[j].indicePagina, aux->PID, aux->tablaPaginas[j].ultimoUso);
                        break;
                    }
                }
            }
        } else {
            printf("Marco %d: Libre\n", i);
        }
    }
}

int numeroPaginas(int * tam){
	int totpagina = 0;
	totpagina = (int)ceil((float)*tam / SizePage);
	
	return totpagina;
	}
	
void crearProceso(){
	
	int tam = 0;
	printf("Elige el tamaño del proceso (KB): ");
	scanf("%d",&tam);
	proceso *nuevoProceso = (proceso*)malloc(sizeof(proceso));
	nuevoProceso->PID=contProceso;
	nuevoProceso->size=tam;
	nuevoProceso->cantidadPaginas=numeroPaginas(&tam);
	nuevoProceso->tablaPaginas = (TablePage*)malloc(sizeof(TablePage) * nuevoProceso->cantidadPaginas);
	
	for(int i = 0; i<nuevoProceso->cantidadPaginas;i++){
		nuevoProceso->tablaPaginas[i].indicePagina = i;
		nuevoProceso->tablaPaginas[i].cargada = 0;
		nuevoProceso->tablaPaginas[i].marcoAsignado= -1;
		
		}
		nuevoProceso->siguiente=cabeza;
		cabeza = nuevoProceso;
		contProceso++;
	}
	

void asignarPaginas() {
    if (cabeza == NULL) {
        printf("No hay procesos creados.\n");
        return;
    }

    printf("Seleccione el proceso para asignar páginas:\n");

    proceso *temp = cabeza;
    while (temp != NULL) {
        printf("| ID: %d | Tamaño: %d KB | Páginas: %d |\n", temp->PID, temp->size, temp->cantidadPaginas);
        temp = temp->siguiente;
    }

    printf("Ingresa el ID del proceso: ");
    int idProceso;
    scanf("%d", &idProceso);

    proceso *temp2 = cabeza;
    while (temp2 != NULL) {
        if (temp2->PID == idProceso) {

            int todasAsignadas = 1;
            for (int i = 0; i < temp2->cantidadPaginas; i++) {
                if (temp2->tablaPaginas[i].marcoAsignado == -1) {
                    todasAsignadas = 0;
                    break;
                }
            }

            

            for (int i = 0; i < temp2->cantidadPaginas; i++) {
                printf("| Página %d | Marco asignado: %d | Cargada: %d |\n", temp2->tablaPaginas[i].indicePagina, temp2->tablaPaginas[i].marcoAsignado, temp2->tablaPaginas[i].cargada);
            }

            int opc = 0;
            do {
                int pagseleccion;
                printf("Selecciona el número de página a cargar en memoria: ");
                scanf("%d", &pagseleccion);
                
                if (pagseleccion < 0 || pagseleccion >= temp2->cantidadPaginas) {
                    printf("Página inválida.\n");
                    return;
                }

                if (temp2->tablaPaginas[pagseleccion].marcoAsignado != -1) {
                    printf("Página ya asignada a un marco.(Nuevo Uso)\n");
                    temp2->tablaPaginas[pagseleccion].ultimoUso = contadorUso;
                    contadorUso++;
                    return;
                }

                int marcosLibres[totalMarcos];
                int numLibres = 0;
                for (int i = 0; i < totalMarcos; i++) {
                    if (memoriaFisica[i].paginaAsignada == -1) {
                        marcosLibres[numLibres++] = i;
                    }
                }

                if (numLibres == 0) {
                    LRU();
                }

                numLibres = 0;
                for (int i = 0; i < totalMarcos; i++) {
                    if (memoriaFisica[i].paginaAsignada == -1) {
                        marcosLibres[numLibres++] = i;
                    }
                }

                int marcoAleatorio = marcosLibres[rand() % numLibres];
                memoriaFisica[marcoAleatorio].paginaAsignada = temp2->tablaPaginas[pagseleccion].indicePagina;
                memoriaFisica[marcoAleatorio].procesoId = temp2->PID;
                temp2->tablaPaginas[pagseleccion].marcoAsignado = marcoAleatorio;
                temp2->tablaPaginas[pagseleccion].cargada = 1;
                temp2->tablaPaginas[pagseleccion].ultimoUso = contadorUso;
                contadorUso++;

                printf("Página %d asignada al marco %d.\n", pagseleccion, marcoAleatorio);
                todasAsignadas = 1;
                for (int i = 0; i < temp2->cantidadPaginas; i++) {
                    if (temp2->tablaPaginas[i].marcoAsignado == -1) {
                        todasAsignadas = 0;
                        break;
                    }
                }

                if (todasAsignadas) {
                    return;
                }

                printf("1.- Asignar otra página\n");
                printf("0.- Salir\n");
                scanf("%d", &opc);
            } while (opc != 0);

            return;
        }
        temp2 = temp2->siguiente;
    }

    printf("Proceso no encontrado.\n");
}


void LRU() {
    if (cabeza == NULL) {
        printf("No hay procesos creados.\n");
        return;
    }

    proceso *temp2 = cabeza;
    int delatepage = -1;
    int menorUso = contadorUso;
    proceso *Aux = NULL;

    while (temp2 != NULL) {
        for (int i = 0; i < temp2->cantidadPaginas; i++) {
            if (temp2->tablaPaginas[i].cargada && temp2->tablaPaginas[i].ultimoUso < menorUso) {
                menorUso = temp2->tablaPaginas[i].ultimoUso;
                delatepage = i;
                Aux = temp2;
            }
        }
        temp2 = temp2->siguiente;
    }

    if (delatepage == -1) {
        printf("No se encontró página cargada para eliminar.\n");
        return;
    }
    if(Aux!=NULL){
		int marcoLiberado = Aux->tablaPaginas[delatepage].marcoAsignado;
		memoriaFisica[marcoLiberado].paginaAsignada = -1;
		Aux->tablaPaginas[delatepage].marcoAsignado = -1;
		Aux->tablaPaginas[delatepage].cargada = 0;
		printf("Página %d eliminada del marco %d del proceso[%d].\n", delatepage, marcoLiberado,memoriaFisica[marcoLiberado].procesoId);
		printf("\n");
		memoriaFisica[marcoLiberado].procesoId = -1;

		}

    
}


int main()
{
	srand(time(NULL));
	//Inicializar Memoria Fisica
	
	for(int i = 0; i < totalMarcos ;i++){
			memoriaFisica[i].numeroMarco = i;
			memoriaFisica[i].paginaAsignada = -1;
		}
		
	int opc = 0;
	
	do{
		printf("------------- Menu -------------\n");
		printf("1.- Crear Proceso\n");
		printf("2.- Asignar Paginas\n");
		printf("3.- Mostrar procesos\n");
		printf("4.- Mostrar Memoria Fisica\n");
		printf("5.- Salir\n");
		printf("--------------------------------\n");
		scanf("%d",&opc);
		switch(opc){
			case 1:
				crearProceso();
				break;
				
			case 2:
				asignarPaginas();
				break;
				
			case 3:
				printfTablasProcesos();
				break;
				
			case 4:
				printfMemFisica();
				
				break;
			case 5:
				return 0;
				break;
				
			default:
			printf("Opcion invalida");
				
			}
			
	}while(true);
    
  return 0 ;
 }
