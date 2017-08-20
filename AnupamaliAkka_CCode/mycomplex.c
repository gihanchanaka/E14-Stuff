/* complex number library for C : library implementation

E-number : <E/14/400>
Name : <Anupamali>
Date : <02/08/2017>

*/

#include "mycomplex.h"

void complex_add(double c[2], double a[2], double b[2])// add two complex numbers
{


          c[0]=a[0]+b[0];//add real numbers
          c[1]=a[1]+b[1];//add imaginary numbers
}

void complex_sub(double c[2], double a[2], double b[2])//subtract two numbers
{


           c[0]=a[0]-b[0];//subtract real numbers
           c[1]=a[1]-b[1];// subtract imaginary numbers
}
void complex_mul(double c[2], double a[2], double b[2])// multiply two numbers
{


           c[0]=a[0]*b[0]-a[1]*b[1];//real part
           c[1]=a[0]*b[1]+a[1]*b[0];//imaginary part
}

void complex_div(double c[2], double a[2], double b[2])//division of two numbers
{


           c[0]=(a[0]*b[0]+a[1]*b[1])/(b[0]*b[0]+ b[1]*b[1]);//real part
           c[1]=(a[1]*b[0]-a[0]*b[1])/(b[0]*b[0]+ b[1]*b[1]);//imaginary part

}


