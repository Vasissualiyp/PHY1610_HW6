// evolve.h
#ifndef _EVOLVEH_
#define _EVOLVEH_

#include <memory>
#include "parameters.h"

// The 'one_time_step' function advances the state of the wave by one
// time step.
//
// The parameters of the evolution are set through the first Params
// argument.
//
// The function should be called with rho_prev and rho set to the
// current wave form and the wave form in the previous time step,
// while rho_next is an auxiliar array that will be used internally,
// and whose values upon entering the function are inconsequential.
//
// Upon returning from the function call, rho_prev with contain the
// previous values of rho, rho will contain the new values for the
// wave form.  The values in rho_next after the call should not be
// used.
void one_time_step(const Parameters& param, 
                   std::unique_ptr<double[]>& rho_prev,
                   std::unique_ptr<double[]>& rho, 
                   std::unique_ptr<double[]>& rho_next);

#endif
