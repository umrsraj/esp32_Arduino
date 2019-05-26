#include <WiFi.h>
#include <HTTPClient.h>

#include <LiquidCrystal.h>
#include <String.h>

// WiFi parameters to be configured
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig
String a = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=8143513239&from=MYDREM&message=";
String msg = "\0";
String r = "http://projectsiot.xyz/IoTProjects/GarbageSystem/upload.php?a=";
String rs = "\0";
String BIN1 = "\0";
String BIN2 = "\0";
String G1 = "\0";
String G2 = "\0";
int alc;
String read_msg = "\0";

LiquidCrystal lcd (15,2,0,4,5,18);

#define trigPin 27
#define echoPin 26
#define trigPin1 12
#define echoPin1 14
#define gas1Pin 34
#define buzzer 21
#define gas2Pin 35

#define SIM900 Serial2
#define RXD2 16
#define TXD2 17

long duration, distance,duration1,distance1;

unsigned int obstacle = 0;
unsigned int fire = 0;
int gas1 = 0;
int gas2 = 0;
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
void beep ()
{
  digitalWrite(buzzer,HIGH); delay(1000);
  digitalWrite(buzzer,LOW); delay(100);
}
void setup() {
  Serial.begin(9600);
  
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  
  Serial.println("power up");
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);

pinMode(gas2Pin,INPUT);
pinMode(gas1Pin,INPUT);
//pinMode(buzzer,OUTPUT);

lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("*IOT BSD GARBAGE ***");
  lcd.setCursor( 0, 1);
  lcd.print("MONITORING SYSTEM ");
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


Serial.print("A = "); Serial.println("http://projectsiot.xyz/IoTProjects/GarbageMonitoring/upload.php?a=U&b=86&c=L");


if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   
  http.begin("http://projectsiot.xyz/IoTProjects/GarbageSystem/upload.php?a=U");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(5000);

lcd.clear ();

lcdstring(0,0,"B1:");
lcdstring(0,1,"B2:");
lcdstring(8,0,"G1:");
lcdstring(8,1,"G2:");
}

}


