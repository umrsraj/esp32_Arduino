#include <WiFi.h>
#include <HTTPClient.h>
#include <LiquidCrystal.h>
#include <String.h>

int count1 = 0;                                          // count = 0
char input[12];

LiquidCrystal lcd (15,2,4,16,17,5);

#define ldr1Pin 34
#define ldr2Pin 35
#define ldr3Pin 32
#define ldr4Pin 33
#define ir 18
#define m11 22
#define m12 23
#define buzzer 21
#define light1 27
#define light2 26
#define light3 25



void send2server (String linkk);


// WiFi parameters to be configured
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig

String a1 = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9652490222&from=MYDREM&message=";
String msg = "\0";
String updat = "http://projectsiot.xyz/IoTProjects/CarBooking/carbslot1.php?a=";
String gett = "http://projectsiot.xyz/IoTProjects/CarBooking/carslotup.php";
String rs = "\0";

char v1 = '\0';
char v2 = '\0';
char v3 = '\0';

char s1 = '\0';
char s2 = '\0';
char s3 = '\0';

int flag1 = 30000;
int flag2 = 30000;
int flag3 = 30000;

int ldr1  = 0;
int ldr2  = 0;
int ldr3 = 0;


String L1 = "N";
String L2 = "N";
String L0 = "N";

void forward ()
{
  digitalWrite(m11,HIGH);
  digitalWrite(m12,LOW);
}
void backward ()
{
  digitalWrite(m12,HIGH);
  digitalWrite(m11,LOW);
}

void stopp ()
{
  digitalWrite(m12,LOW);
  digitalWrite(m11,LOW);
}



void setup() {
  Serial.begin(9600);
  Serial.println("power up");

 
lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ADVANCED PARKING");
  lcd.setCursor( 0, 1);
  lcd.print("PARKING SYSTEM     ");
  delay(2500);

   pinMode(ldr1Pin,INPUT);
          pinMode(ldr2Pin,INPUT);
          pinMode(ldr3Pin,INPUT);
          pinMode(ldr4Pin,INPUT);
          pinMode(ir,INPUT);
          pinMode(buzzer,OUTPUT);
          pinMode(m11,OUTPUT);
          pinMode(m12,OUTPUT);
pinMode(light1,OUTPUT);
pinMode(light2,OUTPUT);
pinMode(light3,OUTPUT);
          
  
lcd.clear();
lcd.setCursor(0,0);
        lcd.print("CONNECTING--TO");
        lcd.setCursor( 2,1);
         lcd.print(ssid);
         delay(100);

Serial.print("Bezig met verbinden");
  WiFi.begin(ssid, password); // Connect to WiFi
 
  // while wifi not connected yet, print '.'
  // then after it connected, get out of the loop
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
  }
  
  // Verbonden.
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


Serial.print("A = "); Serial.println(updat+"0&b=0&c=0&d=0");


if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   
  http.begin(updat+"0&b=0&c=0&d=0");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(5000);

  lcd.setCursor(0, 0);
  lcd.print("SERVER INT.       ");
  lcd.setCursor( 0, 1);
  lcd.print("     DONE     ");
delay(3000);

}

lcd.clear ();

lcd.setCursor(0,0);
lcd.print("S1:");
lcd.setCursor(5,0);
lcd.print("S2:");
lcd.setCursor(10,0);
lcd.print("S3:");


lcd.setCursor(3,0);
lcd.print("0");
lcd.setCursor(8,0);
lcd.print("0");
lcd.setCursor(13,0);
lcd.print("0");

  lcd.setCursor(0,1);
  lcd.print("GATE -- CLOSE    ");
  delay(200);

}


void loop()
{

flag1++;
flag2++;
flag3++;

if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
 http.begin(gett);

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println("PAYLOAD="+payload); //Print the response payload


Serial.println(payload[payload.indexOf("sts0")+7]);
Serial.println(payload[payload.indexOf("sts1")+7]);
Serial.println(payload[payload.indexOf("sts2")+7]);

 v1 = payload[payload.indexOf("sts0")+7];
 v2 = payload[payload.indexOf("sts1")+7];
 v3 = payload[payload.indexOf("sts2")+7];

Serial.println("v1="+String(v1));
Serial.println("v2="+String(v2));
Serial.println("v3="+String(v3));

/*
lcd.setCursor(3,0);
lcd.print("0");
lcd.setCursor(8,0);
lcd.print("0");
lcd.setCursor(13,0);
lcd.print("0");

lcd.setCursor(3,1);
lcd.print("0");
lcd.setCursor(9,1);
lcd.print("0");

*/

ledcheck ();

if (v1 == 'Y')
{
  //v= '0';
  Serial.println("slot-1 booked from server");
flag1 = 0;
v1 = '1';
lcd.setCursor(3,0);
lcd.print("1");  
delay(100);
rs = updat + v1 + "&b=" + v2 + "&c=" + v3;
send2server (rs);
msg = a1 + "SLOT-1%20BOOKED";
//send2server (msg);
send2server (gett);
}
else
{
  flag1 = 5000;
}
if (v2 == 'Y')
{
  Serial.println("SLOT-2 BOOKED FROM SERVER");
//v = '0';
flag2 = 0;
lcd.setCursor(8,0);
lcd.print("1");  
delay(100);
v2='1';
 rs = updat + v1 + "&b=" + v2 + "&c=" + v3;
send2server (rs);
msg = a1 + "SLOT-2%20BOOKED";
//send2server (msg);
send2server (gett);
}
else
{
  flag2 = 5000;
}
if (v3 == 'Y')
{
  Serial.println("slot - 3 booked form server");
//v = '0';
flag3 = 0;
lcd.setCursor(13,0);
lcd.print("1");  
delay(100);
v3 = '1';
 rs = updat + v1 + "&b=" + v2 + "&c=" + v3;
send2server (rs);
msg = a1 + "SLOT-3%20BOOKED";
//send2server (msg);
send2server (gett);
}
else
{
  flag3 = 5000;
}





    http.end(); //Close connection
 
delay(500);
}
}


