
<div align="center">

# Sistemas Operativos   ISC

#### Docente: Jesus Eduardo Alacaraz Chavez

#### Alumno: López Martínez Antonio

#### Numero Control: 22121322

</div>

<!-- toc -->

# Administrador de Memoria

## 3.1 Política y filosofía

**1.- ¿Cuál es la diferencia entre fragmentación interna y externa? Explica cómo cada una afecta el rendimiento de la memoria.**

La principal diferencia es el problema que origina cada uno ya que si se origina una fragmentacion indica que la memoria se utiliza de manera inificiente


#### Fragmentacion Interna
Se origina cuando se asigna mas memoria de la necesaria a una particion desperdiciando la memoria sobrante de esa particion esto trairia el problema es que este desperdicio se acumule dando como resultado que el rendimiento base baje porque no es posible asignar la misma cantidad de particiones.
#### Fragmentacion Externa
Se origina cuando hay sufiiente memoria teorica pero esta esta distribuida en pequeñas particiones no contiguas dando como resultado que aunque haya espacio suficiente para una particion grande esta no se peueda asignar provocando que el sistema no pueda utilizar el espacio eficientemente afectando el rendimiento

---
**2.- Investiga y explica las políticas de reemplazo de páginas en sistemas operativos. ¿Cuál consideras más eficiente y por qué?**



- Algoritmo FIFO (Firts Input Firts Output): 

    Es el algortimo de remplazo mas sencillo. Este algortimo asocia a cada pagina el instante en el que se trajo a memoria. Cuando hay que reemplazar una pagina, se elige la mas antigua. A pesar de ser el mas sencillo su rendimiento no siempre es bueno ademas este algortimo presenta una irregularidad denominada anomalia de Belady.
    
- Algoritmo Optimo OPT:

    Es un algoritmo que funciona de la siguiente forma cuando es necesario intercambiar una página, el sistema operativo intercambia la página cuyo próximo uso ocurrirá más lejos en el futuro. Por ejemplo, una página que no se utilizará durante los próximos 6 segundos se intercambiará por una página que se utilizará en los próximos 0,4 segundos. Este algoritmo no se puede implementar en un sistema operativo de propósito general porque es imposible calcular de manera confiable cuánto tiempo pasará antes de que se utilice una página. Este algoritmo puede ofrecer un rendimiento casi óptimo, pero no en la primera ejecución de un programa, y sólo si el patrón de referencia de memoria del programa es relativamente consistente cada vez que se ejecuta.


- Algoritmo LRU (Least Recencly Used):

    Es un algoritmo de reemplazo de páginas que se basa en el principio de que las páginas que han sido utilizadas recientemente tienen más probabilidades de ser utilizadas nuevamente. Aunque su rendimiento es casi óptimo, su implementación en la práctica puede ser costosa. Hay dos métodos principales de implementación:

    * Metodo de lista enlazada
    * Metodo basado en Hardware

    A pesar de su costo de implementación, LRU tiene una ventaja importante: su análisis estadístico demuestra que nunca generará más de N veces más fallos de página que el algoritmo óptimo (OPT), donde N es el número de páginas en el grupo de memoria gestionado. Sin embargo, su desempeño puede decaer bajo patrones comunes de acceso, como bucles sobre matrices grandes.


- Algortimo de Segunda Oportunidad:

    El algoritmo de reemplazo de páginas de segunda oportunidad es una mejora del algoritmo FIFO. Funciona de manera similar, utilizando una cola donde las páginas se almacenan en orden de llegada. Cuando se necesita reemplazar una página, se verifica el bit de referencia (R) de la página más antigua. Si el bit R es 0, la página no ha sido utilizada recientemente, por lo que se reemplaza inmediatamente. Si el bit R es 1, significa que la página ha sido utilizada recientemente. En este caso, el bit R se borra (se pone en 0) y la página se mueve al final de la cola, como si fuera una página nueva. Este proceso se repite hasta que se encuentra una página que pueda ser reemplazada. Si todas las páginas tienen el bit R en 1, el algoritmo funciona como FIFO puro, ya que todas las páginas se moverían al final de la cola antes de ser reemplazadas. De esta manera, el algoritmo da a las páginas utilizadas recientemente una "segunda oportunidad" para permanecer en la memoria, evitando su reemplazo prematuro.

- Algortimo de Reloj:

    El algoritmo de reloj es una versión más eficiente del algoritmo Second-Chance (segunda oportunidad) porque no requiere mover las páginas constantemente al final de la lista. En su lugar, mantiene una lista circular de páginas en memoria y utiliza un índice (manecilla) que apunta a la última página examinada. Cuando ocurre un fallo de página y no hay marcos vacíos, se inspecciona el bit de referencia (R) de la página a la que apunta la manecilla. Si el bit R es 0, la página se reemplaza por la nueva página, y la manecilla avanza a la siguiente posición. Si el bit R es 1, se borra el bit R y la manecilla avanza a la siguiente página, repitiendo el proceso hasta encontrar una página con R en 0.

    Este algoritmo es más eficiente que el de segunda oportunidad, ya que no mueve las páginas al final de la lista, sino que simplemente recorre la lista circular, similar a un reloj. La implementación es más directa, y la manecilla actúa como un iterador, asegurando que solo las páginas no referenciadas recientemente sean reemplazadas.

- Algortimo LFU (Last Frequently Used):

    Este algoritmo mantiene un contador del número de referencias que se han hecho para cada página. Se reemplaza la página con el menor recuento. La razón para esta selección es que una página que se usa activamente debe tener un alto número de referencias. Este algoritmo tiene problemas cuando una página se usa mucho en la fase inicial de un proceso, pero después ya no se utiliza. Como se usó bastantes veces, tiene un recuento alto y permanece en memoria aunque ya no se necesite. Una solución consiste en desplazar los recuentos un bit a la derecha a intervalos regulares, formando un recuento promedio de utilización que disminuye exponencialmente.

- Algoritmo NFU (Not Frequently Used): 

    El algoritmo NFU (Not Frequently Used) es un método de reemplazo de páginas que selecciona la página con menor frecuencia de uso acumulada para ser reemplazada. Cada página tiene asociado un contador, que inicialmente se establece en 0 y se incrementa en cada intervalo de tiempo si la página ha sido referenciada. Cuando es necesario reemplazar una página, se elige aquella con el contador más bajo.

    Este enfoque tiene el problema de que no considera cuándo se utilizaron las páginas, lo que puede llevar a priorizar páginas frecuentemente usadas en el pasado pero que ya no son relevantes en el presente.

- Algortimo MFU (Most Frequently Used):

    Selecciona para su reemplazo la página con el mayor número de referencias acumuladas. Este enfoque se basa en la idea de que una página que ha sido referenciada con mucha frecuencia probablemente ya no sea tan relevante para el sistema, en contraste con una página con pocas referencias, que puede estar comenzando a ser utilizada. MFU supone que las páginas más referenciadas ya cumplieron su utilidad y pueden ser reemplazadas.



- Algortimo NRU (Not Recently Used):

    Es un método que utiliza los bits de referencia (R) y modificación (M) presentes en las tablas de páginas para clasificar las páginas en memoria y determinar cuál reemplazar cuando ocurre un fallo de página. El bit R indica si una página ha sido referenciada recientemente, mientras que el bit M señala si ha sido modificada. Estos bits suelen ser configurados automáticamente por el hardware, aunque también pueden ser simulados por software. En este caso, el sistema operativo marca inicialmente las páginas como no presentes, lo que genera fallos de página al acceder a ellas. En respuesta, se activan los bits R y M según corresponda, y se ajustan los permisos de la página.
    
    El algoritmo NRU opera dividiendo las páginas en memoria en cuatro clases, basadas en los valores de los bits R y M:

    | Clase   | Referenciada (R)   | Modificada (M)   | Descripción                              |
    |:-------:|:------------------:|:----------------:|:----------------------------------------:|
    |   0     |        0           |       0          | No referenciada y no modificada          | 
    |   1     |        0           |       1          | No referenciada, pero modificada         |
    |   2     |        1           |       0          | Referenciada, pero no modificada         |
    |   3     |        1           |       1          | Referenciada y modificada                |

