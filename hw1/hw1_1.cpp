#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat frame; // 메트릭스 선언
	VideoCapture cap; // cap 이라는 비디오 캡처 클래스 선언
	if (cap.open("background.mp4") == 0) // 비디오 파일 오픈
		return -1;
	double fps = cap.get(CAP_PROP_FPS); // CAP_PROP_FPS메소드를 사용해 frame rate 확인
	double time_in_msec = 0; // 현재 재생되고 있는 시간 0으로 초기화
	int curr_frame = 0; // 현재 재생되고 있는 프레임 0으로 초기화
	int total_frames = cap.get(CAP_PROP_FRAME_COUNT); // CAP_PROP_FRAME_COUNT메소드를 사용해 동영상의 전체 프레임을 구해준다.
	// video stops after 3 sec
	while (time_in_msec < 3000) // time_in_msec가 밀리세컨이기 때문에 일반 초로 변환 후 3초 동안 실행 조건
	{
		cap >> frame; // 
		if (frame.empty()) // 비디오의 끝에 도달했는지의 여부 파악
			break;
		time_in_msec = cap.get(CAP_PROP_POS_MSEC); // 현재 재생되는 시간이 들어감.
		curr_frame = cap.get(CAP_PROP_POS_FRAMES); // 현재 재생되는 프레임이 들어감.
		// printing current frames over total frames
		cout << "frames: " << curr_frame << " / " << total_frames << endl;
		imshow("video", frame); // imshow()함수를 통해 비디오 재생
		// calculating the right delay from given fps
		waitKey(1000 / fps); // 초당 재생하는 영상수를 1초 단위로 파악하여 기다린다. 
	}
	waitKey(0);
	return 0;
}
