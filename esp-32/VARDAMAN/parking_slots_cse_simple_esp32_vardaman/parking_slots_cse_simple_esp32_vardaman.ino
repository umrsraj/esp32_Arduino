#include <WiFi.h>
#include <HTTPClient.h>
#include <LiquidCrystal.h>
#include <String.h>

LiquidCrystal lcd (15,2,4,16,17,5);

#define slot1Pin 34
#define slot2Pin 35
#define slot3Pin 32
#define slot4Pin 33
#define m11 25
#define m12 26

String S1 = "N";
String S2 = "N";
String S3 = "N";
String S4 = "N";

void lcdstring (int a, int b, String w);
int s1 = 0;
int s2 = 0;
int s3 = 0;
int s4 = 0;

unsigned int P1 = 0;
unsigned int P2 = 0;
unsigned int P3 = 0;
unsigned int P4 = 0;

String slot1 = "0";
String slot2 = "0";
String slot3 = "0";
String slot4 = "0";


int count1 = 0;                                          // count = 0
char input[12];


// WiFi parameters to be configured
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig 

String q = "http://projectsiot.xyz/IoTProjects/CarParking/upload.php?";
String iot = "\0";
String p = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9493206867&from=MYDREM&message=";
String msg = "\0";


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
  digitalWrite(m11,LOW);
  digitalWrite(m12,LOW);
}

 
void setup(void) { 
  Serial.begin(9600);
  Serial.print("Bezig met verbinden");
 WiFi.begin(ssid, password); // Connect to WiFi
 lcd.begin(16,2);
 
lcd.clear();  
   lcd.setCursor(0,0);
    lcd.print(" RFID BASED CAR ");
     
  lcd.setCursor(0,1);
    lcd.print(" PARKING SLOTS  ");
    delay(2000);

          pinMode(slot1Pin,INPUT);
          pinMode(slot2Pin,INPUT);
          pinMode(slot3Pin,INPUT);
          pinMode(slot4Pin,INPUT);
          pinMode(m11,OUTPUT);
          pinMode(m12,OUTPUT);
          
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

  http.begin("http://projectsiot.xyz/IoTProjects/CarParking/upload.php?a=U&b=N&c=N&d=N&e=N");

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
   http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9652490222&from=MYDREM&message=WELCOME%20TO%20PROJECT"); //Specify request destination

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

}
 
void loop() {

analogReadResolution(10);

s1 = analogRead(slot1Pin);
s2 = analogRead(slot2Pin);
s3 = analogRead(slot3Pin);
s4 = analogRead(slot4Pin);

Serial.print("ldr1 = "); Serial.println(s1);
Serial.print("ldr2 = "); Serial.println(s2);
Serial.print("ldr3 = "); Serial.println(s3);
Serial.print("ldr4 = "); Serial.println(s4);

lcd.setCursor(0,1);
    lcd.print("                     ");

if (s1>400)
{
  P1 = 0;
  S1 = "N";
}
else 
{
  P1 = 1;
  S1 = "Y";
}
if (s2>400)
{
  P2 = 0;
  S2 = "N";
}
else 
{
  P2 = 1;
  S2 = "Y";
}
if (s3>400)
{
  P3 = 0;
  S3 = "N";
}
else 
{
  P3 = 1;
  S3 = "Y";
}
if (s4>200)
{
  P4 = 0;
  S4 = "N";
}
else 
{
  P4 = 1;
  S4 = "Y";
}

lcd.setCursor(0,0);
    lcd.print("plz show card         ");
lcdstring(0,1,"S1:"+String(P1)+"S2:"+String(P2)+"S3:"+String(P3)+"S4:"+String(P4));
/*    
lcd.setCursor (0,1);
  lcd.print("S1= ");
lcd.setCursor (3,1);
  lcd.print(P1);

  lcd.setCursor (5,1);
  lcd.print("S2= ");
lcd.setCursor (8,1);
  lcd.print(P2);

 lcd.setCursor (10,1);
  lcd.print("S3= ");
lcd.setCursor (13,1);
  lcd.print(P3);
*/
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

if (input[10]=='3')
{
Serial.println("1st vehicle detected");
  if((P1==0)||(P2==0)||(P3==0)||(P4==0))
  {
    Serial.println("gate opening...........");
    
    lcdstring(0,0,"GATE OPENING............");
    forward ();
    delay(2000);
    lcdstring(0,0,"GATE - OPEN           ");
    stopp ();
    delay(5000);
     lcdstring(0,0,"GATE CLOSING............");
    backward ();
    delay(2000);
    stopp ();
    lcdstring(0,0,"GATE - CLOSE           ");
    delay(300);
  }
  else
  {
    
    lcdstring(0,0,"ALL SLOTS FULL       ");
  }
}
else if (input[10]=='7')
{
Serial.println("2nd vehicle detected");
  if((P1==0)||(P2==0)||(P3==0)||(P4==0))
  {
    Serial.println("gate opening...........");
    
    lcdstring(0,0,"GATE OPENING............");
    forward ();
    delay(2000);
    lcdstring(0,0,"GATE - OPEN           ");
    stopp ();
    delay(5000);
     lcdstring(0,0,"GATE CLOSING............");
    backward ();
    delay(2000);
    stopp ();
    lcdstring(0,0,"GATE - CLOSE           ");
    delay(300);
    
  }
  else
  {
    
    lcdstring(0,0,"ALL SLOTS FULL       ");
    delay(2000);
    lcdstring(0,0,"                       ");
  }
}
else
{
 
    lcdstring(0,0,"INVALID CARD...............      "); 
    delay(2000);
    lcdstring(0,0,"                       ");
}
  

}
  iot  = q + "a=" +S1 + "&b=" + S2 +"&c=" + S3 + "&d=" + S4;
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
void lcdstring (int a, int b, String w)
{
  lcd.setCursor(a,b);
  lcd.print(w);
}
