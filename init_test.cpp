#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "parameters.h"
#include "initialize.h"
#include "output.h"

T_CASE("Initialization produces correct output file", "[initialization]") {
    const char* output_filename = "results.txt";
    const char* expected_filename = "test_results.txt";
    const char* parameters_filename = "test_waveparams.txt";
    remove(output_filename); // remove old output file if it exists
    initialize(output_filename, parameters_filename);

    std::ifstream expected(expected_filename);
    std::ifstream actual(output_filename);
    REQUIRE(expected.good());
    REQUIRE(actual.good());

    std::string expected_line, actual_line;
    while (std::getline(expected, expected_line) && std::getline(actual, actual_line)) {
        REQUIRE(expected_line == actual_line);
    }
}
