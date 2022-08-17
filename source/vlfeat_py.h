#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION

extern "C"{
    #include<vl/sift.h>
    #include<vl/dsift.h>
    #include<vl/mser.h>
}

#include <numpy/arrayobject.h>
#include <numpy/ndarrayobject.h>
#include<vector>
#include<pybind11/pybind11.h>
#include<pybind11/eigen.h>
#include<pybind11/stl.h>
namespace py = pybind11;

py::tuple sift_desc(
    py::array_t<float> img,
    int noctaves =-1,
    int nlevels = 3,
    int first_octave = 0
);

py::tuple dsift_desc(
    py::array_t<float> img,
    py::array_t<int> bounds,
    int step = 1,
    int size = 3,
    bool fast = false, 
    bool norm = false
);

py::tuple mser_desc(
    py::array_t<float> img,
    int delta = 5,
    float max_area = 0.75,
    float min_area = -1,
    float max_variation = 0.25,
    float min_diversity = 0.2
);
