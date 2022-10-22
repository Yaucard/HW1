#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"


#include <stdlib.h>
#include <stdio.h>
#include<iostream>

using namespace cv;
using namespace std;


void Morphology1(int, void*);
void Morphology2(int, void*);
int morph_elem = 0;
int morph_size = 1;

double start, stop, close,open;

Mat img, img2, img3,imgopen,imgclose;

int main(int argc, char const* argv[]) {

    
    cv::setUseOptimized(false);

    
    bool simd1 = checkHardwareSupport(CV_CPU_AVX);
    cout << "CV_CPU_AVX 優化狀態：" << simd1 << endl;

    int i = 0;
    img = imread("in000001.jpg");     //抓照片
    cvtColor(img, img2, COLOR_RGB2GRAY);  //做灰皆

    double thresh = 128;     //判定界線
    double maxValue = 255;   

    threshold(img2, img3, thresh, maxValue, THRESH_BINARY); //做二值化
    
    imshow("視窗", img3); //視窗顯示
    
    start = static_cast<double>(getTickCount());    //記錄當前時刻CPU時鐘週期
    for(i=0;i<100;i++)
    {
        Morphology1(0, 0);
    }  
    stop = static_cast<double>(getTickCount());     //記錄程式執行結束CPU時鐘週期
    open = ((double)(stop - start)) / getTickFrequency(); //計算時間，以秒為單位
    cout << " open run time: " << open << "s" << endl;

    start = static_cast<double>(getTickCount());    //記錄當前時刻CPU時鐘週期
    for (i = 0; i < 100; i++)
    {
        Morphology2(0, 0);
    }
    stop = static_cast<double>(getTickCount());     //記錄程式執行結束CPU時鐘週期
    close = ((double)(stop - start)) / getTickFrequency(); //計算時間，以秒為單位
    cout << "close run time: " << close << "s" << endl;

    waitKey(0);
    return 0;
 }

 void Morphology1(int, void*)
 {
     // Since MORPH_X : 2,3,4,5 and 6
     int operation = 2;

     Mat element = getStructuringElement(morph_elem, Size(2 * morph_size + 1, 2 * morph_size + 1), Point(morph_size, morph_size));

     /// Apply the specified morphology operation
     morphologyEx(img3, imgopen, operation, element);
     imshow("open 100", imgopen);
 }
 void Morphology2(int, void*)
 {
     // Since MORPH_X : 2,3,4,5 and 6
     int operation = 3;

     Mat element = getStructuringElement(morph_elem, Size(2 * morph_size + 1, 2 * morph_size + 1), Point(morph_size, morph_size));

     /// Apply the specified morphology operation
     morphologyEx(img3, imgclose, operation, element);
     imshow("colse 100", imgclose);
 }