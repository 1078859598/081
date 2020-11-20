#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
	cv::Mat srcMat = imread("C:/Users/HS/Desktop/1.jpg", 0);
	cv::Mat resultMat = imread("C:/Users/HS/Desktop/1.jpg");

	cv::Mat BinaryMat;

	threshold(srcMat, BinaryMat, 125, 175, THRESH_BINARY_INV);


	
	//Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	//morphologyEx(BinaryMat, OpenMat, MORPH_OPEN, element);

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(BinaryMat, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	for (int i = 0; i < contours.size(); i++) {
		RotatedRect rbox = minAreaRect(contours[i]);

		float width = (float)rbox.size.width;
		float height = (float)rbox.size.height;
		float ratio = width / height;
		float pixel = width * height;
		if (pixel > 1000) {
			if (fabs(ratio - 1) < 0.1) {
				cv::Point2f vtx[4];
				rbox.points(vtx);
				for (int i = 0; i < 4; ++i) {
					cv::line(resultMat, vtx[i], vtx[i < 3 ? i + 1: 0], cv::Scalar(0, 0, 255), 2, CV_AA);
				}
				drawContours(resultMat, contours, i, Scalar(0, 255, 255), -1, 8);
			}

		}
	}
	imshow("srcMat", srcMat);
	imshow("B", BinaryMat);
	imshow("Result", resultMat);
	waitKey(0);

}