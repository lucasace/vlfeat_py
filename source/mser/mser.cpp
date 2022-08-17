#include "../vlfeat_py.h"

namespace py = pybind11;

py::tuple mser_desc(
    py::array_t <float> img,
    int delta, 
    float max_area,
    float min_area,
    float max_variation,
    float min_diversity
){
    if(img.ndim()!=2){
        throw std::runtime_error("Image must be Grayscale");
    }
    auto buf = img.request();
    int height = img.shape(0);
    int width = img.shape(1);
    if(min_area == -1){
        min_area = 3.0/(float)(height*width);
    }
    vl_mser_pix const *ImageData = (vl_mser_pix *) buf.ptr; 
    int const *dims = new int[2]{height, width};
    VlMserFilt *filt = vl_mser_new(2, dims);
    vl_mser_set_delta(filt, (vl_mser_pix)delta);
    vl_mser_set_max_area(filt, max_area);
    vl_mser_set_min_area(filt, min_area);
    vl_mser_set_max_variation(filt, max_variation);
    vl_mser_set_min_diversity(filt, min_diversity);

    vl_mser_process(filt, ImageData);
    vl_mser_ell_fit(filt);

    auto nregions = vl_mser_get_regions_num(filt);
    vl_uint const *regions = vl_mser_get_regions(filt);

    int nframes = vl_mser_get_ell_num(filt);
    int dof = vl_mser_get_ell_dof(filt);
    float const* frames = vl_mser_get_ell(filt);

    std::vector<float> region_buf;
    for(int i=0;i<nframes;i++){
        region_buf.push_back(regions[i]);
    }

    std::vector<std::vector<float>> frames_buf(dof, std::vector<float>(nframes));
    for(int i=0;i<nframes;i++){
        for(int j=0;j<dof;j++){
            frames_buf[j][i] = frames[i*dof+j];
        }
    }
    py::array region_seeds = py::cast(region_buf);
    py::array f_ellipsoids = py::cast(frames_buf);
    vl_mser_delete(filt);
    return py::make_tuple(region_seeds, f_ellipsoids);
}