- Algoritmo WSClock
    El algoritmo WSClock es una mejora sobre el algoritmo de reemplazo de páginas basado en el reloj, y se utiliza para gestionar la memoria de manera eficiente en sistemas con manejo de páginas, especialmente en sistemas con acceso a discos. Usa la manecilla para revisar las páginas en memoria, evaluando su acceso y estado de modificación. Si una página no se utiliza recientemente y es limpia, se reemplaza. Si está sucia, se planifica su escritura a disco. Además, se limita el número de escrituras a disco para evitar sobrecargar el sistema.
---

### - Tabla de Comparativa de los algoritmos

| **Algoritmo**             | **Ventajas**                                    | **Desventajas**                                    |
|---------------------------|-------------------------------------------------|----------------------------------------------------|
| **FIFO**                  | - Sencillo. <br> - Bajo coste de implementación. | - Baja eficiencia. <br> - Anomalía de Belady.      |
| **Óptimo (OPT)**          | - Rendimiento casi óptimo. <br> - Mínima cantidad de fallos. | - Imposible de implementar en SO de propósito general. <br> - Solo efectivo en patrones consistentes. |
| **LRU**                   | - Cercano al óptimo. <br> - Buen desempeño en estadísticas. | - Costoso de implementar. <br> - Decrece con acceso a matrices grandes. |
| **Segunda Oportunidad**   | - Mejora FIFO. <br> - Menor complejidad que LRU. | - Menos eficiente que LRU. <br> - Genera fallos si las referencias no son secuenciales. |
| **Reloj (Clock)**         | - Más eficiente que Segunda Oportunidad. <br> - No requiere mover páginas. | - Menos eficiente que LRU en algunos casos. <br> - Manejo costoso de bits de referencia. |
| **LFU**                   | - Mantiene páginas poco referenciadas. <br> - Bueno para uso a largo plazo. | - No se adapta a patrones cambiantes. <br> - Páginas desactualizadas pueden no ser reemplazadas. |
| **NFU**                   | - Más simple que LFU. <br> - Contadores sencillos. | - No considera el tiempo de acceso. <br> - Puede priorizar páginas no útiles. |
| **MFU**                   | - Reemplaza las más referenciadas. <br> - Útil en procesos de uso inicial alto. | - Supone que las más referenciadas no son útiles. <br> - Puede eliminar páginas útiles. |
| **NRU**                   | - Fácil de implementar en hardware. <br> - Usa clasificación de páginas. | - No tan eficiente como LRU en algunos patrones. <br> - El uso de clases puede no ser ideal. |
| **WSClock**               | - Simplicidad y buen rendimiento. <br> - Utiliza tanto el reloj como el conjunto de trabajo. <br> - Menor tráfico de disco. | - Menos eficiente que LRU en patrones con acceso irregular. <br> - Requiere una implementación de escritura a disco para páginas sucias. |



#### ¿Cual considero el mas optimo?
En mi opinion el algortimo mas eficiente y optimo seria el **OPT** porque veo mas eficiente poder determinar que pagina es mejor remplazar ya que esto siempre cambiaria la pagina que no se usara en un futuro aunque lamentablemente esto es muy dificil de inplementar al punto de que se considera imposible de implementar en SO de proposito general por la cualidad de ver hacia al futuro que este algoritmo usa pero de ser en un futuro posible seria el mas optimo.

## 3.2 Memoria real

**1.- Escribe un programa en C o Python que simule la administración de memoria mediante particiones fijas.**


```c

#include <stdio.h>
#include <stdbool.h>

#define tMem 10

bool Hayprocesos=true;
int tamañoP=0;

typedef struct proceso{
	int PID;
	int tamaño;
	}proceso;

	proceso memoria[tMem];

void asignarParticiones(){
	int sump = 0;
	int temp = 0;
	int c = -1;
	
	if(tamañoP>tMem){
		printf("Las particiones exceden el espacio del disco\n");
		return;
		}
	
	for(int i = 0 ;i<tamañoP; i++){
		c++;

		
		if (sump >= tMem) { 
            printf("Memoria full, no es posible asignar mas particiones\n");
            tamañoP = c;
            break;
        }
        
		do {
            printf("Tamaño de la partición %d (MB): ", (i + 1));
            scanf("%d", &temp);

            if (sump + temp > tMem) {
                printf("Error: La partición excede el tamaño total de memoria (%d MB).\n", tMem);
                printf("Espacio disponible restante: %d MB.\n", tMem - sump);
            } else {
				memoria[i].PID = -1;
                memoria[i].tamaño = temp;
                sump += temp; 
                break;
            }
		}while (true); 

		}
		printf("\n");
	}
	

bool memoriallena(){
	for(int i=0; i<tamañoP;i++){
		if(memoria[i].PID==-1){
			return false;
			}
		}
		return true;
	}
	
bool pidExiste(int pid) {
    for (int i = 0; i < tamañoP; i++) {
        if (memoria[i].PID == pid && pid>=0) {
            return true; 
        }
    }
    return false; 
}
	
void asignarEspacio(){
	int pid;
	int size;
	int rest;
	int bandera = 0;
	
	printf("Id de proceso: ");
	scanf("%d",&pid);
	
	if(pidExiste(pid)){
		printf("Este pid ya existe o no es valido");
		printf("\n");
		return;
		}
	
	printf("Tamaño del proceso(MB): ");
	scanf("%d",&size);
	
	
	
	for(int i = 0; i< tamañoP;i++){
		
		if(memoriallena()==true){
			printf("Memoria llena no hay mas particiones por asignar\n");
			printf("\n");
		return;
		}
		if(memoria[i].PID==-1 && memoria[i].tamaño>=size){
			memoria	[i].PID=pid;
			printf("\nProceso %d asignado a la partición %d\n", pid, i + 1);
			rest=(memoria[i].tamaño)-size;
			printf("Memoria desperdiciada: %d (MB)\n",rest);
			bandera=1;
			break;
		} 
	}
	if(bandera==0){
		printf("No hay particiones que puedan contoner el proceso\n");
		printf("\n");
		}
	printf("\n");
	}
			
	

void liberarEspacio(){
	int opc=0;
	bool bandera=false;
	printf("Seleciona el proceso a eliminar: ");
	scanf("%d",&opc);
	for(int i = 0;i < tamañoP; i++){
		if(opc==memoria[i].PID){
			memoria[i].PID=-1;
			printf("Proceso con PID %d eliminado de la partición %d.\n", opc, i + 1);
			bandera=true;
            break;
		
		}	
	}
	if (!bandera) {
        printf("No se encontró un proceso con PID %d.\n", opc);
    }
}
	
void mostrarMemoria(){
	bool p = true;
	for(int i = 0;i < tamañoP; i++){
		if(memoria[i].PID !=-1){
			printf("PID: %d NumeroParticion: %d TamañoParticion:(%dMB)\n",memoria[i].PID,i+1,memoria[i].tamaño);
			p=false;
			}else if(memoria[i].tamaño>0){
				printf("Particion: %d libre\n",i+1);

				}
			
		}
	

		if(p){
			printf("No hay procesos que mostrar\n");
			Hayprocesos=false;
			}
	}
	

int main()
{
	int opcion = 0;
	do{
		
		printf("------------- Menu -------------\n");
		printf("1.- Asignar particiones\n");
		printf("2.- Asignar Espacio de memoria\n");
		printf("3.- Liberar Espacio de memoria\n");
		printf("4.- Mostrar Espacios de memoria\n");
		printf("5.- Salir\n");
		printf("--------------------------------\n");
		scanf("%d",&opcion);
		switch(opcion){
			case 1:
			printf("Seleccione el Maximo de particion: ");
			scanf("%d",&tamañoP);
				asignarParticiones(tamañoP);
			
				break;
				
			case 2:
			asignarEspacio();
			
				break;
				
			case 3:
			mostrarMemoria();
			if(Hayprocesos){
				liberarEspacio();
				}
				break;
				
			case 4:
			mostrarMemoria();
				break;
				
			case 5:
				return 0;
				break;
				
			default:
			printf("Opcion invalida");
				
			
			}
		
	
	}
	while(true);
	
	return 0;
}

```

