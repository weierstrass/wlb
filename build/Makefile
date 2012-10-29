# Makefile for Lattice Boltzmann code
# Andreas Bülling, 2012
# andreas@bulling.se

#Paths
SRCDIR = ../src
APPDIR = $(SRCDIR)/app
TESTDIR = $(SRCDIR)/tests
TOPDIR = ..

vpath %.cpp $(SRCDIR) $(APPDIR) $(SRCDIR)/col \
			$(SRCDIR)/lat $(SRCDIR)/str \
			$(SRCDIR)/bdr $(SRCDIR)/unit

#Settings

#Objects
OBJS := LBM.o \
		Aux.o \
		HalfWayBBNodes.o \
		BoundaryNodes.o \
		ValueNode.o \
		TypeValueNode.o \
		NodeNeighbors.o \
		BounceBackNodes.o \
		SlipNodes.o \
		HeZouPressureNodes.o \
		HeZouLPMChaiNodes.o \
		HeZouNodes.o \
		DirichletLPMNodes.o \
		NeumannLPMNodes.o \
		NeumannNodes.o \
		NeumannNodesNP.o \
		NeumannNodesPE.o \
		NeumannNodesPESlip.o \
		StreamModel.o \
		CollisionD2Q9.o \
		CollisionD2Q9BGK.o \
		CollisionD2Q9BGKShanChenForce.o \
		CollisionD2Q9LPM.o \
		CollisionD2Q9LPMChai.o \
		CollisionD2Q9LPMChaiHelmholtz.o \
		CollisionD2Q9LPMChai1to1.o \
		CollisionD2Q9LPMChaiRHS.o \
		CollisionD2Q9LPMWang.o \
		CollisionD2Q9WangHelmholtz.o \
		CollisionD2Q9LPMWang1to1.o \
		CollisionD2Q9LNP.o \
		CollisionD2Q9LNPSource.o \
		CollisionD2Q9AD.o \
		CollisionModel.o \
		LatticeModel.o \
		Lattice2D.o \
		StreamD2Q9.o \
		StreamD2Q9Periodic.o \
		Node.o \
		UnitHandler.o \
		UnitHandlerLPM.o \
		UnitHandlerNS.o \
		PressureElectro2DChannel.o \
		#AppADSource2.o \
		#AppPENeumann.o \
		#AppADSource.o \	
		#AppPoiseuilleForce.o \
		#PeriodicTest.o \
		#App1D1to1Chai.o \
		#AppADTest.o \
		#App1D1to1Wang.o \		
		#AppPoiseuille.o \
		#AppLPMChaiTest.o \
		#AppLPMTest.o \
		#AppTaylorVortex.o \
		#AppCylinderBFL.o  \
		AppForceCylinderBFL.o \
		#AppCylinder.o  \
		ConstantPressureBoundaryNodes.o\
		ConstantVelocityBoundaryNodes.o\
		BFLBoundaryNodes.o \
		PeriodicStreamModel.o \
		DefaultStreamModel.o \
	
		
#C++-compiler
CXX = g++

#Compiler options
CPPFLAGS =-O2 -pg

#Libraries
LIBS = -lm

#misc for osx
#OSX = -framework cocoa

all: a.out 

a.out: $(OBJS)
	$(CXX) -o $@ $(CPPFLAGS) $(OBJS) $(LIBS)
	
clean:
	rm -f a.out *.o