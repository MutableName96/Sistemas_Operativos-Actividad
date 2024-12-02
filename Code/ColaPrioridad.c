#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct nodito{
    int id;
    int nivel_prioridad;
    struct nodito *siguiente;
} nodito;

int obtener_prioridad() {
    return (rand() % 5);
}

nodito* crear_nuevo_proceso() {
    static int id_proceso = 1;
    nodito* nuevo = (nodito*)malloc(sizeof(nodito));
    if (nuevo == NULL) {
        printf("Error al asignar memoria.\n");
        exit(1);
    }
    nuevo->id = id_proceso++;
    nuevo->nivel_prioridad = obtener_prioridad();
    nuevo->siguiente = NULL;
    return nuevo;
}

void agregar_proceso(nodito** cabeza) {
    nodito* nuevo = crear_nuevo_proceso();
    
    if (*cabeza == NULL) {
        *cabeza = nuevo;
    } else {
        nodito* temp = *cabeza;
        while (temp->siguiente != NULL) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevo;
    }
}

void mostrar_procesos(nodito* cabeza) {
    nodito* temp = cabeza;
    while (temp != NULL) {
        printf("Proceso %d con prioridad %d -> ", temp->id, temp->nivel_prioridad);
        temp = temp->siguiente;
    }
    printf("NULL\n");
}

void procesar_con_prioridad(nodito** cabeza) {
    if (*cabeza == NULL) {
        printf("No hay procesos para atender.\n");
        return;
    }

    nodito* temp = *cabeza;
    nodito* proceso_max = temp;
    nodito* anterior_max = NULL;
    nodito* anterior = NULL;

    while (temp != NULL) {
        if (temp->nivel_prioridad > proceso_max->nivel_prioridad) {
            proceso_max = temp;
            anterior_max = anterior;
        }
        anterior = temp;
        temp = temp->siguiente;
    }

    printf("Atendiendo proceso %d con prioridad %d\n", proceso_max->id, proceso_max->nivel_prioridad);

    if (anterior_max == NULL) {
        *cabeza = proceso_max->siguiente;
    } else {
        anterior_max->siguiente = proceso_max->siguiente;
    }

    free(proceso_max);
}

void mostrar_menu() {
    printf("1. Crear nuevo proceso\n");
    printf("2. Atender proceso con prioridad más alta\n");
    printf("3. Ver todos los procesos\n");
    printf("4. Salir\n");
    printf("Selecciona una opción: ");
}

int main() {
    srand(time(NULL));
    nodito* cabeza = NULL;
    int opcion = 0;

    do {
        mostrar_menu();
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                agregar_proceso(&cabeza);
                break;
            case 2:
                procesar_con_prioridad(&cabeza);
                break;
            case 3:
                mostrar_procesos(cabeza);
                break;
            case 4:
                printf("Saliendo... Adiós.\n");
                break;
            default:
                printf("Opción no válida. Por favor, elige una opción válida.\n");
        }
    } while (opcion != 4);

    return 0;
}
