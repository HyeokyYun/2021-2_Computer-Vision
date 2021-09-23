#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat image = imread("lena.png", 0); // imread()함수를 통해 이미지 불러옴.
	Mat negative_img = image.clone(); // image.clone()함수를 통해 image의 정보를 negative_img에 복제한다.
	Mat f_img, log_img;
	Mat gamma_img;

	// Negative Transformation
	for (int i = 0; i < image.rows; i++) // 반복문에 .at 오퍼레이터를 사용해 입력된 이미지의 픽셀에 접근한다.
		for (int j = 0; j < image.cols; j++)
			negative_img.at<uchar>(i, j) = 255 - image.at<uchar>(i, j); // 각각 접근한 픽셀값을 255에서 빼준다. 그 이유는 픽셀값이 완전히 반대로 되어야 하기 때문이다.

	// Log Transformation
	double c = 1.5f; // scale constant, 상수는 아무 값이나 상관 없다.
	image.convertTo(f_img, CV_32F); // 32비트 플로트 타입을 가진 메트릭스로 변환 시킨다. 그 이유는 로그 함수를 활용할 때에 적용할 수 있는 타입이 플로트이기 때문이다.
	f_img = abs(f_img) + 1; // 절대값을 취하고 1을 더한다.
	log(f_img, f_img); // 로그 함수를 사용한다. 로그함수를 사용하면 0~255가 아닌 특정한 값이 나온다.
	normalize(f_img, f_img, 0, 255, NORM_MINMAX); // normalize image to (0~255), 이 특정한 값을 normalize을 통해 정규화 시켜준다.
	convertScaleAbs(f_img, log_img, c); // scaling by c, conversion to an unsigned 8-bit type, 입력영상을 원 영상으로 변환을 시켜주는데 8비트로 변환시켜준다.

	// Gamma Transformation
	MatIterator_<uchar> it, end; // 픽셀엑세스를 위해 matiterator를 사용한다.
	float gamma = 0.5;
	unsigned char pix[256];
	for (int i = 0; i < 256; i++)
	{
		pix[i] = saturate_cast<uchar>(pow((float)(i / 255.0), gamma) * 255.0f);
	} // s = cr^y 의 식에서 r값이 크면 그 결과가 너무 커질 수 있기 때문에 0~255의 값을 255로 나눠줘서 0~1 사이의 숫자로 만들어 준다. 그리고 그 값들을 pix배열에 넣는다.
	gamma_img = image.clone();
	for (it = gamma_img.begin<uchar>(), end = gamma_img.end<uchar>(); it != end; it++)
	{
		*it = pix[(*it)];
	} // pix 배열에 담긴 값들은 각각의 픽셀 값들로 이미지를 출력하게 된다.

	imshow("Input image", image);
	imshow("Negative Transformation", negative_img);
	imshow("Log Transformation", log_img);
	imshow("Gamma Transformation", gamma_img);

	waitKey(0);
	return 0;
}
