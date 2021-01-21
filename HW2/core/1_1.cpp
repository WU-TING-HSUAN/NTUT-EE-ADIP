#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace cv;


int one_one()
{
	int width = 256;
	int height = 256;
	int a;
	int size = width * height;
	int eye1[4] = {128,140,120,140};
	int eye2[4] = { 128,140,160,180 };
	char B[255];
	char OriFile[] = "lena256.raw";    //Input Image name
	char OutFile[] = "lenaHW2_1.raw"; //Output Raw Image name


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
	Mat null = Mat(eye1[1]-eye1[0]+1,eye1[3]-eye1[2]+1, CV_8UC1); //
	Mat null2 = Mat(2*(eye1[1] - eye1[0] + 1), 2*(eye1[3] - eye1[2] + 1), CV_8UC1); //
	Mat nulr = Mat(eye2[1] - eye2[0] + 1, eye2[3] - eye2[2] + 2, CV_8UC1); //
	Mat nulr2 = Mat(2 * (eye2[1] - eye2[0] + 1), 2 * (eye2[3] - eye2[2] + 1), CV_8UC1); //
	//-----------------------左眼放大-----------------------//
	for (int i = eye1[0]; i <= eye1[1]; i++) {
		for (int j = eye1[2]; j <= eye1[3]; j++) {
			null.at<uchar>(i-eye1[0], j-eye1[2]) = lenaMat.at<uchar>(i, j) ;
		}
	}
	for (int i = 0; i <= eye1[1] - eye1[0]; i++) {
		for (int j = 0; j <= eye1[3] - eye1[2]; j++) {
			null2.at<uchar>(i*2,j*2) = null.at<uchar>(i, j);
			null2.at<uchar>(i*2,j*2+1) = null.at<uchar>(i, j);
			null2.at<uchar>(i*2+1, j*2) = null.at<uchar>(i, j);
			null2.at<uchar>(i*2+1, j*2+1) = null.at<uchar>(i, j);
		}
	}
	for (int i = 0; i < 2 * (eye1[1] - eye1[0] + 1); i++) {
		for (int j = 0; j < 2 * (eye1[3] - eye1[2] + 1); j++) {
			lenaMat.at<uchar>(122+i,110+j)= null2.at<uchar>(i,j);
		}
	}
	//-----------------------右眼放大-----------------------//
	for (int i = 128; i <= 140; i++) {
		for (int j = 160; j <= 180; j++) {
			nulr.at<uchar>(i-eye2[0], j-eye2[2]) = lenaMat.at<uchar>(i, j);
		}
	}
	for (int i = 0; i <= eye2[1] - eye2[0]; i++) {
		for (int j = 0; j <= eye2[3] - eye2[2]; j++) {
			nulr2.at<uchar>(i * 2, j * 2) = nulr.at<uchar>(i, j);
			nulr2.at<uchar>(i * 2, j * 2 + 1) = nulr.at<uchar>(i, j);
			nulr2.at<uchar>(i * 2 + 1, j * 2) = nulr.at<uchar>(i, j);
			nulr2.at<uchar>(i * 2 + 1, j * 2 + 1) = nulr.at<uchar>(i, j);
		}
	}
	for (int i = 0; i < 2 * (eye2[1] - eye2[0] + 1); i++) {
		for (int j = 0; j < 2 * (eye2[3] - eye2[2] + 1); j++) {
			lenaMat.at<uchar>(122 + i, 160 + j) = nulr2.at<uchar>(i, j);
		}
	}
	//-----------------------4. Save Image as raw format-----------------------//
	fwrite(lenaMat.ptr(0, 0), 1, size, resultFile); //儲存圖片
	namedWindow("lenaFile", 0); //視窗名
	resizeWindow("lenaFile",width,height); //視窗大小
	//moveWindow("lenaFile", 100, 100); //將視窗左上角放在螢幕指定位置
	imshow("lenaFile",lenaMat);//display Image 
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