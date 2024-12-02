#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool printerStatus = false; //f->close t->open
char printerData[256]; // buffer

void open(){
	
}

void read(){
}

void write(){
}
	
void close(){
}

int main(){
	
	fgets(printerData,sizeof(printerData),stdin);
	printf("%s",printerData);
	return 0;
	}
