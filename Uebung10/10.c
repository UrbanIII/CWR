#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<math.h>
#include <time.h>

unsigned int * Linear_congruential_generator(unsigned long a, unsigned long b, unsigned long m, unsigned int seed, unsigned int n){ //Calculation is carried out with long unsigned to prevent overflow
	unsigned int *array = malloc(sizeof(int)*n);
	array[0] = seed;
	for(int i = 1; i<n; i++){
		array[i] = (unsigned int)((a*array[i-1]+b)%m);
	}
	return array;
}

unsigned int * R250(unsigned int *seed, int n){ // This random number generator is periodic. It is technically enough to have an array of constant length 250 and to always output only one generated number at a time (and of course also writing this number into the array).
	unsigned int *array = malloc(sizeof(int)*(n+250));
	for(int i = 0; i<250; i++){
		array[i] = seed[i];
	}
	for(int i = 0; i<n; i++){
		array[i+250] = array[i]^array[i+250-147];
	}
	return array;
}

int main(){

	unsigned long a = 22695477, b = 1, m = pow(2,32), seed = time(NULL); // For systems where ints have 4 bytes

	// Testing Linear_congruential_generator
	FILE *file = fopen("lin_test_hist","w");
	int n = 1000000;
	unsigned int *lin_test = Linear_congruential_generator(a,b,m,seed,n); // Patterns for example for a = 343, b = 3348
	for(int i = 0; i<n; i++){
		fprintf(file,"%lf\n",(double)lin_test[i]/m);
	}
	fclose(file);
	file = fopen("lin_test_2d","w");
	for(int i=0; i<n; i+=2){
		if(i+1<n){
			fprintf(file,"%lf\t%lf\n",(double)lin_test[i]/m,(double)lin_test[i+1]/m);
		}
	}
	fclose(file);
	file = fopen("lin_test_3d","w");
	for(int i=0; i<n; i+=3){
		if(i+2<n){
			fprintf(file,"%lf\t%lf\t%lf\n",(double)lin_test[i]/m,(double)lin_test[i+1]/m,(double)lin_test[i+2]/m);
		}
	}
	fclose(file);
	free(lin_test);

	//Combine the two generators
	unsigned int *start = Linear_congruential_generator(a,b,m,seed,250);
	unsigned int *r_test = R250(start, n);
	file = fopen("r_test_hist","w");
	for(int i = 0; i<n; i++){
		fprintf(file,"%lf\n",(double)r_test[i]/m);
	}
	fclose(file);
	file = fopen("r_test_2d","w");
	for(int i=0; i<n; i+=2){
		if(i+1<n){
			fprintf(file,"%lf\t%lf\n",(double)r_test[i]/m,(double)r_test[i+1]/m);
		}
	}
	fclose(file);
	file = fopen("r_test_3d","w");
	for(int i=0; i<n; i+=3){
		if(i+2<n){
			fprintf(file,"%lf\t%lf\t%lf\n",(double)r_test[i]/m,(double)r_test[i+1]/m,(double)r_test[i+2]/m);
		}
	}
	free(r_test);
	fclose(file);

}
