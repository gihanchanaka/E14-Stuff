/* complex number library for C : library header file

 A complex number here is represented using a double array with 2 elements
 For example : 
 double complexnum[2] will be a complex number,
 where complexnum[0] element is the real part and complexnum[1] is the imaginary part
 
 the number 5.0+4.0i is represented as
 complexnum[0]=5.0 and complexnum[1]=4.0
*/


/* Function prototypes*/

//function to add 2 complex number
//c=a+b
void complex_add(double c[2], double a[2], double b[2]);

//function to subtract 2 complex number
//c=a-b
void complex_sub(double c[2], double a[2], double b[2]);


//function to multiply 2 complex number
//c=a*b
void complex_mul(double c[2], double a[2], double b[2]);

//function to divide 2 complex number
//c=a/b
void complex_div(double c[2], double a[2], double b[2]);

double complex_absSquared(double a[2]);

void complex_conjugate(double c[2],double a[2]);

void complex_divByScalar(double c[2], double a[2], double s);
void complex_print(double a[2]);