// simulation.cpp
#include "simulation.h"
#include <tuple>
#include <rarray>


Parameters set_derived_simulation_parameters(const Parameters& p)
{
    Parameters result = p;
    // Derived parameters 
    result.ngrid  = static_cast<size_t>((result.x2-result.x1)/result.dx);// number of x points (rounded down)
    result.dt     = 0.5*result.dx/result.c;                             // time step size
    result.nsteps = static_cast<size_t>(result.runtime/result.dt);      // number of steps to reach runtime (rounded down)
    result.nper   = static_cast<size_t>(result.outtime/result.dt);      // how many steps between snapshots (rounded down)
    
    // BLAS constants {{{
    
    // diagonal elements for matrix A
    double c_offd = pow(result.dt*result.c/result.dx, 2.0);
    // off-diagonal elements for matrix A
    double c_d = 2.0 - 2.0*pow(result.dt*result.c/result.dx, 2.0) - result.dt/result.tau;
    // scalar beta
    result.beta = result.dt / result.tau - 1.0;
    // putting values into the A matrix
    result.A = rarray<double, 2> (result.ngrid, 2);
    for (int i=0; i<result.ngrid; i++){
    	result.A[i][0] = c_d;
    	result.A[i][1] = c_offd;
    }
    //printmatrix("A", result.A);
    return result;
    
    //}}}
}


void create_simulation_system(const Parameters& param, WaveState& wave)
{
    // Define and allocate arrays
    wave.rho_prev = rarray<double,1>(param.ngrid); // time step t-1
    wave.rho      = rarray<double,1>(param.ngrid); // time step t
    wave.rho_next = rarray<double,1>(param.ngrid); // time step t+1
    wave.x        = rarray<double,1>(param.ngrid); // x values
}
