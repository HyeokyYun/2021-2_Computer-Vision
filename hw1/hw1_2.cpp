#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat image = imread("lena.png", 0);
	Mat negative_img = image.clone();
	Mat f_img, log_img;
	Mat gamma_img;

	// Negative Transformation
	for (int i = 0; i < image.rows; i++)
		for (int j = 0; j < image.cols; j++)
			negative_img.at<uchar>(i, j) = 255 - image.at<uchar>(i, j);

	// Log Transformation
	double c = 1.5f; // scale constant
	image.convertTo(f_img, CV_32F);
	f_img = abs(f_img) + 1;
	log(f_img, f_img);
	normalize(f_img, f_img, 0, 255, NORM_MINMAX); // normalize image to (0~255)
	convertScaleAbs(f_img, log_img, c);			  // scaling by c, conversion to an unsigned 8-bit type

	// Gamma Transformation
	MatIterator_<uchar> it, end;
	float gamma = 0.5;
	unsigned char pix[256];
	for (int i = 0; i < 256; i++)
	{
		pix[i] = saturate_cast<uchar>(pow((float)(i / 255.0), gamma) * 255.0f);
	}
	gamma_img = image.clone();
	for (it = gamma_img.begin<uchar>(), end = gamma_img.end<uchar>(); it != end; it++)
	{
		*it = pix[(*it)];
	}

	imshow("Input image", image);
	imshow("Negative Transformation", negative_img);
	imshow("Log Transformation", log_img);
	imshow("Gamma Transformation", gamma_img);

	waitKey(0);
	return 0;
}