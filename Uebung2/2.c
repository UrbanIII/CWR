#include<stdio.h>
#include<math.h>

const double angle = 3 * M_PI / 8;
const double v_o = 100;
const double g = 9.81;
const double stepsize = 0.001;
const int steps = 1000;

typedef struct Vector {
	double x;
	double y;
} vec;

// Differential equation to be solved
vec f(vec v){
	vec out;
	out.x = 0;
	out.y = -g;
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

	
	vec v = {cos(angle)*v_o, sin(angle)*v_o};
	
	FILE *file = fopen("output.txt","w");
	fprintf(file,"# Time\tvx\tvy\t analytical vx\tanalytical vy\n");
	
	for(int i = 0; i<=steps; i++){
		fprintf(file, "%f\t%f\t%f\t%f\t%f\n", i*stepsize, v.x, v.y, cos(angle)*v_o, sin(angle)*v_o-g*i*stepsize);
		v = euler(f,v,stepsize);
	}
	fclose(file);
}


