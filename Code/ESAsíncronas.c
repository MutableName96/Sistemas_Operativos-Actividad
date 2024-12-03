#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

/****************************************
 *              Struct's                *
 ****************************************/
typedef struct AsyncIO {
    char *fileName;
    char *data;
} AsyncIO;

/****************************************
 *        Variables Globales            *
 ****************************************/
pthread_t readThread, writeThread;

/****************************************
 *              Funciones               *
 ****************************************/
void *readFile(void *arg) {
    AsyncIO *io = (AsyncIO *)arg;
    FILE *file = fopen(io->fileName, "r");
    if (file == NULL) {
        perror("No se pudo abrir el archivo para leer");
        return NULL;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("Leyendo: %s", buffer);
    }

    fclose(file);
    return NULL;
}

void *writeFile(void *arg) {
    AsyncIO *io = (AsyncIO *)arg;
    FILE *file = fopen(io->fileName, "w");
    if (file == NULL) {
        perror("No se pudo abrir el archivo para escribir");
        return NULL;
    }

    fprintf(file, "%s", io->data);
    printf("Escribiendo: %s\n", io->data);
    
    fclose(file);
    return NULL;
}

int main() {
    AsyncIO io;
    io.fileName = "async_file.txt";
    io.data = "Ya quiero dormir\n";

    pthread_create(&writeThread, NULL, writeFile, &io);
    pthread_join(writeThread, NULL);

    pthread_create(&readThread, NULL, readFile, &io);
    pthread_join(readThread, NULL);

    return 0;
}