---

**2. Diseña un algoritmo para calcular qué procesos pueden ser asignados a un sistema con memoria real limitada utilizando el algoritmo de "primera cabida"**


### Inicio

    1.- Leer el Id del proceso

    2.- Leer el tamaño del proceso

    3.- Recorrer todas las particiones de memoria y verificar si la particion esta libre y tiene espacio para asignar ese proceso

    4.- Encuanto ecuentre una particion adecuada asignar el proceso a esa particion marcando la particion con el id del proceso

    6.- Si no se econtro alguna particion adecuada mostrar mesaje indicando que no hay espacio y terminar
  
### Fin

## 3.3 Organización de memoria virtual

**1.-Investiga y explica el concepto de "paginación" y "segmentación". ¿Cuáles son las ventajas y desventajas de cada técnica?**

#### Paginacion

La paginación es una técnica de gestión de memoria utilizada por los sistemas operativos para permitir que los procesos utilicen más memoria de la que físicamente está disponible en la memoria RAM. Esta técnica divide tanto la memoria principal como la memoria virtual en bloques de tamaño fijo llamados páginas y marcos de página, respectivamente. De esta forma, Los procesos son divididos en en paginas que no necesitan estar almacenadas de manera contigua en la memoria, lo que facilita el uso eficiente de la memoria física aunque no es visible para el programador.

Esta informacion es guardada en tablas de paginas que estan cargadas en memoria fisica que contiene el numero de pagina y su contenido que no es mas que el marco que corresponde a esa pagina es decir existe una asociaciones entre los números de página y los marcos de página y a su vez se maneja una lista de marcos libres

Esto basicamente hace que eliminamos la posibilidad de que haya fragmentacion externa el usar los marcos para almacenar cualquier pagina pero no excluye a la fragmentacion interna ya que puede pasar que no se llegue a ocupar el 100% de una pagina y como hay que recordar el tamaño de pagina es equivalente al del marco de pagina.

![Ejemplo Paginacion](img/paginacion.png)




#### Segmentacion

La segmentacion es otra tecnica de gestion de memoria que se utiliza en los SO funciona de la siguiente forma en memoria se divide en segmentos de tamaños variables.Los segmentos son unidades logicas como:

* Codigo: Programa principal, funciones

* Datos: Variables globales

* Stack: Para retorno de las llamadas a funciones, paso de parametros y variables locales

Es por eso que decimos que que un programa es una coleccion de segmentos ademas el esquema de manejo de memoria que es visible para el programador esto significa que el programador puede identificar y trabajar directamente con las diferentes segmentos del programa. En la segmentación, cada segmento tiene su propio identificador conocido como base que contiene la direccion fisicas de los segmentos y límites donde se especifica el tamaño de ese segmento esto es guardado en una tabla de segmento que mapea de forma bi-dimensional direcciones fisicas. Y el sistema de segmentación mapea estos segmentos en la memoria física. Cabe recalcar que no existe una relación simple entre las direcciones lógicas y las direcciones físicas en la segmentación.

![Ejemplo Segmentacion](img/segmentacion.png)


#### Ventajas y Desventajas

| **Técnica**    | **Ventajas**                                                                                          | **Desventajas**                                                                                         |
|-----------------|------------------------------------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------------|
| **Paginación**  | - Elimina la fragmentación externa .<br>- Aprovecha bien la memoria.<br>- No necesita que los datos estén en posiciones seguidas en la memoria. | - Puede haber desperdicio de espacio dentro de las páginas.<br>- El sistema necesita usar recursos para traducir las direcciones y manejar tablas de páginas. |
| **Segmentación**| - Se adapta a la estructura del programa.<br>- Solo usa el espacio necesario.<br>- Bueno para programas grandes y organizados. | - Puede haber fragmentación externa (espacios pequeños e inutilizables).<br>- Es complicado manejar los cálculos y las tablas.<br>- No es tan eficiente con segmentos pequeños. |

<br>


---

**2.- Escribe un programa que simule una tabla de páginas para procesos con acceso aleatorio a memoria virtual.**

