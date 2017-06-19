#include "PMC.hpp"
namespace pmc{

//    PMC::PMC(int argc, char ** argv) : in{}, G{in.graph_stats, in.graph} {
    PMC::PMC(int argc, std::string argv): in{}, G{in.graph_stats, in.graph} {

        std::vector<char *> args;
        std::istringstream iss{argv};

        std::string token;
        while (iss >> token) {
            char *arg = new char[token.size() + 1];
            copy(token.begin(), token.end(), arg);
            arg[token.size()] = '\0';
            args.push_back(arg);
        }
        for (int i = 0; i < args.size(); ++i) {
            std::cout << "arg " << i << " is " << args[i] << std::endl;
        }
        this->in = input{argc, &args[0]};
        // now exec with &args[0], and then:
        for (auto && a : args) { delete[] a; }

        //this->in = input{argc, argv};
        this->G = pmc::pmc_graph{in.graph_stats, in.graph};
        if (in.graph_stats) {
            G.bound_stats(in.algorithm, in.lb, G);
        }
    }
    void PMC::setTime() {
        //! ensure wait time is greater than the time to recompute the graph data structures
        if (G.num_edges() > 1000000000 && in.remove_time < 120)  in.remove_time = 120;
        else if (G.num_edges() > 250000000 && in.remove_time < 10) in.remove_time = 10;
        std::cout << "explicit reduce is set to " << in.remove_time << " seconds" <<endl;
    }
    
    void PMC::setMaxCliqueBounds(){
        //! upper-bound of max clique
        seconds = get_time();
        G.compute_cores();
        if (in.ub == 0) {
            in.ub = G.get_max_core() + 1;
            std::cout << "K: " << in.ub <<endl;
            std::cout << "k-cores time: " << get_time() - seconds << ", ub: " << in.ub << endl;
        }

        //! lower-bound of max clique
        if (in.lb == 0 && in.heu_strat != "0") { // skip if given as input
            pmc::pmc_heu maxclique{G,in};
            in.lb = maxclique.search(G, C);
            std::cout << "Heuristic found clique of size " << in.lb;
            std::cout << " in " << get_time() - seconds << " seconds" <<endl;
            std::cout << "[pmc: heuristic]  ";
            print_max_clique(C);
        }
    }

    void PMC::checkSolution(){
        //! check solution found by heuristic
        if (in.lb == in.ub && !in.MCE) {
            std::cout << "Heuristic found optimal solution." << endl;
        }
        else if (in.algorithm >= 0) {
            switch(in.algorithm) {
                case 0: {
                    //! k-core pruning, neigh-core pruning/ordering, dynamic coloring bounds/sort
                    if (G.num_vertices() < in.adj_limit) {
                        G.create_adj();
                        pmcx_maxclique finder{G,in};
                        finder.search_dense(G,C);
                        break;
                    }
                    else {
                        pmcx_maxclique finder{G,in};
                        finder.search(G,C);
                        break;
                    }
                }
                case 1: {
                    //! k-core pruning, dynamic coloring bounds/sort
                    if (G.num_vertices() < in.adj_limit) {
                        G.create_adj();
                        pmcx_maxclique_basic finder{G,in};
                        finder.search_dense(G,C);
                        break;
                    }
                    else {
                        pmcx_maxclique_basic finder{G,in};
                        finder.search(G,C);
                        break;
                    }
                }
                case 2: {
                    //! simple k-core pruning (four new pruning steps)
                    pmc_maxclique finder{G,in};
                    finder.search(G,C);
                    break;
                }
                default:
                    std::cout << "algorithm " << in.algorithm << " not found." <<endl;
                    break;
            }
            seconds = (get_time() - seconds);
            std::cout << "Time taken: " << seconds << " SEC" << endl;
            std::cout << "Size (omega): " << C.size() << endl;
            print_max_clique(C);

            if (C.size() < in.param_ub)
                std::cout << "Clique of size " << in.param_ub << " does not exist." <<endl;
        }
    }
}