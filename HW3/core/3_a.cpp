#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace cv;


int three()
{
	int WIDTH = 512;
	int HEIGHT = 512;
	int size = WIDTH * HEIGHT;
	int mse, mse1, mse2, mse3, mse4, mse5;
	char B[255];
	char OriFile[] = "livingroom_d512.raw";    //Input Image name
	char OriFile_cameraman[] = "cameraman_b512.raw";    //Input Image name
	char OutFile[] = "lenaHW2_3.raw"; //Output Raw Image name
	double Q = 0;
	double P = 0;

	//-----------------------1. Read File-----------------------//
	FILE* lenaFile, * lenaFile_camera, * resultFile, * result1File;
	lenaFile = fopen(OriFile, "rb");
	lenaFile_camera = fopen(OriFile_cameraman, "rb");
	resultFile = fopen(OutFile, "wb");

	if (lenaFile == NULL) {
		puts("Loading File Error!");
		system("PAUSE");
		exit(0);
	}
	int input1;
	printf("請輸入1或2(1為a小題、2為b小題):");
	scanf("%d", &input1);
	unsigned char* living = new unsigned char[size];
	unsigned char* camera = new unsigned char[size];
	fread(living, 1, size, lenaFile);
	fread(camera, 1, size, lenaFile_camera);
	Mat livingMat = Mat(HEIGHT, WIDTH, CV_8UC1, living); //unsign 8bit channel 1(灰階)
	Mat cameraMat = Mat(HEIGHT, WIDTH, CV_8UC1, camera); //unsign 8bit channel 1(灰階)

	Mat new_livingMat = Mat(HEIGHT, WIDTH, CV_8UC1); //unsign 8bit channel 1(灰階)
	Mat new_cameraMat = Mat(HEIGHT, WIDTH, CV_8UC1); //unsign 8bit channel 1(灰階)
		//-----------------------c=100-----------------------//
	if (input1 == 1) {
		for (int i = 0; i < WIDTH; i++) {
			for (int j = 0; j < HEIGHT; j++) {
				new_livingMat.data[i * WIDTH + j] = 100 * log10(livingMat.data[i * WIDTH + j] + 1);
			}
		}
		namedWindow("new_livingMat_c=100", 0); //視窗名
		resizeWindow("new_livingMat_c=100", WIDTH, HEIGHT); //視窗大小
		imshow("new_livingMat_c=100", new_livingMat);//display Image 
		waitKey(0);
		//-----------------------c=20-----------------------//
		for (int i = 0; i < WIDTH; i++) {
			for (int j = 0; j < HEIGHT; j++) {
				new_livingMat.data[i * WIDTH + j] = 20 * log10(livingMat.data[i * WIDTH + j] + 1);
			}
		}
		namedWindow("new_livingMat_c=20", 0); //視窗名
		resizeWindow("new_livingMat_c=20", WIDTH, HEIGHT); //視窗大小
		imshow("new_livingMat_c=20", new_livingMat);//display Image 
		waitKey(0);
		//-----------------------c=100-----------------------//
		for (int i = 0; i < WIDTH; i++) {
			for (int j = 0; j < HEIGHT; j++) {
				new_cameraMat.data[i * WIDTH + j] = 100 * log10(cameraMat.data[i * WIDTH + j] + 1);
			}
		}
		resizeWindow("new_cameraMatt_c=100", WIDTH, HEIGHT); //視窗大小
		imshow("new_cameraMat_c=100", new_cameraMat);//display Image 
		waitKey(0);
		//-----------------------c=20-----------------------//
		for (int i = 0; i < WIDTH; i++) {
			for (int j = 0; j < HEIGHT; j++) {
				new_cameraMat.data[i * WIDTH + j] = 20 * log10(cameraMat.data[i * WIDTH + j] + 1);
			}
		}
		namedWindow("new_cameraMat_c=20", 0); //視窗名
		resizeWindow("new_cameraMat_c=20", WIDTH, HEIGHT); //視窗大小
		imshow("new_cameraMat_c=20", new_cameraMat);//display Image 
		waitKey(0);
	}
	if (input1 == 2) {
		//-----------------------c=100 γ=0.2-----------------------//
		for (int i = 0; i < WIDTH; i++) {
			for (int j = 0; j < HEIGHT; j++) {
				new_livingMat.data[i * WIDTH + j] = 350 * pow(livingMat.data[i * WIDTH + j], 0.2);
			}
		}
		namedWindow("new_livingMat_c=350_γ=0.2", 0); //視窗名
		resizeWindow("new_livingMat_c=350_γ=0.2", WIDTH, HEIGHT); //視窗大小
		imshow("new_livingMat_c=350_γ=0.2", new_livingMat);//display Image 
		waitKey(0);

		//-----------------------c=20 γ=0.2-----------------------//
		for (int i = 0; i < WIDTH; i++) {
			for (int j = 0; j < HEIGHT; j++) {
				new_cameraMat.data[i * WIDTH + j] = 20 * pow(cameraMat.data[i * WIDTH + j], 0.2);
			}
		}
		namedWindow("new_cameraMat_c=20_γ=0.2", 0); //視窗名
		resizeWindow("new_cameraMat_c=20_γ=0.2", WIDTH, HEIGHT); //視窗大小
		imshow("new_cameraMat_c=20_γ=0.2", new_cameraMat);//display Image 
		waitKey(0);

		//-----------------------c=75 γ=5-----------------------//
		for (int i = 0; i < WIDTH; i++) {
			for (int j = 0; j < HEIGHT; j++) {
				new_cameraMat.data[i * WIDTH + j] = 100 * pow(cameraMat.data[i * WIDTH + j], 5);
			}
		}
		namedWindow("new_cameraMat_c=75_γ=5", 0); //視窗名
		resizeWindow("new_cameraMat_c=75_γ=5", WIDTH, HEIGHT); //視窗大小
		imshow("new_cameraMat_c=75_γ=5", new_cameraMat);//display Image 
		waitKey(0);

		//-----------------------c= 0.00000000000000005 γ=10-----------------------//
		for (int i = 0; i < WIDTH; i++) {
			for (int j = 0; j < HEIGHT; j++) {
				new_cameraMat.data[i * WIDTH + j] = 0.00000000000000005 * pow(cameraMat.data[i * WIDTH + j], 10);
			}
		}
		namedWindow("new_cameraMat_c=0.00000000000000005_γ=10", 0); //視窗名
		resizeWindow("new_cameraMat_c=0.00000000000000005_γ=10", WIDTH, HEIGHT); //視窗大小
		imshow("new_cameraMat_c=0.00000000000000005_γ=10", new_cameraMat);//display Image 
		waitKey(0);
	}
	//-----------------------5. Release memory-----------------------//
	fclose(lenaFile);
	fclose(resultFile);
	delete living;
	destroyWindow("lenaFile");
	livingMat.release();

}