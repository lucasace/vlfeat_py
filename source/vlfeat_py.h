#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION

extern "C"{
    #include<vl/sift.h>
    #include<vl/dsift.h>
    #include<vl/mser.h>
    #include<vl/hog.h>
    #include<vl/lbp.h>
}

#include <numpy/arrayobject.h>
#include <numpy/ndarrayobject.h>
#include<vector>
#include<string>
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

py::array hog_desc(
    py::array_t<float> img,
    int cell_size,
    std::string variant = "UoCTTI",
    int num_orientations = 9
);

py::array lbp_desc(
    py::array_t<float> img,
    int cell_size
);

