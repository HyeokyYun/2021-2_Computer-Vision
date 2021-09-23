#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat image_blur, AvgImg; // blur
	Mat image_sharp, laplacian, abs_laplacian, sharpening; // sharpening

	image_blur = imread("assets/Lena.png");
	image_sharp = imread("assets/moon.png", 0);

	// Using Average Filter
	/*
	blur(input_image, output_image, Size(x, y));
	*/
	blur(image_blur, AvgImg, Size(7,7));

	// Sharpening
	/*
	1. Calculate the Laplacian of an image
	2. convert it to absolute value
	3. add it to original image
	*/
	//GaussianBlur(image_sharp, image_sharp, Size(3,3), 0, 0, BORDER_DEFAULT);
	Laplacian(image_sharp, laplacian, CV_16S, 1, 1, 0);
	convertScaleAbs(laplacian, abs_laplacian);
	sharpening = abs_laplacian + image_sharp;

	imshow("Original Blur Image", image_blur);
	imshow("Blur Image", AvgImg);

	imshow("Original Sharpening Image", image_sharp);
	imshow("Sharpengin Image", sharpening);

	waitKey(0);
	return 0;
}