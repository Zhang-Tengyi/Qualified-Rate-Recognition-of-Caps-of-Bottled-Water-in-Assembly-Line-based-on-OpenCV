#include<Opencv.hpp>
#include<iostream>
#include<string>
#include"bottle_body.h"
#include"cap_scan.h"
#include"initial.h"
using namespace cv;
using namespace std;

//extern Mat Blank;
//extern Mat cap_scan();
double k_cap = 0, k_cap1 = 0;
double k_body = 0, rate;
int R_n = 0, textX, textY;
int bottle_number = 0, bottle_number_old = 0, bottle_number_count;
double bottle_normal_number = 0, bottle_incline_number = 0, bottle_high_number = 0, bottle_empty_number = 0, bottle_unq_number = 0, bottle_unq_number_old = 0;
double normal_number_rate = 0, incline_rate = 0, high_rate = 0, empty_rate = 0, bottle_incline_number_old = 0, bottle_high_number_old = 0, bottle_empty_number_old = 0,bottle_normal_number_old = 0;
int bottle_x_l[5] = { 0,0,0,0,0 };
int bottle_x_r[5] = { 0,0,0,0,0 };
int bottle_xlength[5] = { 0,0,0,0,0 };
int cap_selected_area = 0;

int main() {
	VideoCapture capture(0);
	capture.set(cv::CAP_PROP_FPS, 30);
	capture.set(cv::CAP_PROP_FRAME_WIDTH, 1920);
	capture.set(cv::CAP_PROP_FRAME_HEIGHT, 1080);
	Mat img;

	while (1) {
		capture >> img;
		Mat identify = img.clone();
		Mat Blank = img.clone();
		
		initial(&identify);//检测瓶子
		if(bottle_number != 0){

		for (bottle_number_count = 0; bottle_number_count < bottle_number; bottle_number_count++) {  //依次识别各个瓶子
			
			Mat cap = img.clone();
			Mat body = img.clone();
			Point textP;

			if (bottle_x_l[bottle_number_count] + 20 > 0 && bottle_x_r[bottle_number_count] + 50 < 1920) {
				cap_scan(&cap); //瓶盖最小矩形提取
				Rect rect_cap(bottle_x_l[bottle_number_count] + 20, 8, bottle_xlength[bottle_number_count] + 50, 360);
				cap.copyTo(Blank(Rect(rect_cap)));
				if (R_n == 2) {
					textP.x = bottle_x_l[bottle_number_count];
					textP.y = textY;
					double k_capall;
					k_capall = k_cap - k_cap1;

					if (-0.15 < k_capall && k_capall < 0.15) {
						string text = "High";
						putText(Blank, text, textP, FONT_HERSHEY_SIMPLEX, 3, Scalar(0, 255, 255), 2, 8, 0);
						bottle_high_number = bottle_high_number + 1;
					}
					else {
						string text = "Incline";
						putText(Blank, text, textP, FONT_HERSHEY_SIMPLEX, 3, Scalar(0, 255, 255), 2, 8, 0);
						bottle_incline_number = bottle_incline_number + 1;
					}
//					namedWindow("Blank", 0);
//					imshow("Blank", Blank);

				}
			}
			else {
				rectangle(Blank, Point2d(96, 8), Point2d(1824, 368), Scalar(255, 255, 0), 2, 8, 0);
				namedWindow("检测显示", 0);
				imshow("检测显示", Blank);		
				break;
			}
			if (R_n == 1) {//瓶身矩形提取

				if (bottle_x_l[bottle_number_count] + 20  > 0 && bottle_x_r[bottle_number_count] + 100 < 1920) {
					bottle_body(&body);;
				}
				else {
					rectangle(Blank, Point2d(96, 8), Point2d(1824, 368), Scalar(255, 255, 0), 2, 8, 0);
					namedWindow("检测显示", 0);
					imshow("检测显示", Blank);
					break;
				}
				textP.x = bottle_x_l[bottle_number_count];
				textP.y = textY;
				double k_capbody = k_cap - k_body;

				if (-0.2 >= k_capbody or k_capbody >= 0.2 ) {
					string text = "Incline";
					putText(Blank, text, textP, FONT_HERSHEY_SIMPLEX, 3, Scalar(0, 255, 255), 2, 8, 0);
					bottle_incline_number = bottle_incline_number + 1;

				}
				else if (-0.2 < k_capbody && k_capbody < 0.2 ) { 
					if(cap_selected_area > 3400 && rate >= 0.8){
						string text = "Normal";
						putText(Blank, text, textP, FONT_HERSHEY_SIMPLEX, 3, Scalar(0, 255, 255), 2, 8, 0);
						bottle_normal_number = bottle_normal_number + 1;
					}
					else if (cap_selected_area <= 3400) {
						string text = "No_Cap";
						putText(Blank, text, textP, FONT_HERSHEY_SIMPLEX, 3, Scalar(0, 255, 255), 2, 8, 0);
						bottle_empty_number = bottle_empty_number + 1;
					}
					else {
						string text = "Incline";
						putText(Blank, text, textP, FONT_HERSHEY_SIMPLEX, 3, Scalar(0, 255, 255), 2, 8, 0);
						bottle_incline_number = bottle_incline_number + 1;
					}
				}
				else{
					string text = "No_Cap";
					putText(Blank, text, textP, FONT_HERSHEY_SIMPLEX, 3, Scalar(0, 255, 255), 2, 8, 0);
					bottle_empty_number = bottle_empty_number + 1;
				}
			}

			k_cap = 0; k_cap1 = 0;
			k_body = 0; rate = 0;
			R_n = 0; textX = 0; textY = 0;                                                                                                                                                                                                                                            
			cap_selected_area = 0;

			}
		namedWindow("检测显示", 0);
		imshow("检测显示", Blank);
		}
		else{ 
			rectangle(Blank, Point2d(96, 8), Point2d(1824, 368), Scalar(255, 255, 0), 2, 8, 0);
			namedWindow("检测显示", 0);
			imshow("检测显示", Blank);
		}

		if (waitKey(1) == 9) { //合格率累加计算  cin>>
			while (waitKey(1) == 9) {
				waitKey(12);
				waitKey(1) != 9;
				break;
			}
			bottle_unq_number = bottle_incline_number + bottle_high_number + bottle_empty_number;
			normal_number_rate = bottle_normal_number / bottle_number;
			incline_rate = bottle_incline_number / bottle_number;
			high_rate = bottle_high_number / bottle_number;
			empty_rate = bottle_empty_number / bottle_number;

			std::cout << "识别到瓶子数量为" << bottle_number << "个，产品合格率为" << normal_number_rate << std::endl;
			std::cout << "其中，高盖率：" << high_rate << "，斜盖率为" << incline_rate << "，无盖率为" << empty_rate << std::endl;
			bottle_number_old = bottle_number + bottle_number_old;
			bottle_unq_number_old = bottle_unq_number_old + bottle_unq_number;
			bottle_normal_number_old = bottle_normal_number_old + bottle_normal_number;
			bottle_incline_number_old = bottle_incline_number_old + bottle_incline_number;
			bottle_high_number_old = bottle_high_number_old + bottle_high_number;
			bottle_empty_number_old = bottle_empty_number_old + bottle_empty_number;
		}

		if (waitKey(1) == 32) { //合格率最终计算  cin>>
			while (waitKey(1) == 32) {
				waitKey(12);
				waitKey(1) != 32;
				break;
			}
//			bottle_unq_number = bottle_incline_number + bottle_high_number + bottle_empty_number;
			normal_number_rate = bottle_normal_number_old / bottle_number_old;
			incline_rate = bottle_incline_number_old / bottle_number_old;
			high_rate = bottle_high_number_old / bottle_number_old;
			empty_rate = bottle_empty_number_old / bottle_number_old;

			std::cout << " " << std::endl;
			std::cout << "最终结果输出：" << std::endl;
			std::cout << "总体识别瓶子数量为" << bottle_number_old << "个，总产品合格率为" << normal_number_rate << std::endl;
			std::cout << "其中，总高盖率：" << high_rate << "，总斜盖率为" << incline_rate << "，总无盖率为" << empty_rate << std::endl;
			std::cout << "bottle_incline_number_old：" << bottle_incline_number_old << "，bottle_number_old" << bottle_number_old<< std::endl;

			waitKey(60);
			break;
			capture.release();
			destroyAllWindows();
		}


		for (int i = 0; i < bottle_number; i++) {
			bottle_x_l[i] = 0;
			bottle_x_r[i] = 0;
			bottle_xlength[i] = 0;
		}
		bottle_number = 0;
		bottle_normal_number = 0; bottle_incline_number = 0; bottle_high_number = 0; bottle_empty_number = 0; bottle_unq_number = 0;
		normal_number_rate = 0; incline_rate = 0; high_rate = 0; empty_rate = 0;

		if (waitKey(1)==27) {
			break;
			capture.release();
			destroyAllWindows();
		}
		waitKey(24);

	}
	capture.release();
	destroyAllWindows();
}