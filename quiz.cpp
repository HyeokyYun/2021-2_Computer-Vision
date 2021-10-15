#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("pic.jpg");
	Mat fixed2;
	Mat img_filter = img.clone();
	Laplacian(img, fixed2, CV_16S);
	convertScaleAbs(fixed2, fixed2);
	Rect roi_2(0, 0, img.size().width, img.size().height);
	scaleAdd(fixed2, 1, img, img_filter);
	imshow("original", img);
	imshow("filter", img_filter);
	waitKey(0);
}