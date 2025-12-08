#include "src.h"

#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(_example, m) {
    m.def("foo", &example::foo);
    m.def("bar", &example::bar);
}
