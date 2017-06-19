#include "PMC.hpp"
#include "pmc.h"
#include "pybind11/stl_bind.h"
#include "pybind11/pybind11.h"

namespace py = pybind11;
PYBIND11_PLUGIN(pmc){
    py::module m{"PMC Module", "Python Bindings for PMC"};

    py::class_<pmc::PMC, std::shared_ptr<pmc::PMC>> pmc{m, "PMC"};
    pmc.def(py::init<int, std::string>())
            .def("setTime", &pmc::PMC::setTime)
            .def("setMaxCliqueBounds", &pmc::PMC::setMaxCliqueBounds)
            .def("checkSolution", &pmc::PMC::checkSolution)
            .def_readwrite("C", &pmc::PMC::C);

    py::bind_vector<std::vector<int>>(m, "vInt");

    return m.ptr();
}


