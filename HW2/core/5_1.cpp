#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
using namespace cv;
int find_path(Mat a,Mat aa,int b,int c,int d, int e, int f);
int find_8(Mat aa, Mat aaa, int b, int c, int d, int e, int f);
int find_m(Mat aa, Mat aaa, int b, int c, int d, int e, int f);
int c = 0;

int width = 20;
int height = 20;
int step = 0;
int step_m = 0;
int step_4 = 0;
int stepcount = 0;
int steptottle = 1000000;
int steptottle_m = 1000000;
int steptottle_4 = 1000000;
int score[100];
int step_count = 0;
int finial = 0;
int point_array = 0;
int point_array1 = 0;
int point_array_row[10000000];
int point_array_col[10000000];
int position_4[4][2] = { {0,1},{1,0},{0,-1},{-1,0} };
int position_8[8][2] = { {1,1},{-1,1},{1,-1},{-1,-1},{0,1},{1,0},{0,-1},{-1,0} };
int position_m[8][2] = { {1,1},{-1,1},{1,-1},{-1,-1},{0,1},{1,0},{0,-1},{-1,0}};
int five()
{
	
	int a;
	int size = width * height;
	char B[255];
	char OriFile[] = "map.raw";    //Input Image name
	char OriFile1[] = "map.raw";    //Input Image name
	char OriFile2[] = "map.raw";    //Input Image name
	char OriFile3[] = "map.raw";    //Input Image name
	char OutFile[] = "map_out.raw"; //Output Raw Image name
	int map8[20][20];
	int ip;
	score[1] = 80;
	score[0] = 69;
	//-----------------------1. Read File-----------------------//
	FILE* lenaFile, * lenaFile1, * lenaFile2,  * lenaFile3,*resultFile, * result1File;
	lenaFile = fopen(OriFile, "rb");
	lenaFile1 = fopen(OriFile1, "rb");
	lenaFile2 = fopen(OriFile2, "rb");
	lenaFile3 = fopen(OriFile3, "rb");
	resultFile = fopen(OutFile, "wb");
	if (lenaFile == NULL) {
		puts("Loading File Error!");
		system("PAUSE");
		exit(0);
	}
	unsigned char* lenai = new unsigned char[size];
	unsigned char* lenai1 = new unsigned char[size];
	unsigned char* lenai2 = new unsigned char[size];
	unsigned char* lenai3 = new unsigned char[size];
	fread(lenai, 1, size, lenaFile);
	fread(lenai1, 1, size, lenaFile1);
	fread(lenai2, 1, size, lenaFile2);
	fread(lenai3, 1, size, lenaFile3);
	Mat lenaMat = Mat(height, width, CV_8UC1, lenai); //unsign 8bit channel 1(灰階)
	Mat lenaMat4 = Mat(height, width, CV_8UC1, lenai3); //unsign 8bit channel 1(灰階)
	Mat lenaMat4_tmp = Mat(height, width, CV_8UC1); //unsign 8bit channel 1(灰階)
	Mat lenaMat8 = Mat(height, width, CV_8UC1, lenai1); //unsign 8bit channel 1(灰階)
	Mat lenaMat8_tmp = Mat(height, width, CV_8UC1); //unsign 8bit channel 1(灰階)
	Mat lenaMatm = Mat(height, width, CV_8UC1,lenai2); //unsign 8bit channel 1(灰階)
	Mat lenaMatm_tmp = Mat(height, width, CV_8UC1); //unsign 8bit channel 1(灰階)

	printf("請輸入小題數 1.{80} 2.{80 160} 3.{80 160 255}\n");
	scanf("%d",&ip);
	if (ip == 1) {
		int d4 = find_path(lenaMat4, lenaMat4_tmp, 0, 0, 80, 0, 0);
		printf("D4{ 80 }最短步數為:%d", steptottle_4);
		printf("\n");
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				if (lenaMat4_tmp.data[i * width + j] != 69) {
					lenaMat4_tmp.data[i * width + j] = 0;
				}
			}
		}
		int d8 = find_8(lenaMat8, lenaMat8_tmp, 0, 0, 80, 0, 0);
		printf("D8{ 80 }最短步數為:%d", steptottle);
		printf("\n");
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				if (lenaMat8_tmp.data[i * width + j] != 69) {
					lenaMat8_tmp.data[i * width + j] = 0;
				}
			}
		}
		int dm = find_m(lenaMatm, lenaMatm_tmp, 0, 0, 80, 0, 0);
		printf("Dm{ 80 }最短步數為:%d", steptottle_m);
		printf("\n");
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				if (lenaMatm_tmp.data[i * width + j] != 69) {
					lenaMatm_tmp.data[i * width + j] = 0;
				}
			}
		}

		namedWindow("lenaFile", 0); //視窗名
		resizeWindow("lenaFile", 100, 100); //視窗大小
		//moveWindow("lenaFile", 100, 100); //將視窗左上角放在螢幕指定位置
		imshow("lenaFile", lenaMat4_tmp);//display Image 
		waitKey(0);

	
		namedWindow("lenaFile", 0); //視窗名
		resizeWindow("lenaFile", 100, 100); //視窗大小
		//moveWindow("lenaFile", 100, 100); //將視窗左上角放在螢幕指定位置
		imshow("lenaFile", lenaMat8_tmp);//display Image 
		waitKey(0);

	
		namedWindow("lenaFile", 0); //視窗名
		resizeWindow("lenaFile", 100, 100); //視窗大小
		//moveWindow("lenaFile", 100, 100); //將視窗左上角放在螢幕指定位置
		imshow("lenaFile", lenaMatm_tmp);//display Image 
		waitKey(0);
	}
	if (ip == 2) {
		int d4 = find_path(lenaMat4, lenaMat4_tmp, 0, 0, 80,160,0);
		printf("D4{ 80 160 }最短步數為:%d", steptottle_4);
		printf("\n");
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				if (lenaMat4_tmp.data[i * width + j] != 69) {
					lenaMat4_tmp.data[i * width + j] = 0;
				}
			}
		}
		int d8 = find_8(lenaMat8, lenaMat8_tmp, 0, 0, 80, 160, 0);
		printf("D8{ 80 160 }最短步數為:%d", steptottle);
		printf("\n");
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				if (lenaMat8_tmp.data[i * width + j] != 69) {
					lenaMat8_tmp.data[i * width + j] = 0;
				}
			}
		}
		int dm = find_m(lenaMatm, lenaMatm_tmp, 0, 0, 80, 160, 0);
		printf("Dm{ 80 160 }最短步數為:%d", steptottle_m);
		printf("\n");
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				if (lenaMatm_tmp.data[i * width + j] != 69) {
					lenaMatm_tmp.data[i * width + j] = 0;
				}
			}
		}
	
		namedWindow("lenaFile", 0); //視窗名
		resizeWindow("lenaFile",100,100); //視窗大小
		//moveWindow("lenaFile", 100, 100); //將視窗左上角放在螢幕指定位置
		imshow("lenaFile", lenaMat4_tmp);//display Image 
		waitKey(0);
		
		namedWindow("lenaFile", 0); //視窗名
		resizeWindow("lenaFile", 100, 100); //視窗大小
		//moveWindow("lenaFile", 100, 100); //將視窗左上角放在螢幕指定位置
		imshow("lenaFile", lenaMat8_tmp);//display Image 
		waitKey(0);

		namedWindow("lenaFile", 0); //視窗名
		resizeWindow("lenaFile", 100, 100); //視窗大小
		//moveWindow("lenaFile", 100, 100); //將視窗左上角放在螢幕指定位置
		imshow("lenaFile", lenaMatm_tmp);//display Image 
		waitKey(0);
	}
	if (ip == 3) {
		int d4 = find_path(lenaMat4, lenaMat4_tmp, 0, 0, 80, 160, 255);
		printf("D4{ 80 160 255 }最短步數為:%d", steptottle_4);
		printf("\n");
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				if (lenaMat4_tmp.data[i * width + j] != 69) {
					lenaMat4_tmp.data[i * width + j] = 0;
				}
			}
		}
		int d8 = find_8(lenaMat8, lenaMat8_tmp, 0, 0, 80, 160, 255);
		printf("D8{ 80 160 255 }最短步數為:%d", steptottle);
		printf("\n");
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				if (lenaMat8_tmp.data[i * width + j] != 69) {
					lenaMat8_tmp.data[i * width + j] = 0;
				}
			}
		}
		int dm = find_m(lenaMatm, lenaMatm_tmp, 0, 0, 80, 160, 255);
		printf("Dm{ 80 160 255 }最短步數為:%d", steptottle_m);
		printf("\n");
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				if (lenaMatm_tmp.data[i * width + j] != 69) {
					lenaMatm_tmp.data[i * width + j] = 0;
				}
			}
		}

		
		namedWindow("lenaFile", 0); //視窗名
		resizeWindow("lenaFile", 100, 100); //視窗大小
		//moveWindow("lenaFile", 100, 100); //將視窗左上角放在螢幕指定位置
		imshow("lenaFile", lenaMat4_tmp);//display Image 
		waitKey(0);
		
		namedWindow("lenaFile", 0); //視窗名
		resizeWindow("lenaFile", 100, 100); //視窗大小
		//moveWindow("lenaFile", 100, 100); //將視窗左上角放在螢幕指定位置
		imshow("lenaFile", lenaMat8_tmp);//display Image 
		waitKey(0);

		fwrite(lenaMatm_tmp.ptr(0, 0), 1, size, resultFile); //儲存圖片
		namedWindow("lenaFile", 0); //視窗名
		resizeWindow("lenaFile", 100, 100); //視窗大小
		//moveWindow("lenaFile", 100, 100); //將視窗左上角放在螢幕指定位置
		imshow("lenaFile", lenaMatm_tmp);//display Image 
		waitKey(0);
	}
}

