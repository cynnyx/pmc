/**
 ============================================================================
 Name        : Parallel Maximum Clique (PMC) Library
 Author      : Ryan A. Rossi   (rrossi@purdue.edu)
 Description : A general high-performance parallel framework for computing
               maximum cliques. The library is designed to be fast for large
               sparse graphs.

 Copyright (C) 2012-2013, Ryan A. Rossi, All rights reserved.

 Please cite the following paper if used:
   Ryan A. Rossi, David F. Gleich, Assefaw H. Gebremedhin, Md. Mostofa
   Patwary, A Fast Parallel Maximum Clique Algorithm for Large Sparse Graphs
   and Temporal Strong Components, arXiv preprint 1302.6256, 2013.

 See http://ryanrossi.com/pmc for more information.
 ============================================================================
 */

#include "PMC.hpp"

using namespace std;
using namespace pmc;

int main(int argc, char *argv[]) {

    //! parse command args
    pmc::Input in{argc, argv};
    if (in.help) {
        usage(argv[0]);
        return 0;
    }

    pmc::PMC p{in};
    p.setTime();
    p.setMaxCliqueBounds();
    p.checkSolution();
    return 0;
}

