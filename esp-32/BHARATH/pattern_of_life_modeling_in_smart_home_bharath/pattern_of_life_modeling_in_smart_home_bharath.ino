#include <WiFi.h>
#include <HTTPClient.h>
#include <LiquidCrystal.h>
#include <String.h>
 

LiquidCrystal lcd (15,2,4,16,17,5);

#define temp 35

#define gasPin 34
#define pir 32
#define buzzer 26
#define light 18
#define fan 19
#define m11 22
#define m12 23

float temp1=0.0;
unsigned temp2 = 0;
int gas  = 0;

String g = "N";
String p = "N";

// WiFi parameters to be configured
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig 

String q = "http://projectsiot.xyz/IoTProjects/SmartHome/upload.php?a=";
String iot = "\0";
String m = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydream123&to=9493206867&from=MYDREM&message=";
String msg = "\0";
String gas2 = "\0";
String p1 = "Normal";
/*
int freq = 5000;
int ledChannel = 0;
int resolution = 8;
int dutyCycle = 0;
*/


void lcdstring (int a, int b, String w)
{
  lcd.setCursor(a,b);
  lcd.print(w);
}
void forward ()
{
  digitalWrite(m11,HIGH);
  digitalWrite(m12,LOW);
  delay(50);
}
void backward ()
{
  digitalWrite(m12,HIGH);
  digitalWrite(m11,LOW);
  delay(50);
}
void stopp ()
{
  digitalWrite(m12,LOW);
  digitalWrite(m11,LOW);
  delay(50);
}
void beep ()
{
  digitalWrite(buzzer,HIGH);
  delay(1000);
  digitalWrite(buzzer,LOW);
  delay(100);
}
 
void setup(void) { 
  Serial.begin(9600);
  Serial.print("Bezig met verbinden");
 WiFi.begin(ssid, password); // Connect to WiFi
 lcd.begin(16,2);
 
lcd.clear();
lcd.setCursor(0,0);
        lcd.print("SMART HOME     ");
        lcd.setCursor( 2,1);
         lcd.print("               ");
         delay(2000);
         
          pinMode(gasPin,INPUT);
          pinMode(temp,INPUT);
         pinMode(pir,INPUT);
          
          pinMode(m12,OUTPUT);
          pinMode(m11,OUTPUT);
          pinMode(fan,OUTPUT);
          pinMode(light,OUTPUT);
          pinMode(buzzer,OUTPUT);
          
       // configure LED PWM functionalitites
  //ledcSetup(ledChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  //ledcAttachPin(led, ledChannel);
 
  // while wifi not connected yet, print '.'
  // then after it connected, get out of the loop
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

  http.begin("http://projectsiot.xyz/IoTProjects/SmartHome/upload.php?a=U&b=N&c=N&d=N&e=N");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}
/*
Serial.println("sending welcome message............");
 
 if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9493206867&from=MYDREM&message=WELCOME%20TO%20PROJECT"); //Specify request destination

  //http.begin("http://projectsiot.xyz/IoTProjects/PrepaidCardPetrol/petrolcard.php?a=U&b=0&c=0");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}
*/
lcd.clear ();
}
 
void loop() {
p = "N";
g = "N";
p1 = "Normal";

temp2 = analogRead(temp);  
float V=temp2*(5/(4095.00));  
//float V=temp2*(5/(1023.00));  
  temp1=V*100;  

  temp1 = temp1 - 20;
Serial.print("temperature is = "); Serial.println(temp1);
delay(50);

gas = analogRead(gasPin);
delay(50);

Serial.println("gas = "+String(gas));

if (temp1 > 55)
{
  
    lcdstring(0,0,"T:"+String(temp1));
    lcdstring(8,0,"G:"+String(g));
     lcdstring(0,1,"PIR: "+String(digitalRead(pir)));
     delay(100);
  
  digitalWrite(fan,HIGH);

 // msg = p +"Temperature%20Alert%0AT: "+String(temp1);
// sendmsg();
  delay(2000);
}
else
{
 digitalWrite(fan,LOW); 
}
 if (gas > 3000)
{
  g = "Y";
      lcdstring(0,0,"T:"+String(temp1));
    lcdstring(8,0,"G:"+String(g));
     lcdstring(0,1,"PIR: "+String(digitalRead(pir)));
     delay(100);

  forward ();

 // msg = p +"SOUND%20Alert%20PLEASE%20CHECK";
// sendmsg ();
  delay(2000);
}
if (digitalRead(pir)==HIGH)
{
  p = "Y";
p1 = "Detected";
      lcdstring(0,0,"T:"+String(temp1));
    lcdstring(8,0,"G:"+String(g));
     lcdstring(0,1,"PIR: "+String(digitalRead(pir)));
     delay(100);

  digitalWrite(light,HIGH);
}
else
{
p1 = "Normal";
  digitalWrite(light,LOW);
}
    lcdstring(0,0,"T:"+String(temp1));
    lcdstring(8,0,"G:"+String(g));
     lcdstring(0,1,"PIR: "+String(digitalRead(pir)));
     delay(100);

iot = q + String(temp1) + "&b=" + g + "&c=" + p;
send2server ();
}// LOOP

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
void sendmsg ()
{
  Serial.println("sending message-----------");

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
 
delay(100);
}

}
