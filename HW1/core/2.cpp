#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace cv;


int c()
{
	int width = 512;
	int height = 512;
	int size = width * height;
	char OriFile[] = "figure/input/haha.raw";    //Input Image name
	char OutFile[] = "figure/input/hahaout.png"; //Output Raw Image name

	//-----------------------1. Read File-----------------------//
	FILE* hahaFile, * resultFile;
	hahaFile = fopen(OriFile, "rb");
	resultFile = fopen(OutFile, "wb");
	if (hahaFile == NULL) {
		puts("Loading File Error!");
		system("PAUSE");
		exit(0);
	}

	unsigned char* haha = new unsigned char[size];
	fread(haha, 1, size, hahaFile);

	//-----------------------2. Transfer data type to OpenCV-----------------------//
	//-----------------------You can use "Mat"-----------------------//
	//Mat type
	Mat hahaMat = Mat(height, width, CV_8UC1, haha); //unsign 8bit channel 1(灰階)
	//cv:Mat lenaMat(height, width, CV_8UC1, lenai); #方法2
	//Set lenai data into lenaMat
	Point p = Point(0, hahaMat.rows / 4 - 50);
	putText(hahaMat, "number", p,FONT_HERSHEY_TRIPLEX, 1,Scalar(0, 0, 0), 2);
	Point o = Point(hahaMat.cols/2-220, hahaMat.rows-50);
	putText(hahaMat, "More and More!!!", o, FONT_HERSHEY_TRIPLEX, 1.5, Scalar(0, 0, 0), 2);
	//-----------------------3. Create window and show your Image-----------------------//
	namedWindow("haha", 0); //視窗名
	resizeWindow("haha", width, height); //視窗大小
	//moveWindow("lenaFile", 100, 100); //將視窗左上角放在螢幕指定位置
	imshow("haha", hahaMat);//display Image 
	waitKey(0);

	//-----------------------5. Release memory-----------------------//
	fclose(hahaFile);
	fclose(resultFile);
	delete  haha;
	destroyWindow("haha");
	/*cvReleaseMat(&lenaMat);
	cvReleaseImage(&lenaIpl);*/
}