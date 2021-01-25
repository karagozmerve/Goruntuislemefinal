#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "opencv2/imgproc.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include<opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
#include <vector>
using namespace cv;

int main()
{

    Mat img_blur, img, gray;
    img = imread("C:\\Users\\merve\\OneDrive\\Resimler\\coin.png");


    medianBlur(img, img_blur, 5);
    cvtColor(img_blur, gray, COLOR_BGR2GRAY);
    vector<Vec3f>  circles;
    HoughCircles(gray, circles, HOUGH_GRADIENT, 1, gray.rows / 8, 80, 75, 0, 0);
    cout << circles.size() << endl;
    for (size_t i = 0; i < circles.size(); i++) {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        cout << radius << endl;
        RNG rng(12345);
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        circle(img, center, radius, color, 2, 8, 0);
    }
    putText(img, "Para Sayisi=" + to_string(circles.size()), cv::Point(50, 50), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(0, 255, 0), 2, false);
    imshow("a", img);
    waitKey(0);

    return 0;
}
