#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace cv;


int b()
{
	srand(time(NULL));
	int width = 256;
	int height = 256;
	int a;
	int size = width * height;
	char B[255];
	char OriFile[] = "figure/input/lena256.raw";    //Input Image name
	char OutFile[] = "figure/input/lena256+50.raw"; //Output Raw Image name
	char Out1File[] = "figure/input/lena256+random.raw"; //Output Raw Image name
	int min = -50;
	int max = 50;


	//-----------------------1. Read File-----------------------//
	FILE* lenaFile, * resultFile, * result1File;
	lenaFile = fopen(OriFile, "rb");
	resultFile = fopen(OutFile, "wb");
	result1File = fopen(Out1File, "wb");
	if (lenaFile == NULL) {
		puts("Loading File Error!");
		system("PAUSE");
		exit(0);
	}

	unsigned char* lenai = new unsigned char[size];
	fread(lenai, 1, size, lenaFile);

	//-----------------------2. Transfer data type to OpenCV-----------------------//
	//-----------------------You can use "Mat"-----------------------//
	//Mat type
	Mat lenaMat = Mat(height, width, CV_8UC1, lenai); //unsign 8bit channel 1(灰階)
	Mat lenMat = Mat(height, width, CV_8UC1, lenai);
	//cv:Mat lenaMat(height, width, CV_8UC1, lenai); #方法2
	//Set lenai data into lenaMat
	//-----------------------1-3a-----------------------//
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++)
		{

			if(lenaMat.at<uchar>(i, j) > 205)
			{
				lenaMat.at<uchar>(i, j) = 255;
			}
			if (lenaMat.at<uchar>(i, j) <= 205)
			{
				lenaMat.at<uchar>(i, j) = lenaMat.at<uchar>(i, j) + 50;
			}
		}
	}
	fwrite(lenMat.ptr(0, 0), 1, size, resultFile); //儲存圖片
	namedWindow("lenaFile", 0); //視窗名
	resizeWindow("lenaFile", width, height); //視窗大小
	imshow("lenaFile", lenaMat);//display Image 
	waitKey(0);
	//-----------------------1-3b-----------------------//
	int x = rand() % (max - min + 1) + min;
	printf("%d", x);
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++)
		{
			if (x >= 0)
			{
				if (lenMat.at<uchar>(i, j) > width - x)
				{
					lenMat.at<uchar>(i, j) = width;
				}
				if (lenMat.at<uchar>(i, j) <= width - x)
				{
					lenMat.at<uchar>(i, j) = lenMat.at<uchar>(i, j) + x;
				}

			}
			if (x < 0)
			{
				if (lenMat.at<uchar>(i, j) <= 0 - x)
				{
					lenMat.at<uchar>(i, j) = 0;
				}
				if (lenMat.at<uchar>(i, j) > 0 - x)
				{
					lenMat.at<uchar>(i, j) = lenMat.at<uchar>(i, j)+x;
				}
			}
		}
	}
	//-----------------------3. Create window and show your Image-----------------------//

	namedWindow("lenaFile", 0); //視窗名
	resizeWindow("lenaFile", width, height); //視窗大小
	//moveWindow("lenaFile", 100, 100); //將視窗左上角放在螢幕指定位置
	imshow("lenaFile", lenMat);//display Image 
	waitKey(0);
	//-----------------------4. Save Image as raw format-----------------------//
	//-----------------------5. Release memory-----------------------//
	fclose(lenaFile);
	fclose(resultFile);
	delete lenai;
	destroyWindow("lenaFile");
	lenaMat.release();
	/*cvReleaseMat(&lenaMat);
	cvReleaseImage(&lenaIpl);*/
}