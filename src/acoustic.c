#include "acoustic.h"
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <string.h>

real cosh(real x)
{
return 0.5*(exp(x) + exp(-x));
}


real sinh(real x)
{
return 0.5*(exp(x) - exp(-x));
}


real tanh(real x)
{
return (exp(2.0*x) -1.0)/(exp(2.0*x) +1.0);
}


real coth(real x)
{
return (exp(2.0*x) + 1.0)/(exp(2.0*x) - 1.0);
}

real R1(real x,real LHS)
{
	return ( coth(x)  - 1.0/x  - LHS);
}

real DR1(real x)
{
	return  -1.0/(sinh(x)*sinh(x)) + 1.0/(x*x);
}



real newton( real guess, int Nmax, real LHS)
{
	real tol = 0.0001;
	real xk,xkp1;
	xk=guess;
	int k;
	for (k=0; k<=Nmax; k++){
        
        xkp1= xk - R1(xk,LHS)/DR1(xk);
        
         if (fabs(xkp1-xk) < tol){
            return xkp1;
          }
         xk = xkp1;
    }
     return xkp1;
}



void AcousticNumFlux( real *wL, real *wR, real *vnorm, real *flux) 
{
  real guess=0.5;
  int Nmax = 50;
  real vn = sqrt(0.5) * vnorm[0] + sqrt(0.5) * vnorm[1];
  real vnp = vn > 0.0 ? vn : 0.0;
  real vnm = vn - vnp;
  flux[0] = vnp * wL[1] + vnm * wR[1];

  // Compute R=I/w
  real RxL, RyL, RzL;
  real RxR, RyR, RzR;
  
  RxL = wL[1]/wL[0];
  RyL = wL[2]/wL[0];
  RzL = wL[3]/wL[0];
  
  RxR = wR[1]/wR[0];
  RyR = wR[2]/wR[0];
  RzR = wR[3]/wR[0];

  
  real bxL, byL, bzL;
  real bxR, byR, bzR;
  real bL, bR;
  
  
  bxL = newton(guess, Nmax,RxL);
  printf("%f \n", bxL);
  byL = newton(guess, Nmax,RyL);
  bzL = newton(guess, Nmax,RzL);
  bxR = newton(guess, Nmax,RxR);
  byR = newton(guess, Nmax,RyR);
  bzR = newton(guess, Nmax,RzR);
  
  bL = sqrt( bxL*bxL + byL*byL + bzL*bzL); 
  bR = sqrt( bxR*bxR + byR*byR + bzR*bzR);
  
  
  // solve B
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 }


void AcousticImposedData(const real *x, const real t, real* w) 
{
  w[0] = cos(4*t);
  w[1] = 0.5 ;
  w[2] = 0;
  w[3] = 0;
}

void AcousticInitData(real x[3], real w[]) {
  real t = 0;
  AcousticImposedData(x, t, w);
}

void  AcousticBoundaryFlux(real *x, real t,  real *wL, real *vnorm,   real *flux) 
{
  real wR[4];
  AcousticImposedData(x, t, wR);
  AcousticNumFlux(wL, wR, vnorm, flux);
}







