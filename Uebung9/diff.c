#include <stdio.h>
#include <math.h>

#define LX 1.6
#define LY 1.0
#define VG 0.25
#define V1 0.5
#define V2 0
#define XA 0.4
#define YA 0.6
#define R1 0.2
#define XB 1.1
#define YB 0.4
#define R2 0.3
#define EPS 0.001
#define NX 241
#define NY 161
#define HX (LX/(NX-1))
#define HY (LY/(NY-1))
#define Z (2.0*(HX*HX+HY*HY)/(HX*HX*HY*HY))
#define D 1//0.001
#define STEP D/4.1*(pow(HX,2)+pow(HY,2)-fabs(pow(HX,2)-pow(HY,2))) //seems too small, porgram takes ages

// This program is pretty much the same as for the potential (potential = concentration)

int circlecheck(int x, int y){
	if(pow(x*HX-XA,2)+pow(y*HY-YA,2)-R1*R1 < 0 || pow(x*HX-XB,2)+pow(y*HY-YB,2)-R2*R2 < 0){
		return 1;
	}
	return 0;
}

int main(){
	printf("%f \n",STEP);
	double pot[NX][NX];
	for(int x = 0; x<NX; x++){
		for(int y = 0; y<NY; y++){
			pot[x][y] = 0.25;
			if(x == 0 || y == 0 || x == NX-1 || y == NY-1){
				pot[x][y] = VG;
			}
			if(pow(x*HX-XA,2)+pow(y*HY-YA,2)-R1*R1 < 0){
				pot[x][y] = V1;
			}
			if(pow(x*HX-XB,2)+pow(y*HY-YB,2)-R2*R2< 0){
				pot[x][y] = V2;
			}
		}
	}
	
	double res = EPS+1;
	int count = 0;
	while(res>EPS && count <100000){
		count++ ;
		res = 0;
		for(int x = 1; x<NX-1; x++){ // Exclude the edges here -> makes for easier programming and faster simulations.
			for(int y = 1; y<NY-1; y++){
				if(circlecheck(x,y)==0){
					pot[x][y] += STEP*D*((pot[x-1][y]+pot[x+1][y]-2*pot[x][y])/pow(HX,2)+(pot[x][y-1]+pot[x][y+1]-2*pot[x][y])/pow(HY,2));
				}
			}
		}
		//Calculate residual
		for(int x = 1; x<NX-1; x++){
			for(int y = 1; y<NY-1; y++){
				if(circlecheck(x,y)==0){
					//printf("%f\n",pow((pot[x+1][y]+pot[x-1][y]-2*pot[x][y])/pow(HX,2)+(pot[x][y+1]+pot[x][y-1]-2*pot[x][y])/pow(HY,2),2));
					res += pow((pot[x+1][y]+pot[x-1][y]-2*pot[x][y])/pow(HX,2)+(pot[x][y+1]+pot[x][y-1]-2*pot[x][y])/pow(HY,2),2);
				}
			}
		}
		//printf("RESIDUAL:\t%f\n",res);
	}
	
	printf("%d iterations\n", count);
	FILE *out = fopen("out","w");
	for(int x = 0; x<NX; x++){
		for(int y = 0; y<NY; y++){
			fprintf(out,"%f\t%f\t%f\n",x*HX,y*HY,pot[x][y]);
		}
	}
	
}
