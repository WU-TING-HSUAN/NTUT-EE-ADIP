# NTUT EE ADIP HW3
## :heart_eyes: Introduction my self
大家好，我是吳定軒，目前就讀於國立台北科技大學電機工程系碩士班，我將在我的github上分享我所實作的Project，內容也有許多需要改進的地方，如果你有甚麼建議歡迎寫信到我的信箱t109318095@ntut.org.tw。   

Hello everyone, I am TINGHSUAN-WU. I am currently studying in the Master's Program of the Department of Electrical Engineering, National Taipei University of Technology. I will share the projects I have done on my Github. There are many areas for improvement in the content. If you have any suggestions, welcome Write to my mailbox.

## :yum: Introduction this project
這份作業是ADIP(高等數位影像處理)，教授要求我們使用純C++ 來撰寫，但我還是有些地方使用了Opencv內建的程式碼，因為起初我不知道那是Opencv的內建程式碼，所以我會在解說時補上C++的語法。
## :book: Method
題目我把它放在了Question的資料夾可以去那邊觀看。

### 1.1
**Question:**

Bit Plane(C!C-+-~i-) (20%: Figure, 10%; Discussion, 10%)
(1) Hide baboon_256.raw in lena__.256.raw and save the ﬁie as lena__withmbaboon.raw. Explain
your method. Try not to visually alter baboonm256raw and lena_ 256.raw as much as you
can. Show your results of lena_ with__baboon.raw. Calculate MSE and PNSR of your
lena_with_baboon.raw with respect to the original lena“256.raw. Your design should have
the PSNR value as high as possible in both (1) & (2).

**Discussion:**

**圖片分層**:我先將原圖的lena的灰階值與2^x次方去做AND閘，11111111 & 00000001即可得到00000001也就是lena的最底層的灰階值，依上式即可得到lena的每一層，而baboon的做法也是一樣，並將兩張圖個別的層數儲存至個別的陣列裡，即可做接下來的運算。

**圖片合層**:接下來就是各種嘗試將baboon藏進lena的裡，經過我多次的嘗試發現，lena的Bit plane 5 ~ Bit plane 7一定得是lena的Bit plane 5 ~ Bit plane 7，如果再lena Bit plane 5 ~ Bit plane 7放入任何的baboon Bit plane，都會造成合成之後的圖片有破圖或者是baboon的影子，這也對映了教授上課時說道:越上層的bit plane越重要，所以我後來lena_with_baboon的Bit plane 0 ~ Bit plane 3為baboon的Bit plane 4 ~ Bit plane 7，lena_with_baboon的Bit plane 4 ~ Bit plane 7為lena的Bit plane 4 ~ Bit plane 7。

