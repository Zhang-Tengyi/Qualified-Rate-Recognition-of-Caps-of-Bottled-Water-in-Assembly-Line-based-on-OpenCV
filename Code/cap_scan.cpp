#include<Opencv.hpp>
#include<iostream>
#include<string>
#include "main.h"
using namespace cv;
using namespace std;


//extern Mat cap_scan;

void cap_scan(Mat* cap) {
	Rect rect(bottle_x_l[bottle_number_count] + 20, 8, bottle_xlength[bottle_number_count]+50, 360);
	Mat cap1 = *cap;
	Mat part = cap1(rect);  //提取黄框内容
	Mat clone1 = part.clone();

	std::vector<Mat> channels;
	split(part, channels);
	Mat Color_Split = channels[1];

	Mat dstImage(Color_Split.size(), Color_Split.type());//均值滤波处理
	blur(Color_Split, dstImage, Size(3, 3), Point(-1, -1), 1);

	Mat Outimage, Outimage_depth, Outimage_bw;
	threshold(dstImage, Outimage, 70, 255, CV_THRESH_BINARY);//二值化

	bitwise_not(Outimage, Outimage_bw);


	//漫水法
	Mat fill_ad, im_out;
	//bitwise_not(Outimage, Outimage1);
	Mat fill = Outimage_bw.clone();
	Mat fill_add = Outimage_bw.clone();
	Rect roi;
	Mat mask = Mat::zeros(Size(Outimage_bw.cols + 2, Outimage_bw.rows + 2), CV_8U);
	floodFill(fill, mask, Point(0, 0), 255);
	bitwise_not(fill, fill_ad);
	im_out = fill_ad | fill_add;

//	namedWindow("im_out", 0);
//	imshow("im_out", im_out);

	Mat Blank_cap = Mat::zeros(im_out.size(), CV_8UC3);

	CvPoint2D32f rectpoint[4];
	vector<vector<Point>> contours;//轮廓
	vector<Vec4i> hierarchy;//存放轮廓结构变量
	findContours(im_out, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	//确定轮廓

	for (int i = 0; i < contours.size(); i++) {
	
		double selected_area = 0;
		RotatedRect selected_Rect;
		RotatedRect rect_a = minAreaRect(contours[i]);
		double area = contourArea(contours[i]);

		if (area > 1728) {//10000
			selected_area = area;
			selected_Rect = rect_a;
			R_n = R_n + 1;
			cvBoxPoints(selected_Rect, rectpoint);
			double rectarea = selected_Rect.size.width * selected_Rect.size.height;
			rate = selected_area / rectarea;
		}

		Point2f P[4];

		double k1, y, x;
		selected_Rect.points(P);
		for (int j = 0; j <= 3; j++) {
			line(clone1, P[j], P[(j + 1) % 4], Scalar(0, 255, 255), 2);
			

			if (R_n == 1) {
				y = P[(j + 1) % 4].y - P[j].y;
				x = P[(j + 1) % 4].x - P[j].x;
				k1 = y / x;
				if (k1 < 1 && k1>-1) {
					k_cap = k1;
				}
				cap_selected_area = selected_area;
			}
			if (R_n == 2) {
				y = P[(j + 1) % 4].y - P[j].y;
				x = P[(j + 1) % 4].x - P[j].x;
				k1 = y / x;
				if (k1 < 1 && k1>-1) {
					k_cap1 = k1;
				}
			}
		}
	}

//	namedWindow("clone1", 0);
//	imshow("clone1", clone1);

	int  leftup_y=0, leftup_x1 = 0,  biaozhi=0;
	int leftup_x = 0, leftup_y1 = 0;
	vector<vector<Point>> contours1;//轮廓
	vector<Vec4i> hierarchy1;//存放轮廓结构变量
	findContours(im_out, contours1, hierarchy1, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	//确定轮廓
	vector<Rect> boundRect(contours1.size());
	for (int i = 0; i < contours1.size(); i++) {
		boundRect[i] = boundingRect(Mat(contours1[i]));
		double area = contourArea(contours1[i]);
		if (area > 5184) { //30000
			rectangle(part, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 255), 2, 8, 0);
			leftup_y = boundRect[i].tl().y;
			biaozhi = biaozhi + 1;
		}
		else {
			leftup_y1 = boundRect[i].tl().y;
		}
	}
	Point textP;
	if (biaozhi == 0) {
		textY = leftup_y1 - 10;
	}
	else {
		textY = leftup_y - 10;
	}
	
	*cap = part;

	return;

}