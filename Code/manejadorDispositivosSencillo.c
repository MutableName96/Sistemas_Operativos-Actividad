#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

//los sleeps son como para simular los movimientos mecanicos que hace la impresora
bool printerStatus = false; //f->close t->open
char printerData[256]; // buffer

void open(){
	if(!printerStatus){
		printerStatus = true;
		printf("Abriendo...\n");
		sleep(1);
	} else{
		printf("La impresora esta abierta\n");
		
		}
}

void readBuffer(){
	if(printerStatus){
		printf("leyendo...\n");
		sleep(1);
		printf("Contenido del buffer: %s\n",printerData);
	} else{
		printf("La impresora esta cerrada\n");
		
		}
}

void writeBuffer(){
	if(printerStatus){
		printf("Introduce el texto a imprimir: \n");
		getchar();
		fgets(printerData, sizeof(printerData), stdin);
		printf("Datos cargados\n");
	} else{
		printf("La impresora esta cerrada \n");
	}
}
	
void closePrinter(){
	if(printerStatus){
		printerStatus=false;
		printf("Cerrando...\n");
		sleep(2);
		printf("Espere...\n");
		sleep(1);
		printf("Cerrada\n");
	} else{
		printf("Ya esta cerrada \n");
		
	}
		
}

int main(){
	int x = 0;
	
	do{
		printf("1. Abrir Impresora\n");
		printf("2. Leer buffer de datos\n");
		printf("3. Escribir buffer de datos\n");
		printf("4. Cerrar Impresora\n");
		printf("5. Exit\n");
		printf("Selecciona una opción: ");
		scanf("%d",&x);
		getchar();
		
		switch(x){
			case 1:
				open();
                break;
            case 2:
				readBuffer();
                break;
            case 3:
                writeBuffer();
                break;
            case 4:
				closePrinter();
                break;
            case 5:
				printf("Saliendo... Adiós.\n");
				return 0 ; 
				break;
            default:
                printf("Opción no válida. Por favor, elige una opción válida.\n");
			
			}
				
	}while(true);
	
	return 0;
	}
