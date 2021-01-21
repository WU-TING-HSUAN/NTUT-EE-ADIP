#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <math.h>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace cv;


int two_one()
{
	while (1) {
		int width = 256;
		int height = 256;
		int a;
		int mse,mse1,mse2,mse3,mse4,mse5;
		double Q=0;
		double P = 0;
		int size = width * height;
		int pice;
		char B[255];
		int x, y, count,count1;
		char OriFile[] = "baboon_256.raw";    //Input Image name
		char OriFile1[] = "lena256.raw";    //Input Image name
		char OutFile[] = "lenaHW2_3.raw"; //Output Raw Image name
		char OutFile1[] = "lenaHW2_3_1.raw"; //Output Raw Image name



		//-----------------------1. Read File-----------------------//
		FILE* lenaFile, * lenaFile1, * resultFile, * result1File;
		lenaFile = fopen(OriFile, "rb");
		lenaFile1 = fopen(OriFile1, "rb");
		resultFile = fopen(OutFile, "wb");
		result1File = fopen(OutFile1, "wb");
		if (lenaFile == NULL) {
			puts("Loading File Error!");
			system("PAUSE");
			exit(0);
		}
		unsigned char* lenai = new unsigned char[size];
		unsigned char* lenai1 = new unsigned char[size];
		fread(lenai, 1, size, lenaFile);
		fread(lenai1, 1, size, lenaFile1);
		Mat lenaMat = Mat(height, width, CV_8UC1, lenai); //unsign 8bit channel 1(灰階)
		Mat lenaMat1 = Mat(height, width, CV_8UC1, lenai1); //unsign 8bit channel 1(灰階)
		Mat W = Mat(height, width, CV_8UC1);
		Mat U = Mat(height, width, CV_8UC1);
		//-----------------------4. Save Image as raw format-----------------------//
		printf("請輸入要轉換的bits數(ex:1~7):");
		scanf("%d", &x);
		y = lenaMat.rows / pow(2, x);
		for (int i = 0; i < lenaMat.rows; i++) {
			for (int j = 0; j < lenaMat.cols; j++) {
				count = lenaMat.at<uchar>(i, j) / y;
				count1 = lenaMat1.at<uchar>(i, j) / y;
				//printf("%d", count);
				W.at<uchar>(i, j) = count * 255 / (pow(2, x) - 1);
				U.at<uchar>(i, j) = count1 * 255 / (pow(2, x) - 1);

			}
		}
		for (int i = 0; i < lenaMat.rows; i++) {
			for (int j = 0; j < lenaMat.cols; j++) {
				mse1 = lenaMat.at<uchar>(i, j);
				mse2 = W.at<uchar>(i, j);
				mse = pow((mse1 - mse2),2);
				Q = Q + mse;
			}
		}
		Q = Q / (lenaMat.rows * lenaMat.cols);

		for (int i = 0; i < lenaMat1.rows; i++) {
			for (int j = 0; j < lenaMat1.cols; j++) {
				mse3 = lenaMat1.at<uchar>(i, j);
				mse4 = U.at<uchar>(i, j);
				mse5 = pow((mse3 - mse4), 2);
				P = P + mse5;
			}
		}
		P = P / (lenaMat1.rows * lenaMat1.cols);
		printf("baboon%dbit的MSE為%f",x,Q);
		printf("\n");
		printf("baboon%dbit的PSNR為%f", x,10*log10(255*255/Q));
		printf("\n");
		printf("\n");
		printf("lenaFile%dbit的MSE為%f", x, P);
		printf("\n");
		printf("lenaFile%dbit的PSNR為%f", x, 10 * log10(255 * 255 / P));
		printf("\n");

		namedWindow("baboon", 0); //視窗名
		resizeWindow("baboon", lenaMat1.rows, lenaMat1.cols); //視窗大小
		//moveWindow("lenaFile", 100, 100); //將視窗左上角放在螢幕指定位置
		imshow("baboon", W);//display Image 
		waitKey(0);

		namedWindow("lenaFile", 0); //視窗名
		resizeWindow("lenaFile", lenaMat1.rows, lenaMat1.cols); //視窗大小
		//moveWindow("lenaFile", 100, 100); //將視窗左上角放在螢幕指定位置
		imshow("lenaFile",U);//display Image 
		waitKey(0);


		
		//-----------------------5. Release memory-----------------------//
		fclose(lenaFile1);
		delete lenai1;
		destroyWindow("baboon");
		lenaMat.release();
		fclose(lenaFile);
		delete lenai;
		destroyWindow("lenaFile");
		lenaMat.release();
		/*cvReleaseMat(&lenaMat);
		cvReleaseImage(&lenaIpl);*/
	}
}