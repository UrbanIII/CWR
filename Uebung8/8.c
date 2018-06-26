#include <stdio.h>
#include <math.h>

#define LX 1.6
#define LY 1.0
#define VG 0
#define V1 -1
#define V2 1
#define XA 0.4
#define YA 0.6
#define R1 0.2
#define XB 1.1
#define YB 0.4
#define R2 0.3
#define EPS 0.001
#define NX 5//241
#define NY 5//161
#define HX (LX/(NX-1))
#define HY (LY/(NY-1))
#define Z (2.0*(HX*HX+HY*HY)/(HX*HX*HY*HY))
#define ALPHA 1.9

//###########################################################################################################################################
//		This is essentially the same program as in the last exercise, albeit with the following modifications:
//			-SOR
//			-Residuals instead of Mean Square Displacement
//###########################################################################################################################################

int circlecheck(int x, int y){
	if(pow(x*HX-XA,2)+pow(y*HY-YA,2)-R1*R1 < 0 || pow(x*HX-XB,2)+pow(y*HY-YB,2)-R2*R2 < 0){
		return 1;
	}
	return 0;
}

int main(){

	double pot[NX][NX];
	for(int x = 0; x<NX; x++){
		for(int y = 0; y<NY; y++){
			pot[x][y] = 0; //This number has a very strange effect on the speed of convergence and the quality of the solution.
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
	double new;
	int count = 0;
	while(res>EPS){
		count++ ;
		res = 0;
		for(int x = 1; x<NX-1; x++){ // Exclude the edges here -> makes for easier programming and faster simulations.
			for(int y = 1; y<NY-1; y++){
				if(circlecheck(x,y)==0){
					new = 1.0/pow(HX,2)/Z*(pot[x-1][y]+pot[x+1][y]) + 1.0/pow(HY,2)/Z*(pot[x][y-1]+pot[x][y+1]);
					new = ALPHA*(new-pot[x][y])+pot[x][y];
					pot[x][y] = new;
				}
			}
		}
		//Calculate residual
		for(int x = 1; x<NX-1; x++){
			for(int y = 1; y<NY-1; y++){
				if(circlecheck(x,y)==0){
					res += pow((pot[x+1][y]+pot[x-1][y]-2*pot[x][y])/pow(HX,2)+(pot[x][y+1]+pot[x][y-1]-2*pot[x][y])/pow(HY,2),2);
				}
			}
		}
		printf("RESIDUAL:\t%f\n",res);
	}

	printf("%d iterations\n", count);
	FILE *out = fopen("out","w");
	for(int x = 0; x<NX; x++){
		for(int y = 0; y<NY; y++){
			fprintf(out,"%f\t%f\t%f\n",x*HX,y*HY,pot[x][y]);
		}
	}

}
