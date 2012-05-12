# Makefile for Simple 2D LBM code
# Andreas BŸlling, 2012
# andreas@bulling.se

#Paths
SRCDIR = ../src
APPDIR = $(SRCDIR)/app
TOPDIR = ..

#Settings

#Objects
OBJS := LBM_D2Q9.o \
		Aux.o \
		HalfWayBBNodes.o \
		BoundaryNodes.o \
		ConstantPressureBoundaryNodes.o\
		ConstantVelocityBoundaryNodes.o\
		AppCylinder.o  \
		ValueNode.o \
		#AppPoiseuille.o \
		
#C++-compiler
CXX = g++

#Compiler options
CPPFLAGS = -O2

#Libraries
LIBS = -lm

#misc for osx
#OSX = -framework cocoa

all: clean	a.out 

a.out: $(OBJS)
	$(CXX) -o $@ $(CPPFLAGS) $(OBJS) $(LIBS)

LBM_D2Q9.o:
	g++ -c $(SRCDIR)/LBM_D2Q9.cpp
	
AppPoiseuille.o:
	g++ -c $(APPDIR)/AppPoiseuille.cpp
	
AppCylinder.o:
	g++ -c $(APPDIR)/AppCylinder.cpp
	
Aux.o:
	g++ -c $(SRCDIR)/Aux.cpp
	
HalfWayBBNodes.o:
	g++ -c $(SRCDIR)/HalfWayBBNodes.cpp
	
BoundaryNodes.o:
	g++ -c $(SRCDIR)/BoundaryNodes.cpp

ConstantPressureBoundaryNodes.o:
	g++ -c $(SRCDIR)/ConstantPressureBoundaryNodes.cpp

ConstantVelocityBoundaryNodes.o:
	g++ -c $(SRCDIR)/ConstantVelocityBoundaryNodes.cpp	
	
ValueNode.o:
	g++ -c $(SRCDIR)/ValueNode.cpp	
	
clean:
	rm -f a.out *.o