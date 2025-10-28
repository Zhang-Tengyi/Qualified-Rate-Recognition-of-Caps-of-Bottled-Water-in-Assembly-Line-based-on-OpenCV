#include<Opencv.hpp>
#include<iostream>
#include<string>
#include"bottle_body.h"
#include "main.h"
using namespace cv;
using namespace std;


//extern Mat cap_scan;

void bottle_body(Mat* body) {
	Rect rect(bottle_x_l[bottle_number_count] + 20, 288, bottle_xlength[bottle_number_count] + 80, 576);
	Mat body1 = *body;
	Mat part = body1(rect);  //提取黄框内容
	Mat clone2 = part.clone();

	std::vector<Mat> channels;
	split(part, channels);
	Mat Color_Split = channels[1];

	Mat dstImage(Color_Split.size(), Color_Split.type());//均值滤波处理
	blur(Color_Split, dstImage, Size(3, 3), Point(-1, -1), 1);

	Mat Outimage;
	threshold(dstImage, Outimage, 70, 255, CV_THRESH_BINARY);//二值化


	//漫水法
	Mat Outimage1, fill_ad, im_out;
	bitwise_not(Outimage, Outimage1);
	Mat fill = Outimage1.clone();
	Mat fill_add = Outimage1.clone();
	Rect roi;
	Mat mask = Mat::zeros(Size(Outimage1.cols + 2, Outimage1.rows + 2), CV_8U);
	floodFill(fill, mask, Point(0, 0), 255);
	bitwise_not(fill, fill_ad);
	im_out = fill_ad | fill_add;
//	namedWindow("im_out", 0);
//	imshow("im_out", im_out);

	Mat Blank1 = Mat::zeros(im_out.size(), CV_8UC3);

	vector<vector<Point>> contours;//轮廓
	vector<Vec4i> hierarchy;//存放轮廓结构变量
	findContours(im_out, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	//确定轮廓

	for (int i = 0; i < contours.size(); i++) {
		double selected_area;
		RotatedRect selected_Rect;
		RotatedRect rect_a = minAreaRect(contours[i]);
		double area = contourArea(contours[i]);

		if (area > 1000 && area < 2000) {//15000 25000
			selected_area = area;
			selected_Rect = rect_a;
		}

		Point2f P[4];
		double k1, y, x;
		selected_Rect.points(P);
		for (int j = 0; j <= 3; j++) {
			y = P[(j + 1) % 4].y - P[j].y;
			x = P[(j + 1) % 4].x - P[j].x;
			k1 = y / x;
			if (k1 < 1 && k1>-1 ) {
				k_body = k1;
				line(clone2, P[j], P[(j + 1) % 4], Scalar(0, 255, 255), 2);
			}
			line(clone2, P[j], P[(j + 1) % 4], Scalar(0, 255, 255), 2);
		}
	}

//	namedWindow("clone2", 0);
//	imshow("clone2", clone2);

	return;

}