**MSE、PSNR運算**:如同上一份作業，將pixel值帶入方程式中即可得出各個的MSE及PSNR值。
![](https://i.imgur.com/DRCPlfc.png)
![](https://i.imgur.com/RWNx2v8.png)

**Figure:**

![](https://i.imgur.com/4By12lU.png) ![](https://i.imgur.com/ATT3GhV.png)

### 1.2
**Question:**

Extract your modified babooni256raw from iena_with_baboon.raw. Calculate MSE and
PNSR of your extracted baboonﬁ256.raw with respect to the original baboon_256.raw.

Your design should have the PSNR value as high as possible in both (1) & (2). 

**Discussion:**

**Baboon取出:** 我將lena_with_baboon分層，如同上一題的做法與2^x次方去做AND閘，即可取出每一層，之後將lena_with_baboon的Bit plane 0 ~ Bit plane 3也就是baboon的Bit plane 4 ~ Bit plane 7乘上各自的2^x/255之後加入一張空白的圖片，即可得到lena_with_baboon裡面的baboon圖片。

**MSE、PSNR運算:** 如同上一份作業，將pixel值帶入方程式中即可得出各個的MSE及PSNR值。
 
**Figure:**

![](https://i.imgur.com/gAkA5vi.png)

### 2.a

**Question:**

Synthesize eight bit—plane images (a512x512.raw,...,h512x512.1'aw) back to the original
image (originalraw). The bit—plane images are given in random order (e.g, not from MSB
to LSB) and some of them have been processed by the image negative effect.

**Discussion:**

**圖片分類:** 由於這張圖必須由我們自己來判斷順序，所以我將a.raw~h.raw先分層兩不分，分別是adef與bcgh，由於adef的圖像看起來細節較為不明顯，所以我能先確定它們是被放在比較下面的，而bcgh的細節整體來說比adef多很多，所以能確定他們是越上層。

**負片圖片:** 最直觀的判斷就是h有負片，原因為原圖上的city看板為深色，再h圖上近乎等於白色，g圖的看板為深色，所以我能定h圖是被負片過後的，但較底層我的肉眼無法判斷所以我將在下一個步驟時再判斷底層的def是否有被負片。
	
**圖片順序:** 再來就是圖片順序的部分，這邊我是手動的一個一個調，用我肉眼最直觀的方法下去排序從Bit plane7~Bit Plane0為bghcaedf，但這次的結果出來與原圖在天空的位子略有差異，所以我推測在肉眼無法辨識的情況下，edf是有圖片被負片的，所以我就依序將他們負片，發現把e與d負片完之後，幾乎跟原圖一模一樣，但我再把f負片之後，發現並無差別，也就是f有沒有負片基本上肉眼是無法觀看出來的，所以我認為f是可負片也不可負片的。

**Figure:**

![](https://i.imgur.com/HgXgCJx.png)

### 3.a 

**Question:**

Use the following methods to adjust the darkened image livingroom_d512 and the whiten image
cameraman_b512.rmv to improve their contrast.

**Log transformation(c=100 and c=20)**

**Discussion:**

**公式帶入:** log transformation的公式如下
$s=c$*$log⁡(1+r)$
s為轉換之後的像素值，r為原圖得像素值，c為常數，之後我將原圖的每一個像素值帶入此公式(c=100及c=20)即可獲的轉換後的圖片，我在下一題3.b會詳細的討論差別。

**Figure:**
C=100

![](https://i.imgur.com/rXGVQXc.png) ![](https://i.imgur.com/RMCQYKc.png)

C=20

![](https://i.imgur.com/0yAnFoA.png) ![](https://i.imgur.com/WpLv4gj.png)

### 3.b 

**Question:**

Power-Law transformation (γ = 0.2 and γ = 10, Try different c to discuss the effects)

**Discussion:**

![](https://i.imgur.com/7eSgZ4x.png)(圖二)

**Log-transformation分析:** 對數轉換的特性是將影像比較暗的地方，透過對數轉換，提升成較亮的像素值 

![](https://i.imgur.com/ybFIaYm.png)

所以對log來說livingroom這張是過暗的圖片調整起來的效果是會比cameraman來的好的， 

**Power-Law transformation分析:** 調整照片的明亮度，讓過曝的照片暗一點，讓曝光度不足的照片亮一點。

**分析不同的c與γ:** <font color="red">當γ<1的時候，會將暗的輸入值對映較寬的輸入範圍，當γ>1的時候，會將高亮度的輸入值對映較寬的輸入範圍</font>，也就是說圖片要暗一點γ>1，如果要亮一點γ<1，所以當γ=10的時候第一張圖livingroom不管c等於多少都掉不起來，因為它本身就是一張將近全黑的照片，所以livingroom這張圖應該使用的是γ<1的，也就是γ=0.2，而我設定的數值為γ=0.2 c=100，調整出來的感覺就跟3.a的圖一樣，也就印證了(圖二)的γ<1的部份。
接下來為γ>1的部份，起初我使用γ=10來調整cameraman，但由於γ太大，整張圖片如果c沒有特別小的話其實根本調不起來，所以我後來就改用γ=5來實驗，發現到γ=5 c=100的時候cameraman的臉及衣服的輪廓已經跑了出來，這也證明了圖(二)中的γ>1時，是強調亮的部分，讓過曝的照片調整稍為好一點，

**Figure:**

Cameraman、γ=0.2 c=50

![](https://i.imgur.com/XRnnKSm.png)

Cameraman、γ=0.2 c=20

![](https://i.imgur.com/j17wlsp.png)

Liveingroom、γ=0.2 c=100

![](https://i.imgur.com/pmgUFUo.png)

Liveingroom、γ=0.2 c=350

![](https://i.imgur.com/Bj3hFez.png)

Cameramanγ=5 c=75

![](https://i.imgur.com/lLIAAbp.png)

Cameramanγ=10 c=0.000000000000000005

![](https://i.imgur.com/oB4FzZu.png)

### 4.(a)Histogram Equalization

**Question:**

Plot the histograms of the livingroom512.raw and cmneraman_b512raw Discuss the
difference among these histograms. You have to implement your own histogram function
but you can use OpenCV to plot it.

**Discussion:**

**pixel的次數:** 我先開一個255的陣列，其目的為存取圖片中0~255的pixel出現過的次數，如果出現0，陣列[0]+1，就代表0的次數加一，將圖片中每一個pixel跑一遍之後即可得到一個存著出現次數的陣列。

![](https://i.imgur.com/dCbGWgE.png)

**直方圖的高度:** 如果說直方圖的高度最高為255，我就必須再出現次數的陣列中，找出最大的次數，For example:這張圖的pixel 25出現過50000次，同時也是最大的出現次數也就是50000，於是我將全部的次數/50000再*255，就可以得到一個最高等於255的比例。

![](https://i.imgur.com/IqP7dvr.png) ![](https://i.imgur.com/l8HRZMN.png)

**製作直方圖:** 有了上述兩項我就可以來製作直方圖了，我在這裡使用的是Opencv函式庫的line指令line(儲存的圖片,起點,終點,顏色)及Point(x,y)，我先開設一張空的圖片尺寸為直方圖的尺寸也就是256*256，起點為每一條像素點的起點，而line的圖片是由上至下如圖一((0,255)、(1,255)…(255,255))，終點為
![](https://i.imgur.com/jAYYqZi.png)(圖一)
當前的點減掉出現的次數，顏色調整為白色，即可劃出直方圖

![](https://i.imgur.com/Va1fEOF.png)

**Figure:**

Livingroom_histogram:

![](https://i.imgur.com/fP3qZTW.png)

Cameraman_histogram:

![](https://i.imgur.com/AUn3FXd.png)

### 4.b
**Question:**

Perform histogram equalization (implement your own function) on cameraman_b512.mir
and Iivingmom_d512. Plot their histograms and compare the histograms before and after
histogram equalization. Discuss the outcome with (a).

**Discussion:**

**CDF:** 讓ni表示灰階i出現的次數，這樣圖像中灰階為i的像素的出現概率是

![](https://i.imgur.com/d6ohunW.png)

L是圖像中所有的灰階值數(通常設定為256)，n式圖像中所有的像速點，px(i)實際上是像速點為i的圖像的直方圖，歸一化到[0,1]。
其cdf定義為:
 
![](https://i.imgur.com/fUclzNb.png)

將直方圖帶入上式，即可獲得每一個pixel的cdf

![](https://i.imgur.com/3uFAfam.png)

**直方圖均衡化:** 直方圖均衡化的公式為下，v為灰階值，假設灰階值78

![](https://i.imgur.com/4WWCpw9.png)

的cdf為46，均衡化的公式如下，即可得出新圖的數值為182

![](https://i.imgur.com/zgTKX8k.png)

按照上述的公式打入程式，即可獲得每一點的新的像素質並且同時完成值方圖均衡化。 

![](https://i.imgur.com/UJlwR4N.png)

Livingroom_histogram:

![](https://i.imgur.com/0nda08n.png)

Livingroom_histogram(等化後):

![](https://i.imgur.com/rBOeaof.png)


Cameraman_histogram:

![](https://i.imgur.com/SUKii3C.png)

Cameraman_histogram(等化後):

![](https://i.imgur.com/4YHe4YF.png)

**Figure:**

**Livingroom**

![](https://i.imgur.com/HafyKeu.png)

**直方圖:**

![](https://i.imgur.com/KHOcvzK.png)

**Cameraman**

![](https://i.imgur.com/pK3M0jD.png)

**直方圖:**

![](https://i.imgur.com/SxUV3kw.png)


## :smile: Owner
Made by https://github.com/WU-TING-HSUAN

## :+1: School
:point_right:National Taipei University of Technology	:point_left:
