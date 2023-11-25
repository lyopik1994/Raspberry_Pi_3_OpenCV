#include "MJPEG.h"
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <chrono>


void MJPEG()
{
    auto start_full = std::chrono::steady_clock::now();
    
    cv::VideoCapture inputVideo("D:/source/OpenCV/Raspberry_Pi_3_OpenCV/street.mp4"); //чтение файла

    int codec = cv::VideoWriter::fourcc('M', 'J', 'P', 'G'); //указываем кодек сжатия MJPG

    double fps = inputVideo.get(cv::CAP_PROP_FPS); 
    
    int totalFrames = inputVideo.get(cv::CAP_PROP_FRAME_COUNT);
    

    cv::Size frameSize(
        (int)inputVideo.get(cv::CAP_PROP_FRAME_WIDTH),
        (int)inputVideo.get(cv::CAP_PROP_FRAME_HEIGHT)
    );

    cv::VideoWriter outputVideo;

    outputVideo.open("output_video.avi", codec, fps, frameSize, true); //создаем файл видео

    cv::Mat frame;
    auto start_codec = std::chrono::steady_clock::now();
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
        params.push_back(0);  //качество

        cv::imencode(".jpg", frame, encoded_buf, params);
        encoded_frame = cv::imdecode(encoded_buf, cv::IMREAD_COLOR);

        outputVideo.write(encoded_frame);
    }


    auto end_codec = std::chrono::steady_clock::now();


    std::cout << "Codec time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end_codec - start_codec).count() << " milliseconds" << "\n";// время конвертации в MJPG


    inputVideo.release();
    outputVideo.release();


    auto end_full = std::chrono::steady_clock::now();

    std::cout << "Full time = "<< std::chrono::duration_cast<std::chrono::seconds>(end_full - start_full).count()<< " seconds" << "\n"; // время всей программы
    
    auto frame_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_full - start_full).count() / (totalFrames); // время обработки кадра

    std::cout << "Frame time = " << frame_time << " milliseconds" << "\n";
   
}
