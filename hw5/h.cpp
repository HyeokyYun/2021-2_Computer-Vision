#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void balance_white(Mat mat);

//Path needs to be modified.
String path = "./data";

int main()
{

	// Read an image "lena.png"
	Mat lena = imread("lena.png", IMREAD_COLOR);
	if (lena.empty())
	{
		cout << "Missing lena!" << endl;
		return 0;
	}

	// Read an image "colorful.png"
	Mat colorful = imread("colorful.jpg", IMREAD_COLOR);
	if (colorful.empty())
	{
		cout << "Missing colorful!" << endl;
		return 0;
	}

	// Read an image "balancing.png"
	Mat balancing = imread("balancing.jpg", IMREAD_COLOR);
	if (balancing.empty())
	{
		cout << "Missing balancing!" << endl;
		return 0;
	}

	Mat lena_Huv, colorful_Hsv;

	cvtColor(lena, lena_Huv, COLOR_BGR2HSV);

	Mat lena_target = lena_Huv.clone();

	MatIterator_<uchar> it, end;
	float gamma = 0.5;
	unsigned char pix[256];

	cvtColor(colorful, colorful_Hsv, COLOR_BGR2HSV);

	Mat colorful_target = colorful_Hsv.clone();

	vector<Mat> ch(3);

	Mat balancing_target = balancing.clone();

	imshow("lena", lena);
	imshow("colorful", colorful);
	imshow("balancing", balancing);

	bool isRun = true;
	while (isRun)
	{
		int k = waitKey(10000);

		if (k == -1)
			cout << "There's no key input for 10 seconds." << endl;
		else if (k == 27)
			cout << "ESC was pressed\n"
				 << endl;
		else
			printf("%c was pressed\n", k);

		switch (k)
		{
		case 'R':
		case 'r':
			lena_target = lena_Huv.clone();
			colorful_target = colorful_Hsv.clone();
			balancing_target = balancing.clone();

			imshow("lena", lena);
			imshow("colorful", colorful);
			imshow("balancing", balancing);

			break;

		case 'N':
		case 'n':
			split(lena_target, ch);
			for (int i = 0; i < ch[2].rows; i++)
				for (int j = 0; j < ch[2].cols; j++)
					ch[2].at<uchar>(i, j) = 255 - ch[2].at<uchar>(i, j);

			merge(ch, lena_target);

			cvtColor(lena_target, lena_target, COLOR_HSV2BGR);

			imshow("lena", lena_target);

			cvtColor(lena_target, lena_target, COLOR_BGR2HSV);
			break;

		case 'G':
		case 'g':
			split(lena_target, ch);
			for (int i = 0; i < 256; i++)
			{
				pix[i] = saturate_cast<uchar>(pow(((float)i / 255.0), gamma) * 255.0f);
			}
			for (it = ch[2].begin<uchar>(), end = ch[2].end<uchar>(); it != end; it++)
			{
				*it = pix[(*it)];
			}
			merge(ch, lena_target);

			cvtColor(lena_target, lena_target, COLOR_HSV2BGR);

			imshow("lena", lena_target);

			cvtColor(lena_target, lena_target, COLOR_BGR2HSV);
			break;

		case 'H':
		case 'h':
			split(lena_target, ch);

			equalizeHist(ch[2], ch[2]);

			merge(ch, lena_target);

			cvtColor(lena_target, lena_target, COLOR_HSV2BGR);

			imshow("lena", lena_target);

			cvtColor(lena_target, lena_target, COLOR_BGR2HSV);
			break;

		case 'S':
		case 's':
			split(colorful_target, ch);

			for (int i = 0; i < ch[0].rows; i++)
				for (int j = 0; j < ch[0].cols; j++)
					if (23 <= ch[0].at<uchar>(i, j) || ch[0].at<uchar>(i, j) <= 9) //Hue value: 9<hue<23
						ch[1].at<uchar>(i, j) = 0;

			merge(ch, colorful_target);

			cvtColor(colorful_target, colorful_target, COLOR_HSV2BGR);

			imshow("colorful", colorful_target);

			cvtColor(colorful_target, colorful_target, COLOR_BGR2HSV);

			break;

		case 'C':
		case 'c':
			split(colorful_target, ch);

			for (int i = 0; i < ch[0].rows; i++)
				for (int j = 0; j < ch[0].cols; j++)
					if (129 <= ch[0].at<uchar>(i, j) + 50) //hue values bigger than 129
						ch[0].at<uchar>(i, j) = ch[0].at<uchar>(i, j) + 50 - 129;
					else
						ch[0].at<uchar>(i, j) += 50;

			merge(ch, colorful_target);

			cvtColor(colorful_target, colorful_target, COLOR_HSV2BGR);

			imshow("colorful", colorful_target);

			cvtColor(colorful_target, colorful_target, COLOR_BGR2HSV);

			break;

		case 'A':
		case 'a':

			blur(balancing_target, balancing_target, Size(9, 9));

			imshow("balancing", balancing_target);

			break;

		case 'W':
		case 'w':
			balance_white(balancing_target);

			imshow("balancing", balancing_target);

			break;

		case 27:
		case -1: // pressed esc or if no key pressed before 10 seconds
			isRun = false;

		default:
			break;
		}
	}
	return 0;
}

void balance_white(Mat mat)
{

	vector<Mat> ch(3);

	int b_sum = 0, g_sum = 0, r_sum = 0;
	int b_avg, g_avg, r_avg, b_tmp, g_tmp, r_tmp;

	int rows = mat.rows;
	int cols = mat.cols;
	int pixel = rows * cols;
	// split by B, G, R channel
	split(mat, ch);
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
	b_avg = b_sum / pixel;
	g_avg = g_sum / pixel;
	r_avg = r_sum / pixel;

	// color balancing using gray world assumsption
	for (int i = 0; i < rows; i++)
	{
		b = ch[0].ptr<uchar>(i);
		g = ch[1].ptr<uchar>(i);
		r = ch[2].ptr<uchar>(i);
		for (int j = 0; j < cols; j++)
		{
			// to prevent overflow
			b_tmp = (128 * b[j]) / b_avg;
			b_tmp > 255 ? b[j] = 255 : b[j] = b_tmp;

			g_tmp = (128 * g[j]) / g_avg;
			g_tmp > 255 ? g[j] = 255 : g[j] = g_tmp;

			r_tmp = (128 * r[j]) / r_avg;
			r_tmp > 255 ? r[j] = 255 : r[j] = r_tmp;
		}
	}
	merge(ch, mat);
}