```C
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

/****************************************
 *         		Struct's                *
 ****************************************/
 
typedef struct TablePage{
	int indicePagina;
	int marcoAsignado;
	int cargada;
	
}TablePage;

typedef struct pagina{
	int numPagina;
	int size;
	
	
	}pagina;
	
typedef struct proceso{
	int PID;
	int cantidadPaginas;
	int size;
	TablePage *tablaPaginas;
	struct proceso *siguiente;
	
	}proceso;
	
typedef struct MarcoMem{
	int numeroMarco;
	int paginaAsignada;
	}MarcoMem;
	
/****************************************
 *        Variables Globales            *
 ****************************************/
 
#define SizeMemoryFisic 64 
#define SizePage 4

int totalMarcos = SizeMemoryFisic / SizePage;
int contProceso = 1;
MarcoMem memoriaFisica[SizeMemoryFisic/SizePage];

proceso *cabeza = NULL;


	
/****************************************
 *         		Funciones               *
 ****************************************/

	
void printfTablasProcesos(){
	
if(cabeza==NULL){
	printf("No hay procesos creados\n");
	return;
	}
	proceso *nuevo = cabeza;
	printf("----------------------------------------\n");
	while(nuevo != NULL){
		printf("| PID: %d | Tamaño Proceso: %d (KB) | Paginas: %d |\n\n",nuevo->PID, nuevo->size, nuevo->cantidadPaginas);
		for(int i = 0; i < nuevo->cantidadPaginas;i++){
		printf("| pagina %d | Marco asignado %d | Cargado %d |\n", nuevo->tablaPaginas[i].indicePagina, nuevo->tablaPaginas[i].marcoAsignado, nuevo->tablaPaginas[i].cargada);
		}
		printf("----------------------------------------\n");

		
	nuevo = nuevo->siguiente;
	}
	}
	
void printfMemFisica() {
    printf("Memoria Física:\n");
    for (int i = 0; i < totalMarcos; i++) {
        printf("| Marco %d | ", memoriaFisica[i].numeroMarco);
        if (memoriaFisica[i].paginaAsignada == -1) {
            printf("Libre\n");
        } else {
            int pidProceso = -1;
            for (proceso *temp = cabeza; temp != NULL; temp = temp->siguiente) {
                for (int j = 0; j < temp->cantidadPaginas; j++) {
                    if (temp->tablaPaginas[j].indicePagina == memoriaFisica[i].paginaAsignada) {
                        pidProceso = temp->PID;
                        break;
                    }
                }
                if (pidProceso != -1){
					break;
					} 
                ;  
            }

            if (pidProceso != -1) {
                printf("Asignado a Página %d, Proceso ID: %d\n", memoriaFisica[i].paginaAsignada, pidProceso);
            } else {
                printf("No se encontró proceso asignado.\n");
            }
        }
    }
    printf("\n");
}




int numeroPaginas(int * tam){
	int totpagina = 0;
	totpagina = (int)ceil((float)*tam / SizePage);
	
	return totpagina;
	}
	
void crearProceso(){
	//crear nuevo proceso y inicializar sus atributos
	int tam = 0;
	printf("Elige el tamaño del proceso (KB): ");
	scanf("%d",&tam);
	proceso *nuevoProceso = (proceso*)malloc(sizeof(proceso));
	nuevoProceso->PID=contProceso;
	nuevoProceso->size=tam;
	nuevoProceso->cantidadPaginas=numeroPaginas(&tam);
	nuevoProceso->tablaPaginas = (TablePage*)malloc(sizeof(TablePage) * nuevoProceso->cantidadPaginas);
	
	//inizializar la tabla de paginacion del proceso
	for(int i = 0; i<nuevoProceso->cantidadPaginas;i++){
		nuevoProceso->tablaPaginas[i].indicePagina = i;
		nuevoProceso->tablaPaginas[i].cargada = 0;
		nuevoProceso->tablaPaginas[i].marcoAsignado= -1;
		
		}
		nuevoProceso->siguiente=cabeza;
		cabeza = nuevoProceso;
		contProceso++;
	}
	
void asignarPaginas() {
    if (cabeza == NULL) {
        printf("No hay procesos creados.\n");
        return;
    }

    printf("Seleccione el proceso para asignar páginas:\n");

    proceso *temp = cabeza;
    while (temp != NULL) {
        printf("| ID: %d | Tamaño: %d KB | Páginas: %d |\n", temp->PID, temp->size, temp->cantidadPaginas);
        temp = temp->siguiente;
    }

    printf("Ingresa el ID del proceso: ");
    int idProceso;
    scanf("%d", &idProceso);

    proceso *temp2 = cabeza;
    while (temp2 != NULL) {
        if (temp2->PID == idProceso) {
            printf("Proceso encontrado: ID: %d\n", temp2->PID);

            for (int i = 0; i < temp2->cantidadPaginas; i++) {
                printf("| Página %d | Marco asignado: %d | Cargado: %d |\n", 
                        temp2->tablaPaginas[i].indicePagina, 
                        temp2->tablaPaginas[i].marcoAsignado, 
                        temp2->tablaPaginas[i].cargada);
            }

            int opc = 0;
            do {
                int pagselecion;
                printf("Selecciona el número de página a cargar en memoria: ");
                scanf("%d", &pagselecion);
                
                if (pagselecion < 0 || pagselecion >= temp2->cantidadPaginas) {
                    printf("Página inválida.\n");
                    return;
                }

                if (temp2->tablaPaginas[pagselecion].marcoAsignado != -1) {
                    printf("Página ya asignada a un marco.\n");
                    return;
                }

                printf("Marcos disponibles:\n");
                for (int i = 0; i < totalMarcos; i++) {
                    if (memoriaFisica[i].paginaAsignada == -1) {
                        printf("Marco %d (Libre)\n", i);
                    }
                }

                int marcoSeleccionado;
                printf("Ingresa el número de marco para asignar: ");
                scanf("%d", &marcoSeleccionado);

                if (marcoSeleccionado < 0 || marcoSeleccionado >= totalMarcos) {
                    printf("Marco inválido.\n");
                    return;
                }

                if (memoriaFisica[marcoSeleccionado].paginaAsignada != -1) {
                    printf("El marco %d ya está ocupado. Por favor selecciona otro marco.\n", marcoSeleccionado);
                    return;
                }

                memoriaFisica[marcoSeleccionado].paginaAsignada = temp2->tablaPaginas[pagselecion].indicePagina;
                temp2->tablaPaginas[pagselecion].marcoAsignado = marcoSeleccionado;
                temp2->tablaPaginas[pagselecion].cargada = 1;

                printf("Página %d asignada al marco %d.\n", pagselecion, marcoSeleccionado);

                printf("1.- Asignar otra página\n");
                printf("0.- Salir\n");
                scanf("%d", &opc);
            } while (opc != 0);

            return;
        }
        temp2 = temp2->siguiente;
    }

    printf("Proceso no encontrado.\n");
}

void eliminarPaginas() {
    if (cabeza == NULL) {
        printf("No hay procesos creados.\n");
        return;
    }

    printf("Seleccione el proceso del cual eliminar páginas:\n");
    proceso *temp = cabeza;
    while (temp != NULL) {
        printf("| PID: %d | Tamaño: %d KB | Páginas: %d |\n", temp->PID, temp->size, temp->cantidadPaginas);
        temp = temp->siguiente;
    }

    int idProceso;
    printf("Ingresa el ID del proceso: ");
    scanf("%d", &idProceso);

    proceso *temp2 = cabeza;
    while (temp2 != NULL) {
        if (temp2->PID == idProceso) {
            printf("Proceso encontrado: ID: %d\n", temp2->PID);

            for (int i = 0; i < temp2->cantidadPaginas; i++) {
                printf("| Página %d | Marco asignado: %d | Cargada: %d |\n", 
                        temp2->tablaPaginas[i].indicePagina, 
                        temp2->tablaPaginas[i].marcoAsignado, 
                        temp2->tablaPaginas[i].cargada);
            }

            int pagseleccion;
            printf("Selecciona el número de página a eliminar: ");
            scanf("%d", &pagseleccion);

            if (pagseleccion < 0 || pagseleccion >= temp2->cantidadPaginas) {
                printf("Página inválida.\n");
                return;
            }

            if (temp2->tablaPaginas[pagseleccion].marcoAsignado == -1) {
                printf("La página no tiene un marco asignado.\n");
                return;
            }

            int marcoLiberado = temp2->tablaPaginas[pagseleccion].marcoAsignado;
            memoriaFisica[marcoLiberado].paginaAsignada = -1;
            temp2->tablaPaginas[pagseleccion].marcoAsignado = -1;
            temp2->tablaPaginas[pagseleccion].cargada = 0;

            printf("Página %d liberada del marco %d.\n", pagseleccion, marcoLiberado);
            return;
        }
        temp2 = temp2->siguiente;
    }

    printf("Proceso no encontrado.\n");
}

int main()
{
	srand(time(NULL));
	//Inicializar Memoria Fisica
	
	for(int i = 0; i < totalMarcos ;i++){
			memoriaFisica[i].numeroMarco = i;
			memoriaFisica[i].paginaAsignada = -1;
		}
		
	int opc = 0;
	
	do{
		printf("------------- Menu -------------\n");
		printf("1.- Crear Proceso\n");
		printf("2.- Asignar Paginas\n");
		printf("3.- Liberar Paginas\n");
		printf("4.- Mostrar procesos\n");
		printf("5.- Mostrar Memoria Fisica\n");
		printf("6.- Salir\n");
		printf("--------------------------------\n");
		scanf("%d",&opc);
		switch(opc){
			case 1:
				crearProceso();
				break;
				
			case 2:
				asignarPaginas();
				break;
				
			case 3:
				eliminarPaginas();
				break;
				
			case 4:
				printfTablasProcesos();
				break;
				
			case 5:
				printfMemFisica();
				
				break;
			case 6:
				return 0;
				break;
				
			default:
			printf("Opcion invalida");
				
			}
			
	}while(true);
    
  return 0 ;
 }

```
    
