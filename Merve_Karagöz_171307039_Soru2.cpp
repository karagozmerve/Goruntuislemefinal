#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "opencv2/imgproc.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>

using namespace cv;
using namespace std;

Mat img2, img;
int olcek_deger = 1;
const int zoom_in = 10;

void zoom_trackbar(int, void*)
{
    img2 = Mat::zeros(img.rows * olcek_deger, img.cols * olcek_deger, CV_8UC3);
    for (int i = 0; i < img.cols; i++)
    {
        for (int j = 0; j < img.rows; j++)
        {

            Vec3b imgcolor = img.at<Vec3b>(Point(i, j));
            for (int p = 0;p < olcek_deger;p++)
            {
                for (int q = 0;q < olcek_deger;q++)
                {
                    Vec3b imgcolor2 = img2.at<Vec3b>(Point(i, j));
                    imgcolor2.val[0] = imgcolor.val[0];
                    imgcolor2.val[1] = imgcolor.val[1];
                    imgcolor2.val[2] = imgcolor.val[2];

                    img2.at<Vec3b>(Point(i * olcek_deger + p, j * olcek_deger + q)) = imgcolor2;

                }
            }
        }
    }
    imshow("Zoom in-Zoom out", img2);
}
int main()
{
    img = imread("C:\\Users\\merve\\OneDrive\\Masaüstü\\goruntuisleme\\soru2.png");
    namedWindow("Zoom in-Zoom out", CV_WINDOW_AUTOSIZE);
    createTrackbar("Ölcek", "Zoom in-Zoom out", &olcek_deger, zoom_in, zoom_trackbar);
    zoom_trackbar(olcek_deger, 0);
    namedWindow("Oynanmamýþ Görüntü", CV_WINDOW_AUTOSIZE);
    imshow("Oynanmamýþ Görüntü", img);
    waitKey(0);
    return 0;
}