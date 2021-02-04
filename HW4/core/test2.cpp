#include <opencv2/core/utility.hpp>
#include <opencv2/tracking/tracking.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cstring>
#include<fstream>
#include <time.h>
using namespace std;
using namespace cv;
int max(int a, int b);
int min(int a, int b);
void total(double a);
int IOU_total[10];
int main(int argc, char** argv) {
    fstream file;
    char buffer[200];
    char* pStart = buffer;
    clock_t t1, t2; // typedef time_t long;
    double IOU, overlap_x_max, overlap_y_max,overlap_x_min, overlap_y_min,interArea,groudtruthArea, trackArea;
    char* pEnd;
    char* pEnd_1;
    char* pEnd_2;
    char ad[128] = { 0 };
    int count = 0;
    int dx = 0;
    float PDF[10];
    float CDF[10];
    // declares all required variables
    Mat CDFMat = Mat::zeros(500,500, CV_8UC1);
    Mat frame;
    // create a tracker object
    Ptr<Tracker> tracker = TrackerMedianFlow::create();
    // set input video
    //  std::string video = argv[1];
    VideoCapture cap("1.avi");

    // get bounding box
    cap >> frame;
    Rect2d roi(422, 131, 60, 64);
   /* Rect2d roi(512,120,80,102);*/ //BONIUS
    Rect2d roi_truth;
    printf("Start the tracking process, press ESC to quit.\n");
    file.open("GroundTruth_1.txt", ios::in);
    //file.open("GroundTruth_2.txt", ios::in);//BONIUS
    int i = 1;
    tracker->init(frame, roi);
    if (!file)
        cout << "無法開啟檔案!\n";

    else {
        file.getline(buffer, sizeof(buffer));
        file.getline(buffer, sizeof(buffer));//BONUIS需要把這行關掉
      
        do {
           
            t1 = clock();
            file.getline(buffer, sizeof(buffer));
            int d1, d2, d3, d4;

            d1 = strtod(buffer, &pEnd);
            d2 = strtod(pEnd, &pEnd_1);
            d3 = strtod(pEnd_1, &pEnd_2);
            d4 = strtod(pEnd_2, NULL);
            // get frame from the video
            cap >> frame;
            // stop the program if no more images
            if (frame.rows == 0 || frame.cols == 0)
                break;

            // update the tracking result
            tracker->update(frame,roi);
            // draw the tracked object
            rectangle(frame, roi, Scalar(255, 0, 0), 2, 1);
            roi_truth = Rect2d(d1,d2,d3,d4);
            rectangle(frame, roi_truth, Scalar(0, 0, 255), 2);
            // show image with the tracked object
            imshow("tracker", frame);
            t2  = clock();
            overlap_x_max = max(d1, roi.x);
            overlap_y_max = max(d2, roi.y);
            overlap_x_min = min(d1+d3, roi.x+roi.height);
            overlap_y_min = min(d2+d4, roi.y+roi.width);
            interArea = (overlap_x_min - overlap_x_max + 1) * (overlap_y_min - overlap_y_max + 1);
            trackArea = roi.height * roi.width;
            groudtruthArea = d3 * d4 ;
            IOU = interArea / float(trackArea + groudtruthArea - interArea);
           /* printf("%f\n", IOU);*/
            total(IOU);
            printf("Average computational time per frame:%f\n",(t2 - t1) / (double)(CLOCKS_PER_SEC));
            //quit on ESC button
            i = i + 1;
            /*if (i == 30) {
                sprintf_s(ad, "C:\\Users\\xie\\source\\repos\\Project3\\Project3\\pic3\\test%d.jpg", ++dx);
                imwrite(ad, frame);
                i = 0;
            }*/
            if (waitKey(1) == 27)break;
        } while (!file.eof());
        file.close();
    }
    for (int i = 0; i < 10; i++) {
        count += IOU_total[i];
    }
    for (int i = 0; i < 10; i++) {
        PDF[i]= IOU_total[i]/(float)count;
    }
    for (int i = 0; i < 10; i++) {
        float cdf = 0;
        for (int j = 0; j <= i; j++) {
            cdf += PDF[j];
        }
        CDF[i] = cdf;
    }
    for (int i = 0; i < 9; i++) {
        line(CDFMat, Point(50*i,500-500* CDF[i]), Point(50*(i+1),500-500* CDF[i+1]), Scalar(255));
    }
    imshow("CDF", CDFMat);
    waitKey(0);
}
int max(int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}
int min(int a, int b) {
    if (a > b)
        return b;
    else
        return a;
}
void total(double a){
    if (0.9 <= a < 1) {
        IOU_total[9] += 1;
    }
    if (0.8 <= a < 0.9) {
        IOU_total[8] += 1;
    }
    if (0.7 <= a < 0.8) {
        IOU_total[7] += 1;
    }
    if (0.6 <= a < 0.7) {
        IOU_total[6] += 1;
    }
    if (0.5 <= a < 0.6) {
        IOU_total[5] += 1;
    }
    if (0.4 <= a < 0.5) {
        IOU_total[4] += 1;
    }
    if (0.3 <= a < 0.4) {
        IOU_total[3] += 1;
    }
    if (0.2 <= a < 0.3) {
        IOU_total[2] += 1;
    if (0.1 <= a < 0.2) {
        IOU_total[1] += 1;
        }
    if (0 <= a < 0.1) {
        IOU_total[0] += 1;
    }
    }
}