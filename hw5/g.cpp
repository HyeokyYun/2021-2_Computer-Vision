#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{

	Mat lena, colorful, balancing;
	Mat lena_channels[3];
	Mat colorful_channels[3];
	Mat balancing_channels[3];

	lena = imread("lena.png");
	colorful = imread("colorful.jpg");
	balancing = imread("balancing.jpg");

	int key;
	int row, col;
	int total_B, total_G, total_R, average_B, average_G, average_R;
	int hue;

	//For gamma transformation
	MatIterator_<uchar> it, end;
	float gamma;
	unsigned char pix[256]; //pixel type

	while (1)
	{

		imshow("lena", lena);
		imshow("colorful", colorful);
		imshow("balancing", balancing);

		key = waitKey();
		switch (key)
		{

		// lena
		case 110: //n: Negative transformation
			cvtColor(lena, lena, CV_BGR2HSV);
			split(lena, lena_channels);
			for (row = 0; row < lena.rows; row++)
			{
				for (col = 0; col < lena.cols; col++)
				{
					lena_channels[2].at<uchar>(row, col) = 255 - lena_channels[2].at<uchar>(row, col);
				}
			}
			merge(lena_channels, 3, lena);
			cvtColor(lena, lena, CV_HSV2BGR);
			break;

		case 103: //g: gamma transformation
			cvtColor(lena, lena, CV_BGR2HSV);
			split(lena, lena_channels);

			gamma = 2.5f;
			for (int i = 0; i < 256; i++)
				pix[i] = (uchar)(pow((float)(i / 255.0), gamma) * 255.0f); //pre compute possible case

			for (it = lena_channels[2].begin<uchar>(), end = lena_channels[2].end<uchar>(); it != end; it++)
				*it = pix[(*it)];

			merge(lena_channels, 3, lena);
			cvtColor(lena, lena, CV_HSV2BGR);
			break;

		case 104: //h: Histogram equalization
			cvtColor(lena, lena, CV_BGR2HSV);
			split(lena, lena_channels);
			equalizeHist(lena_channels[2], lena_channels[2]); // equalize V of HSV
			merge(lena_channels, 3, lena);
			cvtColor(lena, lena, CV_HSV2BGR);
			break;

		// colorful
		case 115: //s: Color Slicing
			cvtColor(colorful, colorful, CV_BGR2HSV);
			split(colorful, colorful_channels);
			for (row = 0; row < colorful.rows; row++)
			{
				for (col = 0; col < colorful.cols; col++)
				{
					hue = colorful_channels[0].at<uchar>(row, col);
					if (hue <= 9 || hue >= 23)
						colorful_channels[1].at<uchar>(row, col) = 0;
				}
			}
			merge(colorful_channels, 3, colorful);
			cvtColor(colorful, colorful, CV_HSV2BGR);
			break;

		case 99: //c: Color Conversion
			cvtColor(colorful, colorful, CV_BGR2HSV);
			split(colorful, colorful_channels);
			for (row = 0; row < colorful.rows; row++)
			{
				for (col = 0; col < colorful.cols; col++)
				{
					if (colorful_channels[0].at<uchar>(row, col) < 129)
						colorful_channels[0].at<uchar>(row, col) = colorful_channels[0].at<uchar>(row, col) + 50;
					else
						colorful_channels[0].at<uchar>(row, col) = colorful_channels[0].at<uchar>(row, col) - 129;
				}
			}
			merge(colorful_channels, 3, colorful);
			cvtColor(colorful, colorful, CV_HSV2BGR);
			break;

		// balancing
		case 97: //a: Average filtering
			cvtColor(balancing, balancing, CV_BGR2HSV);
			split(balancing, balancing_channels);
			blur(balancing_channels[2], balancing_channels[2], Size(9, 9));
			merge(balancing_channels, 3, balancing);
			cvtColor(balancing, balancing, CV_HSV2BGR);
			break;

		case 119: //w: White balancing
			total_B = 0;
			total_G = 0;
			total_R = 0;

			for (row = 0; row < balancing.rows; row++)
			{
				for (col = 0; col < balancing.cols; col++)
				{
					total_B = total_B + balancing.at<Vec3b>(row, col)[0];
					total_G = total_G + balancing.at<Vec3b>(row, col)[1];
					total_R = total_R + balancing.at<Vec3b>(row, col)[2];
				}
			}

			average_B = total_B / (balancing.rows * balancing.cols);
			average_G = total_G / (balancing.rows * balancing.cols);
			average_R = total_R / (balancing.rows * balancing.cols);

			for (row = 0; row < balancing.rows; row++)
			{
				for (col = 0; col < balancing.cols; col++)
				{
					balancing.at<Vec3b>(row, col)[0] = balancing.at<Vec3b>(row, col)[0] * 128 / average_B;
					balancing.at<Vec3b>(row, col)[1] = balancing.at<Vec3b>(row, col)[1] * 128 / average_G;
					balancing.at<Vec3b>(row, col)[2] = balancing.at<Vec3b>(row, col)[2] * 128 / average_R;
				}
			}
			break;

		// reset
		case 114: //r: reset all
			lena = imread("lena.png");
			colorful = imread("colorful.jpg");
			balancing = imread("balancing.jpg");
			break;

		//exit
		case 27: //esc
			cout << "esc" << endl;
			return 0;
		}
	}
}