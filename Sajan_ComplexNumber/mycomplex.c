/* complex number library for C : library implementation 

E-number : <fill these>
Name : <fill these>
Date : <fill these>

*/

#include "mycomplex.h"

/****************************************************************
Implement the functions in mycomplex.h here
*****************************************************************/


void complex_add(double c[2], double a[2], double b[2]){
	int i;
	for(i=0;i<2;i++)c[i]=a[i]+b[i];
}

//function to subtract 2 complex number
//c=a-b
void complex_sub(double c[2], double a[2], double b[2]){
	int i;
	for(i=0;i<2;i++)c[i]=a[i]-b[i];
}


//function to multiply 2 complex number
//c=a*b
void complex_mul(double c[2], double a[2], double b[2]){
	double t=a[0]*b[0]-a[1]*b[1];
	c[1]=a[0]*b[1]+b[0]*a[1];
	c[0]=t;
}

double complex_absSquared(double a[2]){
	return (a[0]*a[0] + a[1]*a[1]);
}

void complex_divByScalar(double c[2], double a[2], double s){
	int i;
	for(i=0;i<2;i++)c[i]=a[i]/s;
}

void complex_conjugate(double c[2],double a[2]){
	c[0]=a[0];
	c[1]=-1*a[1];
}


//function to divide 2 complex number
//c=a/b
void complex_div(double c[2], double a[2], double b[2]){
	complex_conjugate(c,b);
	complex_mul(c,c,a);
	complex_divByScalar(c,c,complex_absSquared(b));
}

void complex_print(double a[2]){
	printf("%.1lf + %.1lfi",a[0],a[1]);
}