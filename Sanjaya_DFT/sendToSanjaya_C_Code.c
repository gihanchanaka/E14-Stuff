#include "mycomplex.h"
#include <stdio.h>
#include<math.h>
#define PI 3.14159265
int main(){
 
    int N;
    double a[2],b[2];
   
    printf("Enter the period:");
    scanf("%d",&N);
   
    double Val[N][2],Cof[N][2];
    int i;
   
    //The problem is that declaring an array will not clean that memory block.
    //The "garbage" values are in those memeory locations
    //You have to use

    for(i=0;i<N;i++){
    	Cof[i][0]=Cof[i][1]=0.0;
    }



    for(i=0;i<N;i++){  
       
    printf("%0.1lf+%0.1lfi  ",Cof[i][0],Cof[i][1]);//here there is some error
       
    }
   
    for(i=0;i<N;i++){
       
        printf("Enter the time domain signal value %d:",i+1);
        scanf("%lf+%lfi",&Val[i][0],&Val[i][1]);
       
    }
   
    int k,n;
    for(k=0;k<N;k++){
        for(n=0;n<N;n++){
            double x[2],y[2];
            double ex[2]={cos(2*PI*k*n/N),-sin(2*PI*k*n/N)};
            complex_mul(x,Val[n],ex);
            y[0]+=x[0];
            y[1]+=x[1];
            printf("%0.1lf+%0.1lfi\n",y[0],y[1]);
           
        }
       
       
    }
   
   
   
   
 
 
 
 
    return 0;
}