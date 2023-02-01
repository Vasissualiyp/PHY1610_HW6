#include "parameters.h"

#include <fstream>
#include <iostream>
#include <filesystem>

Parameters readParametersFromFile(const std::string& filename)
{
    if (not std::filesystem::exists(filename)) {
        std::cerr << "Error: parameter file '" << filename << "' not found.\n";
        throw 2;
    }    

    std::ifstream infile(filename);
    // The following line causes 'infile' to throw exceptions for errors.
    // (instead of the default behavior of setting an internal flag and having the program continue.)
    infile.exceptions(std::ifstream::failbit|std::ifstream::badbit);  

    Parameters result;

    try {
        infile >> result.c;
        infile >> result.tau;
        infile >> result.x1;
        infile >> result.x2;
        infile >> result.runtime;
        infile >> result.dx;
        infile >> result.outtime;
        infile >> result.outfilename;
        infile.close();
    }
    catch (std::ifstream::failure& e) {
        std::cerr << "Error while reading file '" << filename << "'.\n";
        throw 3;
    }
    // Check input sanity, quit if there are errors
    bool correctinput = false ; // assume the worst first.
    if (result.c <= 0.0) {
        std::cerr << "wave speed c must be postive.\n";
    } else if (result.tau <= 0.0) {
        std::cerr << "damping time tau must be positive or zero\n";
    } else if (result.x1 >= result.x2) {
        std::cerr << "x1 must be less that x2.\n";
    } else if (result.dx < 0) {
        std::cerr << "dx must be postive.\n";
    } else if (result.dx > result.x2 - result.x1) {
        std::cerr << "dx too large for domain.\n";
    } else if (result.runtime < 0.0) {
        std::cerr << "runtime must be positive.\n";
    } else if (result.outtime < 0.0) {
        std::cerr << "outtime must be positive.\n";
    } else if (result.outfilename.size() == 0) {
        std::cerr << "no output filename given.\n";
    } else {
        correctinput = true;
    }
    if (not correctinput) {
        std::cerr << "Parameter value error in file '" << filename << "'\n";
        throw 4;
    }
    return result;
}
