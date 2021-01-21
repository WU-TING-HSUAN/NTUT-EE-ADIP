#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <math.h>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace cv;


int three_one()
{
	int width = 256;
	int height = 256;
	int a;
	int mse, mse1, mse2;
	double Q = 0;
	int size = width * height;
	int pice;
	char B[255];
	int x, y, count, count1, count2;
	char OriFile[] = "baboon_256.raw";    //Input Image name
	char OriFile1[] = "lena256.raw";    //Input Image name
	char OriFile2[] = "lena_512.raw";    //Input Image name
	char OutFile[] = "lenaHW2_3.raw"; //Output Raw Image name



	//-----------------------1. Read File-----------------------//
	FILE* lenaFile, * lenaFile1, * lenaFile2, * resultFile, * result1File;
	lenaFile = fopen(OriFile, "rb");
	lenaFile1 = fopen(OriFile1, "rb");
	lenaFile2 = fopen(OriFile2, "rb");
	resultFile = fopen(OutFile, "wb");
	if (lenaFile == NULL) {
		puts("Loading File Error!");
		system("PAUSE");
		exit(0);
	}
	unsigned char* lenai = new unsigned char[size];
	unsigned char* lenai1 = new unsigned char[size];
	unsigned char* lenai2 = new unsigned char[512 * 512];
	fread(lenai, 1, size, lenaFile);
	fread(lenai1, 1, size, lenaFile1);
	fread(lenai2, 1, 512 * 512, lenaFile2);
	Mat lenaMat = Mat(height, width, CV_8UC1, lenai); //unsign 8bit channel 1(灰階)
	Mat lenaMat1 = Mat(height, width, CV_8UC1, lenai1); //unsign 8bit channel 1(灰階)
	Mat lenaMat2 = Mat(512, 512, CV_8UC1, lenai2); //unsign 8bit channel 1(灰階)
	Mat W = Mat(height, width, CV_8UC1);
	Mat U = Mat(height, width, CV_8UC1);
	Mat T = Mat(512, 512, CV_8UC1);
	//-----------------------4. Save Image as raw format-----------------------//
	for (int x = 1; x < 8; x++) {
		y = width / pow(2, x);
		for (int i = 0; i < lenaMat.rows; i++) {
			for (int j = 0; j < lenaMat.cols; j++) {
				count = lenaMat.at<uchar>(i, j) / y;
				count1 = lenaMat1.at<uchar>(i, j) / y;
				//printf("%d", count);
				W.at<uchar>(i, j) = count * 255 / (pow(2, x) - 1);
				U.at<uchar>(i, j) = count1 * 255 / (pow(2, x) - 1);
			}
		}

		namedWindow("baboon", 0); //視窗名
		resizeWindow("baboon", lenaMat.rows, lenaMat.cols); //視窗大小
		imshow("baboon", W);//display Image 
		waitKey(0);

		namedWindow("lenaFile", 0); //視窗名
		resizeWindow("lenaFile", lenaMat.rows, lenaMat.cols); //視窗大小
		imshow("lenaFile", U);//display Image 
		waitKey(0);
	}
	for (int x = 1; x < 8; x++) {
		y = width / pow(2, x);
		for (int i = 0; i < lenaMat2.rows; i++) {
			for (int j = 0; j < lenaMat2.cols; j++) {
				count2 = lenaMat2.at<uchar>(i, j) / y;
				T.at<uchar>(i, j) = count2 * 255 / (pow(2, x) - 1);
			}
		}
		for (int i = 0; i < lenaMat2.rows; i++) {
			for (int j = 0; j < lenaMat2.cols; j++) {
				mse1 = lenaMat2.at<uchar>(i, j);
				mse2 = T.at<uchar>(i, j);
				mse = pow((mse1 - mse2), 2);
				Q = Q + mse;
			}
		}
		Q = Q / (lenaMat2.rows * lenaMat2.cols);
		printf("lena%dbit的MSE為%f", x, Q);
		printf("\n");
		printf("lena%dbit的PSNR為%f", x, 10 * log10(255 * 255 / Q));
		printf("\n");
		namedWindow("lenabig", 0); //視窗名
		resizeWindow("lenabig", lenaMat2.rows, lenaMat2.cols); //視窗大小
		//moveWindow("lenaFile", 100, 100); //將視窗左上角放在螢幕指定位置
		imshow("lenabig", T);//display Image 
		waitKey(0);
	}


	//-----------------------5. Release memory-----------------------//

}