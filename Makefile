# makefile for the wave1d application

CXX=g++
CXXFLAGS=-O2 -g -std=c++17 -Wall -Wfatal-errors -Wconversion
LDFLAGS=-O2 -g
all: wave1d test

# Modules compilation {{{

wave1d: wave1d.o parameters.o initialize.o output.o evolve.o simulation.o
	$(CXX) $(LDFLAGS) -o $@ $^

wave1d.o: wave1d.cpp parameters.h wavetypes.h initialize.h output.h evolve.h simulation.h
	$(CXX) -c $(CXXFLAGS) -o wave1d.o wave1d.cpp

parameters.o: parameters.cpp parameters.h wavetypes.h
	$(CXX) -c $(CXXFLAGS) -o parameters.o parameters.cpp

initialize.o: initialize.cpp initialize.h wavetypes.h
	$(CXX) -c $(CXXFLAGS) -o initialize.o initialize.cpp

output.o: output.cpp output.h wavetypes.h
	$(CXX) -c $(CXXFLAGS) -o output.o output.cpp

evolve.o: evolve.cpp evolve.h wavetypes.h
	$(CXX) -c $(CXXFLAGS) -o evolve.o evolve.cpp

simulation.o: simulation.cpp simulation.h wavetypes.h
	$(CXX) -c $(CXXFLAGS) -o simulation.o simulation.cpp
#}}}

# Module tests compilation {{{

./int_test: int_test.o
	$(CXX) $(LDFLAGS) -o $@ $^   -lCatch2Main -lCatch2 #-lboost_unit_test_framework

int_test.o: int_test.cpp
	$(CXX) -c $(CXXFLAGS) -o int_test.o int_test.cpp

#}}}

# General commands {{{

run: wave1d
	./wave1d waveparams.txt

cleanall:
	$(RM) wave1d.o parameters.o initialize.o output.o evolve.o simulation.o results.dat wave1d int_test int_test.o

clean:
	$(RM) wave1d.o parameters.o initialize.o output.o evolve.o simulation.o int_test.o

#Runs integrated test
test: wave1d int_test
	./int_test

#Runs integrated test and then cleans up afterwards
testandclean: wave1d int_test
	./int_test
	$(MAKE) cleanall

.PHONY: all clean run cleanall test
#}}}
