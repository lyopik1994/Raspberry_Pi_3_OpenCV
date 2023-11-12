#include "JPEG_Compression.h"
#include <opencv2/highgui.hpp>

void JPEG_Compression()
{
    cv::Mat img = cv::imread("D:/source/OpenCV/cat.jpg");

    std::vector<int> compression_params;
    compression_params.push_back(cv::IMWRITE_JPEG_QUALITY);
    compression_params.push_back(0);

    std::string output_filename = "output.jpg";
    cv::imwrite(output_filename, img, compression_params);
}
