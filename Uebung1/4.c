#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int fak(int n){
	if (n<2) return 1;
	return n*fak(n-1);
}

double sine(double x){
	double tolerance = 0.001;
	double delta = tolerance; 
	int k = 0;
	double sin = 0, oldsin = 2;
	while(delta>=tolerance){
		sin += pow(-1,k)*pow(x,1+2*k)/fak(1+2*k);
		delta = fabs(sin-oldsin);
		oldsin = sin;
		k++;
printf("%d\t%d\n",k,fak(2*k));
	}
	return sin;
}

int main(){

	FILE *f = fopen("output.txt","w");
	int steps = 100;
	double low = 40, up = 43;
	double x;
	for(int i = 0; i<steps; i++){
		x = low + i*(up-low)/steps;
		fprintf(f,"%f\t%f\n", x, sine(x));
	}
	fclose(f);

}
