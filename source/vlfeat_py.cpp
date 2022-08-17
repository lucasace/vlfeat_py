
#include"vlfeat_py.h"
namespace py = pybind11;

PYBIND11_MODULE(vlfeat_py , m){
    m.doc() = "A Vlfeat based python package"; // optional module docstring

    m.def("sift_desc", &sift_desc, "Computes the SIFT Frames and Descriptors.", py::arg("img"), py::arg("noctaves")=-1, py::arg("nlevels")=3, py::arg("first_octave")=0);

    m.def("dsift_desc", &dsift_desc, "Computes the Dense SIFT Frames and Descriptors.", py::arg("img"), py::arg("bounds"), py::arg("step")=1, py::arg("size")=3, py::arg("fast")=false, py::arg("norm")=false);

    m.def("mser_desc", &mser_desc, "Computes the MSER Frames and Descriptors.", py::arg("img"), py::arg("delta")=5, py::arg("max_area")=0.75, py::arg("min_area")=-1, py::arg("max_variation")=0.25, py::arg("min_diversity")=0.2);
}