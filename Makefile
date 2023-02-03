# makefile for the wave1d application

CXX=g++
CXXFLAGS=-O2 -g -std=c++17 -Wall -Wfatal-errors -Wconversion
LDFLAGS=-O2 -g
all: wave1d

wave1d: wave1d.o parameters.o initialize.o output.o
	$(CXX) $(LDFLAGS) -o $@ $^

wave1d.o: wave1d.cpp parameters.h initialize.h
	$(CXX) -c $(CXXFLAGS) -o wave1d.o wave1d.cpp

parameters.o: parameters.cpp parameters.h
	$(CXX) -c $(CXXFLAGS) -o parameters.o parameters.cpp

initialize.o: initialize.cpp initialize.h parameters.h
	$(CXX) -c $(CXXFLAGS) -o initialize.o initialize.cpp

output.o: output.cpp output.h parameters.h
	$(CXX) -c $(CXXFLAGS) -o output.o output.cpp

run: wave1d
	./wave1d waveparams.txt

clean:
	$(RM) wave1d.o parameters.o initialize.o output.o

.PHONY: all clean run

