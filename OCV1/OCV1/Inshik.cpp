#include <filesystem>
#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void black_image(Mat img);
void white_image(Mat img);

int main() {
	cout << "안녕 ㅋㅋ루삥뽕아. 무슨 이미지? (input = 이름.확장자)" << endl;

	string path = "images";
	vector<string> images;
	for (const auto& entry : filesystem::directory_iterator(path))
		cout << entry.path() << endl;

	string selected;
	cin >> selected;
	
	Mat img = imread("images/" + selected, IMREAD_GRAYSCALE);
	if (img.empty()) {
		cout << "응 그런거 없어~" << endl;
		return 1;
	}

	cout << "톤이 하양이냐 검정이냐 [white/black]" << endl;
	string color;
	cin >> color;

	if (color == "white") {
		white_image(img);
	}
	else if (color == "black") {
		black_image(img);
	}
	else {
		cout << "응 그런거 없어~" << endl;
		return 1;
	}

	cout << "어 그래 그럼 잘가" << endl;
	return 1;
}

void white_image(Mat img) {
	img = ~img;

	Mat bin;
	threshold(img, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);

	Mat labels, stats, centroids;
	int cnt = connectedComponentsWithStats(bin, labels, stats, centroids);

	Mat dst;
	cvtColor(img, dst, COLOR_GRAY2BGR);

	for (int i = 1; i < cnt; i++) {
		int* p = stats.ptr<int>(i);
		if (p[4] < 20) continue;

		rectangle(dst, Rect(p[0], p[1], p[2], p[3]), Scalar(255, 0, 0), 2);
	}

	dst = ~dst;
	imshow("dst", dst);
	waitKey();
	destroyAllWindows();
}

void black_image(Mat img) {

	Mat bin; 
	threshold(img, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);

	Mat labels, stats, centroids;
	int cnt = connectedComponentsWithStats(bin, labels, stats, centroids);

	Mat dst;
	cvtColor(img, dst, COLOR_GRAY2BGR);

	for (int i = 1; i < cnt; i++) {
		int* p = stats.ptr<int>(i);
		if (p[4] < 20) continue;

		rectangle(dst, Rect(p[0], p[1], p[2], p[3]), Scalar(0, 255, 255), 2);
	}

	imshow("dst", dst);
	waitKey();
	destroyAllWindows();
}