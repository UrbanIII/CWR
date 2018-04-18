#include<stdio.h>

double f(int n){
	return n*(1/3.0)-n/3.0;
}

int main(){
	int n = 7;
	while(n<=8){
		printf("N = %d:\n\t%0.4f\n\t%1.3e\n",n,f(n),f(n));
		n++;
	}	
}
