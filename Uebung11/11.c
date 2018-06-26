#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>

#define N 100
#define T 300 // Not in Kelvin because k = 1
#define H 0

void print_array(signed char array[N][N], FILE *file){
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			// I do not know how to proceed further. This is highly dependent on the way in which the data will be processed further. My current idea is to simply let compute many iterations of ising_step and then plot array (perhaps with gnuplot matrix mode?). Then calculate the magnetisation as the sum of all spins. 
// Perhaps in the futur one could do this for many different temperatures... Also interesting: plotting energy or magnetization after many steps vs. temperature.
		}
	}	
}

double energy(signed char array[N][N]){
	double E = 0;
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			E += -array[i][j]*array[(i+1)%N][j]-array[i][j]*array[(i+N-1)%N][j]-array[i][j]*array[i][(j+1)%N]-array[i][j]*array[i][(j+N-1)%N]-H*array[i][j]; 
		}
	}
	return E;
}

void ising_step(signed char array[N][N]){
	int accepted = 0, i, j;
	double old_energy = energy(array);
	while(accepted == 0){
		i = round(rand()/RAND_MAX*N);
		j = round(rand()/RAND_MAX*N);
		array[i][j] *= -1;
		if(energy(array)-old_energy <= 0){
			accepted = 1;
		}
		else{
			if((rand()/RAND_MAX)<=exp(-(energy(array)-old_energy)/T)){ // k = 1
				accepted = 1;
			}
			else{
				array[i][j] *= -1;
			}
		}	
	}
	return;
}

int main(){

	srand(time(NULL)); //Initialize rand
	signed char array[N][N]; //Build array
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			if(rand()>RAND_MAX/2){
				array[i][j] = 1;
			}
			else{
				array[i][j] = 0;
			}
		}
	}
	
	FILE *old = fopen("old","w");
	FILE *new = fopen("new","w");
	print_array(array, old);
	for(int i = 0; i<10000; i++){	
		ising_step(array);
	}
	print_array(array, new);
	

}
