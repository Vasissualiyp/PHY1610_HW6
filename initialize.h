#ifndef _INITH_
#define _INITH_

#include <memory>
#include "parameters.h"

void initialize(Parameters& param, std::unique_ptr<double[]>& x, std::unique_ptr<double[]>& rho, std::unique_ptr<double[]>& rho_prev);

#endif
