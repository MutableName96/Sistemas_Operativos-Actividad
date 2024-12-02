#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

/****************************************
 *              Struct's                *
 ****************************************/
typedef struct Device {
    bool interrupcion;
    int id;
} Device;

typedef struct TablaEstadosDispositivos {
    int estado; // 0 -> espera, 1 -> en proceso, 2 -> completado
    int parameters; // parámetros especiales
} TablaEstadosDispositivos;

/****************************************
 *        Variables Globales            *
 ****************************************/
#define Devices 5 
Device dispositivos[Devices];
TablaEstadosDispositivos tablaEstados[Devices];
bool interrupcionActiva[Devices] = { false };



/****************************************
 *              Funciones               *
 ****************************************/
void ES(int id);
void atenderES(int id);
void driverDevice(Device* dispositivo);

void driverDevice(Device* dispositivo) {
    int id = dispositivo->id;

    while (tablaEstados[id].estado == 1) { 
        printf("Dispositivo %d ocupado\n", id);
        sleep(1);
        printf("Espere...\n");
        sleep(3);
        tablaEstados[id].estado=0;
        
    }

    if (tablaEstados[id].estado == 0) { 
        tablaEstados[id].estado = 1;
        printf("Info: device %d libre\n", id);
        ES(id);
        atenderES(id);
    }
}

void ES(int id) {
    printf("Iniciando operación de E/S en dispositivo %d...\n", id);
    sleep(2);
    tablaEstados[id].estado = 2;
    interrupcionActiva[id] = true;
    printf("Operación de E/S en dispositivo %d cargada en la tabla de estados.\n", id);
}

void atenderES(int id) {
    if (interrupcionActiva[id]) {
        printf("Interrupción en dispositivo %d\n", id);
        printf("Atendiendo interrupción en dispositivo %d\n", id);
        tablaEstados[id].estado = 0;
        interrupcionActiva[id] = false;
    }
}


int main() {
	
	srand(time(NULL));
	
    for (int i = 0; i < Devices; i++) {
        dispositivos[i].interrupcion = false;
        dispositivos[i].id = i;
        tablaEstados[i].estado = rand()%2;
        tablaEstados[i].parameters = rand()%10;
    }

    while (true) {
        for (int i = 0; i < Devices; i++) {
			printf("\n");
            driverDevice(&dispositivos[i]);
            sleep(3);
        }
    }

    return 0;
}

