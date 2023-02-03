#ifndef  _OUTPUTH_
#define  _OUTPUTH_

#include <memory>
#include <fstream>
#include "parameters.h"

void output_parameters(const Parameters& param, std::ofstream& fout);

void output_wave(const Parameters& param,
                 std::ofstream& fout,
                 double time,
                 std::unique_ptr<double[]>& x,
                 std::unique_ptr<double[]>& rho);

#endif
