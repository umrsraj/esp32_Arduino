#include <WiFi.h>
#include <HTTPClient.h>
#include <LiquidCrystal.h>
#include <String.h>
 
LiquidCrystal lcd (15,2,4,16,17,5);

#define ldr1Pin 34
#define ldr2Pin 35
#define ldr3Pin 32
#define smokePin 33
#define buzzer 21
#define light1 18
#define light2 19 

int ldr1  = 0;
int ldr2  = 0;
int ldr3 = 0;
int smoke = 0;

// WiFi parameters to be configured
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig 

String q = "http://projectsiot.xyz/IoTProjects/Light/upload.php?";
String iot = "\0";
String p = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9177369558&from=MYDREM&message=";
String msg = "\0";

String L1 = "N";
String L2 = "N";
String L0 = "N";

/*
int freq = 5000;
int ledChannel = 0;
int resolution = 8;
int dutyCycle = 0;
*/
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
        lcd.print("     SMART       ");
        lcd.setCursor( 0,1);
         lcd.print(" STREET LIGHTS  ");
         delay(2000);
         
          pinMode(ldr1Pin,INPUT);
          pinMode(ldr2Pin,INPUT);
          pinMode(ldr3Pin,INPUT);
          pinMode(smoke,INPUT);
          pinMode(buzzer,OUTPUT);
          pinMode(light1,OUTPUT);
          pinMode(light2,OUTPUT);
          
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
     delay(2000);
     
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
   // http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=91773 69558‬&from=MYDREM&message=RJANED;LKSDF"); //Specify request destination

  http.begin("http://projectsiot.xyz/IoTProjects/Light/upload.php?a=U&b=N&c=N&d=N&e=N");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}

Serial.println("sending welcome message............");
 
 if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9177369558&from=MYDREM&message=WELCOME%20TO%20PROJECT"); //Specify request destination

  //http.begin("http://projectsiot.xyz/IoTProjects/PrepaidCardPetrol/petrolcard.php?a=U&b=0&c=0");

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

ldr1 = analogRead(ldr1Pin);
ldr2 = analogRead(ldr2Pin);
ldr3 = analogRead(ldr3Pin);
smoke = analogRead(smokePin);

Serial.println("ldr1 = "+String(ldr1));
Serial.println("ldr2 = "+String(ldr2));
Serial.println("ldr3 = "+String(ldr3));
Serial.println("smoke = "+String(smoke));
/*
lcd.clear();
lcd.setCursor(0,0);
lcd.print(ldr1);
lcd.setCursor(8,0);
lcd.print(ldr2);
lcd.setCursor(0,1);
lcd.print(ldr3);
delay(500);
*/

if(ldr1> 3000)
{
  Serial.println("night detected");
 L0 = "Y";
 digitalWrite(light1,HIGH);
 digitalWrite(light2,HIGH);
 delay(100);
}
else
{
  Serial.println("day detected");
 L0 = "N";
 digitalWrite(light1,LOW);
 digitalWrite(light2,LOW);
 delay(100);
}
if(ldr2 < 1000)
{
  Serial.println("1st light on");
 L1 = "Y";
}
else
{
  Serial.println("1st light off");
 L1 = "N";
}

if(ldr3 < 1000)
{
  Serial.println("2nd light on");
 L2 = "Y";
}
else
{
  Serial.println("1st light off");
 L2 = "N";
}
if (smoke > 3800)
{
   lcd.clear();
  lcdstring(0,0,"SMOKE ALERT     ");
  lcdstring(0,1,"PLEASE CHECK....");
  delay(20);
  beep ();
   iot  = q + "a=" + L0 + "&b=" + L1 +"&c=" + L2 + "&d=Y";
  send2server ();
  msg = p +"SMOKE%DETECTED%20PLEASE%20CHECK";
  sendmsg ();
  delay(2000);
}

else
{
   lcd.clear();
  lcdstring(0,0,"L0:"+L0+" L1:"+L1+" L2:"+L2);
  lcdstring(8,1,"L1:"+L1);
  lcdstring(0,1,"SMOKE NORMAL    ");
  delay(200);
   iot  = q + "a=" + L0 + "&b=" + L1 +"&c=" + L2 + "&d=N";
  send2server (); 
}
if((L0 == "Y")&&(L1 == "N")&&(L2 == "N"))
{
  Serial.println("both lights fault");
   msg = p +"BOTH%20LIGHTS%20FAULT";
  sendmsg ();
}
else if((L0 == "Y")&&(L1 == "N")&&(L2 == "Y"))
{
  Serial.println("light-1 fault");
   msg = p +"LIGHT-1%20FAULT";
  sendmsg ();
}
else if((L0 == "Y")&&(L1 == "Y")&&(L2 == "N"))
{
  Serial.println("light-2 fault");
   msg = p +"LIGHT-2%20FAULT";
  sendmsg ();
}
else if((L0 == "N")&&(L1 == "Y")&&(L2 == "Y"))
{
  Serial.println("both lights fault");
   msg = p +"BOTH%20LIGHTS%20FAULT";
  sendmsg ();
}
else if((L0 == "N")&&(L1 == "Y")&&(L2 == "N"))
{
  Serial.println("light-1 fault");
   msg = p +"LIGHT-1%20FAULT";
  sendmsg ();
}
else if((L0 == "N")&&(L1 == "N")&&(L2 == "Y"))
{
  Serial.println("light-2 fault");
   msg = p +"LIGHT-2%20FAULT";
  sendmsg ();
}

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
   // http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9652490222&from=MYDREM&message=RJANED;LKSDF"); //Specify request destination

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
void lcdstring (int a, int b, String w)
{
  lcd.setCursor(a,b);
  lcd.print(w);
}
