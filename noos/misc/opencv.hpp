#ifndef NOOS_OPENCV
#define NOOS_OPENCV

#if HAVE_OPENCV
    #include <opencv2/opencv.hpp>
    #include <opencv2/imgproc/imgproc.hpp>
#endif

namespace noos{

namespace misc{

#if HAVE_OPENCV
    ///@brief convert a cv::Mat to a noos::object::picture
    ///@param matrix cv::Mat 
    ///@return noos::object::picture
    inline noos::object::picture mat_to_pict(const cv::Mat & matrix)
    {
        std::vector<unsigned char> buf;
        cv::imencode(".png", matrix, buf);
        std::vector<noos::types::byte> conversion(buf.begin(), buf.end());
        return noos::object::picture(conversion);
    }
#endif

}
}

#endif
