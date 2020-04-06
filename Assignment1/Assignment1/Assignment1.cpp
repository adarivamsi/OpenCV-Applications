// Assignment1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include <stdio.h> //create a file, this is a default library
#include <iostream> //system library

//Below are the three important OpenCV library header files
#include <opencv2/core/core.hpp> //the very basics tool for	image processing
#include <opencv2/highgui/highgui.hpp> //for input/output,	e.g.load the image into RAM //show the image to the screen
#include <opencv2/imgproc/imgproc.hpp> //some advanced tool for image processing 

using namespace cv; //tell the compiler all the types involved	are from OpenCV library
		
int main(int argc, char** argv)
	{
		Mat img; //declare an empty Mat variable

		//option 1: creating the image by loading from a file
		img = imread("test.jpg"); //load the image file "test.jpg" into RAM and store it to the img variable

		//Option 2: create the image manually
		Mat img2; //color image uchar
		Mat img3; //single channel, float type
		img2.create(500, 500, CV_8UC3); //8U - 8 bits uchar
		//C3 - 3 channels

		img3.create(5, 5, CV_32FC1); //32F - float
		//C1 - 1 channel
		img2 = Scalar(100, 250, 250); // Change 1

		//Option 3: create the image by using "copyTo()"
		Mat img4;
		img.copyTo(img4);

		//Option 4: load the image from the camera (put it into a loop)
		VideoCapture vc(0); //vc is handle for the first camera
		Mat img5;

		resize(img, img, Size(img.cols * 0.5, img.rows * 0.5));


		while (1)
		{

			vc >> img5; //dynamically grab a frame from the camera
			resize(img5, img5, Size(img5.cols , img5.rows )); // Change 2


			char c = waitKey(1); //opencv will keep checking the keyboard event

				if (c == 27) //user can decide when to stop the loop, i.e. 27 is the "ESc" key
					break;

			imshow("test_window", img); //show the image on the screen from the RAM
			imshow("test_window2", img2); //show the color image on the screen
			imshow("test_window3", img3); // show the single channel image on the screen
			imshow("test_window4", img4); // show the copy of img on the screen
			imshow("test_window5", img5); // show the image from the camera
		}
	}