
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>


#define MemoryRam 10
#define Swap 20


bool Hayprocesos=true;
int tamañoP=0;

typedef struct proceso{
	int PID;
	int tamaño;
	}proceso;

	proceso memoria[MemoryRam];
	proceso swap[Swap];
	
	

bool memoriallena(){
	for(int i=0; i<tamañoP;i++){
		if(memoria[i].PID==-1){
			return false;
			}
		}
		return true;
	}
	
bool pidExiste(int pid) {
    for (int i = 0; i < tamañoP; i++) {
        if (memoria[i].PID == pid && pid>=0) {
            return true; 
        }
    }
    return false; 
}

void swapping(){
	for(int i = 0; i < MemoryRam; i++ ){
		if(memoria[i].PID !=-1){
			
			for(int j = 0; j < MemoryRam;j++){
				if(swap[j].PID == -1){
						swap[j] = memoria[i];
						memoria[i].PID = -1;
						printf("Proceso %d movido a Swap\n", swap[j].PID);
						return;
					}
				}
				printf("No hay espacio en Swap para el proceso %d\n", memoria[i].PID);
				return;
			
			}
		}
		printf("No hay procesos en ram para mover.\n");
	
	}

void asignarParticiones(){
	bool flag =false;
	int pid;
    int size;
    int rest;
    
	printf("Id de proceso: ");
    scanf("%d", &pid);

    if(pidExiste(pid)){
        printf("Este pid ya existe o no es valido");
        printf("\n");
        return;
    }

    printf("Tamaño del proceso(MB): ");
    scanf("%d", &size);

    for(int i = 0; i < MemoryRam; i++){
        if(memoriallena() == true){
            printf("Memoria llena"); 
            printf("Realizando swap...\n");
            sleep(1);
            swapping();
        }
	}
			
	

void liberarEspacio(){
	int opc=0;
	bool bandera=false;
	printf("Seleciona el proceso a eliminar: ");
	scanf("%d",&opc);
	for(int i = 0;i < tamañoP; i++){
		if(opc==memoria[i].PID){
			memoria[i].PID=-1;
			printf("Proceso con PID %d eliminado de la partición %d.\n", opc, i + 1);
			bandera=true;
            break;
		
		}	
	}
	if (!bandera) {
        printf("No se encontró un proceso con PID %d.\n", opc);
    }
}
	
void mostrarMemoria(){
	bool p = true;
	for(int i = 0;i < tamañoP; i++){
		if(memoria[i].PID !=-1){
			printf("PID: %d NumeroParticion: %d TamañoParticion:(%dMB)\n",memoria[i].PID,i+1,memoria[i].tamaño);
			p=false;
			}else if(memoria[i].tamaño>0){
				printf("Particion: %d libre\n",i+1);

				}
			
		}
	

		if(p){
			printf("No hay procesos que mostrar\n");
			Hayprocesos=false;
			}
	}
	

int main()
{
	int opcion = 0;
	do{
		
		printf("------------- Menu -------------\n");
		printf("1.- Asignar particiones\n");
		printf("2.- Asignar Espacio de memoria\n");
		printf("3.- Liberar Espacio de memoria\n");
		printf("4.- Mostrar Espacios de memoria\n");
		printf("5.- Salir\n");
		printf("--------------------------------\n");
		scanf("%d",&opcion);
		switch(opcion){
			case 1:
			printf("Seleccione el Maximo de particion: ");
			scanf("%d",&tamañoP);
				asignarParticiones(tamañoP);
			
				break;
				
			case 2:
			asignarEspacio();
			
				break;
				
			case 3:
			mostrarMemoria();
			if(Hayprocesos){
				liberarEspacio();
				}
				break;
				
			case 4:
			mostrarMemoria();
				break;
				
			case 5:
				return 0;
				break;
				
			default:
			printf("Opcion invalida");
				
			
			}
		
	
	}
	while(true);
	
	return 0;
}

