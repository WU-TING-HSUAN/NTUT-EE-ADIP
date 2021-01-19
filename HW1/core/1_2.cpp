#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <time.h>
using namespace cv;

int a()
{
	int width = 256;
	int height = 256;
	int isused;
	int rd;
	int size = width * height;
	int n[16];
	int a[15];
	char input[100];
	char OriFile[] = "figure/input/lena256.raw";    //Input Image name
	char OutFile[] = "figure/input/lena256out.raw"; //Output Raw Image name
	char Out1File[] = "figure/input/lenarandomout1.raw"; //Output Raw Image name
	char Out2File[] = "figure/input/lenarandomout2.raw"; //Output Raw Image name
	char Out3File[] = "figure/input/moonstar.raw";
	char In1File[] = "figure/input/p01.raw";
	char In2File[] = "figure/input/p02.raw";
	char In3File[] = "figure/input/p03.raw";
	char In4File[] = "figure/input/p04.raw";
	Mat lenas[16];
	Mat lenanser[16];

	//-----------------------1. Read File-----------------------//
	FILE* lenaFile,* PoneFile, * PtwoFile, * PthreeFile, * PfourFile,* resultFile,* result1File, * result2File, * result3File;
	lenaFile = fopen(OriFile, "rb");
	PoneFile = fopen(In1File, "rb");
	PtwoFile = fopen(In2File, "rb");
	PthreeFile = fopen(In3File, "rb");
	PfourFile = fopen(In4File, "rb");
	resultFile = fopen(OutFile, "wb");
	result1File = fopen(Out1File, "wb");
	result2File = fopen(Out2File, "wb");
	result3File = fopen(Out3File, "wb");
	if (lenaFile == NULL) {
		puts("Loading File Error!");
		system("PAUSE");
		exit(0);
	}
	/*unsigned int buff;*/
	unsigned char* lenai = new unsigned char[size];
	unsigned char* a1 = new unsigned char[size];
	unsigned char* a2 = new unsigned char[size];
	unsigned char* a3 = new unsigned char[size];
	unsigned char* a4 = new unsigned char[size];
	fread(lenai, size, 1, lenaFile);
	fread(a1, size,1, PoneFile);
	fread(a2, size, 1, PtwoFile);
	fread(a3, size, 1, PthreeFile);
	fread(a4, size, 1, PfourFile);
	//-----------------------2. Transfer data type to OpenCV-----------------------//
	//-----------------------You can use "CvMat" or "IplImage" or "Mat"-----------------------//

	Mat lenaMat(height, width, CV_8UC1, lenai);
	Mat a1Mat(height, width, CV_8UC1, a1);
	Mat a2Mat(height, width, CV_8UC1, a2);
	Mat a3Mat(height, width, CV_8UC1, a3);
	Mat a4Mat(height, width, CV_8UC1, a4);

	printf("ex:1.2-b\nex:1.2-c\nex:1.2-d\nex:1.2-e\nex:1.2-f\nEnter the question number to select out result:");
	scanf("%s", input);
	//.......................1.2 B作業................///
	if(strcmp(input,"1.2-b")==0)
	{
		uchar B_1 = lenaMat.at<uchar>(123, 234);
		rd = 5487 / 256;
		uchar B_2 = lenaMat.at<uchar>(5487);
		printf("This is No.123rd&No.234th:%d \nThis is No.5487:%d\n", B_1,B_2);
		printf("This is No.5487 pixel coordinate row:%d,col:%d\n",rd,5487-rd*256);
	}
	//.......................1.2 D作業................///
	Mat Dleana(height, width, CV_8UC1);
	for (int i = 0; i <width; i++)
		for(int j =0;j< height;j++)
			Dleana.at<uchar>(j,i) = lenaMat.at<uchar>(i,j);
	
	//.......................1.2 F作業................///
	Mat Fleana(height*2, width*2, CV_8UC1);
	for (int i = 0; i < 4; i++) {   
		for (int j = 0; j < width; j++) {
			for (int k = 0; k < height; k++) {
				if (i == 0) {
					Fleana.at<uchar>(j,k) = a3Mat.at<uchar>(j,k);
				}            
				if (i == 1) {
					Fleana.at<uchar>((i / 4) * width + j, i % 4 * height + k) = a4Mat.at<uchar>(j, k);
				}
				if (i == 2) {
					Fleana.at<uchar>((i / 2) * width + j, i % 2 * height + k) = a2Mat.at<uchar>(j, k);
				}
				if (i == 3) {
					Fleana.at<uchar>(i / 2 * width + j, i % 2 * height + k) = a1Mat.at<uchar>(j, k);
				}
			}
		}
	}
	//-----------------------3. Create window and show your Image-----------------------//
	if (strcmp(input, "1.2-c") == 0) {
		namedWindow("1.2-c", 0);
		resizeWindow("1.2-c", width, 256);
		moveWindow("1.2-c", 100, 100);
		imshow("1.2-c", lenaMat);//display Image	
		waitKey(0);
	}
	if (strcmp(input, "1.2-d") == 0) {
		namedWindow("1.2-d", 0);
		resizeWindow("1.2-d", width, height);
		moveWindow("1.2-d", 100, 100);
		fwrite(Dleana.ptr(0, 0), 1, size, resultFile);
		imshow("1.2-d", Dleana);//display Image	
		waitKey(0);
		
	}
	//.......................1.2 E作業................///
	//for (int i = 0; i < 16; i++) {
		//Mat a[i]= lenaMat(Range(0, 64), Range(0, 64));
	//}
	Mat Eleana(height, width, CV_8UC1);
	Mat E2leana(height, width, CV_8UC1);
	srand(time(NULL));
	if (strcmp(input, "1.2-e") == 0) {
		for (int q = 0; q < 2; q++)
		{
			for (int i = 1; i <= 16; i++) {
				do {
					n[i - 1] = rand() % 16 + 1;
					isused = 0;
					for (int j = 1; j < i; j++) {
						if (n[i - 1] == n[j - 1]) {
							isused = 1;
						}
					}
				} while (isused == 1);
			}

		
			
			if (q == 0)
			{
				for (int k = 0; k < 16; k++) {
					for (int i = 0; i < 64; i++) {
						for (int j = 0; j < 64; j++) {
							Eleana.at<uchar>((n[k] - 1) / 4 * 64 + i, (n[k] - 1) % 4 * 64 + j) = lenaMat.at<uchar>(k / 4 * 64 + i, k % 4 * 64 + j);
						}
					}
				}
				namedWindow("1.2-e", 0);
				resizeWindow("1.2-e", width, height);
				moveWindow("1.2-e", 100, 100);
				imshow("1.2-e", Eleana);//display Image	
				waitKey(0);
				fwrite(Eleana.ptr(0, 0), 1, size, result1File);
			}
			if (q == 1)
			{
				for (int k = 0; k < 16; k++) {
					for (int i = 0; i < 64; i++) {
						for (int j = 0; j < 64; j++) {
							E2leana.at<uchar>((n[k] - 1) / 4 * 64 + i, (n[k] - 1) % 4 * 64 + j) = lenaMat.at<uchar>(k / 4 * 64 + i, k % 4 * 64 + j);
						}
					}
				}
				namedWindow("1.2-e", 0);
				resizeWindow("1.2-e", width, height);
				moveWindow("1.2-e", 100, 100);
				imshow("1.2-e", E2leana);//display Image	
				waitKey(0);
				fwrite(E2leana.ptr(0, 0), 1, size, result2File);
			}

		}
	}
	if (strcmp(input, "1.2-f") == 0) {
		namedWindow("1.2-f", 0);
		resizeWindow("1.2-f", width, height);
		moveWindow("1.2-f", 100, 100);
		imshow("1.2-f", Fleana);//display Image	
		fwrite(Fleana.ptr(0, 0), 1, size*4, result3File);
		waitKey(0);
	}
	//-----------------------4. Save Image as raw format-----------------------//
	
	/*fwrite(Dleana, 1, size, resultFile);*/
	//-----------------------5. Release memory-----------------------//
	fwrite(Dleana.ptr(0, 0), 1, size, resultFile);
	fwrite(Eleana.ptr(0, 0), 1, size, result1File);
	fwrite(E2leana.ptr(0, 0), 1, size, result2File);
	fwrite(Fleana.ptr(0, 0), 1, size * 4, result3File);

	fclose(lenaFile);
	fclose(resultFile);
	delete lenai;
	destroyWindow("lenaFile");
	lenaMat.release();
}
