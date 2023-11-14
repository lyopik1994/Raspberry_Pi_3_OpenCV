#include "MJPEG.h"
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

void MJPEG()
{

    cv::VideoCapture inputVideo("D:/source/OpenCV/Raspberry_Pi_3_OpenCV/corgi.mp4"); //чтение файла

    int codec = cv::VideoWriter::fourcc('M', 'J', 'P', 'G'); //указываем кодек сжатия MJPG

    double fps = inputVideo.get(cv::CAP_PROP_FPS); 
    

    cv::Size frameSize(
        (int)inputVideo.get(cv::CAP_PROP_FRAME_WIDTH),
        (int)inputVideo.get(cv::CAP_PROP_FRAME_HEIGHT)
    );

    cv::VideoWriter outputVideo;

    outputVideo.open("output_video.avi", codec, fps, frameSize, true); //создаем файл видео

    cv::Mat frame;
    while (true) {

        inputVideo.read(frame); // считываем кадры из исходного видео

        if (frame.empty()) {
            break;
        }

        // сжатие с регулировкой качества 
        cv::Mat encoded_frame;
        std::vector<uchar> encoded_buf;
        std::vector<int> params;
        params.push_back(cv::IMWRITE_JPEG_QUALITY);
        params.push_back(2);  //качество

        cv::imencode(".jpg", frame, encoded_buf, params);
        encoded_frame = cv::imdecode(encoded_buf, cv::IMREAD_COLOR);

        outputVideo.write(encoded_frame);
    }

    inputVideo.release();
    outputVideo.release();

    
}
