

#include <WiFi.h>
#include <HTTPClient.h>

#include <LiquidCrystal.h>
#include <String.h>

// WiFi parameters to be configured
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig
//String a = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9014449822&from=MYDREM&message=";
String msg = "\0";
String r = "http://projectsiot.xyz/IoTProjects/TrafficLight/trafficupload.php?a=";
String rs = "\0";
String obs = "\0";
String fir = "\0";
int alc;

LiquidCrystal lcd (15,2,4,16,17,5);
//#define fire_sensor D1
//#define obstacle_sensor D0 

//#define m11 D2
//#define m12 D3
//#define m21 D4
//#define m22 D5

#define ir1 18
#define ir2 19
#define ir3 22
#define ir4 23

#define red1 33
#define red2 32
#define red3 13
#define red4 12

#define green1 25
#define green2 26
#define green3 27
#define green4 14

unsigned int obstacle = 0;
unsigned int fire = 0;

char a,b,c,d;
/*
void forward ()
{
  digitalWrite(m11, HIGH);
  digitalWrite(m12, LOW);
  digitalWrite(m21, HIGH);
  digitalWrite(m22, LOW);
  delay(10);
}

void backward ()
{
  digitalWrite(m12, HIGH);
  digitalWrite(m11, LOW);
  digitalWrite(m22, HIGH);
  digitalWrite(m21, LOW);
  delay(10);
}
void left ()
{
  digitalWrite(m12, LOW);
  digitalWrite(m11, HIGH);
  digitalWrite(m21, LOW);
  digitalWrite(m22, HIGH);
  delay(10);
}

void right ()
{

  digitalWrite(m11, LOW);
  digitalWrite(m12, HIGH);
  digitalWrite(m21, HIGH);
  digitalWrite(m22, LOW);
  delay(10);
}
void stopp ()
{
  digitalWrite(m12, LOW);
  digitalWrite(m11, LOW);
  digitalWrite(m22, LOW);
  digitalWrite(m21, LOW);
  delay(10);
}
*/

void setup() {
  Serial.begin(9600);
  Serial.println("power up");
 
//pinMode (rled,OUTPUT);
//pinMode (gled,OUTPUT);
  
pinMode (ir1,INPUT);
pinMode (ir2,INPUT);
pinMode (ir3,INPUT);
pinMode (ir4,INPUT);

pinMode(green1,OUTPUT);
pinMode(green2,OUTPUT);
pinMode(green3,OUTPUT);
pinMode(green4,OUTPUT);


pinMode(red1,OUTPUT);
pinMode(red2,OUTPUT);
pinMode(red3,OUTPUT);
pinMode(red4,OUTPUT);

lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("***IOT BSD ***");
  lcd.setCursor( 0, 1);
  lcd.print("TRAFFIC CONTROL S/M ");
  delay(2500);
  
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


Serial.print("A = "); Serial.println("http://projectsiot.xyz/IoTProjects/HealthCare/healthupload.php?a=U&b=86&c=L");


if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   
  http.begin("http://projectsiot.xyz/IoTProjects/TrafficLight/trafficupload.php?a=U&b=Y&c=Y&d=Y");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(5000);
}

}


