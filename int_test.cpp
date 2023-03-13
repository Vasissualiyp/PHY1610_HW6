#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
//#include "evolve.h"
//#include "initialize.h"
//#include "output.h"
//#include "parameters.h"
//#include "simulation.h"
//#include "wavetypes.h"
#include <fstream>
#include <iostream>

TEST_CASE("Integrated test of wave1d") {
    
    // Run the sim with test wave parameters file
    std::system("./wave1d test_waveparams.txt");

    // Compare the output file with the expected file
    std::ifstream expected_file("test_results.dat");
    std::ifstream output_file("results.dat");
    std::stringstream expected_stream, output_stream;
    expected_stream << expected_file.rdbuf();
    output_stream << output_file.rdbuf();

    REQUIRE(expected_stream.str() == output_stream.str());


}
