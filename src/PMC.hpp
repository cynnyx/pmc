#pragma once

#include <memory>
#include "pmc.h"

namespace pmc{
    class PMC {
    public:
        PMC(std::string arguments);
        PMC(pmc::Input _in);
        void setTime();
        void setMaxCliqueBounds();
        void checkSolution();
        void run();
    public:
        std::vector<int> C; //lower bound of max clique
    private:
        void initGraph();
        double seconds;
        std::unique_ptr<pmc::pmc_graph> G;
        pmc::Input in;
    };
}

