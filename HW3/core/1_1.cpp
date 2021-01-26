#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace cv;


int one_one()
{
	int WIDTH = 256;
	int HEIGHT = 256;
	int size = WIDTH * HEIGHT;
	int mse,mse1,mse2,mse3,mse4,mse5;
	char B[255];
	char OriFile[] = "lena_256.raw";    //Input Image name
	char OriFile_baboon[] = "baboon_256.raw";    //Input Image name
	char OutFile[] = "lena_with_baboon.raw"; //Output Raw Image name
	double Q = 0;
	double P = 0;

	//-----------------------1. Read File-----------------------//
	FILE* lenaFile, * lenaFile_baboon, * resultFile, * result1File;
	lenaFile = fopen(OriFile, "rb");
	lenaFile_baboon = fopen(OriFile_baboon, "rb");
	resultFile = fopen(OutFile, "wb");

	if (lenaFile == NULL) {
		puts("Loading File Error!");
		system("PAUSE");
		exit(0);
	}
	unsigned char* lenai = new unsigned char[size];
	unsigned char* babooni = new unsigned char[size];
	fread(lenai, 1, size, lenaFile);
	fread(babooni, 1, size, lenaFile_baboon);
	Mat lenaMat = Mat(HEIGHT, WIDTH, CV_8UC1, lenai); //unsign 8bit channel 1(灰階)
	Mat baboonMat = Mat(HEIGHT, WIDTH, CV_8UC1, babooni);
	Mat LenaMat = Mat(HEIGHT, WIDTH, CV_8UC1);
	Mat LenacompareMat = Mat(HEIGHT, WIDTH, CV_8UC1);

	Mat bit_plane[8];
	Mat baboon_bit_plane[8];
	Mat lena_plan[8];
	int pow_bit;
	 for (int i = 0; i < 8; i++) { //bit plane
	  bit_plane[i] = Mat(lenaMat.rows, lenaMat.cols, CV_8UC1);
	  baboon_bit_plane[i] = Mat(baboonMat.rows, baboonMat.cols, CV_8UC1);
	  lena_plan[i] = Mat(WIDTH, HEIGHT, CV_8UC1);
	 }
	 for (int k = 0; k < 8;k++) {
		for (int i = 0; i < lenaMat.rows; i++) {
			for (int j = 0; j < lenaMat.cols; j++) {
			pow_bit = pow(2, k);
			bit_plane[k].data[i * WIDTH + j] = (lenaMat.data[i * WIDTH + j]& pow_bit)/ pow_bit;
			}
		}
	 }

	 for (int k = 0; k < 8; k++) {
		 for (int i = 0; i < baboonMat.rows; i++) {
			 for (int j = 0; j < baboonMat.cols; j++) {
				 pow_bit = pow(2, k);
				 baboon_bit_plane[k].data[i * WIDTH + j] = (baboonMat.data[i * WIDTH + j] & pow_bit)/ pow_bit;
			 }
		 }
	 }
	 for (int k = 0; k < 4; k++) {
		 for (int i = 0; i < lenaMat.rows; i++) {
			 for (int j = 0; j < lenaMat.cols; j++) {
				 bit_plane[k].data[i * WIDTH + j] = baboon_bit_plane[4+k].data[i * WIDTH + j];
			 }
		 }
	 }
	 for (int i = 0; i < WIDTH; i++) {
		 for (int j = 0; j < HEIGHT; j++) {
			 LenaMat.data[i * WIDTH + j] = 0;
			 LenacompareMat.data[i * WIDTH + j] = 0;
		 }
	 }
	 for (int k = 0; k < 8; k++) {
		 for (int i = 0; i < WIDTH; i++) {
			 for (int j = 0; j < HEIGHT; j++) {
				 pow_bit = pow(2, k);
				 LenaMat.data[i * WIDTH + j] = LenaMat.data[i * WIDTH + j] + bit_plane[k].data[i * WIDTH + j]* pow_bit;
			 }
		 }
	}

	 for (int k = 0; k < 4; k++) {
		 for (int i = 0; i < lenaMat.rows; i++) {
			 for (int j = 0; j < lenaMat.cols; j++) {
				 pow_bit = pow(2, k+4);
				 LenacompareMat.data[i * WIDTH + j] = LenacompareMat.data[i * WIDTH + j]+ bit_plane[k].data[i * WIDTH + j] * pow_bit;
			 }
		 }
	 }
	 for (int k = 0; k < 8; k++) {
			for (int i = 0; i < lenaMat.rows; i++) {
				for (int j = 0; j < lenaMat.cols; j++) {
					pow_bit = pow(2, k);
					bit_plane[k].data[i * WIDTH + j] = (LenaMat.data[i * WIDTH + j] & pow_bit) / pow_bit * 255;
				}
			}
			imwrite("4.jpg", bit_plane[3]);
			waitKey(0);
		}
		for (int i = 0; i < lenaMat.rows; i++) {
			for (int j = 0; j < lenaMat.cols; j++) {
				mse1 = lenaMat.at<uchar>(i, j);
				mse2 = LenaMat.at<uchar>(i, j);
				mse = pow((mse1 - mse2), 2);
				Q = Q + mse;
			}
		}
		Q = Q / (WIDTH * HEIGHT);
		for (int i = 0; i < baboonMat.rows; i++) {
			for (int j = 0; j < baboonMat.cols; j++) {
				mse4 = baboonMat.at<uchar>(i, j);
				mse5 = LenacompareMat.at<uchar>(i, j);
				mse3 = pow((mse4 - mse5), 2);
				P = P + mse3;
			}
		}
		P = P / (WIDTH * HEIGHT);
		Mat q = Mat(256, 256, CV_8UC1);

		printf("lena_with_baboon對lena的MSE為%f",Q);
		printf("\n");
		printf("lena_with_baboon對lena的PSNR為%f",10 * log10(255 * 255 / Q));
		printf("\n");
		printf("lena_with_baboon對babbon的MSE為%f", P);
		printf("\n");
		printf("lena_with_baboon對babbon的PSNR為%f", 10 * log10(255 * 255 / P));
		printf("\n");
	fwrite(LenaMat.ptr(0, 0), 1, size, resultFile); //儲存圖片
	namedWindow("lena_with_baboon", 0); //視窗名
	resizeWindow("lena_with_baboon", 256, 256); //視窗大小
	imshow("lena_with_baboon", LenaMat);//display Image 
	waitKey(0);
	//-----------------------4. Save Image as raw format-----------------------//
	//fwrite(null.ptr(0, 0), 1, size, resultFile); //儲存圖片
	//namedWindow("lenaFile", 0); //視窗名
	//resizeWindow("lenaFile", 256, 256); //視窗大小
	//moveWindow("lenaFile", 100, 100); //將視窗左上角放在螢幕指定位置
	//imshow("lenaFile", null);//display Image 
	//waitKey(0);
	//-----------------------5. Release memory-----------------------//
	fclose(lenaFile);
	fclose(resultFile);
	delete lenai;
	destroyWindow("lenaFile");
	lenaMat.release();
	/*cvReleaseMat(&lenaMat);
	cvReleaseImage(&lenaIpl);*/
}