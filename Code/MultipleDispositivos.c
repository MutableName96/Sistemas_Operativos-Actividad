#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

/****************************************
 *              Struct's                *
 ****************************************/
typedef struct Disk {
    char data[256];
} Disk;

typedef struct Printer {
    bool status; // false -> cerrada, true -> abierta
    char buffer[256];
} Printer;

typedef struct Keyboard {
    char input[256];
} Keyboard;

/****************************************
 *        Variables Globales            *
 ****************************************/
Disk discoDuro;
Printer impresora;
Keyboard teclado;

/****************************************
 *              Funciones               *
 ****************************************/
void openPrinter();
void writePrinterBuffer(const char *data);
void closePrinter();
void readPrinterBuffer();
void initSistema();
void writeToDisk();
void readFromKeyboard();
void readFromDisk();

void openPrinter() {
    if (!impresora.status) {
        impresora.status = true;
        printf("Abriendo impresora...\n");
        sleep(1);
        printf("Impresora abierta exitosamente.\n");
    } else {
        printf("La impresora ya estaba abierta.\n");
    }
}

void readPrinterBuffer() {
    if (impresora.status) {
        printf("Leyendo buffer de la impresora...\n");
        sleep(1);
        if (strlen(impresora.buffer) > 0) {
            printf("Contenido del buffer: %s\n", impresora.buffer);
        } else {
            printf("El buffer está vacío.\n");
        }
    } else {
        printf("La impresora está cerrada.\n");
    }
}

void writePrinterBuffer(const char *data) {
    if (impresora.status) {
        printf("Escribiendo datos en el buffer de la impresora...\n");
        sleep(1);
        strncpy(impresora.buffer, data, 256 - 1);
        impresora.buffer[256 - 1] = '\0';
        printf("Datos escritos exitosamente.\n");
    } else {
        printf("La impresora está cerrada.\n");
    }
}

void closePrinter() {
    if (impresora.status) {
        printf("Cerrando impresora...\n");
        sleep(2);
        impresora.status = false;
        printf("Impresora cerrada exitosamente.\n");
    } else {
        printf("La impresora ya estaba cerrada.\n");
    }
}

void readFromKeyboard() {
    printf("Escribe algo: ");
    fgets(teclado.input, 256, stdin);
    
}

void writeToDisk() {
    strcpy(discoDuro.data, teclado.input);
    printf("Datos escritos en el disco duro: %s\n", discoDuro.data);
}

void readFromDisk() {
    strcpy(impresora.buffer, discoDuro.data);
    printf("Datos leídos del disco duro para impresión: %s\n", impresora.buffer);
}

void initSistema() {
    memset(&discoDuro, 0, sizeof(discoDuro));
    memset(&impresora, 0, sizeof(impresora));
    memset(&teclado, 0, sizeof(teclado));
    impresora.status = false;
}

int main() {
    initSistema();
    
    openPrinter();
    readFromKeyboard();
    writeToDisk();
    readFromDisk();
    writePrinterBuffer(impresora.buffer);
    readPrinterBuffer();
    closePrinter();

    return 0;
}
