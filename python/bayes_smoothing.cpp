#include <pybind11/pybind11.h>

namespace py = pybind11;

void PyInit_bayes_smoothing(py::module &);

PYBIND11_MODULE(bayes_smoothing, m) {
    // Optional docstring
    m.doc() = "Bayes Smoothing";
    
    PyInit_bayes_smoothing(m);
}
