# NTUT EE ADIP HW2
## :heart_eyes: Introduction my self
大家好，我是吳定軒，目前就讀於國立台北科技大學電機工程系碩士班，我將在我的github上分享我所實作的Project，內容也有許多需要改進的地方，如果你有甚麼建議歡迎寫信到我的信箱t109318095@ntut.org.tw。   

Hello everyone, I am TINGHSUAN-WU. I am currently studying in the Master's Program of the Department of Electrical Engineering, National Taipei University of Technology. I will share the projects I have done on my Github. There are many areas for improvement in the content. If you have any suggestions, welcome Write to my mailbox.

## :yum: Introduction this project
這份作業是ADIP(高等數位影像處理)，教授要求我們使用純C++ 來撰寫，但我還是有些地方使用了Opencv內建的程式碼，因為起初我不知道那是Opencv的內建程式碼，所以我會在解說時補上C++的語法。
## :book: Method
題目我把它放在了Question的資料夾可以去那邊觀看。
### 1.1 將lena256.raw的眼睛放大為兩倍
我的作法是將左右兩眼分開取出來，我先手動找左眼的範圍(高度在128 ~ 140，寬度則在120 ~ 140)，之後我在開兩張空的圖片，第一張的size為眼睛的size(140-128) x (140-120)，用來儲存左眼，另一張圖片為它的size定眼睛size的兩倍 = (140-128) x (140-120) x 2，用來放大，再來就是把每一個pixel重複兩次放到新開的空圖，就可以得到兩倍大的左眼。

