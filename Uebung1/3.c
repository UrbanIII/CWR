#include<stdio.h>
#include<math.h> //Must be compiled with -lm ti link the math stuff.

int main(){
	
	printf("Single Precision (Float):\n");
	
	float up = 0, down = 0;
	for(int i = 0; i<=200; i++){
		up += pow(i,3);
		down += pow(200-i,3);	
	}
	printf("\tAufwärts - Abwärts:\t%f\n\n",up-down);
	
	printf("Double Precision (Double):\n");
	double up2 = 0, down2 = 0;
	for(int i = 0; i<=200; i++){
		up2 += pow(i,3);
		down2 += pow(200-i,3);	
	}
	printf("\tAufwärts - Abwärts:\t%f\n",up2-down2);

}
