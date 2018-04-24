#include<stdio.h>

const double stepsize = 0.01;
const int steps = 10000;

typedef struct Vector {
	double x;
	double y;
} vec;

// Differential equation to be solved
vec f(vec v){
	vec out;
	out.x = -v.y;
	out.y = v.x;
	return out; 
}

// One iteration of Euler-Cauchy-Algorithm
vec euler( vec (*f)(vec), vec v, double t){
	vec out;
	out.x = v.x + f(v).x*t;
	out.y = v.y + f(v).y*t;
	return out;
}

int main(){
	
	FILE *file = fopen("output.txt","w");
	fprintf(file,"# x\ty\n");
	vec v = {1,0};
	
	for(int i = 0; i<=steps; i++){
		fprintf(file, "%f\t%f\n", v.x, v.y);
		v = euler(f,v,stepsize);
	}
	fclose(file);
}


