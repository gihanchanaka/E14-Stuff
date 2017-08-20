#include "stdio.h"
#include "mycomplex.c"


int main(){

	double a[]={2.0, 5.0};
	double b[]={1.0, 2.0};
	double c[]={0,0};
	char op[5];
	printf("Enter the first number: ");
	scanf("%lf %lf",&a[0],&a[1]);
	printf("Enter the second number: ");
	scanf("%lf %lf",&b[0],&b[1]);
	printf("the operation:");
	scanf("%s",&op);
	if(op[0]=='a')complex_add(c,a,b);
	else if(op[0]=='s')complex_sub(c,a,b);
	else if(op[0]=='m')complex_mul(c,a,b);
	else if(op[0]=='d')complex_div(c,a,b);
	else printf("!!!!!!!!!!!!");
	
	complex_print(c);

	return 0;
}