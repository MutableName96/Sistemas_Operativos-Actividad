#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

/****************************************
 *         		Struct's                *
 ****************************************/
typedef struct Device{
	bool interrupcion;
	}Device;

typedef struct TablaEstadosDispositivos{
	int estado; // 0 -> espera 1-> ocupado/p en proceso 2-> completado
	int parameters; //parametros especiales
	}TablaEstadosDispositivos;

/****************************************
 *        Variables Globales            *
 ****************************************/
Device maus;
TablaEstadosDispositivos tablaEstados;
bool interrupcionActiva = false;

/****************************************
 *         		Funciones               *
 ****************************************/
 void ES();
 void atenderES();
 
 void driverDevice(Device dispositivo){
	 while (tablaEstados.estado==1){
		 printf("Dispositivo ocupado\n");
		 sleep(1);
		 printf("Espere...\n");
		 sleep(2);
		 tablaEstados.estado=0;
		 }
		 
	if(tablaEstados.estado==0){
		tablaEstados.estado=1;
		printf("info: device libre\n");
		ES();
		atenderES();
	
	}	 
	 
}

void ES(){
	printf("Iniciando operación de E/S...\n");
    sleep(2);
    tablaEstados.estado = 2;
    printf("Operación de E/S cargada en la tabla de estados.\n");
}

void atenderES(){
	if(tablaEstados.estado == 2){
		printf("interrupcion\n");
		printf("atendiendo interrupcion\n");
		tablaEstados.estado = 0;
		}
	
}


int main(){
	
	maus.interrupcion = false;
    tablaEstados.estado = 1; 
    tablaEstados.parameters = 0;
    while(true){
		printf("\n");
		driverDevice(maus);
		sleep(3);
		}
	
	return 0;
}
