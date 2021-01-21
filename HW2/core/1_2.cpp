#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace cv;


int one_two()
{
	int width = 256;
	int height = 256;
	int a;
	int size = width * height;
	char B[255];
	char OriFile[] = "lenaHW2_1.raw";    //Input Image name
	char OutFile[] = "lenaHW2_2.raw"; //Output Raw Image name



	//-----------------------1. Read File-----------------------//
	FILE* lenaFile, * resultFile, * result1File;
	lenaFile = fopen(OriFile, "rb");
	resultFile = fopen(OutFile, "wb");
	if (lenaFile == NULL) {
		puts("Loading File Error!");
		system("PAUSE");
		exit(0);
	}
	unsigned char* lenai = new unsigned char[size];
	fread(lenai, 1, size, lenaFile);
	Mat lenaMat = Mat(height, width, CV_8UC1, lenai); //unsign 8bit channel 1(灰階)
	Mat null = Mat(height/2, width/2, CV_8UC1); //unsign 8bit channel 1(灰階)
	//-----------------------縮小-----------------------//
	for (int i = 0; i < null.rows; i++) {
		for (int j = 0; j < null.cols; j++) {
			null.at<uchar>(i, j) = (lenaMat.at<uchar>(i * 2, j * 2) + lenaMat.at<uchar>(i * 2, j * 2 + 1) + lenaMat.at<uchar>(i * 2 + 1, j * 2) + lenaMat.at<uchar>(i * 2 + 1, j * 2 + 1)) / 4;
		}
	}
	//-----------------------4. Save Image as raw format-----------------------//
	fwrite(null.ptr(0, 0), 1, null.rows * null.cols, resultFile); //儲存圖片
	namedWindow("lenaFile", 0); //視窗名
	resizeWindow("lenaFile", null.rows, null.cols); //視窗大小
	//moveWindow("lenaFile", 100, 100); //將視窗左上角放在螢幕指定位置
	imshow("lenaFile", null);//display Image 
	waitKey(0);
	//-----------------------5. Release memory-----------------------//
	fclose(lenaFile);
	fclose(resultFile);
	delete lenai;
	destroyWindow("lenaFile");
	lenaMat.release();
	/*cvReleaseMat(&lenaMat);
	cvReleaseImage(&lenaIpl);*/
}