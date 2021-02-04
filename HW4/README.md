# NTUT EE ACV HW4
## :heart_eyes: Introduction my self
大家好，我是吳定軒，目前就讀於國立台北科技大學電機工程系碩士班，我將在我的github上分享我所實作的Project，內容也有許多需要改進的地方，如果你有甚麼建議歡迎寫信到我的信箱t109318095@ntut.org.tw。   

Hello everyone, I am TINGHSUAN-WU. I am currently studying in the Master's Program of the Department of Electrical Engineering, National Taipei University of Technology. I will share the projects I have done on my Github. There are many areas for improvement in the content. If you have any suggestions, welcome Write to my mailbox.

## :yum: Introduction this project
這份作業是ACV(高等電腦視覺)，我使用C++及opencv來撰寫。

This assignment is ACV (Advanced Computer Vision), I use C++ and opencv to write.

## :books: Source
1. Opencv4.4.0
2. Visual Studio 2019
3. ![](https://i.imgur.com/YpA1ndu.png)

## :book: Method
### Discussion:

**H4**

**1.建立環境:** 建立環境的過程極其的複雜，可使用cmake來建立，建立步驟如附檔(劉俊毅同學撰寫)。

**2.在影片中加入tracker:** 使用`Ptr<Tracker> tracker = TrackerMedianFlow::create();`來啟用內建的Tracker，在第一部影片，使用MedianFlow是最準確的，並且使用tracker->init(frame,roi);來初始化tracker，最後在do while迴圈中不斷的update tracker，tracker->update(frame,roi)，其中roi為追蹤的左上角(x,y)座標、高度、寬度，frame為影片拆為一張一張圖片輸入的代稱，並且為了方便製作IOU我將ground truth的第一個座標與長寬高代入。

**3.將Ground truth的txt檔讀取並且畫圖:** 先使用程式碼file.open開啟Ground truth txt檔案，並且去逐行逐列的讀取，我使用的方法是file.getline來讀取行，接著進去do的迴圈，使用strtod(x,&y)，來逐列逐行的讀取，並將讀取的四個數值儲存至d1,d2,d3,d4，再將這四個數值放入rectangle裡進行畫圖，下一次在讀下一行，即可完成。

**4.IOU製作:**
IOU架構如下

![](https://i.imgur.com/B3q6Dac.png)

 https://blog.csdn.net/IAMoldpan/article/details/78799857

**一、	Area of Overlap計算:**
上方為交集的面積，也就是追蹤的框框與ground truth的框框交集面積，面積為長乘寬，我們先找交集面積左上角的座標，將兩個框框的左上角取較大的數值a=max(x,x_gt)，x為追蹤的框框，x_gt為ground truth的框框，以下使用gt代替，b=max(y,y_gt) ，找完左上角的座標之後，再找右下角的座標，取較大的數值c=min(track高度,gt高度)、d=min(track寬度,gt寬度)，找到之後就可計算交集的面積公式如下(c-a+1)/(d-b+1)，+1的目的是為了防止0有分母的情況發生。

**二、	Area of Union計算:**
下方為聯集的面積，只要把兩個框框的面積加起來在剪掉Area of Overlap，公式如下
`(roi.height*roi.weight)+(d3*d4)`- Area of Overlap

**5.IOU CDF圖製作**
**一、	求PDF:**
再算CDF之前先製作PDF，PDF是IOU出現的機率，IOU的範圍為0 ~ 0.999999，所以我開了一個陣列[10]，來個別儲存0 ~ 0.1,0 ~ 0.2,......,0.9 ~ 0.99999，只要x出現一次陣列[x]+1，將每個數值帶入就可以獲得出現的次數，再將總次數去除與各個的次數，即可獲得PDF。

二、	CDF:
CDF為PDF的累加，IOU每10%分成一個區域，並且開設一個陣列[10]，來進行運算，即可獲得CDF。
三、	CDF圖片製作:
使用`line()`製作，將陣列的前後兩個數值連在一起，即可或的答案。

四、	計算Time
使用`time.h`來進行計算。

**Bonus**

是用了許多Tracker，不是運算量太大，就是準度太低，最後使用的還是MedianFlow來進行運算，效果蠻差的。

**由於這次的輸入輸出是影片，檔案量太大無法上傳，所以我就不附上了。**

## :warning:嚴禁抄襲
這些只是提供我自己的想法而已，程式碼撰寫得也沒有到很嚴謹，禁止抄襲。

These are just to provide my own ideas, and the code is not written very rigorously. I hope that there will be no plagiarism.

## :smile: Owner
Made by https://github.com/WU-TING-HSUAN

## :+1: School
:point_right:National Taipei University of Technology	:point_left:

