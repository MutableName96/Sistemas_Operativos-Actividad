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
 
#define SizeMemoryFisic 64 
#define SizePage 4

int totalMarcos = SizeMemoryFisic / SizePage;
int contProceso = 1;
int contadorUso = 0;
int j = 0;
MarcoMem memoriaFisica[SizeMemoryFisic/SizePage];

proceso *cabeza = NULL;


	
/****************************************
 *         		Funciones               *
 ****************************************/

	
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
    for (int i = 0; i < totalMarcos; i++) {
        if (memoriaFisica[i].paginaAsignada != -1) {
            printf("Marco %d: Página %d (Proceso ID: %d)\n", i, memoriaFisica[i].paginaAsignada, memoriaFisica[i].procesoId);
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
	//crear nuevo proceso y inicializar sus atributos
	
	int tam = 0;
	printf("Elige el tamaño del proceso (KB): ");
	scanf("%d",&tam);
	proceso *nuevoProceso = (proceso*)malloc(sizeof(proceso));
	nuevoProceso->PID=contProceso;
	memoriaFisica[j].procesoId = contProceso;
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
		j++;
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
            printf("Proceso encontrado: ID: %d\n", temp2->PID);

            for (int i = 0; i < temp2->cantidadPaginas; i++) {
                printf("| Página %d | Marco asignado: %d | Cargada: %d |\n", 
                        temp2->tablaPaginas[i].indicePagina, 
                        temp2->tablaPaginas[i].marcoAsignado, 
                        temp2->tablaPaginas[i].cargada);
            }

            int opc = 0;
            do {
                int pagselecion;
                printf("Selecciona el número de página a cargar en memoria: ");
                scanf("%d", &pagselecion);
                
                if (pagselecion < 0 || pagselecion >= temp2->cantidadPaginas) {
                    printf("Página inválida.\n");
                    return;
                }

                if (temp2->tablaPaginas[pagselecion].marcoAsignado != -1) {
                    printf("Página ya asignada a un marco.\n");
                    return;
                }

                printf("Marcos disponibles:\n");
                int marcosLibres[totalMarcos];
                int numLibres = 0;
                for (int i = 0; i < totalMarcos; i++) {
                    if (memoriaFisica[i].paginaAsignada == -1) {
                        marcosLibres[numLibres++] = i;
                    }
                }

                if (numLibres == 0) {
                    printf("No hay marcos libres disponibles.\n");
                    return;
                }

                int marcoAleatorio = marcosLibres[rand() % numLibres];

                memoriaFisica[marcoAleatorio].paginaAsignada = temp2->tablaPaginas[pagselecion].indicePagina;
                temp2->tablaPaginas[pagselecion].marcoAsignado = marcoAleatorio;
                temp2->tablaPaginas[pagselecion].cargada = 1;

                printf("Página %d asignada al marco %d.\n", pagselecion, marcoAleatorio);

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

void eliminarPaginas() {
    if (cabeza == NULL) {
        printf("No hay procesos creados.\n");
        return;
    }

    printf("Seleccione el proceso del cual eliminar páginas:\n");
    proceso *temp = cabeza;
    while (temp != NULL) {
        printf("| PID: %d | Tamaño: %d KB | Páginas: %d |\n", temp->PID, temp->size, temp->cantidadPaginas);
        temp = temp->siguiente;
    }

    int idProceso;
    printf("Ingresa el ID del proceso: ");
    scanf("%d", &idProceso);

    proceso *temp2 = cabeza;
    while (temp2 != NULL) {
        if (temp2->PID == idProceso) {
            printf("Proceso encontrado: ID: %d\n", temp2->PID);

            int paginaEliminar = -1;
            int menorUso = contadorUso;
            for (int i = 0; i < temp2->cantidadPaginas; i++) {
                if (temp2->tablaPaginas[i].cargada && temp2->tablaPaginas[i].ultimoUso < menorUso) {
                    menorUso = temp2->tablaPaginas[i].ultimoUso;
                    paginaEliminar = i;
                }
            }

            if (paginaEliminar == -1) {
                printf("No se encontró página cargada para eliminar.\n");
                return;
            }
            int marcoLiberado = temp2->tablaPaginas[paginaEliminar].marcoAsignado;
            memoriaFisica[marcoLiberado].paginaAsignada = -1;
            temp2->tablaPaginas[paginaEliminar].marcoAsignado = -1;
            temp2->tablaPaginas[paginaEliminar].cargada = 0;

            printf("Página %d eliminada del marco %d.\n", paginaEliminar, marcoLiberado);
            return;
        }
        temp2 = temp2->siguiente;
    }

    printf("Proceso no encontrado.\n");
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
				asignarPaginas();
				break;
				
			case 3:
				eliminarPaginas();
				break;
				
			case 4:
				printfTablasProcesos();
				break;
				
			case 5:
				printfMemFisica();
				
				break;
			case 6:
				return 0;
				break;
				
			default:
			printf("Opcion invalida");
				
			}
			
	}while(true);
    
  return 0 ;
 }
