#include <WiFi.h>
#include <HTTPClient.h>
#include <LiquidCrystal.h>
#include <String.h>

LiquidCrystal lcd (15,2,4,16,17,5);

#define ldr1Pin 34
#define ldr2Pin 35
#define ldr3Pin 32

#define button 22

#define vib1 18
#define vib2 19
#define vib3 21 

#define v0 33
#define v1 25
#define v2 26
#define v3 27
#define v4 14
#define buzzer 23


int ldr1 = 0;
int ldr2 = 0;
int ldr3 = 0;
int flag = 0;
int p = 0;

// WiFi parameters to be configured
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig 

String q = "http://projectsiot.xyz/IoTProjects/Pill/upload.php?a=";
String iot = "\0";
String ml = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9381256458&from=MYDREM&message=";
String msg = "\0";
String gas2 = "\0";

String box1 = "N";
String box2 = "N";
String box3 = "N";

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

void setup(void) { 
  Serial.begin(9600);
  Serial.print("Bezig met verbinden");
 WiFi.begin(ssid, password); // Connect to WiFi
 lcd.begin(16,2);
 
lcd.clear();
lcd.setCursor(0,0);
        lcd.print("MEDICINE REMAINDER");
        lcd.setCursor( 2,1);
         lcd.print("   USING IOT   ");
         delay(2000);
         
 pinMode(ldr1Pin,INPUT);
 pinMode(ldr2Pin,INPUT);
 pinMode(ldr3Pin,INPUT);

 pinMode(button,INPUT);
 
 pinMode(vib1,OUTPUT);
 pinMode(vib2,OUTPUT);
 pinMode(vib3,OUTPUT);
 
 pinMode(v0,OUTPUT);
 pinMode(v1,OUTPUT);
 pinMode(v2,OUTPUT);
 pinMode(v3,OUTPUT);
 pinMode(v4,OUTPUT);

pinMode(buzzer,OUTPUT);

digitalWrite(v0,HIGH);
digitalWrite(v1,HIGH);
digitalWrite(v2,HIGH);
digitalWrite(v3,HIGH);
digitalWrite(v4,HIGH);


digitalWrite(v0,LOW);
delay(200);
digitalWrite(v0,HIGH);
delay(3000);

lcd.clear();
lcd.setCursor(0,0);
        lcd.print("SERVER INIT          ");
        lcd.setCursor( 2,1);
         lcd.print("PLEASE WAIT           ");
         delay(200);
          
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

  http.begin("http://projectsiot.xyz/IoTProjects/Pill/upload.php?a=U&b=N&c=N&d=N&e=N");

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

lcd.clear();
lcd.setCursor(0,0);
        lcd.print("SERVER INIT          ");
        lcd.setCursor( 2,1);
         lcd.print("DONE           ");
         delay(3000);
lcdstring(0,0,"PLEASE SET TIME   ");
lcdstring(0,1,"                    ");
delay(200);          
digitalWrite(v1,LOW);
delay(200);
digitalWrite(v1,HIGH);
delay(1000);

}
 
void loop() {

Serial.println("button="+String(digitalRead(button)));

iot = q + box1 + "&b=" + box2 + "&c=" + box3 ;
send2server ();

while (digitalRead(button)==HIGH);

Serial.println("button="+String(digitalRead(button)));

lcdstring(0,0,"DONE TIME SETTING  ");
lcdstring(0,1,"                    ");
delay(200);

delay(20000);

lcdstring(0,0,"MEDICINE-1 TIME    ");
lcdstring(0,1,"MATCHED             ");
delay(200);

digitalWrite(v2,LOW);
delay(300);
digitalWrite(v2,HIGH);
delay(200);
digitalWrite(buzzer,HIGH);
digitalWrite(vib1,HIGH);
//delay(5000);
p = 0;
while (p < 6)
{
  p ++ ;
ldr1 = analogRead(ldr1Pin);
Serial.println("ldr1="+String(ldr1));
  delay(1000);
}

digitalWrite(buzzer,LOW);
digitalWrite(vib1,LOW);

ldr1 = analogRead(ldr1Pin);
Serial.println("ldr1="+String(ldr1));

if (ldr1< 3000)
{
  box1 = "Y";
  
lcdstring(0,0,"MEDICINE-1 TAKEN   ");
lcdstring(0,1,"                       ");
delay(200);
}
else
{
  box1 = "N";
msg = ml + "MEDICINE%201%0ANOT%20TAKEN";  
sendmsg();  
lcdstring(0,0,"MEDICINE-1 NOT    ");
lcdstring(0,1,"TAKEN                  ");
delay(200);
}

iot = q + box1 + "&b=" + box2 + "&c=" + box3 ;
send2server ();

delay(20000);

lcdstring(0,0,"MEDICINE-2 TIME    ");
lcdstring(0,1,"MATCHED             ");
delay(200);

digitalWrite(v3,LOW);
delay(300);
digitalWrite(v3,HIGH);
delay(200);
digitalWrite(buzzer,HIGH);
digitalWrite(vib2,HIGH);
//delay(5000);
p = 0;
while (p < 6)
{
  p ++ ;
ldr2 = analogRead(ldr2Pin);
Serial.println("ldr2="+String(ldr2));
  delay(1000);
}

digitalWrite(buzzer,LOW);
digitalWrite(vib2,LOW);

ldr2 = analogRead(ldr2Pin);
Serial.println("ldr2="+String(ldr2));

if (ldr2 < 3000)
{
  box2 = "Y";

lcdstring(0,0,"MEDICINE-2 TAKEN   ");
lcdstring(0,1,"                       ");
delay(200);
}
else
{
  box2 = "N";
msg = ml + "MEDICINE%202%0ANOT%20TAKEN";  
sendmsg();  
lcdstring(0,0,"MEDICINE-2 NOT    ");
lcdstring(0,1,"TAKEN                  ");
delay(200);
}

iot = q + box1 + "&b=" + box2 + "&c=" + box3 ;
send2server ();
delay(20000);

lcdstring(0,0,"MEDICINE-3 TIME    ");
lcdstring(0,1,"MATCHED             ");
delay(200);

digitalWrite(v4,LOW);
delay(300);
digitalWrite(v4,HIGH);
delay(200);
digitalWrite(buzzer,HIGH);
digitalWrite(vib3,HIGH);
//delay(5000);
p = 0;
while (p < 6)
{
  p ++ ;
ldr3 = analogRead(ldr3Pin);
Serial.println("ldr3="+String(ldr3));
  delay(1000);
}

digitalWrite(buzzer,LOW);
digitalWrite(vib3,LOW);

ldr3 = analogRead(ldr3Pin);
Serial.println("ldr3="+String(ldr3));

if (ldr3 < 3000)
{
  box3 = "Y";
lcdstring(0,0,"MEDICINE-3 TAKEN   ");
lcdstring(0,1,"                       ");
delay(200);
}
else
{
  box3 = "N";
  
msg = ml + "MEDICINE%203%0ANOT%20TAKEN";  
sendmsg();  
lcdstring(0,0,"MEDICINE-3 NOT    ");
lcdstring(0,1,"TAKEN                  ");

delay(200);
}

iot = q + box1 + "&b=" + box2 + "&c=" + box3 ;
send2server ();

delay(20000);

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
