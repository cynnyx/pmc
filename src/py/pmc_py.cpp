#include "PMC.hpp"
#include "pybind11/stl_bind.h"
#include "pybind11/pybind11.h"

namespace py = pybind11;
PYBIND11_PLUGIN(pmc){
    py::module m{"PMC Module", "Python Bindings for PMC"};

    py::class_<pmc::PMC> pmc{m, "PMC"};
    pmc.def(py::init<std::string>())
            .def("run", &pmc::PMC::run)
            .def_readwrite("maxClique", &pmc::PMC::C);

    py::bind_vector<std::vector<int>>(m, "vector_int");

    return m.ptr();
}