ldr1 = analogRead(ldr1Pin);
ldr2 = analogRead(ldr2Pin);
ldr3 = analogRead(ldr3Pin);

Serial.println("ldr1 = "+String(ldr1));
Serial.println("ldr2 = "+String(ldr2));
Serial.println("ldr3 = "+String(ldr3));

if(ldr1 < 1000)
{
  if (v1 == '0')
{
  Serial.println("s1 - 1");
 s1 = '1';
 v1 = '1';

}
}
else
{
  if (flag1 > 100)
  {
 Serial.println("s1 - 0");
 s1 = '0';
 v1 = '0'; 

  }
}
if(ldr2 < 1000)
{
  if (v2 == '0')
{
  Serial.println("s2 - 1");
 s2 = '1';
 v2 = '1';

}
}
else
{
  if (flag2 > 100)
  {
 Serial.println("s2 - 0");
 s2 = '0';
 v2 = '0';

  }
}
if(ldr3 < 1000)
{
  if (v3 == '0')
{
  Serial.println("s3 - 1");
 s3 = '1';
 v3 = '1';
}
}
else
{
  if (flag3 > 100)
  {
 Serial.println("s3 - 0");
 s3 = '0';
 v3 = '0';

  }
}
rs = updat + v1 + "&b=" + v2 + "&c=" + v3;
send2server (rs);

ledcheck ();

lcd.clear ();
lcd.setCursor(0,0);
lcd.print("S1:");
lcd.setCursor(5,0);
lcd.print("S2:");
lcd.setCursor(10,0);
lcd.print("S3:");


lcd.setCursor(3,0);
lcd.print(v1);
lcd.setCursor(8,0);
lcd.print(v2);
lcd.setCursor(13,0);
lcd.print(v3);

if(Serial.available())
   {
      count1 = 0;
      while(Serial.available() && count1 < 12)          // Read 12 characters and store them in input array
      {
         input[count1] = Serial.read();
         count1++;
         delay(5);
      }//WHILE
//

 Serial.println(input);                           // Print RFID tag number 
   Serial.print("input[10] is "); Serial.println(input[10]);
//////////////////////////////
if (input[10]=='E')
{


  Serial.println("ir detected...........");
if((v1=='0')||(v2=='0')||(v3=='0'))
{
  Serial.println("gate opening");
  lcd.setCursor(0,1);
  lcd.print("GATE OPENING    ");
  forward ();
  lcd.setCursor(0,1);
  lcd.print("GATE -- OPEN    ");
  delay(2500);
  stopp ();
  delay(3000);
  lcd.setCursor(0,1);
  lcd.print("GATE CLOSING    ");
  backward ();
  delay(2500);
  lcd.setCursor(0,1);
  lcd.print("GATE -- CLOSE    ");
  delay(200);
  stopp ();
}
else
{
  Serial.println("all slots full");
  
  lcd.setCursor(0,1);
  lcd.print("ALL SLOTS FULL       ");
  delay(2000);
}
}

    }


} // LOOP

void send2server (String linkk)
{
Serial.print("rs = "); Serial.println(linkk);
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
 http.begin(linkk);

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}
}
void sendsms (String link)
{
Serial.print("msg = "); Serial.println(link);
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
 http.begin(link);

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}
}
void lcdstring (int a, int b, String data)
{
  lcd.setCursor(a,b);
  lcd.print(data);
}
void ledcheck ()
{
 if(v1=='0')
 {
  digitalWrite(light1,HIGH);
 }
 else {
  digitalWrite(light1,LOW);
 }
 if(v2=='0')
 {
  digitalWrite(light2,HIGH);
 }
 else {
  digitalWrite(light2,LOW);
 }
 if(v3=='0')
 {
  digitalWrite(light3,HIGH);
 }
 else {
  digitalWrite(light3,LOW);
 }
}
