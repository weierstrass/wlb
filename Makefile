################################################################################
#                                                                              #
# Core Makefile for Lattice Boltzmann code WLB                                 #
#                                                                              #
#  To use the wlb library, compile the code, if everything goes well, you will #
#  get a wlblib.so file which you may use to link with your code. See the 	   #	
#  examples folder for details.											       #	
#                                                                              # 
#  The code is tested on a UNIX 64 bit system.                                 #
#                                                                              # 
#                                                                              #
#  Andreas Bülling, 2013                                                       #
#  andreas@bulling.se                                                          #
#                                                                              #  
################################################################################

# Path definitions
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

# C++ compiler
CPP = g++

# Compiler options
CPPFLAGS = -O2 -fopenmp -fPIC#-pg

# Linker options
LDFLAGS = 

# Libraries to link to
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