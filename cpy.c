#include <stdio.h>
#include <stdlib.h>
 
double SquareRoot(double X) {
  double A,B,M,XN;
  if(X==0.0) {
     return 0.0;
  } else {
     M=1.0;
     XN=X;
     while(XN>=2.0) {
        XN=0.25*XN;
        M=2.0*M;
     }
     while(XN<0.5) {
        XN=4.0*XN;
        M=0.5*M;
     }
     A=XN;
     B=1.0-XN;
     do {
        A=A*(1.0+0.5*B);
        B=0.25*(3.0+B)*B*B;
     } while(B>=1.0E-15);
     return A*M;
  }
}
 
double Ln(double x) {
  int negatif = 0;
  double fois = 1;
  double ajout = 0;
  if(x<=0.0) return 0;
  if(x<1.0) {
    negatif = 1;
    x = 1.0/x;
  }
  while(x >= 10.0) {
    x /= 10.0;
    ajout += 2.302585092994046;
  };
 
  while(x>=1.1) {
    x = SquareRoot(x);
    fois *= 2;
  };
  x--;
  double savx = x;
  double i = 2;
  double xp = x*x;
  double quotient = (xp/i);
  double dl = x-quotient;
  while (1.0E-15<quotient) {
    i++;
    xp *= x;
    dl += (xp/i);
    i++;
    xp *= x;
    quotient = (xp/i);
    dl -= quotient;
  }
 
  dl *= fois;
  dl += ajout;
  if(negatif) dl = -dl;
  return dl;
}
 
int main()
{
    double I;
    for(I=0;I<=2.0;I+=0.1) printf("Ln(%f)=%f\n",I,Ln(I));
    return 0;
}