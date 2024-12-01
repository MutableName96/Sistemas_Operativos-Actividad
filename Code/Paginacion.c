#include <stdio.h>
#include <unistd.h>

int suma (int a, int b);
int pot(int a, int b){
	if(b==1){
	return a;
	}
	if(b==0){
	return 1;
	}
return suma(a,pot(a,b-1));

}

int suma(int a, int b) {
    if (b == 0) {
        return 0;
    }
        return a + suma(a, b - 1);
}





double div(double a, double b){
	double c=0;
	
	if(b==0){
		printf("Error you cant divide by 0");
		return 0;
	}
	if(a==0)
	{
		return 0;
	}else
	c++;
	return c+div(a-b,b);
}	

int main()
{
	

    
  return 0 ;
  }
