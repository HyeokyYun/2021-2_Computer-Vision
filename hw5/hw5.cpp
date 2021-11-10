#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void whiteBalancing(Mat src);

int main()
{
	// To receive a input from user.
	int key;

	// Read Lena
	Mat lena;
	lena = imread("lena.png");
	if (lena.empty())
	{
		cout << "no lena file" << endl;
		return -1;
	}
	// Divede image's color space to 3, which are Blue, Green, and Red.
	vector<Mat> lenaChannels(3);

	// Read Colorful
	Mat colorful;
	colorful = imread("colorful.jpg");
	if (colorful.empty())
	{
		cout << "no colorful file" << endl;
		return -1;
	}
	// Divede image's color space to 3, which are Blue, Green, and Red.
	vector<Mat> colorfulChannels(3);

	// Read Balancing
	Mat balancing;
	balancing = imread("balancing.jpg");
	resize(balancing, balancing, Size(balancing.cols / 2, balancing.rows / 2));

	if (balancing.empty())
	{
		cout << "no balancing file" << endl;
		return -1;
	}
	// Divede image's color space to 3, which are Blue, Green, and Red.
	vector<Mat> balancingChannels(3);

	// Gamma Transformation
	MatIterator_<uchar> it, end;
	float gamma = 2.5f;
	unsigned char pix[256];

	while (1)
	{
		imshow("lena", lena);
		imshow("colorful", colorful);
		imshow("balancing", balancing);

		key = waitKey();
		switch (key)
		{
		// esc: To exit
		case 27:
			cout << "esc: Exit" << endl;
			return 0;

		// r: Reset
		case 114:
			cout << "r: Reset" << endl
				 << endl;
			lena = imread("lena.png");
			colorful = imread("colorful.jpg");
			balancing = imread("balancing.jpg");
			resize(balancing, balancing, Size(balancing.cols / 2, balancing.rows / 2));
			break;

		// Lena
		// n: Negative transformation
		case 110:
			cout << "n: Negative transformation" << endl;

			// convert the color BGR to HSV
			cvtColor(lena, lena, CV_BGR2HSV);
			/*
				Split image into 3 single-channel matrices.
				First parameter is input multi-channel array.
				Second parameter is output vector of array.
			*/
			split(lena, lenaChannels);
			for (int i = 0; i < lenaChannels[2].cols; i++)
			{
				for (int j = 0; j < lenaChannels[2].rows; j++)
				{
					lenaChannels[2].at<uchar>(i, j) = 255 - lenaChannels[2].at<uchar>(i, j);
				}
			}
			/*
				Merge single-channel matrix to multi-channel matrix.
				First parameter is array.
				Second paramter is output matrix.
			*/
			merge(lenaChannels, lena);
			// convert the color HSV to BRG
			cvtColor(lena, lena, CV_HSV2BGR);
			imshow("lena", lena);
			break;

		// g: Gamma transformation
		case 103:
			cout << "g: Gamma transformation" << endl;
			// convert the color BGR to HSV
			cvtColor(lena, lena, CV_BGR2HSV);
			/*
				Split image into 3 single-channel matrices.
				First parameter is input multi-channel array.
				Second parameter is output vector of array.
			*/
			split(lena, lenaChannels);
			for (int i = 0; i < 256; i++)
			{
				pix[i] = (uchar)(pow((float)(i / 255.0), gamma) * 255.0f);
			}

			for (it = lenaChannels[2].begin<uchar>(), end = lenaChannels[2].end<uchar>(); it != end; it++)
			{
				*it = pix[(*it)];
			}
			/*
				Merge single-channel matrix to multi-channel matrix.
				First parameter is array.
				Second paramter is output matrix.
			*/
			merge(lenaChannels, lena);
			cvtColor(lena, lena, CV_HSV2BGR);
			imshow("lena", lena);
			break;

		// h: Histogram Equalization
		case 104:
			cout << "h: Histogram Equalization" << endl;
			// Convert the color BRG to HSV
			cvtColor(lena, lena, CV_BGR2HSV);
			/*
				Split image into 3 single-channel matrices.
				First parameter is input multi-channel array.
				Second parameter is output vector of array.
			*/
			split(lena, lenaChannels);
			equalizeHist(lenaChannels[2], lenaChannels[2]);
			/*
				Merge single-channel matrix to multi-channel matrix.
				First parameter is array.
				Second paramter is output matrix.
			*/
			merge(lenaChannels, lena);
			cvtColor(lena, lena, CV_HSV2BGR);
			imshow("lena", lena);
			break;

		// Colorful
		// s: Color Slicing
		case 115:
			cout << "s: Color Slicing" << endl;
			// convert the color BGR to HSV
			cvtColor(colorful, colorful, CV_BGR2HSV);
			/*
				Split image into 3 single-channel matrices.
				First parameter is input multi-channel array.
				Second parameter is output vector of array.
			*/
			split(colorful, colorfulChannels);

			for (int i = 0; i < colorfulChannels[0].rows; i++)
			{
				for (int j = 0; j < colorfulChannels[0].cols; j++)
				{
					// Set the hue value from 9 to 23.
					if (colorfulChannels[0].at<uchar>(i, j) <= 9 || colorfulChannels[0].at<uchar>(i, j) >= 23)
						colorfulChannels[1].at<uchar>(i, j) = 0;
				}
			}
			/*
				Merge single-channel matrix to multi-channel matrix.
				First parameter is array.
				Second paramter is output matrix.
			*/
			merge(colorfulChannels, colorful);
			cvtColor(colorful, colorful, CV_HSV2BGR);
			imshow("colorful", colorful);
			break;

		// c: Color conversion
		case 99:
			cout << "c: Color conversion" << endl;
			// convert the color BGR to HSV
			cvtColor(colorful, colorful, CV_BGR2HSV);
			/*
				Split image into 3 single-channel matrices.
				First parameter is input multi-channel array.
				Second parameter is output vector of array.
			*/
			split(colorful, colorfulChannels);

			for (int i = 0; i < colorfulChannels[0].rows; i++)
			{
				for (int j = 0; j < colorfulChannels[0].cols; j++)
				{
					// If the hue value is greater than 129, than subtract 129, if not, add 50.
					if (colorfulChannels[0].at<uchar>(i, j) > 129)
						colorfulChannels[0].at<uchar>(i, j) = colorfulChannels[0].at<uchar>(i, j) - 129;
					else
						colorfulChannels[0].at<uchar>(i, j) += 50;
				}
			}
			/*
				Merge single-channel matrix to multi-channel matrix.
				First parameter is array.
				Second paramter is output matrix.
			*/
			merge(colorfulChannels, colorful);
			cvtColor(colorful, colorful, CV_HSV2BGR);
			imshow("colorful", colorful);
			break;

		// Balancing
		// a = Average Filtering
		case 97:
			cout << "a: Average Filtering" << endl;
			// convert the color BGR to HSV
			cvtColor(balancing, balancing, CV_BGR2HSV);
			/*
				Split image into 3 single-channel matrices.
				First parameter is input multi-channel array.
				Second parameter is output vector of array.
			*/
			split(balancing, balancingChannels);

			blur(balancingChannels[2], balancingChannels[2], Size(9, 9));
			/*
				Merge single-channel matrix to multi-channel matrix.
				First parameter is array.
				Second paramter is output matrix.
			*/
			merge(balancingChannels, balancing);
			cvtColor(balancing, balancing, CV_HSV2BGR);
			imshow("balancing", balancing);
			break;

		// w = White Balance
		case 119:
			cout << "w: White Balancing" << endl;
			whiteBalancing(balancing);
			imshow("balancing", balancing);
			break;
		}
	}
}

