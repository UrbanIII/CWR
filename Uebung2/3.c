#include<stdio.h>
#include<math.h>

const double angle = 3 * M_PI / 8;
const double v_o = 10;
const double g = 9.81;
const double k = 0.2;
const double stepsize = 0.001;
const int steps = 1000;

typedef struct Vector {
	double x;
	double y;
} vec;

//Norm of a 2D-vector
double norm(vec v){
	return sqrt(v.x*v.x+v.y*v.y);
}

// Differential equations to be solved
vec stokes(vec v){
	vec out;
	out.x = -k*v.x;
	out.y = -g-k*v.y;
	return out; 
}

vec newton(vec v){
	vec out;
	out.x = -k*v.x*norm(v);
	out.y = -g-k*v.y*norm(v);
	return out; 
}

vec pos(vec v){
	vec out;
	out.x = v.x;
	out.y = v.y;
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

	
	vec vs = {cos(angle)*v_o, sin(angle)*v_o};
	vec vn = {cos(angle)*v_o, sin(angle)*v_o};
	vec ps = {0,0}; // Positions
	vec pn = {0,0};
	
	FILE *velocities = fopen("velocities.txt","w");
	fprintf(velocities,"# Time\tstokes vx\tstokes vy\tnewton vx\tnewton vy\n");
	FILE *positions = fopen("positions.txt","w");
	fprintf(positions,"# Time\tstokes px\tstokes py\tnewton px\tnewton py\n");
	
	for(int i = 0; i<=steps; i++){
		fprintf(velocities, "%f\t%f\t%f\t%f\t%f\n", i*stepsize, vs.x, vs.y, vn.x, vn.y);
		fprintf(positions, "%f\t%f\t%f\t%f\t%f\n", i*stepsize, ps.x, ps.y, pn.x, pn.y);
		ps.x += vs.x*stepsize;
		ps.y += vs.y*stepsize;
		pn.x += vn.x*stepsize;
		pn.y += vn.y*stepsize;
		vs = euler(stokes,vs,stepsize);
		vn = euler(newton,vn,stepsize);
	}
	fclose(velocities);
}


