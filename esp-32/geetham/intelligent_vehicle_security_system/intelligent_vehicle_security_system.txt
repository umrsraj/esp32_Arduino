#include <WiFi.h>
#include <HTTPClient.h>
#include <LiquidCrystal.h>
#include <String.h>
 

LiquidCrystal lcd (15,2,4,16,17,5);

#define ldrPin 34
#define frontir 14
#define backir 27
#define firePin 26
#define led 12
#define buzzer 33
#define vibPin 25
#define relay 32

// WiFi parameters to be configured
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123"; // Hoofdlettergevoelig 

String q = "http://projectsiot.xyz/IoTProjects/VehicleSecurity/uploadstatus.php?a=";
String iot = "\0";


//iot = q + l + "&b=" + fir + "&c=" + bir + "&d=" + f + "&e=" + accident;

char fir = 'N';
char bir = 'N';
char f = 'N';
char accident = 'N';

String A ;
String B ;
String msg ;
char l = '1';
int ldr = 0;

int freq = 5000;
int ledChannel = 0;
int resolution = 8;
int dutyCycle = 0;

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
        lcd.print("  INTELLIGENT   ");
        lcd.setCursor( 2,1);
         lcd.print("VEHICLE SECURITY");
         delay(2000);
         
lcd.clear();
lcd.setCursor(0,0);
        lcd.print("& PROTECTION S/M");
        lcd.setCursor( 2,1);
         lcd.print("   USING IOT    ");
         delay(2000);

          pinMode(ldrPin,INPUT);
          pinMode(frontir,INPUT);
          pinMode(backir,INPUT);
          pinMode(firePin,INPUT);
          pinMode(vibPin,INPUT);
          pinMode(relay,OUTPUT);
          pinMode(buzzer,OUTPUT);
          


            // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(led, ledChannel);
 
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
 
  // Signaalsterkte.
  long rssi = WiFi.RSSI();
  Serial.print("Signaal sterkte (RSSI): ");
  Serial.print(rssi);
  Serial.println(" dBm");
  Serial.println("");

 
  Serial.print("A = "); Serial.println(A);
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   // http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9133457675&from=MYDREM&message=RJANED;LKSDF"); //Specify request destination

  http.begin("http://projectsiot.xyz/IoTProjects/VehicleSecurity/uploadstatus.php?a=U&b=N&c=N&d=N&e=N");

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
   http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9133457675&from=MYDREM&message=WELCOME%20TO%20PROJECT"); //Specify request destination

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

ldr = analogRead(ldrPin);
Serial.println(ldr);
delay(400);

if(ldr > 3000)
{
  Serial.println(F("light on"));
  l = '2';
 ledcWrite(ledChannel, 255); 
}
/*
else if ((ldr > 1000)&&(ldr < 2000))
{
 ledcWrite(ledChannel, 125); 
}
*/
else if (ldr < 3000)
{
  
  Serial.println(F("light off"));
  l = '1';
 ledcWrite(ledChannel, 0); 

}
if(digitalRead(frontir) == 1)
{
  beep ();
  Serial.println(F("front obstacle alert"));
  fir = 'Y';
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" FRONT OBSTACLE ");
  lcd.setCursor(0,1);
  lcd.print(" VEHICLE -- OFF ");
  digitalWrite(relay,LOW);
  
    beep ();

iot = q + l + "&b=" + fir + "&c=" + bir + "&d=" + f + "&e=" + accident;

send2server ();
   msg = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9133457675&from=MYDREM&message=";
msg += "VEHICLE%20FORNT%20OBSTACLE%20DETECTED%0AAT%0A17.550686%2C78.1655632";
  sendmsg ();
  delay(2000);
 
}
else
{
  fir = 'N';
}
if(digitalRead(backir) == 1)
{
  beep ();
  Serial.println(F("back obstacle alert"));
  bir = 'Y';
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" BACK OBSTACLE  ");
  lcd.setCursor(0,1);
  lcd.print(" VEHICLE -- OFF ");
  digitalWrite(relay,LOW);
      beep ();

iot = q + l + "&b=" + fir + "&c=" + bir + "&d=" + f + "&e=" + accident;

send2server ();
     msg = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9133457675&from=MYDREM&message=";
msg += "VEHICLE%20BACK%20OBSTACLE%20DETECTED%0AAT%0A17.550686%2C78.1655632";
  sendmsg ();
  delay(2000);
 
}
else
{
  bir = 'N';
}

if(digitalRead(firePin) == 1)
{
 
  Serial.println(F("fire alert"));
  f = 'Y';
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   FIRE ALERT   ");
  lcd.setCursor(0,1);
  lcd.print(" VEHICLE -- OFF ");
  digitalWrite(relay,LOW);

  beep ();

iot = q + l + "&b=" + fir + "&c=" + bir + "&d=" + f + "&e=" + accident;

send2server ();
  
  
    msg = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9133457675&from=MYDREM&message=";
msg += "VEHICLE%20FIRE%20OBSTACLE%20DETECTED%0AAT%0A17.550686%2C78.1655632";
  sendmsg ();
  delay(2000);
}
else
{
  f = 'N';
}
if(digitalRead(vibPin) == 0)
{
  
  Serial.println(F("ACCIDENT alert"));
  accident = 'Y';
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ACCIDENT OCCURED");
  lcd.setCursor(0,1);
  lcd.print(" VEHICLE -- OFF ");
  digitalWrite(relay,LOW);

    beep ();

iot = q + l + "&b=" + fir + "&c=" + bir + "&d=" + f + "&e=" + accident;

send2server ();

  
    msg = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9133457675&from=MYDREM&message=";
msg += "VEHICLE%20ACCIDENT%20DETECTED%0AAT%0A17.550686%2C78.1655632";
 sendmsg ();
 delay(2000);
}
else
{
  accident = 'N';
}
if ((digitalRead(frontir) == 0)&&(digitalRead(backir)==0)&&(digitalRead(firePin)==0)&&(digitalRead(vibPin)==1))
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("SYSTEM IS NORMAL ");
  lcd.setCursor(0,1);
  lcd.print(" VEHICLE -- ON  ");
  digitalWrite(relay,HIGH);
  delay(200);
}
iot = q + l + "&b=" + fir + "&c=" + bir + "&d=" + f + "&e=" + accident;

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
 
delay(500);
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
