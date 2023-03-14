// evolve.cpp
#include <cmath>
#include <cblas.h>
#include "evolve.h"

// See evolve.h for how to use the function in this module

void one_time_step(const Parameters& param, WaveState& wave)
{    
    //Matrix-vector roduct using symmetric band matrix, alpha*A*x + beta*y{{{
    cblas_dsbmv(CblasRowMajor,     // Use RowMajor with C
    	CblasUpper,    // upper or lower triangular band matrix?
    	param.ngrid,    // order of matrix A
    	1,   	       // number of super-diagonals of A
    	1.0, 	       // alpha
    	&param.A[0][0], // first element of A
    	param.ngrid,       // Leading dim of A
    	&wave.rho[0],     // x array
    	1,  	       // increment of x
    	param.beta,    // beta
    	&wave.rho_prev[0],// y array
    	1); 	       // increment of y
    //}}}
	
    //// Evolve inner region over a time dt using a leap-frog variant {{{
    //for (size_t i = 1; i <= param.ngrid-2; i++) {
    //    
    //    double laplacian = pow(param.c/param.dx,2)*(wave.rho[i+1] + wave.rho[i-1] - 2*wave.rho[i]);
    //    double friction = (wave.rho[i] - wave.rho_prev[i])/param.tau;
    //    wave.rho_next[i] = 2*wave.rho[i] - wave.rho_prev[i] + param.dt*(laplacian*param.dt-friction);
    //} //}}}
    
    // Update arrays such that t+1 becomes the new t etc.
    std::swap(wave.rho_prev, wave.rho);
    std::swap(wave.rho, wave.rho_next);

    // Explicitly enforce boundary conditions:
    wave.rho[0] = 0.0;
    wave.rho[param.ngrid-1] = 0.0;
}


