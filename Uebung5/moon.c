#include<stdio.h>
#include<math.h>
#define OMEGA 2*M_PI/(27.322*24)
#define RE  cbrt(20/(pow(OMEGA,2)*81.3*pow(1+81.3,2)))
#define RM 81.3*RE
#define V0 sqrt(20/1.06)

typedef struct Vector {
	double x;
	double y;
} vec;

//Norm of a 2D-vector
double norm(vec v){
	return sqrt(v.x*v.x+v.y*v.y);
}

vec moon(double t){
	vec out;
	out.x = RM*cos(OMEGA*t);
	out.y = RM*sin(OMEGA*t);
	return out;
}

vec earth(double t){
	vec out;
	out.x = -RE*cos(OMEGA*t);
	out.y = -RE*sin(OMEGA*t);
	return out;
}

vec acceleration(double t, vec pos){
	vec out, edist, mdist;
	edist.x = pos.x-earth(t).x;
	edist.y = pos.y-earth(t).y;
	mdist.x = pos.x-moon(t).x;
	mdist.y = pos.y-moon(t).y;
	out.x = -20/pow(norm(edist),2)*edist.x/norm(edist) - 20/81.3/pow(norm(mdist),2)*mdist.x/norm(mdist);
	out.y = -20/pow(norm(edist),2)*edist.y/norm(edist) - 20/81.3/pow(norm(mdist),2)*mdist.y/norm(mdist);
	//printf("\t%f\t%f\n",out.x,out.y);
	return out;
}

vec posverlet(vec pos, vec v, vec a, double t){
	vec out;
	//printf("POSITION-VERLET:\n\t%f\t%f\t%f\n", pos.x, v.x, a.x);
	//printf("\t%f\t%f\t%f\n", pos.y, v.y, a.y);
	out.x = pos.x + v.x*t + 0.5*a.x*t*t;
	out.y = pos.y + v.y*t + 0.5*a.y*t*t;
	return out;
}

vec velverlet(vec v, vec firsta, vec seconda, double t){
	vec out;
	out.x = v.x + 0.5*(firsta.x+seconda.x)*t;
	//printf("a.x: %f\ta.y: %f\n",0.5*(firsta.x+seconda.x),0.5*(firsta.y+seconda.y));
	out.y = v.y + 0.5*(firsta.y+seconda.y)*t;
	return out;
}

vec simulate(double boost, double a, double step){
	vec out = {a,1}; //first component of vector is angle a (in rad). second is -1 for angle to small and 1 for angle to big.
	vec pos = {-RE+1.06*cos(a),1.06*sin(a)};
	vec v = {-sin(a)*(V0+boost),cos(a)*(V0+boost)-RE*OMEGA}; //Boost relative to earth
	vec npos;
	vec fa,sa;
	double t = 0;
	vec mdist;
	FILE *sat = fopen("sat.txt","w");
	fprintf(sat,"%f\t%f\n",pos.x,pos.y);
	while(norm(pos)<RM&&t<25){
		npos = posverlet(pos,v,acceleration(t,pos),step);
		fa = acceleration(t,pos), sa=acceleration(t+step,npos);
		//printf("Sim:\t%f\t%f\t%f\t%f\n",fa.x,fa.y,sa.x,sa.y);
		v = velverlet(v,fa,sa,step);
		//printf("V.x: %f\tV.y: %f\n",v.x,v.y);
		pos = npos;
		t += step;
		fprintf(sat,"%f\t%f\n",pos.x,pos.y);
		mdist.x = pos.x-moon(t).x;
		mdist.y = pos.y-moon(t).y;
		if (norm(mdist)<=35/64){
			out.y = 0;
			break;
		}
		if(norm(pos)>RM){
			if(OMEGA*t>atan2(pos.y,pos.x)){
				out.y = -1;
			}
		}
	}
	return out;
}

int main(){

	//Testing some stuff
	FILE *output = fopen("output.txt","w");
	//printf("V0: %f\n",V0);
	for(int t = 0; t<25; t++){
		fprintf(output,"%f\t%f\t%f\t%f\n", moon(t).x,moon(t).y,earth(t).x,earth(t).y);
	}
	vec foo = simulate(0,0,1.0/200);



}
