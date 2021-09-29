#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
String Path = "./data";
int main()
{
	// Read an image "lena.png"
	Mat lena = imread("assets/Lena.png", IMREAD_COLOR);
	Rect R1(0, 0, lena.size().width / 2, lena.size().height);
	Mat lena_filtered = lena.clone();
	Mat dst1(lena_filtered, R1);
	blur(dst1, dst1, Size(7, 7));
	imshow("lena", lena);
	imshow("lena_filtered", lena_filtered);
	// Read an image "moon.png"
	Mat moon = imread("assets/moon.jpg", IMREAD_COLOR);
	Mat moon_filtered = moon.clone();
	Mat dst2;
	Laplacian(moon_filtered, dst2, CV_16S);
	convertScaleAbs(dst2, dst2);
	Rect R2(0, 0, moon.size().width / 2, moon.size().height);
	Mat dst3(dst2, R2);
	dst3 = Mat::zeros(dst3.size(), dst3.type());
	scaleAdd(dst2, 1, moon_filtered, moon_filtered);
	imshow("moon", moon);
	imshow("moon_filtered", moon_filtered);
	// Read an image "saltnpepper.png"
	Mat saltnpepper = imread("assets/saltnpepper.png", IMREAD_COLOR);
	Mat saltnpepper_filtered = moon.clone();
	medianBlur(saltnpepper, saltnpepper_filtered, 9);
	imshow("saltnpepper", saltnpepper);
	imshow("saltnpepper_filtered", saltnpepper_filtered);
	waitKey(0);
	return 0;
}