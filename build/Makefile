# Makefile for Simple 2D LBM code
# Andreas BŸlling, 2012
# andreas@bulling.se

#Paths
SRCDIR = ../src
APPDIR = $(SRCDIR)/app
TESTDIR = $(SRCDIR)/tests
TOPDIR = ..

vpath %.cpp $(SRCDIR) $(APPDIR)

#Settings

#Objects
OBJS := LBM_D2Q9.o \
		Aux.o \
		HalfWayBBNodes.o \
		BoundaryNodes.o \
		ConstantPressureBoundaryNodes.o\
		ConstantVelocityBoundaryNodes.o\
		BFLBoundaryNodes.o \
		ValueNode.o \
		StreamModel.o \
		PeriodicStreamModel.o \
		DefaultStreamModel.o \
		AppPoiseuilleForce.o \
		#AppCylinderBFL.o  \
		#AppCylinder.o  \
		#AppPoiseuille.o \
		
#C++-compiler
CXX = g++

#Compiler options
CPPFLAGS = -O2

#Libraries
LIBS = -lm

#misc for osx
#OSX = -framework cocoa

all: a.out 

a.out: $(OBJS)
	$(CXX) -o $@ $(CPPFLAGS) $(OBJS) $(LIBS)
	
clean:
	rm -f a.out *.o