void loop()
{

digitalWrite(green1,HIGH);
digitalWrite(green2,LOW);
digitalWrite(green3,LOW);
digitalWrite(green4,LOW);

digitalWrite(red1,LOW);
digitalWrite(red2,HIGH);
digitalWrite(red3,HIGH);
digitalWrite(red4,HIGH);
 delay(500);
check ();

////////////////////////

digitalWrite(green1,LOW);
  digitalWrite(green2,HIGH);
  digitalWrite(green3,LOW);
  digitalWrite(green4,LOW);

digitalWrite(red1,HIGH);
digitalWrite(red2,LOW);
digitalWrite(red3,HIGH);
digitalWrite(red4,HIGH);
 delay(500);
check ();

////////////////////////

digitalWrite(green1,LOW);
  digitalWrite(green2,LOW);
  digitalWrite(green3,HIGH);
  digitalWrite(green4,LOW);

digitalWrite(red1,HIGH);
digitalWrite(red2,HIGH);
digitalWrite(red3,LOW);
digitalWrite(red4,HIGH);
 delay(500);
check ();

////////////////////////

digitalWrite(green1,LOW);
  digitalWrite(green2,LOW);
  digitalWrite(green3,LOW);
  digitalWrite(green4,HIGH);

digitalWrite(red1,HIGH);
digitalWrite(red2,HIGH);
digitalWrite(red3,HIGH);
digitalWrite(red4,LOW);
 delay(500);
check ();

//rs= r + a + "&b=" + b + "&c=" + c + "&d=" + d;
//send2server ();
//fire = digitalRead(fire_sensor);

} // LOOP

void check ()
{
  if(digitalRead(ir1)==HIGH)
{
  lcd.setCursor(0, 0);
  lcd.print("TRAFIC H :EAST   ");
  lcd.setCursor( 0, 1);
  lcd.print("                     ");
  delay(1500);
  a='Y';
  digitalWrite(green1,HIGH);
  digitalWrite(green2,LOW);
  digitalWrite(green3,LOW);
  digitalWrite(green4,LOW);

digitalWrite(red1,LOW);
digitalWrite(red2,HIGH);
digitalWrite(red3,HIGH);
digitalWrite(red4,HIGH);

 delay(500);
 
rs= r + a + "&b=" + b + "&c=" + c + "&d=" + d;
send2server ();
delay(8000);
 
}
else
{
a='N';
}
if(digitalRead(ir2)==HIGH)
{
  lcd.setCursor(0, 0);
  lcd.print("TRAFIC H :WEST   ");
  lcd.setCursor( 0, 1);
  lcd.print("                 ");
  delay(500);
  b='Y';
  digitalWrite(green1,LOW);
  digitalWrite(green2,HIGH);
  digitalWrite(green3,LOW);
  digitalWrite(green4,LOW);

digitalWrite(red1,HIGH);
digitalWrite(red2,LOW);
digitalWrite(red3,HIGH);
digitalWrite(red4,HIGH);
 delay(500);
 
rs= r + a + "&b=" + b + "&c=" + c + "&d=" + d;
send2server ();
delay(8000);
}
else
{
b='N';
}
if(digitalRead(ir3)==HIGH)
{
  lcd.setCursor(0, 0);
  lcd.print("TRAFIC H :NORTH   ");
  lcd.setCursor( 0, 1);
  lcd.print("                 ");
  delay(500);
  d='Y';

  digitalWrite(green1,LOW);
  digitalWrite(green2,LOW);
  digitalWrite(green3,HIGH);
  digitalWrite(green4,LOW);

digitalWrite(red1,HIGH);
digitalWrite(red2,HIGH);
digitalWrite(red3,LOW);
digitalWrite(red4,HIGH);

 delay(500);
 
rs= r + a + "&b=" + b + "&c=" + c + "&d=" + d;
send2server ();
delay(8000);
}
else
{
d='N';
}
if(digitalRead(ir4)==HIGH)
{
  lcd.setCursor(0, 0);
  lcd.print("TRAFIC H :SOUTH   ");
  lcd.setCursor( 0, 1);
  lcd.print("                   ");
  delay(500);
  c='Y';

  digitalWrite(green1,LOW);
  digitalWrite(green2,LOW);
  digitalWrite(green3,LOW);
  digitalWrite(green4,HIGH);

digitalWrite(red1,HIGH);
digitalWrite(red2,HIGH);
digitalWrite(red3,HIGH);
digitalWrite(red4,LOW);

 delay(500);
 
rs= r + a + "&b=" + b + "&c=" + c + "&d=" + d;
send2server ();
delay(8000);
}
else
{
c='N';
}
}//check ()

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
