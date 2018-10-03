#include <ESP8266WiFi.h>

const char* ssid = "WUSAMR";
const char* pass = "W3612116";
WiFiServer server(80);

IPAddress ip(192, 168, 5, 105);
IPAddress subnet(255, 255, 255, 0);
IPAddress gateway(192, 168, 5, 1);

//Setup
void setup()
{
  Serial.begin(115200);
  delay(10);
  Serial.println("");
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid,pass);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  
  server.begin();
  Serial.println("Server started.");
  Serial.println(WiFi.localIP());
}

//Loop
void loop()
{
  WiFiClient client = server.available();
  if (!client)
  {
    return;
  }

  Serial.println("new client.");
  while (!client.available())
  {
    delay(1);
  }

  String req = client.readStringUntil('\r');
  client.flush();

  Serial.println(req);

  //前進
  if (req.indexOf("/Car/Forward") != -1)
  {
    Serial.println("前進");
    Forward();
  }
  //後退
  if (req.indexOf("/Car/Back") != -1)
  {
    Serial.println("後退");
    Back();
  }
  //左轉
  if (req.indexOf("/Car/Left") != -1)
  {
    String leftValue = req;
    leftValue.replace("/Car/Left/" , "");
    leftValue.replace("GET" , "");
    leftValue.replace("HTTP/1.1" , "");
    leftValue.trim();

    int drgValue = leftValue.toInt();
    drgValue = 50 - drgValue;
    drgValue = map(drgValue, 0, 50, 0, 255);
  
    Serial.println("左轉:" + leftValue + "("+drgValue+")");
    TurnLeft(drgValue);
  }
  //右轉
  if (req.indexOf("/Car/Right") != -1)
  {
    String rightValue = req;
    rightValue.replace("/Car/Right/" , "");
    rightValue.replace("GET" , "");
    rightValue.replace("HTTP/1.1" , "");
    rightValue.trim();

    int drgValue = rightValue.toInt();
    drgValue = drgValue - 50;
    drgValue = map(drgValue, 0, 50, 0, 255);
    
    Serial.println("右轉:" + rightValue + "("+drgValue+")");
    TurnRight(drgValue);
  }
  //停止前進和後退
  if (req.indexOf("/Car/StopUD") != -1)
  {
    Serial.println("停止前進和後退");
    Stop();
  }
  //停止左轉和右轉
  if (req.indexOf("/Car/StopLR") != -1)
  {
    Serial.println("停止左轉和右轉");
    TurnCenter();
  }

  client.flush();
  delay(1);
  Serial.println("Client disconnected.");
}

//前進
void Forward()
{
  
}

//後退
void Back()
{
  
}

//左轉
void TurnLeft(int value)
{

}

//右轉
void TurnRight(int value)
{
  
}

//停止
void Stop()
{
  
}

//方向盤回正
void TurnCenter()
{
  
}
