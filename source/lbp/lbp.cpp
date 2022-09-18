
#include "../vlfeat_py.h"
namespace py = pybind11;

py::array lbp_desc(
    py::array_t<float> img,
    int cell_size
){
    if(img.ndim()!=2){
        throw std::runtime_error("Image must be Grayscale");
    }
    auto buf = img.request();
    int height = img.shape(0);
    int width = img.shape(1);

    VlLbp * lbp = vl_lbp_new(VlLbpUniform, VL_FALSE);

    vl_size dimensions = vl_lbp_get_dimension(lbp);

    float * lbpData = new float[(height/cell_size)*(width/cell_size)*dimensions];

    vl_lbp_process(lbp, lbpData, (float *)buf.ptr, width, height, cell_size);

    py::array lbpArray = py::array_t<float>((height/cell_size)*(width/cell_size)*dimensions, lbpData);

    return lbpArray;
}