// initialize.cpp
#include "initialize.h"
#include <cmath>

// See initialize.h for how to use the function in this module

void initialize(Parameters& param,
                std::unique_ptr<double[]>& x,
                std::unique_ptr<double[]>& rho,
                std::unique_ptr<double[]>& rho_prev)
{
    // Initialize array of x values 
    for (size_t i = 0; i < param.ngrid; i++) {
        x[i] = param.x1 + (static_cast<double>(i)*(param.x2-param.x1))/static_cast<double>(param.ngrid-1);
    }
    
    // Initialize wave with a triangle shape from xstart to xfinish
    double xstart = 0.25*(param.x2-param.x1) + param.x1;
    double xmid = 0.5*(param.x2+param.x1);
    double xfinish = 0.75*(param.x2-param.x1) + param.x1;
    for (size_t i = 0; i < param.ngrid; i++) {
        if (x[i] < xstart or x[i] > xfinish) {
            rho[i] = 0.0;
        } else {
            rho[i] = 0.25 - fabs(x[i]-xmid)/(param.x2-param.x1);
        }
        rho_prev[i] = rho[i];
    }
}
