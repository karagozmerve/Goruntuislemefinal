#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

void rgbthosv(float r,float g,float b) {
    float Cmax, Cmin, delta,h,s,v;

    r /= 255.0;
    g /= 255.0;
    b /= 255.0;
    Cmax = max(r, g, b);
    Cmin = min(r, g, b);
    delta = Cmax - Cmin;
    if (delta == 0) {
        h = 0;
    }
    else if (Cmax == r) {
        h = g - b;
        h = h / delta;
        h = 60 * h;
        h = fmod(h, 360);
    }
    else if (Cmax == g) {
        h = b - r;
        h = h / delta;
        h = 60 * h;
        h = h + 2;
        h = fmod(h, 360);
    }
    else if (Cmax == b) {
        h = r - g;
        h = h / delta;
        h = 60 * h;
        h = h + 4;
        h = fmod(h, 360);

    }
    if (Cmax == 0) {
        s = 0;

    }
    else {
        s = delta / Cmax;

    }

}
int main(int argc, char const* argv[])
{
    Mat image;
    float wdh, hgh;
    int r;
    int g;
    int b;
    int h, s, v;

        Mat img2 = Mat::zeros(image.rows, image.cols, CV_8UC3);
        for (int i = 0; i < image.rows; i++)
        {
            for (int j = 0; j < image.cols; j++)
            {
                Mat3b image = imread("C:\\Users\\merve\\OneDrive\\Masaüstü\\goruntuisleme\\Lena.png");
                Vec3b imgcolor = image.at<Vec3b>(Point(i, j));
                 b = imgcolor[0];
                g = imgcolor[1];
                 r = imgcolor[2];
               rgbthosv(r, g, b);
                Vec3b imgcolor2 = img2.at<Vec3b>(Point(i, j));
                imgcolor2.val[h] = imgcolor.val[r];
                imgcolor2.val[s] = imgcolor.val[g];
                imgcolor2.val[v] = imgcolor.val[b];
            }
        }

        imshow("a", img2);
        waitKey(0);
        return 0;
}
