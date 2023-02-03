// wave1d.cpp - Simulates a one-dimensional damped wave equation
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
#include "simulation.h"

int main(int argc, char* argv[])
{
    // Check command line argument
    if (argc != 2) {
        std::cerr << "Error: wave1d needs one parameter file argument.\n";
        return 1;
    }

    // Read the values from the parameter file specified on the command line
    // but exit with error code if something went wrong
    Parameters param;
    int errorcode = readParametersFromFile(argv[1], param);
    if (errorcode > 0) {
        return errorcode;
    }
    
    // Derived parameters 
    param = set_derived_simulation_parameters(param);
    
    // Open output file
    std::ofstream fout(param.outfilename);
    
    output_parameters(fout, param);
    
    // Define and allocate arrays
    std::unique_ptr<double[]> rho_prev; // time step t-1
    std::unique_ptr<double[]> rho;      // time step t
    std::unique_ptr<double[]> rho_next; // time step t+1
    std::unique_ptr<double[]> x;        // x values

    create_simulation_system(param, rho_prev, rho, rho_next, x);
    initialize(param, x, rho, rho_prev);

    // Output initial wave to file
    output_wave(fout, 0.0, param.ngrid, x, rho);

    // Take timesteps
    for (size_t s = 0; s < param.nsteps; s++) {

        // Evolve in time
        one_time_step(param, rho_prev, rho, rho_next);
        
        // Output wave to file
        if ((s+1)%param.nper == 0) {
            output_wave(fout, static_cast<double>(s+1)*param.dt, param.ngrid, x, rho);
        }
    }

    // Close file
    fout.close();
    std::cout << "Results written to '"<< param.outfilename << "'.\n";

    return 0;
}

