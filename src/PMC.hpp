#pragma once
#include "pmc.h"

namespace pmc{
    class PMC {
    public:
//        PMC(int, char **);
        PMC(int argc, std::string argv);
        void setTime();
        void setMaxCliqueBounds();
        void checkSolution();
    public:
        std::vector<int> C; //lower bound of max clique
    private:
        double seconds;
        pmc::pmc_graph G;
        input in;
    };
}

