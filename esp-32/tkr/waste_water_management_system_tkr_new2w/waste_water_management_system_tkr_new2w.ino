#include <WiFi.h>
#include <HTTPClient.h>
#include <String.h>
#include <LiquidCrystal.h>


#define flow1Pin 34
#define flow2Pin 35
#define trigPin 18
#define echoPin 19
#define relay 22
#define buzzer 23


// WiFi parameters to be configured
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig

String m1 = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydream123&to=9848645851&from=MYDREM&message=";
String m2 = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydream123&to=8074303938&from=MYDREM&message=";
String msg = "\0";
String r = "http://projectsiot.xyz/IoTProjects/WaterMonitor/upload.php?a=";
String rs = "\0";

int flag1 = 0;
int flag2 = 0;
long duration;
int distance;

int flow1 = 0;
int flow2 = 0;

String L = "N";
int diff=0 ;


LiquidCrystal lcd (15,2,4,16,17,5);


void lcdstring (unsigned int a, unsigned int b, String data);


void beep ()
{
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);
  delay(100);
}


void setup()
{
  // initialize serial for debugging
  Serial.begin(9600);


pinMode(buzzer,OUTPUT);
pinMode(relay,OUTPUT);
pinMode(trigPin,OUTPUT);
pinMode(echoPin,INPUT);
pinMode(flow1Pin,INPUT);
pinMode(flow2Pin,INPUT);

  lcd.begin(16, 2);
  lcd.clear();
  lcdstring(0,0,"WATER MONITORING S/M   ");
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
  Serial.print("A = "); Serial.println("http://projectsiot.xyz/IoTProjects/AirSoundPollution/pfupload.php?a=U&b=0");
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   
  http.begin("http://projectsiot.xyz/IoTProjects/WaterMonitor/upload.php?a=U&b=0");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}
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

L = "N";
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance= duration*0.034/2;

Serial.println("distance="+String(distance));

flow1 = analogRead(flow1Pin);
flow2 = analogRead(flow2Pin);

diff = flow1-flow2;

Serial.println("flow1="+String(flow1));
Serial.println("flow2="+String(flow2));
Serial.println("difference="+String(diff));



if (distance < 10)
{
  flag2 = 0;
  Serial.println("low level");
  lcdstring(0,0,"MIN LEVEL DETECTED     ");
  lcdstring(0,1,"PLEASE CHECK          ");
  digitalWrite(relay,LOW);
  delay(100);
  beep ();
  delay(2000);
  if (flag1 == 0)
  {
    flag1 = 1;
    msg = m1+"MINIMUM%20LEVEL%20DETECTED%20IN%20DAM%0APLEASE%20CHECK";
    sendsms();
    msg = m2+"MINIMUM%20LEVEL%20DETECTED%20IN%20DAM%0APLEASE%20CHECK";
  sendsms();
  }
  }
else if (diff > 300)
{
  flag1 = 0;
  L = "Y";
     Serial.println("water leakage alert");
  lcdstring(0,0,"WATER LEAKING        ");
  lcdstring(0,1,"PLEASE CHECK          ");
  digitalWrite(relay,LOW);
  delay(100);
  beep ();
  delay(2000);
  if (flag2 == 0)
  {
    flag2 = 1;
    msg = m1+"WATER%20LAEKAGE%20ALERT%0APLEASE%20CHECK";
    sendsms();
    msg = m2+"WATER%20LAEKAGE%20ALERT%0APLEASE%20CHECK";
    sendsms();
  }
  
rs = r + String(distance) + "&b=" + L ;

        Serial.println(rs);
        send2server ();
        delay(5000);
}

  else
  {
  flag1 = 0;
  flag2 = 0;
    Serial.print("SYSTEM IS NORMAL");
   lcdstring(0,0,"                          ");
   lcdstring(0,1,"                          ");
  lcdstring(0,0,"DIST:"+String(distance));
  lcdstring(0,1,"LEAKAGE: NORMAL          ");
  delay(20);
  digitalWrite(relay,HIGH);
  delay(300);
    
  }


rs = r + String(distance) + "&b=" + L ;

        Serial.println(rs);
        send2server ();

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
 
delay(500);
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
