/* complex number calculator
Use the complex number library written by you to implement this
*/

#include "mycomplex.h"
#include <stdio.h>
#include <string.h>

/************************************Write your program here*********************************/


int main(){

double a[2];
double b[2];
double c[2];
char operation[20];
char str1[4],str2[4],str3[4],str4[4]; //You need 4 charactes to save these words

strcpy(str1,"add");
strcpy(str2,"sub");
strcpy(str3,"mul");
strcpy(str4,"div");

printf("Enter the first number : ");
scanf("%lf+%lfi",&a[0],&a[1]);
printf("Enter the second number:  ");
scanf("%lf+%lfi",&b[0],&b[1]);
printf("the operation:  ");
scanf("%s",operation);//There was a mistake here..You should give the location you 
//have to write the scanned item to.

 if //strcmp(operation[2]==add[2])
   (  strcmp(operation,str1)==0)
     complex_add(c,a,b);

 else if// strcmp(operation[2]==sub[2])
(strcmp(operation,str2)==0)
	 complex_sub(c,a,b);

 else if// strcmp(operation[2]==mul[2])
    (strcmp(operation,str3)==0)
     complex_mul(c,a,b);


 else// strcmp(operation[2]==div[2]);
    complex_div(c,a,b);


printf("the answer is %0.1f + %0.1f i  \n",c[0],c[1]);
return(0);
}
