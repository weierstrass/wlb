################################################################################
#
# Test Makefile for Lattice Boltzmann code WLB
# 
# Andreas Bülling, 2013
# andreas@bulling.se
# https://github.com/weierstrass/Lattice-Boltzmann
#
################################################################################

# Paths
SRCDIR = .
TOPDIR = ../..

# If the .so file is not placed under the library path, specify 
# the path here. 
PATH_TO_WLB = ../..


vpath %.cpp $(SRCDIR)

#Settings

#Objects
OBJS := TestLatticeD3Q19.o
		
#C++-compiler
CXX = g++

#Compiler options
CPPFLAGS = -O2 -fopenmp -Wl,-rpath,$(PATH_TO_WLB) -L$(TOPDIR)

#-pg

#Libraries
LIBS = -lm -lwlb

all: a.out

a.out: $(OBJS)
	$(CXX) -o $@ $(CPPFLAGS) $(OBJS) $(LIBS)
	
clean:
	rm -f a.out *.o