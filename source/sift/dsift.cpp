
#include "../vlfeat_py.h"
namespace py = pybind11;

py::tuple dsift_desc(
    py::array_t<float> img,
    py::array_t<int> bounds,
    int step,
    int size,
    bool fast, 
    bool norm
){
    if(img.ndim()!=2){
        throw std::runtime_error("Image must be Grayscale");
    }
    auto buf = img.request();
    int height = img.shape(0);
    int width = img.shape(1);
    if(bounds.ndim()!=1 || bounds.size()!=4){ 
        throw std::runtime_error("Bounds must be a 4 element array");
    }
    int *bounds_ptr = (int *) bounds.request().ptr;
    float *ImageData = (float *) buf.ptr;   
    int useNorm = 0;
    int useFlatWindow = 0;
    if(fast)
        useFlatWindow = 1;
    if(norm)
        useNorm =1;
    VlDsiftKeypoint const *frames;
    VlDsiftDescriptorGeometry const *geom;
    float const *descrs;

    VlDsiftFilter * dsift = vl_dsift_new_basic(width, height, step, size);
    vl_dsift_set_bounds(dsift, bounds_ptr[0], bounds_ptr[1], bounds_ptr[2], bounds_ptr[3]);
    vl_dsift_set_flat_window(dsift, useFlatWindow);
    int numFrames = vl_dsift_get_keypoint_num (dsift) ;
	int descrSize = vl_dsift_get_descriptor_size (dsift) ;
	geom = vl_dsift_get_geometry(dsift);
    vl_dsift_process(dsift, ImageData);
    frames = vl_dsift_get_keypoints(dsift);
	descrs = vl_dsift_get_descriptors(dsift);
    std::vector<std::vector<float>> Descriptors;
    std::vector<std::array<float, 2>> Keypoints;
    for(int i=0;i<numFrames;i++){
        float *tmpDescr = (float*) vl_malloc(sizeof(float) * descrSize);
        VlDsiftKeypoint TemptKeyPoint = frames[i];
        std::array<float, 2> TemptKeypoint = {TemptKeyPoint.x, TemptKeyPoint.y};
        Keypoints.push_back(TemptKeypoint);
        vl_dsift_transpose_descriptor(tmpDescr, descrs + descrSize * i, geom->numBinT, geom->numBinX, geom->numBinY);
        std::vector<float> TemptDescriptor = std::vector<float>(tmpDescr, tmpDescr + descrSize);
        Descriptors.push_back(TemptDescriptor);
        vl_free(tmpDescr);
    }
    py::array descriptors = py::cast(Descriptors);
    py::array keypoints = py::cast(Keypoints);
    vl_dsift_delete(dsift);
    return py::make_tuple(keypoints, Descriptors);
}