#include "MJPEG.h"
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

void MJPEG()
{

    cv::VideoCapture inputVideo("D:/source/OpenCV/Raspberry_Pi_3_OpenCV/corgi.mp4"); //������ �����

    int codec = cv::VideoWriter::fourcc('M', 'J', 'P', 'G'); //��������� ����� ������ MJPG

    double fps = inputVideo.get(cv::CAP_PROP_FPS); 
    

    cv::Size frameSize(
        (int)inputVideo.get(cv::CAP_PROP_FRAME_WIDTH),
        (int)inputVideo.get(cv::CAP_PROP_FRAME_HEIGHT)
    );

    cv::VideoWriter outputVideo;

    outputVideo.open("output_video.avi", codec, fps, frameSize, true); //������� ���� �����

    cv::Mat frame;
    while (true) {

        inputVideo.read(frame); // ��������� ����� �� ��������� �����

        if (frame.empty()) {
            break;
        }

        // ������ � ������������ �������� 
        cv::Mat encoded_frame;
        std::vector<uchar> encoded_buf;
        std::vector<int> params;
        params.push_back(cv::IMWRITE_JPEG_QUALITY);
        params.push_back(2);  //��������

        cv::imencode(".jpg", frame, encoded_buf, params);
        encoded_frame = cv::imdecode(encoded_buf, cv::IMREAD_COLOR);

        outputVideo.write(encoded_frame);
    }

    inputVideo.release();
    outputVideo.release();

    
}
