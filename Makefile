#################################################################
#                                                               #
# Core Makefile for Lattice Boltzmann code WLB                  #
#                                                               # 
# The code is compiled into a static and a share library.       #
# Chose the one to use from your own preferences. The code      #
# is tested and verified on a X86_64 architecture, but should   #
# function fine (in some cases with minor modifications) on     #
# other architectures as well.                                  #
#                                                               #
# Andreas Bülling, 2013                                         #
# andreas@bulling.se                                            #
#                                                               # 
#################################################################

# Paths
SRCDIR = src
TESTDIR = $(SRCDIR)/tests
TOPDIR = .
OBJDIR = build

SUBDIRS =   col lat str bdr unit io
CPPDIRS = $(addprefix $(SRCDIR)/, $(SUBDIRS)) $(SRCDIR)
			
VPATH = $(CPPDIRS)

CPPSRCS = $(addsuffix /*.cpp, $(CPPDIRS))
SRCS = $(wildcard $(CPPSRCS))
OBJS = $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.cpp=.o)))

VPATH = $(CPPDIRS)

# C++-compiler
CPP = g++

# Compiler options
CPPFLAGS = -O2 -fopenmp -fPIC#-pg

# Linker options
LDFLAGS = 

# Libraries
LIBS = -lm

# Build rules
.PHONY: print all clean

all: $(OBJDIR) libwlb.so

$(OBJDIR):
	mkdir $(OBJDIR)

$(OBJDIR)/%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

libwlb.so: $(OBJS)
	$(CPP) -shared -o $@ $(CPPFLAGS) $(OBJS) $(LIBS)
	
clean:
	rm -f a.out $(OBJDIR)/*.o *.o libwlb.so
	
print:
	echo $(SRCS)
	echo $(OBJS)
	echo $(CPPDIRS)