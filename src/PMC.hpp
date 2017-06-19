#pragma once
#include "pmc.h"

namespace pmc{
    class PMC {
    public:
        PMC(std::string arguments);
        PMC(input _in);
        void setTime();
        void setMaxCliqueBounds();
        void checkSolution();
        void run();
    public:
        std::vector<int> C; //lower bound of max clique
    private:
        void initGraph();
        double seconds;
        pmc::pmc_graph G;
        input in;
    };
}

