#
# Makefile for PMC
#
# Ryan A. Rossi
# Copyright, 2012-2016
#

.KEEP_STATE:

all: pmc libpmc libpmc_test

#OPTFLAGS    = -g -D _GLIBCXX_DEBUG
OPTFLAGS    = -O3
CFLAGS      = $(OPTFLAGS) -fPIC
#CFLAGS 		+= -D_GLIBCXX_PARALLEL
#CFLAGS 		+= -floop-parallelize-all -ftree-loop-distribution


CXX          = g++
H_FILES     = src/pmc.h


.cpp.o:
	$(CXX) $(CFLAGS) -c $<

IO_SRC 				   = src/pmc_utils.cpp \
						 src/pmc_graph.cpp \
						 src/pmc_clique_utils.cpp

PMC_SRC 			   = src/pmc_heu.cpp \
						 src/pmc_maxclique.cpp \
						 src/pmcx_maxclique.cpp \
						 src/pmcx_maxclique_basic.cpp \
						 src/PMC.cpp

BOUND_LIB_SRC 		   = src/pmc_cores.cpp

PMC_MAIN			   = src/pmc_driver.cpp

OBJ_PMC	= $(PMC_MAIN) $(IO_SRC) $(PMC_SRC) $(BOUND_LIB_SRC)
$(OBJ_PMC): $(H_FILES) Makefile

pmc: $(OBJ_PMC) $(H_FILES)
	$(CXX) $(CFLAGS) -o pmc $(OBJ_PMC) -fopenmp


libpmc: $(IO_SRC) $(PMC_SRC) $(BOUND_LIB_SRC) $(H_FILES) src/pmc_lib.cpp
	$(CXX) -static-libstdc++ $(CFLAGS) -shared -o libpmc.so \
		$(IO_SRC) $(PMC_SRC) $(BOUND_LIB_SRC) src/pmc_lib.cpp -fopenmp

libpmc_test: libpmc test/libpmc_test.cpp
	$(CXX) test/libpmc_test.cpp ./libpmc.so  -o libpmc_test
	./libpmc_test

clean:
	rm -rf *.o pmc *.so *.dylib libpmc_test
