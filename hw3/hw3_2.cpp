#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	// Lena image
	Mat lena = imread("assets/Lena.png");
	Rect roi_1(0, 0, lena.size().width / 2, lena.size().height / 2);
	Mat lena_filtered = lena.clone();
	Mat dst1(lena_filtered, roi_1);
	blur(dst1, dst1, Size(7, 7));
	imshow("lena", lena);
	imshow("lena_filtered", lena_filtered);

	// Moon Image
	Mat moon = imread("assets/moon.png", 0);
	Mat moon_filtered = moon.clone();
	Mat dst2;
	Laplacian(moon_filtered, dst2, CV_16S);
	convertScaleAbs(dst2, dst2);
	Rect roi_2(moon.size().width / 2, moon.size().height / 2, moon.size().width, moon.size().height);
	scaleAdd(dst2, 1, moon_filtered, moon_filtered);
	imshow("moon", moon);
	imshow("moon_filtered", moon_filtered);

	// SaltnPepper Image
	Mat saltnpepper = imread("assets/saltnpepper.png", 0);
	Mat saltnpepper_filtered = saltnpepper.clone();

	medianBlur(saltnpepper, saltnpepper_filtered, 9);
	imshow("saltnpepper", saltnpepper);
	imshow("saltnpepper_filtered", saltnpepper_filtered);

	waitKey(0);
	return 0;
}