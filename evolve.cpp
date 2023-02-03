// evolve.cpp
#include <cmath>
#include "evolve.h"

// See evolve.h for how to use the function in this module

void one_time_step(const Parameters& param,
                   std::unique_ptr<double[]>& rho_prev,
                   std::unique_ptr<double[]>& rho,
                   std::unique_ptr<double[]>& rho_next)
{
    // Set zero Dirichlet boundary conditions
    rho[0] = 0.0;
    rho[param.ngrid-1] = 0.0;
    
    // Evolve inner region over a time dt using a leap-frog variant
    for (size_t i = 1; i <= param.ngrid-2; i++) {
        double laplacian = pow(param.c/param.dx,2)*(rho[i+1] + rho[i-1] - 2*rho[i]);
        double friction = (rho[i] - rho_prev[i])/param.tau;
        rho_next[i] = 2*rho[i] - rho_prev[i] + param.dt*(laplacian*param.dt-friction);
    }
    
    // Update arrays such that t+1 becomes the new t etc.
    std::swap(rho_prev, rho);
    std::swap(rho, rho_next);
}