## 3.4 Administración de memoria virtual

**1.-  Escribe un código que implemente el algoritmo de reemplazo de página "Least Recently Used" (LRU)**

```C
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

/****************************************
 *         		Struct's                *
 ****************************************/
 
typedef struct TablePage{
	int indicePagina;
	int marcoAsignado;
	int cargada;
	int ultimoUso;
	
}TablePage;

typedef struct pagina{
	int numPagina;
	int size;
	
	
	}pagina;
	
typedef struct proceso{
	int PID;
	int cantidadPaginas;
	int size;
	TablePage *tablaPaginas;
	struct proceso *siguiente;
	
	}proceso;
	
typedef struct MarcoMem{
	int numeroMarco;
	int paginaAsignada;
	int procesoId;
	}MarcoMem;
	
/****************************************
 *        Variables Globales            *
 ****************************************/
 
#define SizeMemoryFisic 8 
#define SizePage 4

int totalMarcos = SizeMemoryFisic / SizePage;
int contProceso = 1;
int contadorUso = 0;
MarcoMem memoriaFisica[SizeMemoryFisic/SizePage];

proceso *cabeza = NULL;
	
/****************************************
 *         		Funciones               *
 ****************************************/
 void LRU();
	
void printfTablasProcesos(){
	
if(cabeza==NULL){
	printf("No hay procesos creados\n");
	return;
	}
	proceso *nuevo = cabeza;
	printf("----------------------------------------\n");
	while(nuevo != NULL){
		printf("| PID: %d | Tamaño Proceso: %d (KB) | Paginas: %d |\n\n",nuevo->PID, nuevo->size, nuevo->cantidadPaginas);
		for(int i = 0; i < nuevo->cantidadPaginas;i++){
		printf("| pagina %d | Marco asignado %d | Cargado %d |\n", nuevo->tablaPaginas[i].indicePagina, nuevo->tablaPaginas[i].marcoAsignado, nuevo->tablaPaginas[i].cargada);
		}
		printf("----------------------------------------\n");

		
	nuevo = nuevo->siguiente;
	}
	}
	
void printfMemFisica() {
    printf("-- Memoria Fisica --\n");
        for (int i = 0; i < totalMarcos; i++) {
        if (memoriaFisica[i].paginaAsignada != -1) {
            int pidProceso = memoriaFisica[i].procesoId;
            proceso *aux = cabeza;
            while (aux != NULL && aux->PID != pidProceso) {
                aux = aux->siguiente;
            }

            if (aux != NULL) {
                for (int j = 0; j < aux->cantidadPaginas; j++) {
                    if (aux->tablaPaginas[j].marcoAsignado == i) {
                        printf("| Marco: %d | Página: %d | (Proceso ID: %d) | Último Uso: %d \n", 
                               i, aux->tablaPaginas[j].indicePagina, aux->PID, aux->tablaPaginas[j].ultimoUso);
                        break;
                    }
                }
            }
        } else {
            printf("Marco %d: Libre\n", i);
        }
    }
}

int numeroPaginas(int * tam){
	int totpagina = 0;
	totpagina = (int)ceil((float)*tam / SizePage);
	
	return totpagina;
	}
	
void crearProceso(){
	
	int tam = 0;
	printf("Elige el tamaño del proceso (KB): ");
	scanf("%d",&tam);
	proceso *nuevoProceso = (proceso*)malloc(sizeof(proceso));
	nuevoProceso->PID=contProceso;
	nuevoProceso->size=tam;
	nuevoProceso->cantidadPaginas=numeroPaginas(&tam);
	nuevoProceso->tablaPaginas = (TablePage*)malloc(sizeof(TablePage) * nuevoProceso->cantidadPaginas);
	
	for(int i = 0; i<nuevoProceso->cantidadPaginas;i++){
		nuevoProceso->tablaPaginas[i].indicePagina = i;
		nuevoProceso->tablaPaginas[i].cargada = 0;
		nuevoProceso->tablaPaginas[i].marcoAsignado= -1;
		
		}
		nuevoProceso->siguiente=cabeza;
		cabeza = nuevoProceso;
		contProceso++;
	}
	

void asignarPaginas() {
    if (cabeza == NULL) {
        printf("No hay procesos creados.\n");
        return;
    }

    printf("Seleccione el proceso para asignar páginas:\n");

    proceso *temp = cabeza;
    while (temp != NULL) {
        printf("| ID: %d | Tamaño: %d KB | Páginas: %d |\n", temp->PID, temp->size, temp->cantidadPaginas);
        temp = temp->siguiente;
    }

    printf("Ingresa el ID del proceso: ");
    int idProceso;
    scanf("%d", &idProceso);

    proceso *temp2 = cabeza;
    while (temp2 != NULL) {
        if (temp2->PID == idProceso) {

            int todasAsignadas = 1;
            for (int i = 0; i < temp2->cantidadPaginas; i++) {
                if (temp2->tablaPaginas[i].marcoAsignado == -1) {
                    todasAsignadas = 0;
                    break;
                }
            }

            

            for (int i = 0; i < temp2->cantidadPaginas; i++) {
                printf("| Página %d | Marco asignado: %d | Cargada: %d |\n", temp2->tablaPaginas[i].indicePagina, temp2->tablaPaginas[i].marcoAsignado, temp2->tablaPaginas[i].cargada);
            }

            int opc = 0;
            do {
                int pagseleccion;
                printf("Selecciona el número de página a cargar en memoria: ");
                scanf("%d", &pagseleccion);
                
                if (pagseleccion < 0 || pagseleccion >= temp2->cantidadPaginas) {
                    printf("Página inválida.\n");
                    return;
                }

                if (temp2->tablaPaginas[pagseleccion].marcoAsignado != -1) {
                    printf("Página ya asignada a un marco.(Nuevo Uso)\n");
                    temp2->tablaPaginas[pagseleccion].ultimoUso = contadorUso;
                    contadorUso++;
                    return;
                }

                int marcosLibres[totalMarcos];
                int numLibres = 0;
                for (int i = 0; i < totalMarcos; i++) {
                    if (memoriaFisica[i].paginaAsignada == -1) {
                        marcosLibres[numLibres++] = i;
                    }
                }

                if (numLibres == 0) {
                    LRU();
                }

                numLibres = 0;
                for (int i = 0; i < totalMarcos; i++) {
                    if (memoriaFisica[i].paginaAsignada == -1) {
                        marcosLibres[numLibres++] = i;
                    }
                }

                int marcoAleatorio = marcosLibres[rand() % numLibres];
                memoriaFisica[marcoAleatorio].paginaAsignada = temp2->tablaPaginas[pagseleccion].indicePagina;
                memoriaFisica[marcoAleatorio].procesoId = temp2->PID;
                temp2->tablaPaginas[pagseleccion].marcoAsignado = marcoAleatorio;
                temp2->tablaPaginas[pagseleccion].cargada = 1;
                temp2->tablaPaginas[pagseleccion].ultimoUso = contadorUso;
                contadorUso++;

                printf("Página %d asignada al marco %d.\n", pagseleccion, marcoAleatorio);
                todasAsignadas = 1;
                for (int i = 0; i < temp2->cantidadPaginas; i++) {
                    if (temp2->tablaPaginas[i].marcoAsignado == -1) {
                        todasAsignadas = 0;
                        break;
                    }
                }

                if (todasAsignadas) {
                    return;
                }

                printf("1.- Asignar otra página\n");
                printf("0.- Salir\n");
                scanf("%d", &opc);
            } while (opc != 0);

            return;
        }
        temp2 = temp2->siguiente;
    }

    printf("Proceso no encontrado.\n");
}


void LRU() {
    if (cabeza == NULL) {
        printf("No hay procesos creados.\n");
        return;
    }

    proceso *temp2 = cabeza;
    int delatepage = -1;
    int menorUso = contadorUso;
    proceso *Aux = NULL;

    while (temp2 != NULL) {
        for (int i = 0; i < temp2->cantidadPaginas; i++) {
            if (temp2->tablaPaginas[i].cargada && temp2->tablaPaginas[i].ultimoUso < menorUso) {
                menorUso = temp2->tablaPaginas[i].ultimoUso;
                delatepage = i;
                Aux = temp2;
            }
        }
        temp2 = temp2->siguiente;
    }

    if (delatepage == -1) {
        printf("No se encontró página cargada para eliminar.\n");
        return;
    }
    if(Aux!=NULL){
		int marcoLiberado = Aux->tablaPaginas[delatepage].marcoAsignado;
		memoriaFisica[marcoLiberado].paginaAsignada = -1;
		Aux->tablaPaginas[delatepage].marcoAsignado = -1;
		Aux->tablaPaginas[delatepage].cargada = 0;
		printf("Página %d eliminada del marco %d del proceso[%d].\n", delatepage, marcoLiberado,memoriaFisica[marcoLiberado].procesoId);
		printf("\n");
		memoriaFisica[marcoLiberado].procesoId = -1;

		}

    
}


int main()
{
	srand(time(NULL));
	//Inicializar Memoria Fisica
	
	for(int i = 0; i < totalMarcos ;i++){
			memoriaFisica[i].numeroMarco = i;
			memoriaFisica[i].paginaAsignada = -1;
		}
		
	int opc = 0;
	
	do{
		printf("------------- Menu -------------\n");
		printf("1.- Crear Proceso\n");
		printf("2.- Asignar Paginas\n");
		printf("3.- Mostrar procesos\n");
		printf("4.- Mostrar Memoria Fisica\n");
		printf("5.- Salir\n");
		printf("--------------------------------\n");
		scanf("%d",&opc);
		switch(opc){
			case 1:
				crearProceso();
				break;
				
			case 2:
				asignarPaginas();
				break;
				
			case 3:
				printfTablasProcesos();
				break;
				
			case 4:
				printfMemFisica();
				
				break;
			case 5:
				return 0;
				break;
				
			default:
			printf("Opcion invalida");
				
			}
			
	}while(true);
    
  return 0 ;
 }



```
---
**2.- Diseña un diagrama que represente el proceso de traducción de direcciones virtuales a físicas en un sistema con memoria virtual.**

Las direcciones identifican unívocamente una ubicación en la memoria. Tenemos dos tipos de direcciones que son la dirección lógica o virtual y la dirección física. La dirección lógica se utiliza como referencia para acceder a la dirección física.

- Direcciones logicas

* Las direcciones logicas se componen de:
    * Numero de pagina(p): Se usa como un indice en la tabla de paginas que contiene la direccion base de cada pagina en memoria fisica.

    * Desplazamiento(d): Combinado con la direccion base define la direccion fisica que se envia a la unidad de manejo de memoria (mmu).

![Direccion Logica Paginaccion](img/adressLogicPag01.png)
![Direccion Logica Paginaccion](img/adressLogicPag02.png)

Este ejemplo fue hecho usando de ejemplo la paginacion pero el procedimiento es exactamente igual con la segmentacion para traducir las direcciones logicas a fisicas lo unico que varia es que se debe verificar que el desplzamiento no exceda el tamaño del segmento referenciado en la direccion

* En paginación, las direcciones virtuales se dividen en dos partes: el número de página (que actúa como índice en la tabla de páginas) y el desplazamiento dentro de la página. La traducción se realiza buscando el número de página en la tabla de páginas y combinando el contenido de la tabla que contiene marcos de pagina juntandolo con el desplazamiento.

* En segmentación, las direcciones lógicas se dividen en dos partes: el número de segmento y el desplazamiento dentro del segmento. La diferencia principal es que en segmentación no hay un tamaño fijo para cada segmento, ya que el tamaño de los segmentos puede variar. Entonces, al traducir una dirección lógica a física, además de buscar la base del segmento en la tabla de segmentos, también debes verificar que el desplazamiento no exceda el tamaño del segmento referido en la dirección.

### Integracion

**1.- Analiza un sistema operativo moderno (por ejemplo, Linux o Windows) e identifica cómo administra la memoria virtual.**

Ubuntu es un sistema operativo basado en Linux, que gestiona la memoria virtual a través de paginación y el uso de un espacio de intercambio llamado swap o swapping pa los amigos. Las páginas son de 4 KB aunque es posible aumentarla a paginas grandes, y se utiliza la Unidad de Gestión de Memoria (MMU) pn resumen, Ubuntu administra la memoria virtual con paginación y swap para optimizar el uso de la memoria, pero el uso excesivo de swap puede reducir el rendimiento. La memoria se maneja de forma eficiente gracias a la MMU, pero es importante tener suficiente RAM para evitar un rendimiento lento debido al uso frecuente de swap.ara traducir las direcciones virtuales a físicas igual que windows. Cada proceso tiene su propio espacio de direcciones virtuales, y cuando necesita acceder a una dirección que no está en la memoria RAM, se produce el famoso fallo de pagina si la página no está en la RAM y pues como no esta el SO procede a cargarla desde el disco que comunmente se usa el swap, lo que puede hacer que el sistema se vuelva más lento ya que las velocidades del disco son mas lentas que la ram.

El sistema usa un archivo o partición de swap para almacenar páginas que no se usan activamente. Si la RAM se llena, Ubuntu mueve las páginas a swap, liberando memoria para otros procesos. Aunque el swap ayuda a evitar que el sistema se quede sin memoria, usarlo constantemente puede afectar el rendimiento.

Ubuntu también permite configurar el parámetro swappiness, que determina cuánta memoria debe ser movida al swap. Por ejemplo, un valor de swappiness de 60 significa que Ubuntu comenzará a usar el swap cuando la RAM esté al 60% de su capacidad.

---

**2.- Realiza una simulación en cualquier lenguaje de programación que emule el swapping de procesos en memoria virtual.**
```C

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



```
<br>

# Administración de Entrada/Salida

## 4.1 Dispositivos y manejadores de dispositivos
**1.- Explica la diferencia entre dispositivos de bloque y dispositivos de carácter. Da un ejemplo de cada uno.**


Los dispositivos de bloque y de carácter son dos categorías fundamentales en las que se clasifican los dispositivos de almacenamiento y entrada/salida en un sistema informático. La principal diferencia entre ellos radica en la forma en que organizan y acceden a los datos.

### Dispositivos de Bloque
Los dispositivos de bloque almacenan datos en unidades fijas de tamaño, llamadas bloques. Cada bloque tiene una dirección única, lo que permite acceder a cualquier parte del dispositivo de manera aleatoria.

El sistema operativo divide el dispositivo en bloques de tamaño fijo, y cada bloque tiene una dirección lógica que se utiliza para acceder a los datos. El controlador del dispositivo es el encargado de traducir esta dirección lógica en una dirección física en el dispositivo, permitiendo así la correcta localización y acceso a los datos almacenados.

#### Caracteristicas

* Acceso aleatorio: Se puede leer o escribir cualquier bloque sin tener que pasar por los anteriores.
* Estructura: Los datos se organizan en una estructura jerárquica, lo que facilita la gestión y búsqueda de 
información.

#### Ejemplos:

Ejemplos: Discos duros (HDD), unidades de estado sólido (SSD), unidades USB flash, discos ópticos (CD, DVD, Blu-ray).

#### Ventajas:
* Alto rendimiento para operaciones de lectura y escritura aleatoria

* Estructura de datos eficiente para almacenar grandes cantidades de información

* Ideal para sistemas de archivos y bases de datos

### Dispositivos de Carácter

En contraste, los dispositivos de carácter no almacenan datos en bloques, sino que los manejan como un flujo continuo de caracteres. No permiten el acceso aleatorio a los datos, ya que no se estructuran en bloques direccionables. Los dispositivos de carácter son típicamente utilizados para la entrada o salida de datos en tiempo real, donde la secuencia de los datos es más importante que el acceso directo a partes específicas de ellos.

##### Características:
* Acceso secuencial: Los datos se leen o escriben de forma secuencial, uno tras otro

* Estructura: No tienen una estructura de bloques, por lo que no se puede acceder directamente a una parte específica del dispositivo

#### Ejemplos:

Ejemplos: Teclados, ratones, impresoras, módems, terminales serie.

#### Ventajas:
* Simpleza en la implementación.

* Adecuados para dispositivos de entrada/salida interactivos.

#### Comparativa

| Característica        | Dispositivos de Bloque       | Dispositivos de Carácter     |
|-----------------------|------------------------------|------------------------------|
| Unidad de acceso      | Bloque                       | Carácter                     |
| Acceso a datos        | Aleatorio                    | Secuencial                   |
| Estructura de datos   | Jerárquica                   | Lineal                       |
| Ejemplos              | Discos duros, SSD, USB flash | Teclados, ratones, impresoras |
| Uso típico            | Almacenamiento de archivos, sistemas operativos | Interacción con el usuario, comunicaciones |

--- 
**2.- Diseña un programa que implemente un manejador de dispositivos sencillo para un dispositivo virtual de entrada.**

```C
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

```

## 4.2 Mecanismos y funciones de los manejadores de dispositivos
**1.- Investiga qué es la interrupción por E/S y cómo la administra el sistema operativo. Escribe un ejemplo en pseudocódigo  simular este proceso**

Las interrupciones por E/S son señales enviadas por los dispositivos de entrada/salida (E/S) al procesador para solicitar atención inmediata. En lugar de esperar a que el procesador termine con sus tareas actuales, los dispositivos de E/S interrumpen su ejecución para que el procesador pueda atender la solicitud.

Con objeto de eliminar la necesidad de interrogar continuamente al disposi­tivo, una alternativa es el empleo de las interrupciones. En este caso, cuando el procesador da una orden de E/S a la controladora puede continuar con otro tra­bajo, ya que ésta le notificará mediante una interrupción del fin de la operación de E/S.

Estas interrupciones permiten al sistema operativo y a los programas controlar y responder a eventos externos de manera eficiente. Sin embargo, sigue consu­miendo una gran cantidad de tiempo del procesador, ya que éste se encarga de transferir cada palabra de datos que va de la memoria al dispositivo o viceversa. Esto hace que el rendimiento del sistema disminuya cuando se tiene que transferir un gran volumen de datos.

#### Tipos Interrupciones
* Interrupciones por Hardware
    * Internas: Se generan cuando un dispositivo de entrada o salida necesita atención del procesador.

    * Externas: se generan por eventos internos del procesador, como divisiones por cero, desbordamiento de memoria o errores de hardware

* Interrupciones por Software
    * Interrupciones del Sistema Operativo: Se utilizan para solicitar servicios del sistema operativo, como la impresión de un archivo o la asignación de memoria.

    * Interrupciones de software: Son generadas por programas en ejecución para solicitar servicios del sistema operativo, como la apertura de un archivo o la comunicación con un dispositivo externo.

* Interrupciones por tiempo
* Interrupciones por excepcion

#### Proceso de Gestión de Interrupciones por E/S

1. Detección de la Interrupción: El procesador detecta una señal de interrupción de un dispositivo de E/S

2. Guardado del Contexto: El sistema guarda el estado del procesador (registros, contador de programa) antes de interrumpir el proceso actual.

3. Ejecución de la ISR (Rutina de Servicio de Interrupción): El procesador salta a la Rutina de Servicio de Interrupción (ISR) correspondiente al dispositivo que generó la interrupción. La ISR procesa la solicitud del dispositivo (lectura/escritura).

4. Restauración del Contexto: El sistema restaura el estado del procesador para reanudar el proceso que fue interrumpido.

5. Reanudación de la Ejecución del Proceso: El procesador continúa ejecutando el proceso interrumpido desde donde lo dejó.

#### Pseucodigo
##### Inicio
```Pseucodigo

  definir dispositivo de e/s
  definir tabla de estados de dispositivos

  iniciar el sistema operativo

  // usuario solicita una operación de e/s
  funcion solicitarES():
      // se solicita que el dispositivo realice una operación
      imprimir "solicitud de e/s iniciada..."
      cambiar el estado del dispositivo a "en proceso"
      almacenar información sobre la operación en la tabla de estados
      iniciar operación de e/s en el dispositivo

  // el manejador de dispositivos verifica si el dispositivo está libre
  funcion driverDevice():
      si el dispositivo está ocupado:
          imprimir "el dispositivo está ocupado. esperando..."
          esperar hasta que la operación termine
      si no:
          imprimir "el dispositivo está libre. iniciando operación de e/s..."
          cambiar estado del dispositivo a "en proceso"
          iniciar la operación de e/s en el dispositivo

  // simulamos la operación de e/s que tarda cierto tiempo
      solicitares();
      imprimir "operación de e/s en proceso..."
      simular el tiempo de la operación
      cambiar estado del dispositivo a "completado"
      imprimir "operación de e/s completada."

  // el sistema operativo maneja la interrupción cuando la operación de e/s termina de cargar
  funcion driverDevice():
      si el dispositivo ha completado la operación:
          imprimir "interrupción recibida: operación de e/s completada."
          devolver control al proceso original
          cambiar estado a "espera"

  // simulamos la interrupcion del SO
  funcion SO():
      // verificar drivers
      si interrupcion está activa:
          manejar interrupcion
      si no:
          ejecutar otra tarea del sistema operativo

```
##### Fin
---

**2.- Escribe un programa que utilice el manejo de interrupciones en un sistema básico de simulación.**

```C
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

```
###

## 4.3 Estructuras de datos para manejo de dispositivos

**1.- Investiga y explica qué es una cola de E/S. Diseña una simulación de una cola con prioridad.**

#### Cola de E/S

Una cola de E/S es una estructura de datos que organiza las solicitudes de entrada/salida en un sistema operativo de manera similar a una fila en un banco, donde las solicitudes se procesan en el orden en que llegan, siguiendo generalmente el principio FIFO (Primero en Entrar, Primero en Salir). Estas solicitudes pueden ser de diversos tipos, como:

* Lectura de datos desde disco

* Escritura de datos a un archivo

* Envio de datos a travez de la red

Las solicitudes en la cola se envían a los controladores de dispositivos correspondientes para su ejecución.

#### Cola de E/S con Prioridad

En sistemas donde ciertas tareas tienen mayor urgencia, como en sistemas en tiempo real, se utilizan colas de E/S con prioridad. Cada solicitud tiene asignada una prioridad, y las solicitudes con mayor prioridad se procesan primero, independientemente de cuándo llegaron.

```C
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



```
---

**2.- Escribe un programa que simule las operaciones de un manejador de dispositivos utilizando una tabla de estructuras.**
```C
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


```


## 4.4 Operaciones de Entrada/Salida

