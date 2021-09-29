#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	// Image Read by imread() method.
	Mat lena_img = imread("assets/Lena.png");
	Mat moon_img = imread("assets/moon.png");
	Mat saltnpepper_img = imread("assets/saltnpepper.png");

	// Lena Image
	/*
		Using blur method to make the Lena image to blur.
	*/

	/*
	1. Use Rect class to set the size to blur, which is left half of the image.
	2. Set the start point at 0, 0. 
	3. Set the end width and end height, which are the end of picture, use size() method divided by 2.
	4. Make a clone of original Lena image.
	5. Set the fixed1 method to add the region with cloned image of Lena.
	6. Use blur() method to make the image to blur with setted region and set the Size to 7. 
	*/
	Rect roi_1(0, 0, lena_img.size().width / 2, lena_img.size().height / 2);
	Mat lena_filtered = lena_img.clone();
	Mat fixed1(lena_filtered, roi_1);
	blur(fixed1, fixed1, Size(7, 7));
	imshow("lena", lena_img);
	imshow("lena_filtered", lena_filtered);

	// Moon Image
	/*
	Using Laplacian filter
	*/
	/*
	1. Clone the original moon image to moon_filtered.
	2. Make a variable fixed2, which will be used for Laplacian filter.
	3. Use Laplacian() method to change the moon picture with type of CV_16S which is 16-bit signed integer.
	4. Convert it to absolute value.
	5. Use scaleAdd() method to change it sharpen. 
	*/
	Mat moon_filtered = moon_img.clone();
	Mat fixed2;
	Laplacian(moon_filtered, fixed2, CV_16S);
	convertScaleAbs(fixed2, fixed2);
	Rect roi_2(moon_img.size().width / 2, moon_img.size().height / 2, moon_img.size().width, moon_img.size().height);
	scaleAdd(fixed2, 1, moon_filtered, moon_filtered);
	imshow("moon", moon_img);
	imshow("moon_filtered", moon_filtered);

	// SaltnPepper Image
	/*
	Using medianBlur
	*/
	/*
	1. Clone the original image of saltnpepper
	2. Use medianBlur method to filter the image.
	*/
	Mat saltnpepper_filtered = saltnpepper_img.clone();

	medianBlur(saltnpepper_img, saltnpepper_filtered, 9);
	imshow("saltnpepper", saltnpepper_img);
	imshow("saltnpepper_filtered", saltnpepper_filtered);

	waitKey(0);
	return 0;
}