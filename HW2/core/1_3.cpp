#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <math.h>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <time.h>

using namespace cv;

Mat nearest(Mat a,int aa,int aaa,float b);
Mat bilnear(Mat a, int aa, int aaa, float b);
Mat Bicubic(Mat a, int aa, int aaa, float b);
float wx(float a);
float wy(float a);
clock_t t1, t2;
int countb1 = 1;
int countb2 = 1;
int countb3 = 1;
int one_three()
{
	int width = 256;
	int height = 256;
	int size = width * height;
	char B[255];
	char OriFile[] = "lena256.raw";    //Input Image name
	char OutFile1[] = "1.raw"; //Output Raw Image name
	char OutFile2[] = "2.raw"; //Output Raw Image name
	char OutFile3[] = "3.raw"; //Output Raw Image name
	char OutFile4[] = "4.raw"; //Output Raw Image name
	char OutFile5[] = "5.raw"; //Output Raw Image name
	char OutFile6[] = "6.raw"; //Output Raw Image name
	char OutFile7[] = "7.raw"; //Output Raw Image name
	char OutFile8[] = "8.raw"; //Output Raw Image name
	char OutFile9[] = "9.raw"; //Output Raw Image name
	
	//-----------------------1. Read File-----------------------//
	FILE* lenaFile, * lenaFile1, * lenaFile2, * result1File, * result2File, * result3File, * result4File, * result5File, * result6File, * result7File, * result8File, * result9File;
	lenaFile = fopen(OriFile, "rb");
	lenaFile1 = fopen(OriFile, "rb");
	lenaFile2 = fopen(OriFile, "rb");
	result1File = fopen(OutFile1, "wb");
	result2File = fopen(OutFile2, "wb");
	result3File = fopen(OutFile3, "wb");
	result4File = fopen(OutFile4, "wb");
	result5File = fopen(OutFile5, "wb");
	result6File = fopen(OutFile6, "wb");
	result7File = fopen(OutFile7, "wb");
	result8File = fopen(OutFile8, "wb");
	result9File = fopen(OutFile9, "wb");
	if (lenaFile == NULL) {
		puts("Loading File Error!");
		system("PAUSE");
		exit(0);
	}
	unsigned char* lenai = new unsigned char[size];
	unsigned char* lenai1 = new unsigned char[size];
	unsigned char* lenai2 = new unsigned char[size];
	fread(lenai, 1, size, lenaFile);
	fread(lenai1, 1, size, lenaFile1);
	fread(lenai2, 1, size, lenaFile2);
	Mat lenaMat = Mat(height, width, CV_8UC1, lenai); //unsign 8bit channel 1(灰階)
	Mat lenaMat1 = Mat(height, width, CV_8UC1, lenai1); //unsign 8bit channel 1(灰階)
	Mat lenaMat2 = Mat(height, width, CV_8UC1, lenai2); //unsign 8bit channel 1(灰階)
	Mat sull = Mat(320, 320, CV_8UC1); //unsign 8bit channel 1(灰階)
	Mat sull1 = Mat(320, 320, CV_8UC1); //unsign 8bit channel 1(灰階)
	Mat sull2 = Mat(128, 128, CV_8UC1); //unsign 8bit channel 1(灰階)
	
	Mat sull3 = Mat(320, 320, CV_8UC1); //unsign 8bit channel 1(灰階)
	Mat sull4 = Mat(128, 128, CV_8UC1); //unsign 8bit channel 1(灰階)
	Mat sull5 = Mat(128, 128, CV_8UC1); //unsign 8bit channel 1(灰階)

	Mat c= nearest(lenaMat,256,256,2.5); //up2.5 small2
	for (int i = 0; i < sull.rows; i++) {
		for (int j = 0; j < sull.cols; j++) {
			sull.at<uchar>(i, j) = (c.at<uchar>(i * 2, j * 2) + c.at<uchar>(i * 2, j * 2 + 1) + c.at<uchar>(i * 2 + 1, j * 2) + c.at<uchar>(i * 2 + 1, j * 2 + 1)) / 4;
		}
	}
	Mat d = bilnear(lenaMat,256,256,2.5);//up2.5 small2
	for (int i = 0; i < sull1.rows; i++) {
		for (int j = 0; j < sull1.cols; j++) {
			sull1.at<uchar>(i, j) = (d.at<uchar>(i * 2, j * 2) + d.at<uchar>(i * 2, j * 2 + 1) + d.at<uchar>(i * 2 + 1, j * 2) + d.at<uchar>(i * 2 + 1, j * 2 + 1)) / 4;
		}
	}
	Mat k = Bicubic(lenaMat, 256, 256, 2.5);//up2.5 small2
	for (int i = 0; i < sull3.rows; i++) {
		for (int j = 0; j < sull3.cols; j++) {
			sull3.at<uchar>(i, j) = (k.at<uchar>(i * 2, j * 2) + k.at<uchar>(i * 2, j * 2 + 1) + k.at<uchar>(i * 2 + 1, j * 2) + k.at<uchar>(i * 2 + 1, j * 2 + 1)) / 4;

		}
	}


	for (int i = 0; i < sull2.rows; i++) {
		for (int j = 0; j < sull2.cols; j++) {
			sull2.at<uchar>(i, j) = (lenaMat.at<uchar>(i * 2, j * 2) + lenaMat.at<uchar>(i * 2, j * 2 + 1) + lenaMat.at<uchar>(i * 2 + 1, j * 2) + lenaMat.at<uchar>(i * 2 + 1, j * 2 + 1)) / 4;
			sull4.at<uchar>(i, j) = (lenaMat.at<uchar>(i * 2, j * 2) + lenaMat.at<uchar>(i * 2, j * 2 + 1) + lenaMat.at<uchar>(i * 2 + 1, j * 2) + lenaMat.at<uchar>(i * 2 + 1, j * 2 + 1)) / 4;
			sull5.at<uchar>(i, j) = (lenaMat.at<uchar>(i * 2, j * 2) + lenaMat.at<uchar>(i * 2, j * 2 + 1) + lenaMat.at<uchar>(i * 2 + 1, j * 2) + lenaMat.at<uchar>(i * 2 + 1, j * 2 + 1)) / 4;
		}
	}
	Mat g = nearest(sull2,128,128,2.5);//small2up2.5 
	Mat h = bilnear(sull4,128,128,2.5);//small2up2.5 
	Mat p = Bicubic(sull5, 128, 128, 2.5);//small2up2.5 

	Mat f = nearest(lenaMat, 256, 256, 1.25);//*1.25
	Mat e = bilnear(lenaMat1, 256, 256, 1.25);//*1.25
	Mat l = Bicubic(lenaMat2, 256, 256, 1.25);
	//-------------------------------------------------------------------------//
	
	//-----------------------4. Save Image as raw format-----------------------//
	fwrite(sull.ptr(0, 0), 1, sull.rows * sull.cols, result1File); //儲存圖片
	resizeWindow("nearest1", sull.rows, sull.cols); //視窗大小
	imshow("nearest1", sull);//display Image 
	waitKey(0);
	resizeWindow("nearest1", sull.rows, sull.cols); //視窗大小

	fwrite(sull1.ptr(0, 0), 1, sull1.rows * sull1.cols, result2File); //儲存圖片
	imshow("bilnear1", sull1);//display Image 
	waitKey(0);
	resizeWindow("bilnear1", sull1.rows, sull1.cols); //視窗大小
	moveWindow("bilnear1", 100, 100); //將視窗左上角放在螢幕指定位置

	fwrite(sull3.ptr(0, 0), 1, sull3.rows * sull3.cols, result3File); //儲存圖片
	imshow("Bicubic1", sull3);//display Image 
	waitKey(0);
	resizeWindow("lenaFile", sull3.rows, sull3.cols); //視窗大小
	moveWindow("lenaFile", 100, 100); //將視窗左上角放在螢幕指定位置

	fwrite(g.ptr(0, 0), 1, g.rows * g.cols, result4File); //儲存圖片
	imshow("nearest2", g);//display Image 
	waitKey(0);
	resizeWindow("nearest2", g.rows, g.cols); //視窗大小
	moveWindow("nearest2", 100, 100); //將視窗左上角放在螢幕指定位置

	fwrite(h.ptr(0, 0), 1, h.rows * h.cols, result5File); //儲存圖片
	imshow("bilnear2", h);//display Image 
	waitKey(0); 
	resizeWindow("bilnear2", h.rows, h.cols); //視窗大小
	moveWindow("bilnear2", 100, 100); //將視窗左上角放在螢幕指定位置


	fwrite(p.ptr(0, 0), 1, p.rows * p.cols, result6File); //儲存圖片
	imshow("Bicubic2", p);//display Image 
	waitKey(0);
	resizeWindow("Bicubic2", p.rows, p.cols); //視窗大小
	moveWindow("Bicubic2", 100, 100); //將視窗左上角放在螢幕指定位置

	fwrite(f.ptr(0, 0), 1, f.rows * f.cols, result7File); //儲存圖片
	imshow("nearest3", f);//display Image 
	waitKey(0);

	fwrite(e.ptr(0, 0), 1, e.rows * e.cols, result8File); //儲存圖片
	resizeWindow("bilnear3", e.rows, e.cols); //視窗大小
	imshow("bilnear3", e);//display Image 
	waitKey(0);

	fwrite(l.ptr(0, 0), 1, l.rows * l.cols, result9File); //儲存圖片
	resizeWindow("Bicubic3", l.rows, l.cols); //視窗大小
	imshow("Bicubic3", l);//display Image 
	waitKey(0);
	
	//-----------------------5. Release memory-----------------------//
	//fclose(lenaFile);
	//fclose(resultFile);
	delete lenai;
	//destroyWindow("lenaFile");
	//lenaMat.release();
}
Mat nearest(Mat a,int aa,int aaa,float b) {
	int width = aa;
	int height =aaa;
	int size = width * height;
	Mat c = Mat(height * b, width * b, CV_8UC1); //unsign 8bit channel 1(灰階)
	Mat d = Mat(height * b, width * b, CV_8UC1); //unsign 8bit channel 1(灰階)
	t1 = clock();

	
	for (int i = 0; i < aa-1; i++) {
		for (int j = 0; j < aaa-1; j++) {
			c.at<uchar>(i * b, j * b) = a.at<uchar>(i, j);
			//-----------------------nearest neighbor-----------------------//
			for (int k = i * b; k < (i + 1) * b; k++) {
				for (int l = j * b; l < (j + 1) * b; l++) {
					if (i <=(2*i+b)/2 && j <= (2*j+b)/2)
					{
						c.at<uchar>(k, l)=a.at<uchar>(i , j);
					}
					if (i <= (2 * i + b) / 2 && j>(2 * j + b) / 2)
					{
						c.at<uchar>(k, l) = a.at<uchar>(i, (j+1));
					}
					if (i > (2 * i + b) / 2 && j<(2 * j + b) / 2)
					{
						c.at<uchar>(k, l) = a.at<uchar>((i+1), j);
					}
					if (i > (2 * i + b) / 2 && j>(2 * j + b) / 2)
					{
						c.at<uchar>(k, l) = a.at<uchar>((i+1) , (j+1));
					}
				}
			}
			//-------------------------------------------------------------//.
			
		}
	}

	for (int j = (aa-1) * b; j < aa * b; j++) {
		for (int i = 0; i < aaa * b; i++) {
			c.at<uchar>(j, i) = c.at<uchar>(j-1, i);
		}
	}
	for (int j = (aa-1) * b; j < aa * b; j++) {
		for (int i = 0; i < aaa * b; i++) {
			c.at<uchar>(i, j) = c.at<uchar>(i, j-1);
		}
	}
	
	t2 = clock();
	printf("nearest %d time:%f\n", countb1, (t2 - t1) / (double)(CLOCKS_PER_SEC));
	countb1 += 1;
	return c;
}
Mat bilnear(Mat a,int aa,int aaa, float b)
{
	int width = aa;
	int height = aaa;
	int size = width * height;
	Mat c = Mat(height * b, width * b, CV_8UC1); //unsign 8bit channel 1(灰階)
	Mat d = Mat(height * b, width * b, CV_8UC1); //unsign 8bit channel 1(灰階)
	t1 = clock();
	for (int i = 0; i < aa-1; i++) {
		for (int j = 0; j < aaa-1; j++) {
			c.at<uchar>(i * b, j * b) = a.at<uchar>(i, j);
			d.at<uchar>(i * b, j * b) = a.at<uchar>(i, j);
			float x1, y1, x2, y2, Q11, Q12, Q21, Q22;
			float aQ11, aQ12, aQ21, aQ22;
			x1 = i * b;
			y1 = j * b;
			x2 = (i + 1) * b;
			y2 = (j + 1) * b;
			Q11 = a.at<uchar>(i, j);
			Q12 = a.at<uchar>(i, j + 1);
			Q21 = a.at<uchar>(i + 1, j);
			Q22 = a.at<uchar>(i + 1, j + 1);
			for (int k = i * b; k < (i + 1) * b; k++) {
				for (int l = j * b; l < (j + 1) * b; l++) {
					d.at < uchar>(k, l) = 1 / ((x2 - x1) * (y2 - y1)) * (Q11 * (x2 - k) * (y2 - l) + Q21 * (k - x1) * (y2 - l) + Q12 * (x2 - k) * (l - y1) + Q22 * (k - x1) * (l - y1));
				}
			}
		}

		
	}
	for (int j = (aa-1) * b; j < aa * b; j++) {
		for (int i = 0; i < aaa * b; i++) {
			d.at<uchar>(j, i) = d.at<uchar>(j - 1, i);
		}
	}
	for (int j = (aa-1) * b; j < aa * b; j++) {
		for (int i = 0; i < aaa * b; i++) {
			d.at<uchar>(i, j) = d.at<uchar>(i, j - 1);
		}
	}
	t2 = clock();
	printf("bilnear  %d time:%f\n",countb2, (t2 - t1) / (double)(CLOCKS_PER_SEC));
	countb2 += 1;
	return d;
} 
Mat Bicubic(Mat a, int aa, int aaa, float b) {
	int width = aa;
	float o = 0;
	int height = aaa;
	int size = width * height;
	float tmp0, tmp1, tmp2, tmp3;
	int tmp4, tmp5, tmp6, tmp7;
	Mat c = Mat(height * b, width * b, CV_8UC1); //unsign 8bit channel 1(灰階)
	//tmp4 = (8 / b);//i整數
	//tmp1 = 8 - tmp4 * b;
	//printf("%f\n", tmp1);
	/*tmp0 = 254 / 2.5;
	tmp4 = 254 / 2.5;
	printf("%f", tmp0-tmp4);*/
	t1 = clock();
	for (int i=1; i < aa-2; i++) {
		for (int j=1; j < aaa -2; j++) {
			c.at<uchar>(i * b, j * b) = a.at<uchar>(i, j);
			for (int k = (i-1) * b; k < i  * b; k++) {
				for (int l = (j-1) * b; l < j  * b; l++){
					double o = 0;
					for (int t = 0; t < 4; t++) {
						for (int r = 0; r < 4; r++) {
							double score[10];

							tmp0 = i / 2.5;
							tmp4 = i / 2.5;
							tmp1 = tmp0 - tmp4;
							tmp3 = j / 2.5;
							tmp5 = j / 2.5;
							tmp2 = tmp3 - tmp5;
							score[0] = 1 + tmp1;
							score[1] = tmp1;
							score[2] = 1 - tmp1;
							score[3] = 2 - tmp1;
							score[4] = 1 + tmp2;
							score[5] = tmp2;
							score[6] = 1 - tmp2;
							score[7] = 2 - tmp2;

							float w1 = wx(score[t]);
							float w2 = wy(score[4 + r]);
							o = o+ a.at<uchar>(i,j)*w1 * w2;
							/*printf("%f\n", o);*/
						} 
					}
					c.at<uchar>(k, l) = o;
				}
			}
		}
	}
	/*for (int i = 0; i < aa * b; i++) {
		for (int j = 0; j < aaa * b; j++) { 
			c.at<uchar>(i, j) = a.at<uchar>(i, j);
		}
	}*/
	
	t2 = clock();
	printf("Bicubic %d time:%f\n", countb3,(t2 - t1) / (double)(CLOCKS_PER_SEC));
	countb3 += 1;
	return c;
}
float wx(float a) {
	/*printf("1:%f", a);*/
	float aa = abs(a);
	//printf("a1:%f\n", aa);
	if (abs(a) <= 1) {
		a = 1.5 * pow(abs(a), 3) - 2.5 * pow(a, 2) +1;
		/*printf("a1:%f\n", a);*/
	}
	//printf("%f", aa);
	if (1<abs(a) && abs(a) <= 2) {
		a = -0.5 * pow(abs(a), 3) - 5*(-0.5) * pow(abs(a), 2) + 8*(-0.5)* abs(a)-4*(-0.5);
		/*printf("aa2%f\n", aa);*/
	}
	return a;
}
float wy(float a) {
	/*printf("2:%f", a);*/
	float aa = abs(a);
	/*printf("2:%f", a);*/
	if (abs(a) <= 1) {
		a = 1.5 * pow(abs(a), 3) - 2.5 * pow(abs(a), 2) + 1;

	}
	if (1 < abs(a) && abs(a) <= 2) {
		a = -0.5 * pow(abs(a), 3) - 5 * (-0.5) * pow(abs(a), 2) + 8 * (-0.5) * abs(a) - 4 * (-0.5);
	}
	return a;
}