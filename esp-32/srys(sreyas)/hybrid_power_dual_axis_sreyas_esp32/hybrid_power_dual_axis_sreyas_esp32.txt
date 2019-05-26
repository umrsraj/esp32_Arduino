#include <WiFi.h>
#include <HTTPClient.h>
#include <LiquidCrystal.h>
#include <String.h>

LiquidCrystal lcd (15,2,4,16,17,5);
#define wind 34
#define solar 35


int r, i, flag;


#define ldr_1 32
#define ldr_2 33
#define ldr_3 25
#define ldr_4 26
#define m11 18
#define m12 19
#define m21 22
#define m22 23

unsigned int ldr1 = 0;
unsigned int ldr2 = 0;
unsigned int ldr3 = 0;
unsigned int ldr4 = 0;

unsigned int t = 0;

float w = 0;
float s = 0;

void lcdstring (int a, int b, String w);

// WiFi parameters to be configured
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig 

String q = "http://projectsiot.xyz/IoTProjects/Hybrid/upload.php?";
String iot = "\0";
String p = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9493206867&from=MYDREM&message=";
String msg = "\0";



String voltageS = "\0";
String voltageW = "\0";

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.println("power up");

  
  Serial.print("Bezig met verbinden");
 WiFi.begin(ssid, password); // Connect to WiFi
 lcd.begin(16,2);

Serial.println("power up");


lcd.clear ();
lcd.setCursor (0,0);
lcd.print ("WELCOME TO HYBRID");
lcd.setCursor (0,1);
lcd.print ("POWER GENERATION");

delay (1800);

lcd.clear ();
lcd.setCursor (0,0);
lcd.print ("     SYSTEM");
lcd.setCursor (0,1);
lcd.print ("    WITH IoT    ");
delay(2000);


pinMode(ldr_1,INPUT);
pinMode(ldr_2,INPUT);
pinMode(ldr_3,INPUT);
pinMode(ldr_4,INPUT);

pinMode(wind,INPUT);
pinMode(solar,INPUT);

pinMode(m11,OUTPUT);
pinMode(m12,OUTPUT);
pinMode(m21,OUTPUT);
pinMode(m22,OUTPUT);

  while (WiFi.status() != WL_CONNECTED) {
     lcd.clear();
     lcdstring(0,0,"connecting to ");
     lcdstring(0,1,ssid);
     delay(500);
     Serial.print(".");
  }
  lcd.clear();
     lcdstring(0,0,"connected to");
     lcdstring(0,1,ssid);
  // Verbonden.
  Serial.println("OK!");
  
  // Access Point (SSID).
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  
  // IP adres.
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
 
  // Signaalsterkte.
  long rssi = WiFi.RSSI();
  Serial.print("Signaal sterkte (RSSI): ");
  Serial.print(rssi);
  Serial.println(" dBm");
  Serial.println("");

 
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   // http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9652490222&from=MYDREM&message=RJANED;LKSDF"); //Specify request destination

  http.begin("http://projectsiot.xyz/IoTProjects/Hybrid/upload.php?a=U&b=N");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}
}

void loop() {
  // put your main code here, to run repeatedly:
analogReadResolution(10);
  
w = analogRead (wind);
s = analogRead (solar);

ldr1 = analogRead(ldr_1);
ldr2 = analogRead(ldr_2);
ldr3 = analogRead(ldr_3);
ldr4 = analogRead(ldr_4);
delay (80);

Serial.print("wind value = "); Serial.println(w);
Serial.print("solar value = "); Serial.println (s);
Serial.println("");
Serial.print("ldr1 = "); Serial.println(ldr1);
Serial.print("ldr2 = "); Serial.println(ldr2);
Serial.print("ldr3 = "); Serial.println(ldr3);
Serial.print("ldr4 = "); Serial.println(ldr4);
Serial.println("");
Serial.println("");
//s = s*125/1023;
//w = w*125/1023;

//s = (s/2) - 2;
//w = (w/2) - 2;

float sol= s * (5.00/1023.00)*5;
float win= w * (5.00/1023.00)*5;

Serial.print("WIND VOLTAGE = "); Serial.println (sol);
Serial.print("SOLAR VOLTAGE = "); Serial.println (win);

voltageS = sol;
voltageW = win;

lcd.clear ();
lcd.setCursor (0,0);
lcd.print ("S:"+String(sol));
lcd.setCursor (0,1);
lcd.print ("W:"+String(win));

if((ldr1>80)&&(ldr2<80))
{
  t++;
  Serial.print("t = "); Serial.println(t);
  Serial.println("moving down");
  digitalWrite(m11,HIGH);
  digitalWrite(m12,LOW);
  delay(400);
   digitalWrite(m11,LOW);
  digitalWrite(m12,LOW);
  digitalWrite(m21,LOW);
  digitalWrite(m22,LOW);
  
}
else if((ldr1<80)&&(ldr2>80))
{
  t++;
  Serial.print("t = "); Serial.println(t);
  Serial.println("moving up");
  digitalWrite(m11,LOW);
  digitalWrite(m12,HIGH);
  delay(400);
   digitalWrite(m11,LOW);
  digitalWrite(m12,LOW);
  digitalWrite(m21,LOW);
  digitalWrite(m22,LOW);
  //thingspeak ();
}
else if((ldr3>80)&&(ldr4<80))
{
  t++;
  Serial.print("t = "); Serial.println(t);
  Serial.println("moving left**");
  digitalWrite(m21,HIGH);
  digitalWrite(m22,LOW);
  delay(400);
   digitalWrite(m11,LOW);
  digitalWrite(m12,LOW);
  digitalWrite(m21,LOW);
  digitalWrite(m22,LOW);
 // thingspeak ();
}
else if((ldr3<80)&&(ldr4>80))
{
  t++;
  Serial.print("t = "); Serial.println(t);
  Serial.println("moving right**");
  digitalWrite(m21,LOW);
  digitalWrite(m22,HIGH);
  delay(400);
   digitalWrite(m11,LOW);
  digitalWrite(m12,LOW);
  digitalWrite(m21,LOW);
  digitalWrite(m22,LOW);
  //thingspeak ();
}
else
{
  Serial.println("STOP");
    digitalWrite(m11,LOW);
  digitalWrite(m12,LOW);
  digitalWrite(m21,LOW);
  digitalWrite(m22,LOW);
 // thingspeak ();
}
  iot  = q + "a=" + String(sol) + "&b=" + String(win) ;
  send2server ();  

}//loop
void send2server ()
{
   Serial.println(iot);
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
  
   http.begin(iot);

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(100);
}
}

void lcdstring (int a, int b, String w)
{
  lcd.setCursor(a,b);
  lcd.print(w);
}
