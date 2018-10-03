const int LeftA = 8;   //設定左邊車輪的腳位,變數:LeftA  , 腳位:8
const int LeftB = 9;   //設定左邊車輪的腳位,變數:LeftB  , 腳位:9
const int RightA = 10; //設定右邊車輪的腳位,變數:RightA , 腳位:10 
const int RightB = 11; //設定右邊車輪的腳位,變數:RightA , 腳位:11

const int TrigPin = 2; //設定超音波發出頻率的腳位,變數:TrigPin , 腳位:2
const int EchoPin = 3; //設定超音波接收頻率的腳位,變數:EchoPin , 腳位:3
float CM_Value; //設定變數:CM_Value,超音波偵測到的距離

//這裡只有開機時才會執行,只會執行一次
//======開始======
void setup()
{
  Serial.begin(9600);
  pinMode(RightA, OUTPUT);   //宣告右邊車輪的腳位RightA(10)為輸出腳位
  pinMode(RightB, OUTPUT);   //宣告右邊車輪的腳位RightB(11)為輸出腳位
  pinMode(LeftA, OUTPUT);    //宣告左邊車輪的腳位LeftA(8)為輸出腳位
  pinMode(LeftB, OUTPUT);    //宣告左邊車輪的腳位LeftB(9)為輸出腳位

  pinMode(TrigPin, OUTPUT);  //宣告超音波的腳位TrigPin(2)為輸出腳位
  pinMode(EchoPin, INPUT);   //宣告超音波的腳位EchoPin(3)為輸出腳位

  delay(5000); //延遲5秒,系統是以毫秒為單位,1秒=1000毫秒,所以5000毫秒就是5秒
}
//======結束======

//電路板開完機後,會一直重複這裡的程式,直到關機
//======開始======
void loop()
{
  //一開始先取得超音波偵測到的距離
  //getCM() 是副程式, distance 是變數
  int distance = getCM(); 

  if (distance < 15) //如果偵測到的距離是15公分以下就執行下列程式
  {
    Stop();      //執行Stop()的副程式,主要是停止馬達的動作
    delay(100);  //休息100毫秒
    Back();      //執行Back()的副程式,主要是讓車子後退
    delay(1000); //休息1秒(1000毫秒)
    Right();     //執行Right()的副程式,主要是讓車子右轉
    delay(1000); //休息1秒(1000毫秒)
    Forward();   //執行Forwar()的副程式,主要是讓車子前進
  }
  else //否則就執行下列程式
  {
    Forward(); //執行Forwar()的副程式,主要是讓車子前進 
  }
}
//======結束======

//取得超音波偵側到前方障礙物的距離
int getCM()
{
  digitalWrite(TrigPin, LOW);  //先關掉TrigPin腳位
  delayMicroseconds(2);	       //休息2毫秒	
  digitalWrite(TrigPin, HIGH); //開啟TrigPin腳位,發出高頻聲
  delayMicroseconds(10);       //休息10毫秒	
  digitalWrite(TrigPin, LOW);  //關掉TrigPin腳位

  //開啟EchoPin腳位並且取得TrigPin發出高頻聲傳回來的時間
  //所以目前CM_Value的內容是存放時間
  CM_Value = pulseIn(EchoPin, HIGH);

  //計算距離, 距離=速率*時間
  //但因為去回,所以要除2
  //計算完後CM_Value的內容就是距離(單位是:公分)
  CM_Value = CM_Value * 34 / 1000 / 2;

  //把距離傳回去
  return CM_Value;
}

//後退
void Back()
{
  //把左邊車輪一條線設定成高電位,另一條線設定成低電位
  //這樣車輪就會轉,如果把高電位和低電位調換,則車輪就會往另一方向轉動

  digitalWrite(LeftA, LOW);   //把左邊車輪的LeftA(8)腳位設定低電位
  digitalWrite(LeftB, HIGH);  //把左邊車輪的LeftB(9)腳位設定高電位

  digitalWrite(RightA, LOW);  //把右邊車輪的RightA(10)腳位設定低電位
  digitalWrite(RightB, HIGH); //把右邊車輪的RightB(11)腳位設定低電位
}

//前進
void Forward()
{
  digitalWrite(LeftA, HIGH);
  digitalWrite(LeftB, LOW);

  digitalWrite(RightA, HIGH);
  digitalWrite(RightB, LOW);
}

//左轉
void Left()
{
  digitalWrite(LeftA, HIGH);
  digitalWrite(LeftB, LOW);

  digitalWrite(RightA, LOW);
  digitalWrite(RightB, HIGH);
}

//右轉
void Right()
{
  digitalWrite(LeftA, LOW);
  digitalWrite(LeftB, HIGH);

  digitalWrite(RightA, HIGH);
  digitalWrite(RightB, LOW);
}

//停止
void Stop()
{
  //把所有車輪都設定成低電位,車輪就不會轉動了
  //也可以把所有車輪設定成高電位,則車輪也不會轉動
  digitalWrite(LeftA, LOW);
  digitalWrite(LeftB, LOW);
  
  digitalWrite(RightA, LOW);
  digitalWrite(RightB, LOW);
}