![](https://i.imgur.com/PVd2w17.png)

![](https://i.imgur.com/YJZZg3a.png)

再來是取出右眼，我手動找到右眼的範圍(高度在128 ~ 140，寬度則在160 ~ 180)，之後我同樣在開兩個的空圖片(同左眼)，接下來的做法跟左眼一樣，即可得到兩倍大的右眼。

![](https://i.imgur.com/bfZGIIW.png)

最後將兩張圖片放進原圖，並找到最適合的高度(寬度是一樣的)，最後得出高度從122開始放比較像題目的圖片，之後輸出即可得到結果。

![](https://i.imgur.com/7ZNq9BP.png)
Answer ： 

![](https://i.imgur.com/51Nn249.png)

### 1.2 將上題的圖片縮小2倍
這題是要把上一題輸出的圖片縮小兩倍，256*256變成128*128，我先將上一題的輸出圖片讀近來，<font color="red">再開一張尺寸為128 x 128的空圖(用來放輸出)</font>

我縮小兩倍的原理是採用新圖的pixel對應上原圖的pixel，<font color="red">原圖的pixel四個鄰近的pixel作為平均值</font>，再把平均值放入新的圖片

![](https://i.imgur.com/nZxD22I.png)

實做的部分就是使用兩個for迴圈，兩個都是從0 ~ 128，新圖的pixel=舊圖的piexl x2(因為舊圖為新圖的兩倍所以 x2才是舊圖的點)的四個點總和再除與4
即可得到新圖。

### 1.3 使用Nearest、Bilinear、Bicubic來運算，先放大2.5倍在縮小2倍、縮小2倍再放大2.5倍、放大2.5倍，各三張圖，總共要九張圖，並計算運算時間

#### Nearest
最鄰近搜尋法為，如果這一個pixel沒有數值，則他會去尋找離他最近並且有數值的pixel，這一題一開始為把256 x 256的圖片放大2.5倍，變成640 x 640的圖片，所以我一開始直接把256 x 256的圖片丟入到一張空尺寸為640 x 640的圖片，不過它們的數值差了2.5倍，所以我的256 x 256的每一個座標點都必須乘上2.5倍之後才能放到新圖片。

![](https://i.imgur.com/Llexa0c.png)

上圖為我上一段的邏輯，將原本的256 x 256放到640 x 640裡成果如下圖。

![](https://i.imgur.com/D9Fcz58.png) ![](https://i.imgur.com/tn02vh2.png)

256 x 256放到640 x 640會有一點一點的感覺，因為它有數值的地方為(0,0),(0,2),(0,4),(0,6)...以此列推，所以接下來我再用nearest來判斷(0,1),(0,3),(0,5),(0,7)...這些值為多少。
判斷的方法為先將4個有數值的pixel找出，並將這四個點劃分為四個區塊，並找出它們彼此的中點， 之後再去跑裡面全部的點，滿足條件式，讓該點的值為條件式指定的頂點。 If(x_now<1 && y_now<1)==(x,y) 

#### Bilinear
![](https://i.imgur.com/XF6N5xe.png)(紅色的數據點與待插值得到的綠色點)

Bilinear的公式:

![](https://i.imgur.com/Oq9SLbu.png)

Bilinear與nearest都是使用四個點去做，我也是先將256 x 256的圖片丟入640 x 640的空白圖片裡，Bilinear比較輕鬆的部分就是它是有固定公式的，只要看懂公式並把數值帶入即可完成，我採用的是第三行公式

![](https://i.imgur.com/B6susdp.png)

x1,x2,y1,y2為放大後的圖的四個座標，Q11,Q12,Q21,Q22為放大後的圖的點，並帶入公式，即可完成

#### Bicubic
雙三次插值至少考慮到4個直接相鄰點的灰度影響，而且考慮到各個鄰點間灰度值變化率的影響，而它總告考慮了16個點。

![](https://i.imgur.com/gHLNGis.png)
(圖片來源https://www.itread01.com/content/1548125315.html)

重點公式:
a0X的橫座標權重分別為W(1+u)，W(u)，W(1-u)，W(2-u)；ay0的縱座標權重分別為W(1+v)，W(v)，W(1-v)，W(2-v)；B(X,Y)畫素值為：

![](https://i.imgur.com/FtZzHKZ.png)

假設原圖(256 x 256)為上圖說表示a00~a33，P點為放大之後的圖所對映原圖的座標點，而放大圖的座標點去對映縮小圖的話不可能每一個pixel都能對映的到，有些會是小數點，而這公式則把這些小數點的座標再細分為整數部分及小數部分P(x+u,y+v)，其中x,y分別表示整數部分，u,v分別表示小數部分，而我在程式中使用的式兩個變數，一個為float變數一個為int變數，float變數包含整數及小數，int變數包含整數，再將兩個數值相減及得到小數部分。之後帶入公式，即可獲得xy權重，並帶回上式做運算。

![](https://i.imgur.com/gTzO4fv.png)

#### 此題結論
總體而言Nearest、Bilinear、Bicubic裡最淺顯易懂的就是Nearest，不過它的判斷方式相對的比較不嚴謹，而最難理解的就是Bicubic，但它出來的圖都很漂亮，而我認為放大最好的就是Bicubic，但是時間比較起來Nearest、Bilinear的時間遠小於Bicubic，也許是Bicubic需要龐大的運算所以時間才特別久。

還有一個問題就是如果先放大再縮小圖片或只放大圖片，Nearest、Bicubic的效果超好，但如果變成先縮小再放大，就很明顯可以感受到圖片變得模糊。

如果要我選一個我會常用的方法我會選Nearest因為它跑得最快，而且圖片也是很清楚。

Answer : 

![](https://i.imgur.com/ZSf2ODs.png)

![](https://i.imgur.com/krN6bDE.png)

### 2.1量化 將baboon.raw及lena256.raw量化，並計算MSE、PSNR
#### 量化
我先將256除與要量化的bits數，即可得出多少間隔格一格。

![](https://i.imgur.com/OCBKsdn.png) ![](https://i.imgur.com/DpHeLNq.png)

之後再將圖片每一個值除與這個數值，以1bit舉例，我將每一個pixel都去除與128，再C語言中，小於128的除出來為0，大於128的為1。
再將這些值成上255/2^bit數-1)，即可將每一bit的2~7值化，以2bit為例小於128的數字商都是0，乘上255還是0，但大於128的數值商是1，乘上255都是255，即可二值化。

![](https://i.imgur.com/QOCtLOb.png)

#### MSE
均方誤差為單色向圖片及真實值的差別，所以我將量化後的圖與原圖帶入公式做比較即可解答。

![](https://i.imgur.com/BYp62yg.png)

#### PSNR
一個表示訊號最大可能功率和影響它的表示精度的破壞性雜訊功率的比值的工程術語，也是有常用公式，我將量化後的圖與原圖帶入公式即可解答。

![](https://i.imgur.com/Omk9pIo.png)

Answer : 

![](https://i.imgur.com/zuUDWtv.png)
![](https://i.imgur.com/2JaS7ei.png)

![](https://i.imgur.com/1J8xECQ.png) ![](https://i.imgur.com/m0RlrLJ.png)

### 3.1解釋Isopreference test
由下圖可得知影像複雜度越高時，越不受灰階影響，狒狒與Lena量化時就可以證明這點，lena再4bit的時候開始失真，而狒狒2~3bit的時候其實圖片就已經開始沒甚麼變化，即可得證圖片size固定下，影像複雜度越高時。越不會受灰階值影響。
教授上課提到的另外一個特點就是在圖片size的大小，同時也受灰階值影響，所以我把lena_256.raw，與教授在第一次作業給的lena1024.raw拿來做比較，我發現size的影響真的不大，或者它有我肉眼無法所發現的變化，所以這一點我無法斷言。

![](https://i.imgur.com/OGVsmba.png)

### 4.Bit blane
這題將在下一次的作業進行講解

### 5.給一張迷宮的圖片，使用4相鄰、8相鄰、m相鄰的方法找出最短路徑，而能走的地方有三種限制
* Gray-value of the road{80} 只能走pixel 80的地方
* Gray-value of the road{80 160} 只能走pixel 80 160的地方
* Gray-value of the road{80 160 255} 只能走pixel 80 160 255的地方

如果要走{80 160}，我會先把160的值替換乘80來走，因為我的判斷式就只要判斷是否為80就好，而255也是同樣的道理，同樣會替換乘80。

我全部都是使用遞迴，再走D4的時候，我的判斷是為右>下>左>上也就是右邊優先，判斷右邊的值是否為80，如果是的話就走，不是的話就按照右>下>左>上的下一個if也就是下面是否等於80，每走成功一步步數+1，以此而類推，而等到第一條走到終點時，它會進入終點的if(row和col都等於19的話)，它會記錄現在的步數，然後目前的最小步數為它並記錄起來，然後它會跳回上一層遞迴(19,18)的同時，它會把(19,19)復原為80，然後會一直跳，路徑會一直復原為80，直到它跳到有不同方向走的岔路，就繼續走下去成功步數就+1，然後不斷的走到(19,19)，不斷的與上一個路徑比較哪一個比較短，全部走完後，即可得到答案。

再走D8的時候我只是在上下左右的判別式基礎上，加上判斷斜邊是否能走，跟D4一樣，它會一直走，但我多加了一個條件，也就是如果目前的步數已經超過目前已知的最短路徑，直接不走，因為一定不是最短的，這樣子程式會快很多，我第一次做的沒有加這個的話，基本上會跑不完，加了之後大概30秒內就會跑出來了。

Dm則是再加一條判斷式，如果斜邊等於80時，要判斷它是否能走，如果右斜邊等於80，就必須判斷它的右邊及上面其中一個是否有值等於80，如果有就不能走，其餘的走法就跟D4提過的一樣，不斷的計算最小路徑，這條路徑的步數超過目前已知的最小路徑，直接不走，一直找下去就可以得到最短路徑。

![](https://i.imgur.com/ieAUtZe.png)

## :smile: Owner
Made by https://github.com/WU-TING-HSUAN

## :+1: School
:point_right:National Taipei University of Technology	:point_left:
