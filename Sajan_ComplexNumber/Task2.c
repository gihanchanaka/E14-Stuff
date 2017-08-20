#include "stdio.h"
#include "mycomplex.c"
#include "math.h"
#define PI 3.14

int main(){
	int N;
	printf("Enter the period: ");
	scanf("%d",&N);
	double f[N][2];

	int i,j;
	for(i=0;i<N;i++){
		printf("Enter the time domain signal value %d:",i+1);
		for(j=0;j<2;j++)scanf("%lf",&f[i][j]);
	}
	
	double D[2];
	double DD[2];
	int k;
	for(k=0;k<N;k++){
		D[0]=D[1]=0.0;
		for(i=0;i<N;i++){
			double ee[]={cos(-2*PI*i*k/(double)N), sin(-2*PI*i*k/(double)N)};
			complex_mul(DD,f[i],ee);
			complex_add(D,D,DD);
		}
		complex_print(D);
		printf("    ");
	}

	return 0;
}