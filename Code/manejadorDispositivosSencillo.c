#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>


bool printerStatus = false; //f->close t->open
char printerData[256]; // buffer

void open(){
	if(!printerStatus){
		printerStatus = true;
	} else{
		printf("La impresora esta abierta");
		
		}
}

void readBuffer(){
	if(printerStatus){
		printf("leyendo...");
		sleep(0.5);	
		printf("%s",printerData);
	} else{
		printf("La impresora esta cerrada");
		
		}
}

void writeBuffer(){
}
	
void closePrintf(){
	if(printerStatus){
		printerStatus=false;
	} else{
		printf("Ya esta cerrada");
		
		}
		
}

int main(){
	
	fgets(printerData,sizeof(printerData),stdin);
	printf("%s",printerData);
	read();
	return 0;
	}
