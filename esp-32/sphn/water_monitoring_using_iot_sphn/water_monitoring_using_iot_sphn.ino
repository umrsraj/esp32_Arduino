
#include <WiFi.h>
#include <HTTPClient.h>
#include <String.h>
#include <LiquidCrystal.h>

#define ldr1Pin 34
#define ldr2Pin 35
#define m1a 32
#define m1b 23
#define m1a 25
#define m1b 26
#define bt1 5
#define bt2 18



// WiFi parameters to be configured
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig

String m1 = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9848645851&from=MYDREM&message=";
String m2 = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=8074303938&from=MYDREM&message=";
String msg = "\0";
String r = "http://projectsiot.xyz/IoTProjects/WaterMonitor/upload.php?a=";
String rs = "\0";

String box1 = "N";
String box2 = "N";

int flag1 = 0;
int flag2 = 0;
int ldr1 = 0;
int ldr2 = 0;



LiquidCrystal lcd (15,2,0,4,16,17);


void lcdstring (unsigned int a, unsigned int b, String data);

void open1 ()
{
  digitalWrite(m1a,HIGH);
  digitalWrite(m1b,LOW);
  delay(20);
}
void close1 ()
{
  digitalWrite(m1a,LOW);
  digitalWrite(m1b,HIGH);
  delay(20);
}
void stop1 ()
{
  digitalWrite(m1a,LOW);
  digitalWrite(m1b,LOW);
  delay(20);
}
void open2 ()
{
  digitalWrite(m2a,HIGH);
  digitalWrite(m2b,LOW);
  delay(20);
}
void close2 ()
{
  digitalWrite(m2a,LOW);
  digitalWrite(m2b,HIGH);
  delay(20);
}
void stop2 ()
{
  digitalWrite(m2a,LOW);
  digitalWrite(m2b,LOW);
  delay(20);
}

void setup()
{
  // initialize serial for debugging
  Serial.begin(9600);


pinMode(m1a,OUTPUT);
pinMode(m1b,OUTPUT);
pinMode(m2a,OUTPUT);
pinMode(m2b,OUTPUT);


pinMode(ldr1Pin,INPUT);
pinMode(ldr2Pin,INPUT);
pinMode(bt1,INPUT);
pinMode(bt2,INPUT);


  lcd.begin(16, 2);
  lcd.clear();
  lcdstring(0,0,"MEDICINE BOX");
  lcdstring(0,1,"                       ");
  delay(2500);

Serial.print("Bezig met verbinden");
  WiFi.begin(ssid, password); // Connect to WiFi
 
  // while wifi not connected yet, print '.'
  // then after it connected, get out of the loop
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     lcd.clear();
  lcdstring(0,0," CONNECTING  TO ");
  lcdstring(0,1,ssid);
  delay(200);
     Serial.print(".");
  }

  Serial.println("OK!");
  
  // Access Point (SSID).
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  
  // IP adres.
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
Serial.println("state---------------1"); 
  // Signaalsterkte.
  long rssi = WiFi.RSSI();
  Serial.print("Signaal sterkte (RSSI): ");
  Serial.print(rssi);
  Serial.println(" dBm");
  Serial.println("");
     lcd.clear();
  lcdstring(0,0,"  CONNECTED TO  ");
  lcdstring(0,1,ssid);
  delay(2000);

lcd.clear();
  lcdstring(0,0,"  SERVER INT.  ");
  lcdstring(0,1,"  PLEASE WAIT  ");
  delay(2000);


  
/*
Serial.print(F("sending init message............"));
Serial.print("msg = "); Serial.println("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=8897720828&from=MYDREM&message=KIT%20STARTED");
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   
 http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=8897720828&from=MYDREM&message=KIT%20STARTED");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}
*/


lcd.clear();
  lcdstring(0,0,"  SERVER INT.  ");
  lcdstring(0,1,"      DONE      ");
  delay(2000);
//lcd.clear();    
//Serial.println(F("PLEASE SHOW CARD "));


}

void loop()
{
box1 = "N";
box2 = "N";

if (digitalRead(bt1)==LOW)
{
  Serial.println("bt1 pressed-------");
  lcdstring(0,0,"                     ");
  lcdstring(0,1,"                      ");
  
  lcdstring(0,0,"BOX-1 DOOR OPENING      ");
  lcdstring(0,1,"....................");
  delay(20);
  open1 ();
  delay(2000);
  stop1 ();
  
  lcdstring(0,0,"SENSOR READING    ");
  lcdstring(0,1,"                   ");
  delay(20);  
  for(int k = 0; k<=100; k++)
  {
    ldr1 = analogRead(ldr1Pin);
    Serial.println("ldr1 = "+String(ldr1));
    if (ldr1 > 3000)
    {
      Serial.println("medicine-1 taken");
      box1 = "Y";
    }
  }

  lcdstring(0,0,"                     ");
  lcdstring(0,1,"                      ");
  
  lcdstring(0,0,"BOX-1 DOOR CLOSING      ");
  lcdstring(0,1,"....................");
  delay(20);
  close1 ();
  delay(2000);
  stop1 ();
  
rs = r + box1 + "&b=" + box2;
  send2server ();
  
  delay(5000);

}
else if (digitalRead(bt2)==LOW)
{
  Serial.println("bt2 pressed-------");
  lcdstring(0,0,"                     ");
  lcdstring(0,1,"                      ");
  
  lcdstring(0,0,"BOX-2 DOOR OPENING      ");
  lcdstring(0,1,"....................");
  delay(20);
  open2 ();
  delay(2000);
  stop2 ();
  
  lcdstring(0,0,"SENSOR READING    ");
  lcdstring(0,1,"                   ");
  delay(20);  
  for(int k = 0; k<=100; k++)
  {
    ldr2 = analogRead(ldr2Pin);
    Serial.println("ldr2 = "+String(ldr2));
    if (ldr2 > 3000)
    {
      Serial.println("medicine-2 taken");
      box2 = "Y";
    }
  }

  lcdstring(0,0,"                     ");
  lcdstring(0,1,"                      ");
  
  lcdstring(0,0,"BOX-2 DOOR CLOSING      ");
  lcdstring(0,1,"....................");
  delay(20);
  close2 ();
  delay(2000);
  stop2 ();
  
rs = r + box1 + "&b=" + box2;
  send2server ();
  delay(5000);
}
else
{

  lcdstring(0,0,"                     ");
  lcdstring(0,1,"                      ");
  
  lcdstring(0,0,"MEDICINE BOX     ");
  lcdstring(0,1,"                          ");
  delay(20);
  rs = r + box1 + "&b=" + box2;
  send2server ();
}


}// loop
  void send2server ()
{
Serial.print("rs = "); Serial.println(rs);
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
 http.begin(rs);

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(50);
}
}
 void sendsms ()
{
Serial.print("msg = "); Serial.println(msg);
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
 http.begin(msg);

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}
}

void lcdstring (unsigned int a, unsigned int b, String data)
{
  // lcd.clear();
  lcd.setCursor(a, b);
  lcd.print(data);
}
