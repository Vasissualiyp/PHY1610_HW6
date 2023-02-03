#ifndef _EVOLVEH_
#define _EVOLVEH_

#include <memory>
#include "parameters.h"

Parameters set_simulation_parameters(const Parameters& p);

void one_time_step(const Parameters& param, std::unique_ptr<double[]>& rho_prev,
                   std::unique_ptr<double[]>& rho, std::unique_ptr<double[]>& rho_next);

#endif
