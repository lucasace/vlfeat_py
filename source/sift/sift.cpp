
#include "../vlfeat_py.h"
namespace py = pybind11;

py::tuple sift_desc(
    py::array_t<float> img,
    int noctaves ,
    int nlevels,
    int first_octave
){
    if(img.ndim()!=2){
        throw std::runtime_error("Image must be Grayscale");
    }
    auto buf = img.request();

    vl_sift_pix *ImageData = (vl_sift_pix * ) buf.ptr;
    int height = img.shape(0);
    int width = img.shape(1);
    if(noctaves == -1){
        noctaves = log2(std::min(width, height));
    }
    VlSiftFilt * sift = vl_sift_new(width, height, noctaves, nlevels, first_octave);
    std::vector<std::vector<float>> Descriptors;
    std::vector<std::array<float, 4>> Keypoints;
    int keypoint =0;
    if(vl_sift_process_first_octave(sift, ImageData)!=VL_ERR_EOF){
        while(1){
            vl_sift_detect(sift);
            keypoint += sift->nkeys;
            VlSiftKeypoint *pKeyPoint  = sift->keys;
            for(int i=0;i<sift->nkeys;i++){
                VlSiftKeypoint TemptKeyPoint = *pKeyPoint;
                pKeyPoint++;
                double angles[4];
				int angleCount=vl_sift_calc_keypoint_orientations(sift,angles,&TemptKeyPoint);
                for(int j=0;j<angleCount;j++){
                    float TemptAngle = angles[j];
                    vl_sift_pix *Descriptor = new vl_sift_pix[128];
                    vl_sift_calc_keypoint_descriptor(sift,Descriptor,&TemptKeyPoint,TemptAngle);
                    std::vector<float> TemptDescriptor = std::vector<float>(Descriptor, Descriptor+128);
                    Descriptors.push_back(TemptDescriptor);
                    std::array<float, 4> TemptKeypoint = {TemptKeyPoint.x, TemptKeyPoint.y, TemptKeyPoint.sigma, TemptAngle};
                    Keypoints.push_back(TemptKeypoint);
                }   
            }
            if(vl_sift_process_next_octave(sift)==VL_ERR_EOF){
                break;
            }
        }
    }
    vl_sift_delete(sift);
    py::array descriptors = py::cast(Descriptors);
    py::array keypoints = py::cast(Keypoints);
    return py::make_tuple(keypoints, descriptors);
}