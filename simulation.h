// simulation.h
#ifndef _SIMH_
#define _SIMH_

#include <memory>
#include "parameters.h"


// The 'set_derived_simulation_parameters' function takes a Parameters
// struct that was read in from a parameters file, computes the other
// parameters needed for the simulation, and returns a new Parameters
// struct with the original values plus the derived ones.
Parameters set_derived_simulation_parameters(const Parameters& p);

// The 'create_simulation_system' allocates memory for the wave field
// at three time points and for the position array, and assigns these
// to the references unique pointers passed as arguments.
//
// Because these are unique_pointers, their memory will be
// automatically deallocated when they get out of scope.
void create_simulation_system(const Parameters& param, 
                              std::unique_ptr<double[]>& rho_prev,
                              std::unique_ptr<double[]>& rho,
                              std::unique_ptr<double[]>& rho_next,
                              std::unique_ptr<double[]>& x);

#endif
