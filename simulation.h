#ifndef _SIMH_
#define _SIMH_

#include <memory>
#include "parameters.h"

Parameters set_simulation_parameters(const Parameters& p);
void create_simulation_system(const Parameters& param, std::unique_ptr<double[]>& rho_prev, std::unique_ptr<double[]>& rho, std::unique_ptr<double[]>& rho_next, std::unique_ptr<double[]>& x);

#endif
