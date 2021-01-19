# NTUT EE ADIP HW1
## :heart_eyes: Introduction my self
大家好，我是吳定軒，目前就讀於國立台北科技大學電機工程系碩士班，我將在我的github上分享我所實作的Project，內容也有許多需要改進的地方，如果你有甚麼建議歡迎寫信到我的信箱t109318095@ntut.org.tw。   

Hello everyone, I am TINGHSUAN-WU. I am currently studying in the Master's Program of the Department of Electrical Engineering, National Taipei University of Technology. I will share the projects I have done on my Github. There are many areas for improvement in the content. If you have any suggestions, welcome Write to my mailbox.

## :yum: Introduction this project
這份作業是ADIP(高等數位影像處理)，教授要求我們使用純C++ 來撰寫，但我還是有些地方使用了Opencv內建的程式碼，因為起初我不知道那是Opencv的內建程式碼，所以我會在解說時補上C++的語法。
## :book: Method
題目我把它放在了Question的資料夾可以去那邊觀看，題目的1.1 1.2(a)是在介紹如何安裝Opencv，而這並不是我這份Project的主軸，所以接下來我會從1.2(b)開始介紹我詳細的實作方式
### 1.2(b)
#### (1) 123rd row&234th column的intensity value為多少
這題算是比較基礎的部分，而我在這部分有個失誤，我使用了   
`lenaMat.at<uchar>(i,j)`及`lenaMat.at<uchar>(第幾格)`這是Opencv裡面內建的語法，純C++的語法為`lenaMat.data[i*width,j]`，其中width為圖片的寬度，row而這樣就可以讀取座標的intensity value。  
![](https://i.imgur.com/5oS3eEf.png)  

![](https://i.imgur.com/S2n4F4u.png)  

Answer : <font color="red">123rd row&234th column的intensity value為:157</font>

#### (2) 第5487 th的intensity value為多少?並且找出它的pixel coordinate
同上題 使用`lenaMat.at<uchar>`程式碼讀取5487格的intensity value，至於它的pixel coordinate，我是採用5487/256(256為圖片的尺寸256 x 256)的商即為它的row，col為5487-256*它的row，即可得到答案。

![](https://i.imgur.com/m044o8l.png) 

![](https://i.imgur.com/S4j7ZnO.png)

Answer : <font color="red">5487 th的intensity value為119, pixel coordinate為(21,111)</font>

### 1.2(c)將lena256.raw展示在視窗上
純 C++ 讀取raw比較複雜，下列為純 C++ 讀取raw檔案的程式碼步驟
* `char OriFile[] = "檔案路徑"`:先將檔案路徑儲存
* `FILE* lenaFile`:宣告lenaFile
* `lenaFile = fopen(OriFile, "rb")`:之後要Read file決定他是讀還是寫的模式先宣告
* `unsigned char* lenai = new unsigned char[size]`
* `fread(lenai, size, 1, lenaFile)`
* `Mat lenaMat(height, width, CV_8UC1, lenai)`:這樣圖片就可以直接使用Mat宣告來讀取了   

上述的處理完之後我們就可以直接使用`imshow`把lena256.raw給show出來了  
`imshow("lenaMat", lenaMat)`。  

Answer :   
![](https://i.imgur.com/2TIZ3KG.png) ![](https://i.imgur.com/7dh59qe.png)

### 1.2(d)將lena256.raw旋轉90度之後show出來
我將原本圖片的每一個座標互換之後即可獲得此圖(x,y)改成(y,x) 

![](https://i.imgur.com/rVnhsSf.png)

Answer :

![](https://i.imgur.com/WxPJENb.png)

### 1.2(e)將lena256.raw切成16塊，並重新打散存成一張新圖，並製作兩次(不能重複)
我先寫了可以random 1到16並且數字不重複的程式，而這1~16就代表著16塊的編號，並丟到空白的陣列裡  

For example
1. [16,3,15,1,4,13,5,8,2,12,6,10,7,11,9,14]
2. [7,10,16,1,15,8,2,14,3,9,4,11,6,5,12,13]

這樣就保證我每一次的random一定不會重複，也就代表我這16塊一定不會有重複的位子。
再來我把原圖切成16塊按照順序切(row:0到64,col:0到64)，也就是說我現在會有一張原圖切了16塊跟一張空白的圖也切成了16塊  
![](https://i.imgur.com/Gslu3yA.png)  
這時我將陣列一裡面的順序當成我原圖存放進空白圖的順序，也原圖的第一塊存放到空白圖的第16塊，依此而類推，就可以得到一張16塊都是random排序地的圖片，並以此製作兩次，即可得到兩個切成16塊但排序都是不同的圖片
![](https://i.imgur.com/Q4XCmJF.png)

Answer :   

![](https://i.imgur.com/Mb67PGX.png)  ![](https://i.imgur.com/7KMXaLg.png)


### 1.2(f)將p01.raw,p02.raw,p03.raw,p04.raw合成為一張圖片

#### (1 )決定合成之後的image size
因為這是四張256 x 256的圖片，所以我決定將合成出來的圖片size定在512 x 512，所以我在fwrite的size把它改成原本的四倍(原本是256 x 256後來改成512 x 512)

![](https://i.imgur.com/WUKRr1k.png)

#### (2) 請將四張圖檔合成起來
我先開了一張空白的圖片，將圖片切成四等分(第一部分(row:0到255,col:0到255),第二部分(row:0到255,col:256到511)，第三部分(row:256到511,col:0到255),第四部份(row:256到511,col:256到256))，並將p01.raw到p04.raw，依序丟入  

Answer :  

![](https://i.imgur.com/nimSNXj.png)

#### (3)將結果存成raw檔，並使用Xnview開啟

### 1.3亮度
#### (a) 將lena256.raw每一個pixel加50,並將結果儲存成raw檔，使用Xnview觀看結果
Answer :   

![](https://i.imgur.com/vijjdNI.png)
#### (b) 同上題只是加的範圍改成隨機的數值(-50到50)
(圖片random值為-48)  

Answer :   

![](https://i.imgur.com/vWhecwI.png)

#### (c) 此題哪一部分需要注意?
兩題我都認為在數值加超過255的時候會有問題，我起初是先加完255之後再去判斷是否有大於255，但由於加超過255時數字並不會繼續加上去，所以這個方法是沒辦法使用的，後來我就改用先用205去判別看，因為205以上+50的話就會超過255或等於255。

Answer : 

![](https://i.imgur.com/mwpw6Ht.png)


### 2.把學號跟想說的話繡上熊貓這張haha.raw，並存成png檔
由於這題題目有說到能夠使用opencv的指令，我就使用Point及putText指令即可完成

![](https://i.imgur.com/FTbsAUs.png)

Answer : 

![](https://i.imgur.com/B7GiY6I.png)

## :smile: Owner
Made by https://github.com/WU-TING-HSUAN

## :+1: School
:point_right:National Taipei University of Technology	:point_left:

