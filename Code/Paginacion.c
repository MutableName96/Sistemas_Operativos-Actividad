#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct TablePage{
	int indice;
	int contenido;
	int cargada;
	
}TablePage;

int NumRandom(){
	return (rand() %5);
	
	}



int main()
{
	srand(time(NULL));
	printf("%d",NumRandom());

	

    
  return 0 ;
 }
