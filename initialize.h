// initialize.h
#ifndef _INITH_
#define _INITH_

#include <memory>
#include "parameters.h"

// The 'initialize' function fills the existing array x, rho, and
// rho_prev.
//
// The values of x will be position coordinates of the grid to use, as
// determined by the parameters passed through param, while rho and
// rho_prev are set to the same triangular wave form (see description
// of assignment 3).
void initialize(Parameters& param, 
                std::unique_ptr<double[]>& x, 
                std::unique_ptr<double[]>& rho, 
                std::unique_ptr<double[]>& rho_prev);

#endif
