#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
float inverse[25][25];


int m(float resistor[][25],int NL);
float determinant(float [][25], float);
void cofactor(float [][25], float);
void transpose(float [][25], float [][25], float);


int main()
{
    int NL;
    int NE;
    char answer;

    printf("Do you want to continue:   ");
    scanf("%c",&answer);
    printf("Enter the number of loop:    ");
    scanf("%d",&NL);
    printf("enter the number of elements:  ");
    scanf("%d",&NE);
    


    int loop[NL];
    char branch[NE];
    char type[NE];
    float value[NE];
    int i,x,y,z;
    int presance[NE][NL];
    float voltagedrops[NL];
    float resistor[NL][NL];
    float I[NL];

    for(x=0;x<NL;x++)loop[x]=0;
    for(x=0;x<NE;x++)branch[x]=0;
    for(x=0;x<NE;x++) type[x]=0;
    for(x=0;x<NE;x++)value[x]=0;
    for(x=0;x<NE;x++){
      for(y=0;y<NL;y++){
        presance[x][y]=0;
      }
    }
    for(x=0;x<NL;x++){
      for(y=0;y<NL;y++){
        resistor[x][y]=0;
      }
    }
    for(x=0;x<NL;x++)I[NL]=0;


    //Do the ZERO initialization of all these arrays! There is a hell lot of garbage here
    
i=0;
while (answer=='y')
{
    for (i=0 ; i<NE ; i++ ){
      int loopnumber;
      char branch;
      char thisElementType;
      float valueread;
      char temp[2];

      printf("enter the loop number: ");
      scanf("%d",&loopnumber);
      printf("enter the  Element Name (Known as branch to Anupamali): ");
      scanf("\n%c",&branch);          // \n is added to supress some bug in the input
      printf("resistor or voltage: ");
      scanf("\n%c",&thisElementType); // \n is added to supress some bug in the input
      printf("enter value: ");
      scanf("\n%f",&valueread); // \n is added to supress some bug in the input


      loopnumber--;
      int branchnumber=(int)branch-'A';
      value[branchnumber]=valueread;
      type[branchnumber]=thisElementType;
      presance[branchnumber][loopnumber]=1;
      i++;
      printf("Do you want to continue");
      scanf("\n%c",&answer); // \n is added to supress some bug in the input
    }
}
     
         for ( x=0;x<NE ;x++){
                if (type[x]=='V'){
                        for( y=0 ; y<NL ;y++){
                                if(presance[x][y]==1){
                                        voltagedrops[y]+=value[x];
                                }
                        }
                }
         }
         for(x=0;x<NL;x++){
            if(type[x]=='R'){
                for(y=0;y<NL;y++){
                    if (presance[x][y]==1){
                        resistor[y][y]+=value[x];
                        for( z=0;z<NL;z++){
                            if(y!=z){
                                if (presance[x][z]==1){
                                    resistor[y][z]+=value[x];
                                    resistor[z][y]+=value[x];
                                }
                            }
                        }
                    }
                }
            }
         }

 for(x=0;x<NL;x++){
  printf("VoltageDrop %d = %f\n", x,voltagedrops[x]);
 }        

 printf("\nThe resistor matrix\n");
 for(x=0;x<NL;x++){
  for(y=0;y<NL;y++){
    printf("%f ", resistor[x][y]);
  }
  printf("\n");
 }

 float arToPassToLecturersFunctions[25][25];
 for(x=0;x<25;x++)for(y=0;y<25;y++)arToPassToLecturersFunctions[x][y]=0;
 for(x=0;x<NL;x++)for(y=0;y<NL;y++)arToPassToLecturersFunctions[x][y]=resistor[x][y]; 

 m(arToPassToLecturersFunctions,NL);
 printf("\nThe inverse matrix\n");
 for(x=0;x<NL;x++){
  for(y=0;y<NL;y++){
    printf("%f ", inverse[x][y]);
  }
  printf("\n");
 }


for (x=0;x<NL;x++){
     float sum=0;
    for(y=0;y<NL;y++){
        sum+=inverse[x][y]*voltagedrops[y];
    }
    I[x]=sum;
    printf("the current is %lf  ",I[x]);
  }
return 0;  
}





int m(float resistor[25][25],int NL)
{
  int d = determinant(resistor, NL);
  if (d == 0)
   printf("\nInverse of Entered Matrix is not possible\n");
  else
   cofactor(resistor, NL);

  return 0;

}

/*For calculating Determinant of the Matrix */
float determinant(float a[25][25], float k)
{
  float s = 1, det = 0, b[25][25];
  int i, j, m, n, c;
  if (k == 1)
    {
     return (a[0][0]);
    }
  else
    {
     det = 0;
     for (c = 0; c < k; c++)
       {
        m = 0;
        n = 0;
        for (i = 0;i < k; i++)
          {
            for (j = 0 ;j < k; j++)
              {
                b[i][j] = 0;
                if (i != 0 && j != c)
                 {
                   b[m][n] = a[i][j];
                   if (n < (k - 2))
                    n++;
                   else
                    {
                     n = 0;
                     m++;
                     }
                   }
               }
             }
          det = det + s * (a[0][c] * determinant(b, k - 1));
          s = -1 * s;
          }
    }

    return (det);
}

void cofactor(float num[25][25], float f)
{
 float b[25][25], fac[25][25];
 int p, q, m, n, i, j;
 for (q = 0;q < f; q++)
 {
   for (p = 0;p < f; p++)
    {
     m = 0;
     n = 0;
     for (i = 0;i < f; i++)
     {
       for (j = 0;j < f; j++)
        {
          if (i != q && j != p)
          {
            b[m][n] = num[i][j];
            if (n < (f - 2))
             n++;
            else
             {
               n = 0;
               m++;
               }
            }
        }
      }
      fac[q][p] = pow(-1, q + p) * determinant(b, f - 1);
    }
  }
  transpose(num, fac, f);
}
/*Finding transpose of matrix*/
void transpose(float num[25][25], float fac[25][25], float r)
{
  int i, j;
  float b[25][25],  d;

  for (i = 0;i < r; i++)
    {
     for (j = 0;j < r; j++)
       {
         b[i][j] = fac[j][i];
        }
    }
  d = determinant(num, r);
  for (i = 0;i < r; i++)
    {
     for (j = 0;j < r; j++)
       {
        inverse[i][j] = b[i][j] / d;
        }
    }


  //  return 0;
  }