int find_path(Mat aa, Mat aaa, int b, int c, int d, int e, int f)
{
	
	aa.data[0 * width + 0] = score[stepcount];
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			if (e != 0) {
				if (aa.data[i * width + j] == e) {
					aa.data[i * width + j] = d;
				}
			}
			if (f != 0) {
				if (aa.data[i * width + j] == f) {
					aa.data[i * width + j] = d;
				}
			}
		}
	}
	if (b == 19 && c == 19) {
		if (steptottle_4 > step_4) {
			steptottle_4 = step_4;
			for (int i = 0; i < 20; i++) {
				for (int j = 0; j < 20; j++) {
					aaa.data[i * width + j] = aa.data[i * width + j];
				}
			}
		}

	}
	for (int i = 0; i < 4; i++) {
		int new_b = b + position_4[i][0];
		int new_c = c + position_4[i][1];
		if (new_b < 0 || new_b>20 || new_c < 0 || new_c >20 || step_4 > steptottle_4)
		{
			continue;
		}
		else {
				if (aa.data[new_b * width + new_c] == score[stepcount + 1]) {
					aa.data[new_b * width + new_c] = 69;
					step_4 += 1;
					find_path(aa, aaa, new_b, new_c, d, e, f);
					step_4 = step_4 - 1;
					aa.data[new_b * width + new_c] = 80;
				}
			}
	}
	return 0;
}
int find_8(Mat aa, Mat aaa, int b, int c, int d, int e, int f)
{
	aa.data[0 * width + 0] = score[stepcount];
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			if (e != 0) {
				if (aa.data[i * width + j] == e) {
					aa.data[i * width + j] = d;
				}
			}
			if (f != 0) {
				if (aa.data[i * width + j] == f) {
					aa.data[i * width + j] = d;
				}
			}
		}
	}
	if (b == 19 && c == 19) {
		if (steptottle > step) {
			steptottle = step;
			for (int i = 0; i < 20; i++) {
				for (int j = 0; j < 20; j++) {
					aaa.data[i * width + j] = aa.data[i * width + j];
				}
			}
		}

	}
	for (int i = 0; i < 8; i++) {
		int new_b = b + position_8[i][0];
		int new_c = c + position_8[i][1];
		if (new_b < 0 || new_b>20 || new_c < 0 || new_c >20 || step > steptottle)
		{
			continue;
		}
		else {
			if (i < 4) {

				if (aa.data[new_b * width + new_c] == score[stepcount + 1]) {
					if (aa.data[new_b * width + c] == score[stepcount + 1] && aa.data[b * width + new_c] == score[stepcount + 1]) {
						continue;
					}
					else {
						aa.data[new_b * width + new_c] = 69;
						step += 1;
						find_8(aa, aaa, new_b, new_c, d, e, f);
						step = step - 1;
						aa.data[new_b * width + new_c] = 80;
					}
				}
			}
			else {
				if (aa.data[new_b * width + new_c] == score[stepcount + 1]) {
					aa.data[new_b * width + new_c] = 69;
					step += 1;
					find_8(aa, aaa, new_b, new_c, d, e, f);
					step = step - 1;
					aa.data[new_b * width + new_c] = 80;
				}
			}
		}
	}
	return 0;
	/*aa.data[0 * width + 0] = score[stepcount];
	for (int i = 0; i < 20; i++) {
		
		for (int j = 0; j < 20; j++) {
			if (e != 0) {
				if (aa.data[i * width + j] == e) {
					aa.data[i * width + j] = d;
				}
			}
			if (f != 0) {
				if (aa.data[i * width + j] == f) {
					aa.data[i * width + j] = d;
				}
			}
		}
		
	}
	if (b == 19 && c == 19) {
		if (steptottle > step) {
			steptottle = step;
			printf("%d\n", steptottle);
			for (int i = 0; i < 20; i++) {
				for (int j = 0; j < 20; j++) {
					aaa.data[i * width + j] = aa.data[i * width + j];
				}
			}
		}
	
	}
	for (int i = 0; i < 8; i++) {
		int new_b = b + position_8[i][0];
		int new_c = c + position_8[i][1];
		if (new_b < 0 || new_b>20 || new_c < 0 || new_c >20 || step> steptottle)
		{
			continue;
		}
		else {
			if (aa.data[new_b * width + new_c] == score[stepcount + 1]) {
				aa.data[new_b * width + new_c] = 69;
				step += 1;
				find_8(aa, aaa, new_b, new_c, d, e, f);
				step = step - 1;
				aa.data[new_b * width + new_c] = 80;
			}
		}
	}
		return 0;*/
}
int find_m(Mat aa, Mat aaa, int b, int c, int d, int e, int f) {
	aa.data[0 * width + 0] = score[stepcount];
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			if (e != 0) {
				if (aa.data[i * width + j] == e) {
					aa.data[i * width + j] = d;
				}
			}
			if (f != 0) {
				if (aa.data[i * width + j] == f) {
					aa.data[i * width + j] = d;
				}
			}
		}
	}
		if (b == 19 && c == 19) {
			if (steptottle_m > step_m) {
				steptottle_m = step_m;
				for (int i = 0; i < 20; i++) {
					for (int j = 0; j < 20; j++) {
						aaa.data[i * width + j] = aa.data[i * width + j];
					}
				}
			}

		}
		for (int i = 0; i < 8; i++) {
			int new_b = b + position_m[i][0];
			int new_c = c + position_m[i][1];
			if (new_b < 0 || new_b>20 || new_c < 0 || new_c >20 || step_m > steptottle_m)
			{
				continue;
			}
			else {
				if(i<4){
				
					if (aa.data[new_b * width + new_c] == score[stepcount + 1]) {
						if (aa.data[new_b * width + c] == score[stepcount + 1] || aa.data[b * width + new_c] == score[stepcount + 1]) {
							continue;
						}
						else {
							aa.data[new_b * width + new_c] = 69;
							step_m += 1;
							find_m(aa, aaa, new_b, new_c, d, e, f);
							step_m = step_m - 1;
							aa.data[new_b * width + new_c] = 80;
						}
					}
				}
				else{
					if (aa.data[new_b * width + new_c] == score[stepcount + 1]) {
						aa.data[new_b * width + new_c] = 69;
						step_m += 1;
						find_m(aa, aaa, new_b, new_c, d, e, f);
						step_m = step_m - 1;
						aa.data[new_b * width + new_c] = 80;
					}
				}
			}
		}
		return 0;
}