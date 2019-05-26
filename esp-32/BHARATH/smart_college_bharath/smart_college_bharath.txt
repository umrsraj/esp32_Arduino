#include <WiFi.h>
#include <HTTPClient.h>
#include <LiquidCrystal.h>
#include <String.h>
 

LiquidCrystal lcd (15,2,4,16,17,5);

#define inir 18
#define outir 19
#define gasPin 34
#define fire 22
#define vib 23
#define buzzer 35

int in=0,out=0,tot=0;

float temp1=0.0;
unsigned temp2 = 0;
int gas  = 0;
String F = "N";
String V = "N";
String g = "N";

// WiFi parameters to be configured
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig 

String q = "http://projectsiot.xyz/IoTProjects/SmartCollege/upload.php?a=";
String iot = "\0";
String m = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydream123&to=9493206867&from=MYDREM&message=";
String msg = "\0";


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
        lcd.print("SMART COLLEGE        ");
        lcd.setCursor( 2,1);
         lcd.print("               ");
         delay(2000);

#define inir 18
#define outir 19
#define gasPin 34
#define fire 22
#define vib 23
#define buzzer 35

         
          pinMode(gasPin,INPUT);
          pinMode(inir,INPUT);
         pinMode(outir,INPUT);
          pinMode(fire,INPUT);
          pinMode(vib,INPUT);
          pinMode(buzzer,OUTPUT);

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

  http.begin("http://projectsiot.xyz/IoTProjects/SmartCollege/upload.php?a=U&b=N&c=N&d=N&e=N");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}
lcd.clear ();


     lcdstring(0,0,"I:"+String(in));
  lcdstring(5,0,"O:"+String(out));
  lcdstring(10,0,"T:"+String(tot));
  lcdstring(0,1,"G:"+String(g));
  lcdstring(5,1,"F:"+String(F));
  lcdstring(10,1,"V:"+String(V));
delay(200);

}
 
void loop() {

g = "N";
F = "N";
V = "N";

gas = analogRead(gasPin);
Serial.println("gas = "+String(gas));
if (gas > 3000)
{
  Serial.println("gas alert");
  g = "Y";
     lcdstring(0,0,"I:"+String(in));
  lcdstring(5,0,"O:"+String(out));
  lcdstring(10,0,"T:"+String(tot));
  lcdstring(0,1,"G:"+String(g));
  lcdstring(5,1,"F:"+String(F));
  lcdstring(10,1,"V:"+String(V));
  beep ();
}
else
{
  g = "N";
}

if (digitalRead(inir)==HIGH)
{
   Serial.println("in count = "+String(in));
    in++;
    tot = in - out ;

     lcdstring(0,0,"I:"+String(in));
  lcdstring(5,0,"O:"+String(out));
  lcdstring(10,0,"T:"+String(tot));
  lcdstring(0,1,"G:"+String(g));
  lcdstring(5,1,"F:"+String(F));
  lcdstring(10,1,"V:"+String(V));
  
      if (tot> 10)
    {
      beep ();
    }
  iot = q  + String(tot) + "&b=" + V + "&c=" + F + "&d=" + g;

        Serial.println(iot);
        send2server ();

    while(digitalRead(inir)==HIGH);
}
else if (digitalRead(outir)==HIGH)
{
    Serial.println("out count = "+String(in));
    out++;
    
    tot = in - out ;

if (tot < 0 )
{
  tot = 0;
}
    
      lcdstring(0,0,"I:"+String(in));
  lcdstring(5,0,"O:"+String(out));
  lcdstring(10,0,"T:"+String(tot));
  lcdstring(0,1,"G:"+String(g));
  lcdstring(5,1,"F:"+String(F));
  lcdstring(10,1,"V:"+String(V));
  
  iot = q  + String(tot) + "&b=" + V + "&c=" + F + "&d=" + g;

        Serial.println(iot);
        send2server ();

    while(digitalRead(outir)==HIGH);
}
if (digitalRead(fire)==HIGH)
{
  F = "Y";
      lcdstring(0,0,"I:"+String(in));
  lcdstring(5,0,"O:"+String(out));
  lcdstring(10,0,"T:"+String(tot));
  lcdstring(0,1,"G:"+String(g));
  lcdstring(5,1,"F:"+String(F));
  lcdstring(10,1,"V:"+String(V));  
  beep ();
}
else
{
  F = "N";
}
if (digitalRead(vib)==HIGH)
{
  V = "Y";
      lcdstring(0,0,"I:"+String(in));
  lcdstring(5,0,"O:"+String(out));
  lcdstring(10,0,"T:"+String(tot));
  lcdstring(0,1,"G:"+String(g));
  lcdstring(5,1,"F:"+String(F));
  lcdstring(10,1,"V:"+String(V));
  beep ();
}
else
{
  V = "N";
}

  iot = q  + String(tot) + "&b=" + V + "&c=" + F + "&d=" + g;

        Serial.println(iot);
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
 
delay(10);
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
