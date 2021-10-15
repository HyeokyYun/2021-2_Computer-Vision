#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat drawHistogram(Mat src);
void textInput(Mat src);

int main()
{
	// Read the image
	Mat moonImg = imread("moon.png", IMREAD_GRAYSCALE);
	Mat histImg, histGraph, histImgGraph;

	// Check image data
	if (moonImg.empty())
	{
		cout << "No Data Found." << endl;
		return -1;
	}

	// Histogram Equalization
	equalizeHist(moonImg, histImg);

	// Function of making histograms.
	histGraph = drawHistogram(moonImg);
	histImgGraph = drawHistogram(histImg);

	// write the text on the images
	textInput(moonImg);
	textInput(histImg);
	// original Image
	imshow("before", moonImg);
	// Hist Equalized Image
	imshow("after", histImg);
	// Histogram Graph
	imshow("h1", histGraph);
	// Hist Equalized Graph
	imshow("h2", histImgGraph);

	waitKey(0);
	return 0;
}

Mat drawHistogram(Mat src)
{
	Mat hist, histImage;

	// Establish the number of bins
	int i, hist_w, hist_h, bin_w, histSize;
	float range[] = {0, 256};
	const float *histRange = {range};

	hist_w = 512;
	hist_h = 512;
	histSize = 16;
	bin_w = cvRound((double)hist_w / histSize);

	// Draw Histogram
	histImage = Mat(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));

	// Compute Histogram
	/*
		&src: input image
		1: number of src image
		0: number channels numerated from 0 ~ channels()-1
		Mat(): optional mask
		hist: output histogram
		1: histogram dimension
		&histSize: array of histogram size
		&histRange: array of histogram's boundaries
	*/
	calcHist(&src, 1, 0, Mat(), hist, 1, &histSize, &histRange);

	// Normalize the result to [0, histImage.rows]
	/*
		hist: input Mat
		hist: output Mat
		0: lower range boundary of range normalization
		histImage.rows: upper range boundary
	*/
	normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	for (i = 0; i < histSize; i++)
	{
		// The function rectangle draws a rectangle outline or a filled rectangle whose two opposite corners are pt1 and pt2.
		/*
			histImage: image
			Point(): Vertex of the rectangle.
			Point(): Vertex of the rectangle opposite to point1.
			Scalar(): Brightness.
			-1: Thickness.
		*/
		rectangle(histImage, Point(bin_w * i, hist_h), Point(bin_w * i + hist_w / histSize, hist_h - cvRound(hist.at<float>(i))), Scalar(0, 0, 0), -1);
	}
	return histImage;
}

// Function that write the texts on images.
void textInput(Mat src)
{
	// Set the size of image.
	float hist_w, hist_h, bin_w;
	hist_w = src.rows;
	hist_h = src.cols;

	// Set the number of bins to 8
	int histSize = 8;
	bin_w = (double)hist_w / histSize;

	float range[] = {0, 256};
	const float *histRange = {range};

	Mat hist;
	calcHist(&src, 1, 0, Mat(), hist, 1, &histSize, &histRange);

	for (int i = 0; i < histSize; i++)
	{
		/*
			src: input image
			format(): input texts which is the value of input image
			Point(): the place to put the text
			FONT_HERSHEY_SIMPLEX: the font of text
			0.5: font scale
			Scalar(): color of text
			1: thickness of the text
			16: line type	
		*/
		putText(src, format("bin %d: %f", i + 1, cvRound(hist.at<float>(i)) / (hist_w * hist_h)), Point(10, 30 + i * 30), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0), 1, 16);
	}
}