**1.- Diseña un flujo que describa el proceso de lectura de un archivo desde un disco magnético. Acompáñalo con un programa básico que simule el proceso.**

El rendimiento de un disco depende de varios factores que afectan el tiempo total de acceso y transferencia de datos:

* Tiempo de búsqueda: Es el tiempo necesario para mover la cabeza del disco a la pista requerida. Este tiempo incluye tanto el arranque inicial como el movimiento para atravesar las pistas.

* Retardo rotacional: Es el tiempo que tarda el sector correcto en rotar hasta quedar bajo la cabeza de lectura/escritura. El retardo depende de la velocidad de rotación del disco (por ejemplo, entre 3600 y 15,000 revoluciones por minuto).

* Tiempo de transferencia: Este es el tiempo que se tarda en leer o escribir datos una vez que la cabeza está en posición y el sector deseado está debajo de ella.



![Direccion Logica Paginaccion](img/Componentes_HD_comentados.png)



#### Flujo
## Proceso de Lectura de un Archivo

El número de bloques que componen un archivo puede variar dependiendo de varios factores, entre ellos el tamaño del archivo y el sistema de archivos del disco. Un bloque es la unidad básica de almacenamiento en el disco, y su tamaño suele ser de 512 bytes, 1 KB, 2 KB, 4 KB, o más.

Diferentes sistemas de archivos (NTFS, FAT32, ext4, etc.) manejan el almacenamiento de manera distinta.

**Solicitud → Búsqueda → Posicionamiento → Lectura → Transferencia → Finalización**


| Paso | Paso                                            |
|:------:|--------------------------------------------------------|
| 1    | **Solicitud de Lectura**: El sistema operativo recibe una solicitud para leer un archivo. |
| 2    | **Búsqueda del Archivo**: El sistema operativo busca la ubicación del archivo en el disco. |
| 3    | **Posicionamiento de la Cabeza**: La cabeza de lectura/escritura del disco se mueve a la pista adecuada. |
| 4    | **Lectura de Datos**: Los datos del archivo se leen en bloques y se almacenan en un buffer. |
| 5    | **Transferencia al Proceso**: Los datos leídos se transfieren al proceso que realizó la solicitud. |
| 6    | **Finalización**: El sistema operativo actualiza los estados y libera recursos. |



![Direccion Logica Paginaccion](img/disco1.jpg)

![Direccion Logica Paginaccion](img/disco%202.jpg)

#### Condiciones para leeer un archivo
Las condiciones para que un disco pueda encontrar un archivo dependen de la estructura del sistema de archivos y cómo se almacenan los archivos en el disco. Pero para el ejemplo que proponemos las condiciones que tratamos de recrear son las siguientes:

* Ubicación del archivo: Se sabe en qué pista o bloque está.
* Cabezal en la posición correcta: El cabezal de lectura debe estar en la pista adecuada.
* Retardo rotacional: Esperar que el disco gire al sector adecuado.
* Existencia del archivo: Verificar que el archivo realmente exista.
* Acceso a los bloques de datos: Verificar que los bloques estén accesibles.
* Estado del disco: Asegurarse de que el disco y la cabeza de lectura no estén ocupados.


---


#### Programa
```C
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


```

---

**2.- Implementa un programa en Python, C o java que realice operaciones de entrada/salida asíncronas usando archivos.**

```C
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


```

### Integracion

**1.- Escribe un programa que implemente el algoritmo de planificación de discos "Elevator (SCAN)".**

El algoritmo SCAN procesa solicitudes en una sola dirección hasta alcanzar el final del recorrido. Una vez completado el recorrido ascendente, se invierte la dirección y se procesan las solicitudes en sentido descendente.
```C

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

/****************************************
 *              Struct's                *
 ****************************************/
typedef struct Request {
    int track;
    bool handled;
} Request;

typedef struct Disk {
    int *tracks;
    int numTracks;
} Disk;

/****************************************
 *        Variables Globales            *
 ****************************************/
Disk disco;
Request *requests;
int numRequests;
int currentTrack;
int direction; // -1 left 1 rigth

/****************************************
 *              Funciones               *
 ****************************************/
void scan();
int findNextRequest();
void initRequests(int *reqTracks, int numReq);
void initDisk(int *tracks, int numTracks);
void handleRequest(int index);

void scan() {
    printf("Iniciando planificación SCAN (Elevator)...\n");
    while (true) {
        int nextRequest = findNextRequest();
        if (nextRequest == -1) {
            if (direction == 1 && currentTrack == disco.numTracks - 1) {
                direction = -1;
            } else if (direction == -1 && currentTrack == 0) {
                direction = 1;
            } else {
                break;
            }
        } else {
            handleRequest(nextRequest);
        }
    }
    printf("Planificación completada.\n");
}

int findNextRequest() {
    int nextIndex = -1;
    int minDistance = __INT_MAX__;
    for (int i = 0; i < numRequests; i++) {
        if (!requests[i].handled) {
            int distance = requests[i].track - currentTrack;
            if ((direction == 1 && distance >= 0) || (direction == -1 && distance <= 0)) {
                distance = abs(distance);
                if (distance < minDistance) {
                    minDistance = distance;
                    nextIndex = i;
                }
            }
        }
    }
    return nextIndex;
}

void initRequests(int *reqTracks, int numReq) {
    requests = (Request *)malloc(numReq * sizeof(Request));
    numRequests = numReq;
    for (int i = 0; i < numReq; i++) {
        requests[i].track = reqTracks[i];
        requests[i].handled = false;
    }
}

void initDisk(int *tracks, int numTracks) {
    disco.tracks = tracks;
    disco.numTracks = numTracks;
}

void handleRequest(int index) {
    printf("Moviendo cabezal de %d a %d\n", currentTrack, requests[index].track);
    currentTrack = requests[index].track;
    requests[index].handled = true;
    printf("Solicitud en pista %d atendida.\n", currentTrack);
}

int main() {
	srand(time(0));
	
    int trackArray[] = {34, 62, 95, 123, 180, 499,1,12,5,2};
    int numTracks = 500;
    int numReq = sizeof(trackArray) / sizeof(trackArray[0]);

    initDisk(NULL, numTracks);
    initRequests(trackArray, numReq);

    currentTrack = rand()%100+1;
    direction = 1;
    scan();

    free(requests);
    return 0;
}


```
**2.- Diseña un sistema que maneje múltiples dispositivos simulados (disco duro, impresora, teclado) y muestra cómo se realiza la comunicación entre ellos.**

```C
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


```

### Avanzados

**1. Explica cómo los sistemas operativos modernos optimizan las operaciones de entrada/salida con el uso de memoria caché**

La memoria caché es de las memorias de acceso mas rápido que una computadora tiene a su desposicion ya que es la mas cercana al microprocesador porque normalmente se encuentra dentro de este. Los sistemas operativos modernos utilizan cachés para almacenar temporalmente los datos más frecuentemente solicitados o recientemente utilizados siendo los mas comunes instrucciones de manejo de E/S, drivers, paginas de memoria virtual, proxy E/S, archivos etc... aunque  la mayoria de instrucciones estandar estan en la BIOS. Esto reduce la latencia y mejora la eficiencia de las operaciones de E/S y manejadores de hardware, ya que los datos pueden ser accedidos más rápidamente desde la caché en lugar de tener que acceder al disco duro o la memoria secundaria, que tiene tiempos de acceso más lentos. Gracias a la cache podemos evitar realizar costosos accesos a dispositivos de almacenamiento, acelerando así la ejecución de procesos.

---

<div align="center">

# Dispositivos Entradas y Salidas en Linuxs

</div>

## Actividad 1: Listar dispositivos conectados

