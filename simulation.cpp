// simulation.cpp
#include "simulation.h"
#include <tuple>
#include <rarray>

// See simulation.h for how to use the functions in this module

Parameters set_derived_simulation_parameters(const Parameters& p)
{
    Parameters result = p;
    // Derived parameters 
    result.ngrid  = static_cast<size_t>((result.x2-result.x1)/result.dx);// number of x points (rounded down)
    result.dt     = 0.5*result.dx/result.c;                             // time step size
    result.nsteps = static_cast<size_t>(result.runtime/result.dt);      // number of steps to reach runtime (rounded down)
    result.nper   = static_cast<size_t>(result.outtime/result.dt);      // how many steps between snapshots (rounded down)
    return result;
}


void create_simulation_system(const Parameters& param, WaveState& wave)
{
    // Define and allocate arrays
    wave.rho_prev = rarray<double,1>(param.ngrid); // time step t-1
    wave.rho      = rarray<double,1>(param.ngrid); // time step t
    wave.rho_next = rarray<double,1>(param.ngrid); // time step t+1
    wave.x        = rarray<double,1>(param.ngrid); // x values
}
