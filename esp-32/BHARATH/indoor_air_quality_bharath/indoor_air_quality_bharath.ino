#include <WiFi.h>
#include <HTTPClient.h>
#include <LiquidCrystal.h>
#include <String.h>

LiquidCrystal lcd (15,2,4,16,17,5);

#define temp 34
#define gasPin 35
#define soundPin 32
#define humPin 33
#define buzzer 26

float temp1=0.0;
unsigned temp2 = 0;
int gas  = 0;
int sound  = 0;
int hum = 0;
int gas1 = 0;


char g = 'N';
char s = 'N';
char h = 'N';

// WiFi parameters to be configured
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig 

String q = "http://projectsiot.xyz/IoTProjects/IndoorAir/upload.php?";
String iot = "\0";
String p = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydream123&to=9493206867&from=MYDREM&message=";
String msg = "\0";
String gas2 = "\0";
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
        lcd.print("AIR QUALITY S/M");
        lcd.setCursor( 2,1);
         lcd.print("   USING IOT   ");
         delay(2000);
         
          pinMode(humPin,INPUT);
          pinMode(soundPin,INPUT);
          pinMode(gasPin,INPUT);
          pinMode(temp,INPUT);
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

  http.begin("http://projectsiot.xyz/IoTProjects/IndoorAir/upload.php?a=U&b=N&c=N&d=N&e=N");

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
}
 
void loop() {

g = 'R';
s = 'N';
h = 'N';

temp2 = analogRead(temp);  
float V=temp2*(5/(4095.00));  
//float V=temp2*(5/(1023.00));  
  temp1=V*10;  

  temp1 = temp1 +15 ;
Serial.print("temperature is = "); Serial.println(temp1);
delay(50);

gas = analogRead(gasPin);
delay(50);
sound = analogRead(soundPin);
delay(50);
//analogReadResolution(10);
hum = analogRead(humPin);
delay(50);

Serial.println("gas = "+String(gas));
Serial.println("sound = "+String(sound));
Serial.println("hum = "+String(hum));

if (temp1 > 55)
{
  lcd.clear();
  lcdstring(0,0,"TEMPERATURE ALERT");
  lcdstring(0,1,"T: "+String(temp1));
  delay(20);
  beep ();
   iot  = q + "a=" + String(temp1) + "&b=" + h +"&c=" + g + "&d=" + s;
  send2server ();
  msg = p +"Temperature%20Alert%0AT: "+String(temp1);
// sendmsg();
  delay(2000);
}
else if (sound > 3500)
{
  s = 'Y';
  lcd.clear();
  lcdstring(0,0,"CO2 ALERT        ");
  lcdstring(0,1,"PLEASE CHECK     ");
  delay(20);
 beep ();
   iot  = q + "a=" + String(temp1) + "&b=" + h +"&c=" + g + "&d=" + s;
  send2server ();
  msg = p +"SOUND%20Alert%20PLEASE%20CHECK";
// sendmsg ();
  delay(2000);
}
/*
else if (gas > 3000)
{
   lcd.clear();
  lcdstring(0,0,"CO  ALERT       ");
  lcdstring(0,1,"PLEASE CHECK....");
  delay(20);
  beep ();
   iot  = q + "a=" + String(temp1) + "&b=" + h +"&c=" + g + "&d=" + s;
  send2server ();
  msg = p +"HARMFULL%20AIR%DETECTED%20PLEASE%20CHECK";
// sendmsg ();
  delay(2000);
}
*/
else if (hum < 3500)
{
  h = 'Y';
  lcd.clear();
  lcdstring(0,0," HUMIDITY ALERT");
  lcdstring(0,1,"PLEASE CHECK....");
  delay(20);
  beep ();
   iot  = q + "a=" + String(temp1) + "&b=" + h +"&c=" + g + "&d=" + s;
  send2server ();
  msg = p +"HUMIDITY%20Alert%20PLEASE%20CHECK";
//sendmsg ();
  delay(2000);
}


else
{
  lcd.clear();
  lcdstring(0,0,"T: "+String(temp1));
  lcdstring(8,0,"H: "+ String(h));
  lcdstring(0,1,"CO: "+String(s));
//  lcdstring(8,1,"CO2: "+String(g));
  delay(10);
   iot  = q + "a=" + String(temp1) + "&b=" + h +"&c=" + g + "&d=" + s;
  send2server ();
}

/*
if (gas <650)
{
  gas1 = map(gas,50,650,350,1000);
  gas2 = "FRESH%20AIR";
  Serial.println("map1 = "+String(gas1));
}
else if ((gas >= 650)&&(gas < 1000))
{
  gas1 = map(gas,650,1000,1000,2000);
  gas2 = "POOR%20AIR";
  Serial.println("map2 = "+String(gas1));
}
else if (gas >= 1000)
{
  gas1 = map(gas,1500,4000,2000,4000);
  gas2 = "HARMFUL%20AIR";
  Serial.println("map2 = "+String(gas1));
}

if (temp1 > 55)
{
  lcd.clear();
  lcdstring(0,0,"TEMPERATURE ALERT");
  lcdstring(0,1,"T: "+String(temp1));
  delay(20);
  beep ();
   iot  = q + "a=" + String(temp1) + "&b=" + String(gas2) +"&c=N&d=N";
  send2server ();
  msg = p +"Temperature%20Alert%0AT: "+String(temp1);
// sendmsg();
  delay(2000);
}

else if (gas > 1000)
{
   lcd.clear();
  lcdstring(0,0,"HARMFULL AIR ALERT");
  lcdstring(0,1,"PLEASE CHECK....");
  delay(20);
  beep ();
   iot  = q + "a=" + String(temp1) + "&b=" + String(gas2) +"&c=N&d=N";
  send2server ();
  msg = p +"HARMFULL%20AIR%DETECTED%20PLEASE%20CHECK";
 // sendmsg ();
  delay(2000);
}
else if (hum < 3500)
{
  lcd.clear();
  lcdstring(0,0," HUMIDITY ALERT");
  lcdstring(0,1,"PLEASE CHECK....");
  delay(20);
  beep ();
  iot  = q + "a=" + String(temp1) + "&b=" + String(gas2) +"&c=Y&d=N";
  send2server ();
  msg = p +"HUMIDITY%20Alert%20PLEASE%20CHECK";
  //sendmsg ();
  delay(2000);
}
else if ((sound > 1100)&&(sound < 4000))
{
  lcd.clear();
  lcdstring(0,0,"SOUND ALERT");
  lcdstring(0,1,"PLEASE CHECK....");
  delay(20);
 beep ();
 iot  = q + "a=" + String(temp1) + "&b=" + String(gas2) +"&c=N&d=Y";
  send2server ();
  msg = p +"SOUND%20Alert%20PLEASE%20CHECK";
//  sendmsg ();
  delay(2000);
}

else
{
  lcd.clear();
  lcdstring(0,0,"T: "+String(temp1));
  lcdstring(8,0,"G: "+ String(gas1));
  lcdstring(0,1,"S: 0");
  lcdstring(8,1,"H: 0");
  delay(10);
  iot  = q + "a=" + String(temp1) + "&b=" + String(gas2) +"&c=N&d=N";
  send2server ();
}
*/
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
