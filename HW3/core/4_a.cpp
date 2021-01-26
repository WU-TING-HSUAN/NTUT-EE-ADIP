#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <math.h>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace cv;

int HISTOGRAM[256], HISTOGRAM_1[256],HISTOGRAM_Equalization[255], aaa[255];
double  HISTOGRAM_Equalization_1[255];
int WIDTH = 512;
int HEIGHT = 512;
int size = WIDTH * HEIGHT;
int N=0;
double maxs = 0;
int max_cdf = 100, min_cdf = 10;
int histogram(Mat a);
int histogram_Equalization(Mat a);
int four()
{
	
	
	char OriFile[] = "livingroom_d512.raw";    //Input Image name
	char OriFile_cameraman[] = "cameraman_b512.raw";    //Input Image name
	char OutFile[] = "lenaHW2_3.raw"; //Output Raw Image name

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
	unsigned char* living = new unsigned char[size];
	unsigned char* camera = new unsigned char[size];
	fread(living, 1, size, lenaFile);
	fread(camera, 1, size, lenaFile_camera);
	Mat livingMat = Mat(HEIGHT, WIDTH, CV_8UC1, living); //unsign 8bit channel 1(灰階)
	Mat cameraMat = Mat(HEIGHT, WIDTH, CV_8UC1, camera); //unsign 8bit channel 1(灰階)
	int input2;
	printf("請輸入1或2(1為a小題、2為b小題):");
	scanf("%d", &input2);
	if (input2 == 1) {
		histogram(livingMat);
		histogram(cameraMat);
	}
	if (input2 == 2) {
		histogram_Equalization(livingMat);
		histogram_Equalization(cameraMat);
	}
	
	

		//-----------------------c=100-----------------------//

	//-----------------------5. Release memory-----------------------//
	fclose(lenaFile);
	fclose(resultFile);
	delete living;
	destroyWindow("lenaFile");
	livingMat.release();

}
int histogram(Mat a) {
	for (int k = 0; k < 256; k++) {
		for (int i = 0; i < WIDTH; i++) {
			for (int j = 0; j < HEIGHT; j++) {
				if (a.data[i * WIDTH + j] == k) {
					HISTOGRAM[k] = HISTOGRAM[k] + 1;
				}
			}
		}
	}
	Mat histogram_image = Mat(256,256, CV_8UC1);
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 256; j++) {
			histogram_image.data[i * 256 + j] = 0;
		}
	}
	for (int k = 0; k < 256; k++) {
		if (maxs < HISTOGRAM[k]) {
			maxs = HISTOGRAM[k];
		}
	}
	for (int i = 0; i < 256; i++) {
		HISTOGRAM[i] = (HISTOGRAM[i] / maxs * 255);
	}
	for (int i = 0; i < 256; i++) {
		line(histogram_image, Point(i, 255),Point(i,255- HISTOGRAM[i]),Scalar(255));
	}	
	imshow("histogram", histogram_image);//display Image 
	waitKey(0);

	return 0;
}
int histogram_Equalization(Mat a) {
	for (int i = 0; i < WIDTH; i++) {
		HISTOGRAM_1[i] = 0;
	}
	for (int i = 0; i < 256; i++) {
		HISTOGRAM_1[i] = 0;
	}
	for (int k = 0; k < 256; k++) {
		for (int i = 0; i < WIDTH; i++) {
			for (int j = 0; j < HEIGHT; j++) {
				if (a.data[i * WIDTH + j] == k) {
					HISTOGRAM_1[k] = HISTOGRAM_1[k] + 1;
				}
			}
		}
		
	}

	for (int k = 0; k < 256; k++) {
		for (int i = 0; i < WIDTH; i++) {
			for (int j = 0; j < HEIGHT; j++) {
				if (a.data[i * WIDTH + j] == k) {
					HISTOGRAM_Equalization[k] = HISTOGRAM_Equalization[k] + 1;
				}
			}
		}
		
	}
	Mat histogram_Equalization_1_image = Mat(512, 512, CV_8UC1);

	for (int i = 0; i < 256; i++) {
		int eq = 0;
		for (int j = 0; j <= i; j++) {
			/*HISTOGRAM_Equalization_1[i] = (HISTOGRAM[j]+eq)/255;*/
			eq = eq + HISTOGRAM_1[j];
		}
		eq = eq /(float)512;
		HISTOGRAM_Equalization_1[i] = eq;
		if (HISTOGRAM_Equalization_1[i] > max_cdf)
		{
			max_cdf = HISTOGRAM_Equalization_1[i];
		}
		if (HISTOGRAM_Equalization_1[i] < min_cdf) {
			min_cdf = HISTOGRAM_Equalization_1[i];
		}
		}
	for (int i = 0; i < 512; i++) {
		for (int j = 0; j < 512; j++) {
			int gray = a.data[i * 512 + j];
			histogram_Equalization_1_image.data[i * 512 + j] = round((HISTOGRAM_Equalization_1[gray] - 1) /(float)(max_cdf- min_cdf)* 255);
		}
	}
	histogram(histogram_Equalization_1_image);
	imshow("histogram_Equalization_image",histogram_Equalization_1_image);
	waitKey(0);
	return 0;
}