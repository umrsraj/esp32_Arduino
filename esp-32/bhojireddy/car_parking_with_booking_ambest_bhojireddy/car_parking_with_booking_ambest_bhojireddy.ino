

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include <LiquidCrystal.h>
#include <String.h>

// WiFi parameters to be configured
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig
String a1 = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9652490222&from=MYDREM&message=";
String a2 = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9652490222&from=MYDREM&message=";
String a3 = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9652490222&from=MYDREM&message=";
String a4 = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9652490222&from=MYDREM&message=";
String a5 = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9652490222&from=MYDREM&message=";
String msg = "\0";
String r = "http://projectsiot.xyz/IoTProjects/BloodBank/upload.php?bg=R";
String rs = "\0";
String m1 = "\0";


#define bt1 D6
#define bt2 D7
#define bt3 D8
//#define bt4 3
//#define bt5 1


LiquidCrystal lcd (D0,D1,D2,D3,D4,D5);

void setup() {
  Serial.begin(9600);
  Serial.println("power up");

 
lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("BLOOD BANK         ");
  lcd.setCursor( 0, 1);
  lcd.print("                  ");
  delay(2500);

pinMode(bt1,INPUT);
pinMode(bt2,INPUT);
pinMode(bt3,INPUT);
//pinMode(bt4,INPUT);
//pinMode(bt5,INPUT);
  
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


Serial.print("A = "); Serial.println("http://projectsiot.xyz/IoTProjects/BloodBank/update.php");


if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   
  http.begin("http://projectsiot.xyz/IoTProjects/BloodBank/update.php");

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
lcd.print("O+:");
lcd.setCursor(5,0);
lcd.print("B+:");
lcd.setCursor(10,0);
lcd.print("B-:");

lcd.setCursor(0,1);
lcd.print("O-:");
lcd.setCursor(5,1);
lcd.print("AB+:");


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
}


void loop()
{

if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
 http.begin("http://projectsiot.xyz/IoTProjects/BloodBank/update.php");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload


Serial.println(payload[payload.indexOf("sts0")+7]);

char vig = payload[payload.indexOf("sts0")+7];

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
if (vig == '1')
{
  Serial.println("O+ REQUESTED");

lcd.setCursor(3,0);
lcd.print("1");  
delay(100);
}
else if (vig == '2')
{
  Serial.println("B+ REQUESTED");

lcd.setCursor(8,0);
lcd.print("1");  
delay(100);
}
else if (vig == '3')
{
  Serial.println("B- REQUESTED");

lcd.setCursor(13,0);
lcd.print("1");  
delay(100);
}
else if (vig == '4')
{
  Serial.println("O- REQUESTED");

lcd.setCursor(3,1);
lcd.print("1");  
delay(100);
}
else if (vig == '5')
{
  Serial.println("AB+ REQUESTED");

lcd.setCursor(9,1);
lcd.print("1");  
delay(100);
}

if (digitalRead(bt1)==LOW)
{
  Serial.println("button-1 pressed");
  msg = a1 + "O+%20REQUESTED";
  sendsms (msg);
  lcd.setCursor(3,0);
lcd.print("0");
send2server(r);
}
else if (digitalRead(bt2)==LOW)
{
  Serial.println("button-2 pressed");
  msg = a2 + "B+%20REQUESTED";
  sendsms (msg);
  lcd.setCursor(8,0);
lcd.print("0");
send2server(r);
}
else if (digitalRead(bt3)==LOW)
{
  Serial.println("button-3 pressed");
  msg = a3 + "B-%20REQUESTED";
  sendsms (msg);
  lcd.setCursor(13,0);
lcd.print("0");
send2server(r);
}
/*
else if (digitalRead(bt4)==LOW)
{
  Serial.println("button-4 pressed");
  msg = a4 + "O-%20REQUESTED";
  sendsms (msg);
  lcd.setCursor(3,1);
lcd.print("0");
send2server(r);
}
else if (digitalRead(bt5)==LOW)
{
  Serial.println("button-5 pressed");
  msg = a5 + "O-%20REQUESTED";
  sendsms (msg);
  lcd.setCursor(9,1);
lcd.print("0");
send2server(r);
}
*/
      
    }
    http.end(); //Close connection
 
delay(500);
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
