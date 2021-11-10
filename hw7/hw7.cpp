#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	// Read images
	Mat finger_print = imread("images/finger_print.png", 0);
	Mat adaptive_image = imread("images/adaptive.png", 0);
	Mat adaptive1 = imread("images/adaptive_1.jpg", 0);

	if (finger_print.empty())
	{
		cout << "No finger_print image" << endl;
		return -1;
	}
	if (adaptive_image.empty())
	{
		cout << "No adaptive image" << endl;
		return -1;
	}
	if (adaptive1.empty())
	{
		cout << "No adaptive1 image" << endl;
		return -1;
	}

	adaptiveThreshold(finger_print, finger_print, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 7, 10);
	adaptiveThreshold(adaptive_image, adaptive_image, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 5, 10);
	adaptiveThreshold(adaptive1, adaptive1, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 7, 10);

	imshow("finger_print", finger_print);
	imshow("adaptive_image", adaptive_image);
	imshow("adaptive1", adaptive1);

	waitKey(0);
	return 0;
}