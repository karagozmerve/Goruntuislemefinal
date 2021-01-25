#include "stdlib.h"
#include "math.h"
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <string>
using namespace std;
using namespace cv;


int reflect(int M, int x)
{
    if (x < 0)
    {
        return -x - 1;
    }
    if (x >= M)
    {
        return 2 * M - x - 1;
    }
    return x;
}

int circular(int M, int x)
{
    if (x < 0)
        return x + M;
    if (x >= M)
        return x - M;
    return x;
}


void noBorderProcessing(Mat src, Mat dst, float Kernel[][3])
{

    float sum;
    for (int y = 1; y < src.rows - 1; y++) {
        for (int x = 1; x < src.cols - 1; x++) {
            sum = 0.0;
            for (int k = -1; k <= 1;k++) {
                for (int j = -1; j <= 1; j++) {
                    sum = sum + Kernel[j + 1][k + 1] * src.at<uchar>(y - j, x - k);
                }
            }
            dst.at<uchar>(y, x) = sum;
        }
    }
}

void refletedIndexing(Mat src, Mat dst, float Kernel[][3])
{
    float sum, x1, y1;
    for (int y = 0; y < src.rows; y++) {
        for (int x = 0; x < src.cols; x++) {
            sum = 0.0;
            for (int k = -1;k <= 1; k++) {
                for (int j = -1;j <= 1; j++) {
                    x1 = reflect(src.cols, x - j);
                    y1 = reflect(src.rows, y - k);
                    sum = sum + Kernel[j + 1][k + 1] * src.at<uchar>(y1, x1);
                }
            }
            dst.at<uchar>(y, x) = sum;
        }
    }
}

void circularIndexing(Mat src, Mat dst, float Kernel[][3])
{
    float sum, x1, y1;
    for (int y = 0; y < src.rows; y++) {
        for (int x = 0; x < src.cols; x++) {
            sum = 0.0;
            for (int k = -1;k <= 1; k++) {
                for (int j = -1;j <= 1; j++) {
                    x1 = circular(src.cols, x - j);
                    y1 = circular(src.rows, y - k);
                    sum = sum + Kernel[j + 1][k + 1] * src.at<uchar>(y1, x1);
                }
            }
            dst.at<uchar>(y, x) = sum;
        }
    }
}

int main(int argc, char* argv[])
{

    Mat src, dst;
    string a;
    int b;

    cout << "Yuklemek istediginiz resmi giriniz." << endl;
    cin >> a;
    src = imread("C:\\Users\\merve\\OneDrive\\Masaüstü\\goruntuisleme\\" + a);

    cvtColor(src, src, COLOR_BGR2GRAY);
    if (!src.data)
    {
        return -1;
    }
    dst = src.clone();
    for (int y = 0; y < src.rows; y++)
        for (int x = 0; x < src.cols; x++)
            dst.at<uchar>(y, x) = 0.0;
    cout << "Lutfen bir filtre seciniz." << endl;
    cout << "1. Box Blur Filtresi" << endl;
    cout << "2. Gaussian Blur Fitresi" << endl;
    cout << "3. Edge Detection (Kenar Bulma) Islemi" << endl;
    cout << "4. Sharpen (Keskinlestirme) Islemi" << endl;
    cin >> b;
    if(b==1){
    float Kernel[3][3] = {
                          {1 / 9.0, 1 / 9.0, 1 / 9.0},
                          {1 / 9.0, 1 / 9.0, 1 / 9.0},
                          {1 / 9.0, 1 / 9.0, 1 / 9.0}
    };
    circularIndexing(src, dst, Kernel);
    }
    if (b ==2) {

        float Kernel[3][3] = {
                              {1 / 16.0, 2 / 16.0, 1 / 16.0},
                              {2 / 16.0, 4 / 16.0, 2 / 16.0},
                              {1 / 16.0, 2 / 16.0, 1 / 16.0}
        };
        circularIndexing(src, dst, Kernel);
    }
    if (b ==3) {
        float Kernel[3][3] = {
                              {-1.0, -1.0, -1.0},
                              {-1.0, 8.0, -1.0},
                              {-1.0, -1.0, -1.0}
        };
        circularIndexing(src, dst, Kernel);
    }
    if (b == 4) {
        float Kernel[3][3] = {
                              {0.0, -1.0, 0.0},
                              {-1.0, 5.0, -1.0},
                              {0.0, -1.0, 0.0}
        };
        circularIndexing(src, dst, Kernel);
    }

    namedWindow("Konvulasyon Islemlerinden Gecen Goruntunuz");
    imshow("Konvulasyon Islemlerinden Gecen Goruntunuz", dst);

    namedWindow("Giris Resminizin Gri Goruntusu");
    imshow("Giris Resminizin Gri Goruntusu", src);

    waitKey();


    return 0;
}


