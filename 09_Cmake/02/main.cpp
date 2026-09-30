#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    cout << "Hello OpenCV " << CV_VERSION << endl;

    Mat img, gray, two_jin;

    img = imread("../src/lenna.bmp");

    if (img.empty())
    {
        cerr << "Image load failed!" << endl;
        return -1;
    }

    // 컬러 영상 -> 그레이스케일 영상
    cvtColor(img, gray, COLOR_BGR2GRAY);

    // 그레이스케일 영상 -> 이진 영상
    threshold(gray, two_jin, 128, 255, THRESH_BINARY);

    imshow("Original", img);
    imshow("Gray", gray);
    imshow("Binary", two_jin);

    waitKey(0);

    return 0;
}
