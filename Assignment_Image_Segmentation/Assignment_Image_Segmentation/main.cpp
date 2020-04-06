// Assignment_Photo_Booth.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <stdio.h>
#include <opencv2\core\core.hpp> //basic data type
#include <opencv2\highgui\highgui.hpp> //input/output
#include <opencv2\imgproc\imgproc.hpp> //process images

using namespace cv;
using namespace std;

void k_means(const Mat img, Mat label_img)
{
	int cluster1, cluster2;
	double m1 = 100.0; // Mean1
	double m2 = 200.0; // Mean2
	double sum1, sum2;

	label_img.create(img.rows, img.cols, CV_8UC1);

	for (int a = 0; a < 20; a++)
	{
		sum1 = 0.0;
		sum2 = 0.0;
		cluster1 = 0;
		cluster2 = 0;

		for (int b = 0; b < img.rows; b++)
		{
			for (int c = 0; c < img.cols; c++)
			{
				double d1 = abs((double)img.ptr<uchar>(b)[c] - m1);
				double d2 = abs((double)img.ptr<uchar>(b)[c] - m2);
				if (d1 > d2)
				{
					sum2 += img.ptr<uchar>(b)[c];
					cluster2++;
					label_img.ptr<uchar>(b)[c] = 0;
				}
				else
				{
					sum1 += img.ptr<uchar>(b)[c];
					cluster1++;
					label_img.ptr<uchar>(b)[c] = 255;
				}
			}
		}
		m1 = sum1 / cluster1;
		m2 = sum2 / cluster2;
	}
	imshow("Labeled Image after K Means", label_img);
}

Mat em(const Mat img, Mat label_img)
{
	int cluster1, cluster2;
	double m1 = 100.0; // Mean1
	double m2 = 200.0; // Mean2
	double sum1, sum2;

	label_img.create(img.rows, img.cols, CV_8UC1);

	for (int a = 0; a < 20; a++)
	{
		sum1 = 0.0;
		sum2 = 0.0;
		cluster1 = 0;
		cluster2 = 0;

		for (int b = 0; b < img.rows; b++)
		{
			for (int c = 0; c < img.cols; c++)
			{
				double d1 = abs((double)img.ptr<uchar>(b)[c] - m1);
				d1 *= 0.80;
				double d2 = abs((double)img.ptr<uchar>(b)[c] - m2);
				d2 *= 0.20;

				if (d1 > d2)
				{
					sum2 += img.ptr<uchar>(b)[c];
					cluster2++;
					label_img.ptr<uchar>(b)[c] = 0;
				}
				else
				{
					sum1 += img.ptr<uchar>(b)[c];
					cluster1++;
					label_img.ptr<uchar>(b)[c] = 255;
				}
			}
		}
		m1 = sum1 / cluster1;
		m2 = sum2 / cluster2;
	}
	imshow("Labeled Image after Expectation Maximization", label_img);
	return label_img;
}

int main(int argc, char** argv) {
	Mat img; //store the frame captured from the VideoCapture
	Mat label_img; //store the labeled image

	img = imread("Image.png",0);

	Mat rgb;

	while (1)
	{
		imshow("Original", img);

		k_means(img, label_img); // 1. Segmentation -> K-Means
		Mat save_img = em(img, label_img); // 1. Segmentation -> Expectation Maximization
		
		Mat canny_img; 
		Canny(save_img, canny_img, 100, 200, 3); // 2. Circle Recognition -> Canny Edge Extraction
		canny_img.convertTo(canny_img, CV_8UC1);

		imshow("Edge Image after Canny Edge detection", canny_img);

		vector<Vec3f> circles;
		HoughCircles(canny_img, circles, HOUGH_GRADIENT, 1, canny_img.rows / 8, 200, 15, 0, 0);
		cvtColor(canny_img, rgb, COLOR_GRAY2BGR);
		for (size_t i = 0; i < circles.size(); i++)
		{
			Point center(cvRound(circles[i][0]), cvRound(circles[i][1])); 
			int r = cvRound(circles[i][2]);
			circle(rgb, center, r, Scalar(0, 0, 255), 1, 8, 0); // 2. Circle Recognition -> Hough Circle Detection
		}
		imshow("Circled Image after Hough circle detection", rgb);

		char c = waitKey(1); //listen to your keyboard
		if (c == 27) //27 - "Esc" ASCII
			break;
	}
	return 0;
}