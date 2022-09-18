#include "../vlfeat_py.h"
namespace py = pybind11;

py::array hog_desc(
    py::array_t<float> img,
    int cell_size,
    std::string variant,
    int num_orientations
){
    if(img.ndim()!=2 && img.ndim()!=3){
        throw std::runtime_error("Image must be Grayscale");
    }
    auto buf = img.request();
    int height = img.shape(0);
    int width = img.shape(1);
    int channels = 1;
    if(img.ndim()==3){
        channels = img.shape(2);
    }
    VlHogVariant vl_variant;
    if(variant == "dalaltriggs"){
        vl_variant = VlHogVariantDalalTriggs;
    }
    else if(variant == "UoCTTI"){
        vl_variant = VlHogVariantUoctti;
    }
    else{
        throw std::runtime_error("Variant must be either dalaltriggs or zhuramanan");
    }
    VlHog * hog = vl_hog_new(vl_variant, num_orientations, VL_FALSE);
    vl_hog_put_image(hog, (float *)buf.ptr, width, height, channels , cell_size);
    vl_size hogWidth = vl_hog_get_width(hog);
    vl_size hogHeight = vl_hog_get_height(hog);
    vl_size hogDimension = vl_hog_get_dimension(hog);
    float * hogData = new float[hogWidth*hogHeight*hogDimension];
    vl_hog_extract(hog, hogData);
    vl_hog_delete(hog);
    py::array hogArray = py::array_t<float>(hogWidth*hogHeight*hogDimension, hogData);
    return hogArray;
}