#include<stdio.h>
#include<math.h>
#define OMEGA 2*M_PI/(27.322*24)
#define RE  cbrt(20/(pow(OMEGA,2)*81.3*pow(1+81.3,2)))
#define RM 81.3*RE
#define TIME 500
#define BOOST 1.76 //experimtenting with TIME 500 yields 1.75 as very small boost that can transport the satellite to the moon's altitude.
#define STEP 1.0/200

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
	return out;
}

vec posverlet(vec pos, vec v, vec a){
	vec out;
	out.x = pos.x + v.x*STEP + 0.5*a.x*STEP*STEP;
	out.y = pos.y + v.y*STEP + 0.5*a.y*STEP*STEP;
	return out;
}

vec velverlet(vec v, vec firsta, vec seconda){
	vec out;
	out.x = v.x + 0.5*(firsta.x+seconda.x)*STEP;
	out.y = v.y + 0.5*(firsta.y+seconda.y)*STEP;
	return out;
}

int simulate(double a, int print){ // output is -1 if angle a was too small and 1 if it was too big
	int out = 1;
	vec pos = {-RE+1.06*cos(a),1.06*sin(a)};
	vec v = {-sin(a)*(V0+BOOST),cos(a)*(V0+BOOST)-RE*OMEGA}; //Boost relative to earth
	vec npos;
	double t = 0;
	double sat_angle; // Angle at which the satellite passes the moon's orbit.
	vec mdist;
	FILE *sat = fopen("sat.txt","w");
	if (print== 1){
		fprintf(sat,"%f\t%f\n",pos.x,pos.y);	
	}
	while(norm(pos)<RM+1 && t<TIME){
		npos = posverlet(pos,v,acceleration(t,pos));
		v = velverlet(v,acceleration(t,pos),acceleration(t+STEP,npos));
		pos = npos;
		t += STEP;
		if(print == 1){
			fprintf(sat,"%f\t%f\n",pos.x,pos.y);		
		}
		mdist.x = pos.x-moon(t).x;
		mdist.y = pos.y-moon(t).y;
		if (norm(mdist)<=35.0/64){ //Hit the moon!
			out = 0;
			break;
		}
		if(norm(pos)>=RM){
			sat_angle = atan2(pos.y,pos.x) - 2*M_PI;// Account for the fact that atan returns values between -180 and 180 degrees. (and not between 0 and 360)
			while(fabs(sat_angle+2*M_PI-OMEGA*t)<fabs(sat_angle-OMEGA*t)){
				sat_angle += 2*M_PI;
			}
			if(OMEGA*t>sat_angle){
				out = -1;
			}
		}
	}
	//printf("t: %f\n",t);
	FILE *output = fopen("output.txt","w");
	if (print == 1){
		for(int time = 0; time<t; time++){
			fprintf(output,"%f\t%f\t%f\t%f\n", moon(time).x,moon(time).y,earth(time).x,earth(time).y);
		}
	}
	return out;
}


int main(){

	// Doesn't work. Almost no new code was created, only junk from moon.c deleted.

	vec lagrange = {-RE*cos(OMEGA*t)+cos()*(RM+RE), };
	

}
