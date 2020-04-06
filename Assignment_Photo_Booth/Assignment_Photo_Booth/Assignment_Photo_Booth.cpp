// Assignment_Photo_Booth.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <opencv2\core\core.hpp> //basic data type
#include <opencv2\highgui\highgui.hpp> //input/output
#include <opencv2\imgproc\imgproc.hpp> //process images


using namespace cv;

int main(int argc, char** argv) {
	VideoCapture camera(0); //the camera variable is initialized automatically by using "(#)" number # indicates the camera's index
	Mat img; //store the frame captured from the VideoCapture
	Mat img_small; //to store the reduced size version
	Mat img_output; //to store the camera frame

	Mat kernel;
	Mat identical = (Mat_<float>(3, 3) << 0, 0, 0, 0, 1, 0, 0, 0, 0);
	Mat gaussian = (Mat_<float>(3, 3) << 1, 2, 1, 2, 4, 2, 1, 2, 1)/16;
	Mat mean = (Mat_<float>(3, 3) << 1, 1, 1, 1, 1, 1, 1, 1, 1)/9;
	Mat edge = (Mat_<float>(3, 3) << -1, -1, -1, -1, 8, -1, -1, -1, -1);
	Mat verticalSobel = (Mat_<float>(3, 3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);
	Mat horizontalSobel = (Mat_<float>(3, 3) << -1, -2, -1, 0, 0, 0, 1, 2, 1);
	Mat sharpen = (Mat_<float>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);

	kernel = identical;
	while (1)
	{
		camera >> img;

		resize(img, img_small, Size(img.cols/2, img.rows/2));
		imshow("Original", img_small);

		filter2D(img_small, img_output, CV_8UC3, kernel, Point(-1, -1), 0, BORDER_DEFAULT);
		imshow("Filtered", img_output);
		char c = waitKey(1); //listen to your keyboard
		if (c == 27) //27 - "Esc" ASCII
			break;
		else if (c == 'i') 
			kernel = identical; // Show Original Video
		else if (c == 'g') 
			kernel = gaussian; // Show Gaussian Blurred Video
		else if (c == 'm') 
			kernel = mean; // Show Mean/Average Blurred Video
		else if (c == 'e') 
			kernel = edge; // Show Ordinary Edge Video
		else if (c == 'v') 
			kernel = verticalSobel; // Show Applied Vertical Edge Sobel Filter Video
		else if (c == 'h') 
			kernel = horizontalSobel; // Show Applied Horizontal Edge Sobel Filter Video 
		else if (c == 's') 
			kernel = sharpen; // Show Sharpen Video
	}
	return 0;
}