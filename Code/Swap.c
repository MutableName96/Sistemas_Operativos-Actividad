
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>


#define MemoryRam 10
#define Swap 20


bool Hayprocesos=true;


typedef struct proceso{
	int PID;
	int tamaño;
	}proceso;

	proceso memoria[MemoryRam];
	proceso swap[Swap];
	
proceso memoria[MemoryRam] = {
    { -1, 5 }, { -1, 5 }, { -1, 5 }, { -1, 5 }, { -1, 5 }, 
    { -1, 5 }, { -1, 5 }, { -1, 5 }, { -1, 5 }, { -1, 5 }
};  
proceso swap[Swap] = {
    { -1, 10 }, { -1, 10 }, { -1, 10 }, { -1, 10 }, { -1, 10 },
    { -1, 10 }, { -1, 10 }, { -1, 10 }, { -1, 10 }, { -1, 10 },
    { -1, 10 }, { -1, 10 }, { -1, 10 }, { -1, 10 }, { -1, 10 },
    { -1, 10 }, { -1, 10 }, { -1, 10 }, { -1, 10 }, { -1, 10 }
};
	
	

bool memoriallena(){
	for(int i=0; i<MemoryRam;i++){
		if(memoria[i].PID==-1){
			return false;
			}
		}
		return true;
	}
	
bool pidExiste(int pid) {
    for (int i = 0; i < MemoryRam; i++) {
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

void asignarEspacio(){
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
        if(memoriallena()){
            printf("Memoria llena\n"); 
            printf("Realizando swap...\n");
            //sleep(1);
            swapping();
        }
        if(memoria[i].PID ==-1 && memoria[i].tamaño >= size){
			memoria[i].PID = pid;
			printf("\nProceso %d asignado a la partición %d\n", pid, i + 1);
			rest = (memoria[i].tamaño) - size;
            printf("Memoria desperdiciada: %d (MB)\n", rest);
             flag = true;
             break;
			}
	}
	
	if(flag == 0){
        printf("No hay particiones que puedan contener el proceso\n");
        printf("\n");
    }
    printf("\n");
}
void liberarEspacio(){
	
	int opc = 0;
    bool bandera = false;
    printf("Selecciona el proceso a eliminar: ");
    scanf("%d", &opc);
    for(int i = 0; i < MemoryRam; i++){
        if(opc == memoria[i].PID){
            memoria[i].PID = -1;
            printf("Proceso con PID %d eliminado de la partición %d.\n", opc, i + 1);
            bandera = true;
            break;
        }
    }
    if (!bandera) {
        for (int i = 0; i < Swap; i++) {
            if (opc == swap[i].PID) {
                swap[i].PID = -1;
                printf("Proceso con PID %d eliminado de Swap.\n", opc);
                bandera = true;
                break;
            }
        }
    }

    if (!bandera) {
        printf("No se encontró un proceso con PID %d.\n", opc);
    }
	}
	
void mostrarMemoria(){
    bool p = true;
    printf("\n--- Memoria RAM ---\n");
    for(int i = 0; i < MemoryRam; i++){
        if(memoria[i].PID != -1){
            printf("PID: %d Partición: %d Tamaño: %d MB\n", memoria[i].PID, i + 1, memoria[i].tamaño);
            p = false;
        } else if (memoria[i].tamaño > 0){
            printf("Partición: %d Libre\n", i + 1);
        }
    }
    printf("\n--- Memoria Swap ---\n");
    for(int i = 0; i < Swap; i++){
        if(swap[i].PID != -1){
            printf("PID: %d Partición Swap: %d Tamaño: %d MB\n", swap[i].PID, i + 1, swap[i].tamaño);
        } else if (swap[i].tamaño > 0){
            printf("Partición Swap: %d Libre\n", i + 1);
        }
    }

    if(p){
        printf("No hay procesos que mostrar en la RAM\n");
        Hayprocesos = false;
    }
}

			

int main()
{
	int opcion = 0;
	do{
		
		printf("------------- Menu -------------\n");
		printf("1.- Asignar Proceso\n");
		printf("2.- Liberar Espacio de memoria\n");
		printf("3.- Mostrar Espacios de memoria\n");
		printf("4.- Salir\n");
		printf("--------------------------------\n");
		scanf("%d",&opcion);
		switch(opcion){
			case 1:
				asignarEspacio();

				break;
				
			case 2:
				mostrarMemoria();
				if(Hayprocesos){
					liberarEspacio();
					}
			
				break;
				
			case 3:
				mostrarMemoria();
				break;
				
			case 4:
				return 0;
			
				break;
		
			default:
			printf("Opcion invalida");
				
			}
	
	}
	while(true);
	
	return 0;
}