void whiteBalancing(Mat src)
{
	vector<Mat> ch(3);

	int b_sum = 0, g_sum = 0, r_sum = 0;
	int b_avg, g_avg, r_avg, b_tmp, g_tmp, r_tmp;

	int rows = src.rows;
	int cols = src.cols;
	int pixno = rows * cols;

	// split by B, G, R channel
	split(src, ch);
	uchar *b;
	uchar *g;
	uchar *r;

	// calculate each channel's average
	for (int i = 0; i < rows; i++)
	{
		b = ch[0].ptr<uchar>(i);
		g = ch[1].ptr<uchar>(i);
		r = ch[2].ptr<uchar>(i);
		for (int j = 0; j < cols; j++)
		{
			b_sum += b[j];
			g_sum += g[j];
			r_sum += r[j];
		}
	}
	b_avg = b_sum / pixno;
	g_avg = g_sum / pixno;
	r_avg = r_sum / pixno;

	// color balancing using gray world assuption
	for (int i = 0; i < rows; i++)
	{
		b = ch[0].ptr<uchar>(i);
		g = ch[1].ptr<uchar>(i);
		r = ch[2].ptr<uchar>(i);
		for (int j = 0; j < cols; j++)
		{
			// to prevent overflow
			/*
				All the average values are supposed to be 128,
				if the average is not 128, it makes the value to 128.
			*/
			b_tmp = (128 * b[j]) / b_avg;
			b_tmp > 255 ? b[j] = 255 : b[j] = b_tmp;

			g_tmp = (128 * g[j]) / g_avg;
			g_tmp > 255 ? g[j] = 255 : g[j] = g_tmp;

			r_tmp = (128 * r[j]) / r_avg;
			r_tmp > 255 ? r[j] = 255 : r[j] = r_tmp;
		}
	}
	// merge 3 channel's image
	merge(ch, src);
}