#################################################################
#
# Example Makefile for Lattice Boltzmann code WLB
# 
# Force driven Poiseuille flow.
# 
# Andreas Bülling, 2013
# andreas@bulling.se
#
#################################################################

# Paths
SRCDIR = .
TOPDIR = ../..

# If the .so file is not placed under the library path, specify 
# the path here. 
PATH_TO_WLB = ../..


vpath %.cpp $(SRCDIR)

#Settings

#Objects
OBJS := PoiseuilleForce.o
		
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