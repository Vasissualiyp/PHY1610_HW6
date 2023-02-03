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

        // Evolve in time
        one_time_step(param,rho_prev,rho,rho_next);
        
        // Output wave to file
        if ((s+1)%param.nper == 0) {
            output_wave(param,fout,static_cast<double>(s+1)*param.dt,x,rho);
        }
    }

    // Close file
    fout.close();
    std::cout << "Results written to '"<< param.outfilename << "'.\n";
    
}

