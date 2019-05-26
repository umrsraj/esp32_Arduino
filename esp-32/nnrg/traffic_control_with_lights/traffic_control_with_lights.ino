

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

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

LiquidCrystal lcd (D0,D3,D4,D5,D6,D7);
//#define fire_sensor D1
//#define obstacle_sensor D0 

//#define m11 D2
//#define m12 D3
//#define m21 D4
//#define m22 D5

#define ir1 D1
#define ir2 D2
#define ir3 D8
#define ir4 10

//#define gled D8
//#define rled 1

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

if(digitalRead(ir1)==HIGH)
{
  lcd.setCursor(0, 0);
  lcd.print("TRAFIC H :EAST   ");
  lcd.setCursor( 0, 1);
  lcd.print("                     ");
  delay(1500);
  a='Y';
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
}
else
{
c='N';
}
rs= r + a + "&b=" + b + "&c=" + c + "&d=" + d;
send2server ();
//fire = digitalRead(fire_sensor);

} // LOOP

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
