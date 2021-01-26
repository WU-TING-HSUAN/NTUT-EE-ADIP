#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace cv;


int two()
{
	int WIDTH = 512;
	int HEIGHT = 512;
	int size = WIDTH * HEIGHT;
	int mse, mse1, mse2, mse3, mse4, mse5;
	char B[255];
	char OriFile_a[] = "a512x512.raw";    //Input Image name
	char OriFile_b[] = "b512x512.raw";    //Input Image name
	char OriFile_c[] = "c512x512.raw";    //Input Image name
	char OriFile_d[] = "d512x512.raw";    //Input Image name
	char OriFile_e[] = "e512x512.raw";    //Input Image name
	char OriFile_f[] = "f512x512.raw";    //Input Image name
	char OriFile_g[] = "g512x512.raw";    //Input Image name
	char OriFile_h[] = "h512x512.raw";    //Input Image name
	char OutFile[] = "lenaHW3_2_1.raw"; //Output Raw Image name
	double Q = 0;
	double P = 0;

	//-----------------------1. Read File-----------------------//
	FILE* lenaFile_a, * lenaFile_b, * lenaFile_c, * lenaFile_d, * lenaFile_e, * lenaFile_f, * lenaFile_g, * lenaFile_h, * lenaFile_baboon, * resultFile, * result1File;
	lenaFile_a = fopen(OriFile_a, "rb");
	lenaFile_b = fopen(OriFile_b, "rb");
	lenaFile_c = fopen(OriFile_c, "rb");
	lenaFile_d = fopen(OriFile_d, "rb");
	lenaFile_e = fopen(OriFile_e, "rb");
	lenaFile_f = fopen(OriFile_f, "rb");
	lenaFile_g = fopen(OriFile_g, "rb");
	lenaFile_h = fopen(OriFile_h, "rb");
	resultFile = fopen(OutFile, "wb");

	if (lenaFile_a == NULL) {
		puts("Loading File Error!");
		system("PAUSE");
		exit(0);
	}
	unsigned char* a = new unsigned char[size];
	unsigned char* b = new unsigned char[size];
	unsigned char* c = new unsigned char[size];
	unsigned char* d = new unsigned char[size];
	unsigned char* e = new unsigned char[size];
	unsigned char* f = new unsigned char[size];
	unsigned char* g = new unsigned char[size];
	unsigned char* h = new unsigned char[size];
	fread(a, 1, size, lenaFile_a);
	fread(b, 1, size, lenaFile_b);
	fread(c, 1, size, lenaFile_c);
	fread(d, 1, size, lenaFile_d);
	fread(e, 1, size, lenaFile_e);
	fread(f, 1, size, lenaFile_f);
	fread(g, 1, size, lenaFile_g);
	fread(h, 1, size, lenaFile_h);
	Mat aMat = Mat(HEIGHT, WIDTH, CV_8UC1, a); //unsign 8bit channel 1(¦Ç¶¥)
	Mat bMat = Mat(HEIGHT, WIDTH, CV_8UC1, b); //unsign 8bit channel 1(¦Ç¶¥)
	Mat cMat = Mat(HEIGHT, WIDTH, CV_8UC1, c); //unsign 8bit channel 1(¦Ç¶¥)
	Mat dMat = Mat(HEIGHT, WIDTH, CV_8UC1, d); //unsign 8bit channel 1(¦Ç¶¥)
	Mat eMat = Mat(HEIGHT, WIDTH, CV_8UC1, e); //unsign 8bit channel 1(¦Ç¶¥)
	Mat fMat = Mat(HEIGHT, WIDTH, CV_8UC1, f); //unsign 8bit channel 1(¦Ç¶¥)
	Mat gMat = Mat(HEIGHT, WIDTH, CV_8UC1, g); //unsign 8bit channel 1(¦Ç¶¥)
	Mat hMat = Mat(HEIGHT, WIDTH, CV_8UC1, h); //unsign 8bit channel 1(¦Ç¶¥)
	Mat tree_original = Mat(HEIGHT, WIDTH, CV_8UC1);
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			if (hMat.data[i * WIDTH + j] == 255) {
				hMat.data[i * WIDTH + j] = 0;
			}
			else{
					hMat.data[i * WIDTH + j] = 255;

			} 
		}
	}
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			if (eMat.data[i * WIDTH + j] == 255) {
				eMat.data[i * WIDTH + j] = 0;
			}
			else {
				eMat.data[i * WIDTH + j] = 255;

			}
		}
	}
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			if (dMat.data[i * WIDTH + j] == 255) {
				dMat.data[i * WIDTH + j] = 0;
			}
			else {
				dMat.data[i * WIDTH + j] = 255;

			}
		}
	}

	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			tree_original.data[i * WIDTH + j] = 0;
			tree_original.data[i * WIDTH + j] = 0;
		}
	}
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			tree_original.data[i * WIDTH + j] = bMat.data[i * WIDTH + j] * 128 / 255 + gMat.data[i * WIDTH + j] * 64 / 255 + hMat.data[i * WIDTH + j] * 32 / 255 + cMat.data[i * WIDTH + j] * 16 / 255
				+ aMat.data[i * WIDTH + j] * 8 / 255 + eMat.data[i * WIDTH + j] * 4 / 255 + dMat.data[i * WIDTH + j] * 2 / 255 + fMat.data[i * WIDTH + j] * 1 / 255;
		}
	}

	namedWindow("tree_original", 0); //µøµ¡¦W
	resizeWindow("tree_original", WIDTH, HEIGHT); //µøµ¡¤j¤p
	imshow("tree_original", tree_original);//display Image 
	waitKey(0);
	//-----------------------4. Save Image as raw format-----------------------//

	//-----------------------5. Release memory-----------------------//
	fclose(lenaFile_a);
	fclose(resultFile);
	delete a;
	destroyWindow("lenaFile");
	aMat.release();

}