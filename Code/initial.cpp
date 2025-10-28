#include<Opencv.hpp>
#include<iostream>
#include<string>
#include"main.h"
using namespace cv;
using namespace std;


void initial(Mat* identity) {
		Rect rect(48, 288, 1728, 600);
		Mat body = *identity;
		Mat part = body(rect);  //提取黄框内容
		Mat clone0 = part.clone();

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
		//namedWindow("im_out", 0);
		//imshow("im_out", im_out);


		vector<vector<Point>> contours;//轮廓
		vector<Vec4i> hierarchy1;//存放轮廓结构变量
		findContours(im_out, contours, hierarchy1, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));//确定轮廓
		vector<Rect> boundRect(contours.size());
		for (int i = 0; i < contours.size(); i++) {
			
			boundRect[i] = boundingRect(Mat(contours[i]));
			double area = contourArea(contours[i]);
			
			double x_th = boundRect[i].br().x - boundRect[i].tl().x;
			double y_th = boundRect[i].br().y - boundRect[i].tl().y;
			double y_x = y_th / x_th;

			if (area > 1000 && area < 2000 ) {  //15000 25000
				
//				rectangle(clone0, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 255), 2, 8, 0);
				bottle_number = bottle_number + 1;
				bottle_x_l[bottle_number - 1] = boundRect[i].tl().x;
				bottle_x_r[bottle_number - 1] = boundRect[i].br().x;
				bottle_xlength[bottle_number - 1] = boundRect[i].br().x - boundRect[i].tl().x;
			}
		}

		namedWindow("clone0", 0);
		imshow("clone0", clone0);

		return;
	
}