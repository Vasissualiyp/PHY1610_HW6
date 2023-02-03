//
// wave1d.cc - Simulates a one-dimensional damped wave equation
//
// Ramses van Zon - 2015-2023
//

#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <cmath>

#include "parameters.h"
#include "initialize.h"
#include "output.h"
#include "evolve.h"

int main(int argc, char* argv[])
{
    // Check command line argument
    if (argc != 2) {
        std::cerr << "Error: wave1d needs one parameter file argument.\n";
        return 1;
    }

    // Read the values from the parameter file specified on the command line
    Parameters param;
    try {
       param = readParametersFromFile(argv[1]);
    }
    catch (int i) {
        return i;
    }
    
    // Derived parameters 
    param = set_simulation_parameters(param);
    
    // Open output file
    std::ofstream fout(param.outfilename);
    
    output_parameters(param, fout);
    
    // Define and allocate arrays
    auto rho_prev = std::make_unique<double[]>(param.ngrid); // time step t-1
    auto rho      = std::make_unique<double[]>(param.ngrid); // time step t
    auto rho_next = std::make_unique<double[]>(param.ngrid); // time step t+1
    auto x        = std::make_unique<double[]>(param.ngrid); // x values

    initialize(param,x,rho,rho_prev);

    // Output initial wave to file
    output_wave(param,fout,0.0,x,rho);

    // Take timesteps
    for (size_t s = 0; s < param.nsteps; s++) {

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
        
        // Output wave to file
        if ((s+1)%param.nper == 0) {
            output_wave(param,fout,static_cast<double>(s+1)*param.dt,x,rho);
        }
    }

    // Close file
    fout.close();
    std::cout << "Results written to '"<< param.outfilename << "'.\n";
    
}

