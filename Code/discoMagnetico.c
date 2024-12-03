#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <unistd.h>

 /****************************************
 *        Variables Globales            *
 ****************************************/
 # define Bloque 5
 # define SizeBloque 1024
 

 char buffer[Bloque][SizeBloque];
 
/****************************************
 *              Struct's                *
 ****************************************/
 typedef struct CabezaL{
	 int pista;
	 bool usado;
	 
	}CabezaL;
	
	CabezaL cabeza = {0,false};

typedef struct Archivo{
	char bloques[Bloque][SizeBloque];
	int pista;
	
	}Archivo;

	Archivo archivo;

 
 /****************************************
 *              Funciones               *
 ****************************************/
void terminar();
void buscarArchivo();
void posicionarCabeza(int pista);
void leerDatos();
void rotarDisco();
void transferirDatos();

void solicitarLectura() {
    if (cabeza.usado) {
        printf("La cabeza de lectura ya esta ocupada. No se puede realizar la operación.\n");
        printf("\n");
        return;
    }

    printf("Solicitud de lectura recibida.\n");
    sleep(1);
    printf("espere....\n");
    sleep(2);
    cabeza.usado = true;
    buscarArchivo();
}

void buscarArchivo() {
    printf("Buscando archivo en el disco...\n");
    sleep(5);
    printf("Archivo encontrado en la pista %d.\n", archivo.pista);
    posicionarCabeza(archivo.pista);
}

void posicionarCabeza(int pista) {
    printf("Posicionando cabeza de lectura a la pista %d...\n", pista);
    sleep(3);
    cabeza.pista = pista;
    printf("posicionada en la pista %d \n", pista);
    sleep(1);
    printf("Cabeza lista pa leer %d \n", pista);
    rotarDisco();
}

void rotarDisco() {
    printf("Esperando el sector adecuado...\n");
    sleep(2.5);
    printf("Sector adecuado encontrado\n");
    leerDatos();
}

void leerDatos() {
    printf("Leyendo datos delarchivo...\n");
    printf("espere....\n");
    sleep(2);
    for (int i = 0; i < Bloque ; i++) {
        for (int j = 0; j < SizeBloque; j++) {
            buffer[i][j] = archivo.bloques[i][j];
        }
    }
    printf("Datos leídos y almacenados en el buffer\n");
    transferirDatos();
}

void transferirDatos() {
    printf("Transfiriendo datos...\n");
    sleep(3);
    for (int i = 0; i < Bloque; i++) {
        printf("Bloque %d: ", i + 1);
        for (int j = 0; j < 50; j++) { //impresion
            printf("%d ", buffer[i][j]);
        }
        printf("\n");
    }
    terminar();
}

void terminar() {
    printf("Operacion finalizada...\n");
    cabeza.usado = false;
    printf("Recursos liberados\n");
}






int main(){
	for (int i = 0; i < Bloque; i++) {
			for (int j = 0; j < SizeBloque; j++) {
				archivo.bloques[i][j] = (char)(i * SizeBloque + j);
			}
		}
		archivo.pista = 10;

		solicitarLectura();
		return 0;
}
