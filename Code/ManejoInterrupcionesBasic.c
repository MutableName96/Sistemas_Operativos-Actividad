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
 void driverDevice(Device dispositivo){
	 while (tablaEstados.estado==1){
		 printf("Dispositivo ocupado\n");
		 sleep(1);
		 printf("Espere...");
		 sleep(2);
		 tablaEstados.estado=0;
		 }
		 
	if()
		 
	 
	 }



int main(){
	
	return 0;
}
