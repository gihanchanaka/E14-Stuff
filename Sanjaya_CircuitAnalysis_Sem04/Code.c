#include <stdio.h>
#include <math.h>
#include <stdlib.h>


float inverse[2][2];


float determinant(float [2][2], float);
void cofactor(float [2][2], float);
void transpose(float [2][2], float [][2], float);
int calc_sanjaya(float a[2][2],int k)
{

  double d = determinant(a, k);
  
  int i,j,l;

  for(i=0;i<2;i++){
    for(j=0;j<2;j++){
      printf("%lf ",a[i][j]);
    }
    printf("\n");
  }

  if (d == 0)
   printf("\nInverse of Entered Matrix is not possible\n");
  else
   cofactor(a, k);

  return 0;

}
 
/*For calculating Determinant of the Matrix */
float determinant(float a[2][2], float k)
{
  float s = 1, det = 0, b[2][2];
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
 
void cofactor(float num[2][2], float f)
{
 float b[2][2], fac[2][2];
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
void transpose(float num[2][2], float fac[2][2], float r)
{
  int i, j;
  float b[2][2], d;
 
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
   
}




int main(){

  char run;
  int mesh[20]={1,1,1,2,2,2};
  char branch[20]={'A','B','C','C','D','E'};
  char RV[20]={'V','R','R','R','R','V'};
  double value[20]={20,20,10,10,40,-30};
  int i=6;
  float Rmatrix[2][2]={{0.0f,0.0f},{0.0f,0.0f}};
  float Vmatrix[2]={0,0};
  
  int j=0;
  for(j=0;j<i;j++){
    
    printf("%d %c %c %lf\n",mesh[j],branch[j],RV[j],value[j]);
    
    if(RV[j]=='V')Vmatrix[mesh[j]-1]+=value[j]; 
    if(RV[j]=='R')
    {
      Rmatrix[mesh[j]-1][mesh[j]-1]+=value[j]; 
      if(branch[j]==branch[j+1])
      {
        Rmatrix[mesh[j]-1][mesh[j+1]-1]-=value[j];
        Rmatrix[mesh[j+1]-1][mesh[j]-1]-=value[j];
      }
      
    
    }
  }

 calc_sanjaya(Rmatrix,2);
 






printf("\n\n\nThe inverse of matrix is : \n");
 
   for (i = 0;i < 2; i++)
    {
     for (j = 0;j < 2; j++)
       {
         printf("\t%f", inverse[i][j]);
        }
    printf("\n");
     }




  getchar();
}