void loop()
{

//obstacle = digitalRead(obstacle_sensor);
//fire = digitalRead(fire_sensor);
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance= duration*0.034/2;
Serial.print("Distance: ");
Serial.println(distance);
delay(50);
Serial.print(F("distance = ")); Serial.println(distance);
//Serial.print(F("obstacle = ")); Serial.println(obstacle);
digitalWrite(trigPin1, LOW);
delayMicroseconds(2);
digitalWrite(trigPin1, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin1, LOW);
duration1 = pulseIn(echoPin1, HIGH);
distance1= duration1*0.034/2;
Serial.print("Distance: ");
Serial.println(distance1);
delay(50);
Serial.print(F("distance1 = ")); Serial.println(distance1);

if(distance>14)
{
  
  lcdstring(3,0,"EMT");
  BIN1="EMPTY";
}
else if(distance<14&&distance>5)
{
  
  lcdstring(3,0,"MID");
  BIN1="MIDIUM";
}
else if(distance<6)
{
  
  lcdstring(3,0,"FUL");
  BIN1="FULL";

rs = r+BIN1+"&b="+G1+"&c="+BIN2+"&d="+G2 ;
  send2server ();

  
//  beep();
 // beep();
 // msg = a+"BIN1--FULL%0APLEASE%20COLLECT";
 sendsms ("08143513239","BIN-1 FULL \nPLEASE COLLECT AT VITS,DESHMUKHI");
}

if(distance1>14)
{
  lcdstring(3,1,"EMT");
  BIN2="EMPTY";
}
else if(distance1<14&&distance1>5)
{
  
 lcdstring(3,1,"MID");
  BIN2="MEDIUM";
}
else if(distance1<6)
{
  
lcdstring(3,1,"FUL");
  BIN2="FULL";
 // beep();
//  beep();

rs = r+BIN1+"&b="+G1+"&c="+BIN2+"&d="+G2 ;
  send2server ();


   msg = a+"BIN2--FULL%0APLEASE%20COLLECT";

 sendsms ("08143513239","BIN-2 FULL \nPLEASE COLLECT AT VITA,DESHMUKHI");
 }
gas1 = analogRead(gas1Pin);

Serial.println("gas1 = "+String(gas1));

gas2 = analogRead(gas2Pin);

Serial.println("gas2 = "+String(gas2));

if (gas1 > 3800)
{
  Serial.println("gas1 high");
lcdstring(11,0,"H");
G1 = "H";  
beep();

rs = r+BIN1+"&b="+G1+"&c="+BIN2+"&d="+G2 ;
  send2server ();


msg = a+"GAS1--HIGH%0APLEASE%20CHECK";

 sendsms ("08143513239","GAS-1 HIGH\nPLEASE CHECK");
}
else
{
  Serial.println("gas1 low");
lcdstring(11,0,"L");
G1 = "L";
}
if (gas2 > 3800) 
{
  Serial.println("gas2 high");
lcdstring(11,1,"H");
beep();
G2 = "H";

rs = r+BIN1+"&b="+G1+"&c="+BIN2+"&d="+G2 ;
  send2server ();


msg = a+"GAS1--HIGH%0APLEASE%20CHECK";
 sendsms ("08143513239","GAS-2 HIGH\nPLEASE CHECK");
}
else
{
  Serial.println("gas2 low");
lcdstring(11,1,"L");
G2 = "L";
}

rs = r+BIN1+"&b="+G1+"&c="+BIN2+"&d="+G2 ;
  send2server ();

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
read_msg = "\0";
}
void sendsms (String UU, String x)
{
/*
 Serial.print("AT\r\n");
         Serial.print('\n');
        delay(2000);
         Serial.print("ATE1\r\n");
        delay(2000);
        Serial.print("AT&W\r\n");
         Serial.print('\n');
        delay(2000);
         Serial.print("AT+CMGF=1\r\n");
        delay(2000);
         Serial.print("AT+CNMI=2,2,0,0,0\r\n");
        delay(2000);
       // Serial.print("AT+CSMP=17,167,0,0\n");
        delay(2000); 
       Serial.print("AT+CMGS=\""+UU+"\"\r");
        Serial.print('\n');
        delay(2000);
         Serial.print(xx);
         Serial.print('\r');
        Serial.print('\n');
        delay(2000);
        Serial.print((char)26);
        delay(2000);
        */

SIM900.print("AT\r\n");
        SIM900.print('\n');
        ShowSerialData();
        delay(3000);
        SIM900.print("ATE1\r\n");
        ShowSerialData();
        delay(3000);
       SIM900.print("AT&W\r\n");
        SIM900.print('\n');
        ShowSerialData();
        delay(3000);
        SIM900.print("AT+CMGF=1\r\n");
        ShowSerialData();
        delay(3000);
        SIM900.print("AT+CNMI=2,2,0,0,0\r\n");
        ShowSerialData();
        delay(2000);
       // Serial.print("AT+CSMP=17,167,0,0\n");
        delay(2000); 
        SIM900.print("AT+CMGS=\""+UU+"\"\r");
        ShowSerialData();
       // Serial.print('"');
      //Serial.print("9014449822");
      //Serial.print('"');
      //Serial.print('\r');
        SIM900.print('\n');
       delay(1000);
       SIM900.println(x);
     
       SIM900.println();
      
     SIM900.print('\r');
      SIM900.print('\n');
      
     delay(3000);
       SIM900.print((char)26);
       ShowSerialData();
}
void ShowSerialData()
{
  while(SIM900.available()!=0)
   read_msg = SIM900.readString();
   if (read_msg != '\0')
   {
  Serial.println("read_msg is = "); Serial.println(read_msg);
   }
   delay(1);
}
void lcdstring (int a, int b, String data)
{
  lcd.setCursor(a,b);
  lcd.print(data);
}
