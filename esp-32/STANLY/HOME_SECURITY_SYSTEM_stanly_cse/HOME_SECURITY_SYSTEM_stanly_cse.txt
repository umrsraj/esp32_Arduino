// https://thingspeak.com/channels/730868

#include <WiFi.h>
#include <HTTPClient.h>
#include <LiquidCrystal.h>
#include <stdlib.h>
#include <String.h>

LiquidCrystal lcd (15,2,4,16,17,5);


#define fire 18
#define buzzer 23
#define pir 19
#define relay 22
#define vib 21

#define button1 34
#define button2 35
#define button3 32
#define button4 33

// WiFi parameters to be configured
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig

char pass[5] = "\0";
char pass1[5] = "1234";
char pass2[5] = "4321";

int i = 0;

int flag = 0;

String F = "N";
String P = "N";
String V = "N";

String m = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9912752388&from=MYDREM&message=";
String msg = "\0";
String q = "http://projectsiot.xyz/IoTProjects/SecuritySystem/upload.php?a=";
String iot = "\0";
unsigned int no = 0;

void beep ()
{
 digitalWrite(buzzer,HIGH); delay(1200);
 digitalWrite(buzzer,LOW); delay(100);  
}
      
void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
  Serial.print("Bezig met verbinden");
  WiFi.begin(ssid, password); // Connect to WiFi
 lcd.begin(16,2);
 
lcd.clear();
lcd.setCursor(0,0);
        lcd.print("   HOME SECURITY     ");
        lcd.setCursor( 2,1);
         lcd.print("     SYSTEM            ");
         delay(2000);

pinMode(fire, INPUT);
pinMode(pir, INPUT);
pinMode(vib,INPUT);
pinMode(relay, OUTPUT);
pinMode(buzzer, OUTPUT);

pinMode(button1,INPUT);
pinMode(button2,INPUT);
pinMode(button3,INPUT);
pinMode(button4,INPUT);


// while wifi not connected yet, print '.'
  // then after it connected, get out of the loop
  while (WiFi.status() != WL_CONNECTED) {

     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("CONNCETING TO    ");
     lcd.setCursor(0,1);
     lcd.print(ssid);
     delay(500);
     Serial.print(".");
  }
  lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("WI-FI CONNECTED");
     lcd.setCursor(0,1);
     lcd.print("................");
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

 lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("SERVER INIT");
     lcd.setCursor(0,1);
     lcd.print("PLEASE WAIT");
     delay(2000);



if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   http.begin("http://projectsiot.xyz/IoTProjects/SecuritySystem/upload.php?a=U");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}


 lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("SERVER INIT");
     lcd.setCursor(0,1);
     lcd.print("DONE...............");
     delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:


  
  lcd.clear ();
  lcdstring (0,0,"PLEASE ENTR PSWD");
  lcdstring (0,1,"****************");
  delay(2500);
 
  lcd.clear ();
  lcdstring (0,0,"    PASSWORD    ");

Serial.println("in password while loop");

while(i<4)
{

 if (digitalRead(fire)==HIGH)
 {
  F = "Y";
  Serial.println("fire occured");
  lcdstring (0,0,"FIRE ALERT        ");
  lcdstring (0,1,"PLEASE CHECK         ");
  delay(20);
  beep ();
  delay(200);
 digitalWrite(relay,LOW);
 delay(200);
  iot = q + F + "&b=" + P + "&c=" + V;
send2server ();
  delay(3000);
  lcd.clear(); 
  lcdstring (0,0,"    PASSWORD    ");
 }
 else
 {
  
  F = "N";
 }
 if (flag == 1)
 {
 if (digitalRead(pir)==HIGH)
 {
  
  P = "Y";
  Serial.println("Intruder alert");
  lcdstring (0,0,"INTRUDER ALERT        ");
  lcdstring (0,1,"PLEASE CHECK         ");
  delay(20);
  beep ();
  delay(200);
 digitalWrite(relay,LOW);
 delay(200);
  iot = q + F + "&b=" + P + "&c=" + V;
send2server ();
  delay(3000);
  lcd.clear(); 
  lcdstring (0,0,"    PASSWORD    ");
 }
 else
 {
  
  P = "N";
 }
 }
 else
 {
  P = "N";
 }
 
   if (digitalRead(vib)==LOW)
 {
  V="Y";
  Serial.println("vibration alert");
  lcdstring (0,0,"VIBRATION ALERT        ");
  lcdstring (0,1,"PLEASE CHECK         ");
  delay(20);
  beep ();
  delay(200);
 digitalWrite(relay,HIGH);
 delay(200);
  iot = q + F + "&b=" + P + "&c=" + V;
send2server ();
  delay(3000);
  lcd.clear(); 
  lcdstring (0,0,"    PASSWORD    ");
 }
 else
 {
  
  V="N";
 }
  
  iot = q + F + "&b=" + P + "&c=" + V;
send2server ();

 if (digitalRead(button1) == HIGH)
  {
      Serial.println("BUTTON --1");
    pass[i]='1';
    lcd.setCursor(i,1);
    lcd.print(pass[i]);
    i++;
  delay(200);
 digitalWrite(relay,LOW);
 delay(200);
    delay(100);
    while(digitalRead(button1)==HIGH);
  }
  else if (digitalRead(button2) == HIGH)
  {
      Serial.println("BUTTON --2");
    pass[i]='2';
    lcd.setCursor(i,1);
    lcd.print(pass[i]);
    i++;
  delay(200);
 digitalWrite(relay,LOW);
 delay(200);
    delay(100);
    while(digitalRead(button2)==HIGH);
  }
   else if (digitalRead(button3) == HIGH)
  {
      Serial.println("BUTTON --3");
    pass[i]='3';
    lcd.setCursor(i,1);
    lcd.print(pass[i]);
    i++;
  delay(200);
 digitalWrite(relay,LOW);
 delay(200);
    delay(100);
    while(digitalRead(button3)==HIGH);
  }
  else if (digitalRead(button4) == HIGH)
  {
      Serial.println("BUTTON --4");
    pass[i]='4';
    lcd.setCursor(i,1);
    lcd.print('4');
    i++;
  delay(200);
 digitalWrite(relay,LOW);
 delay(200);
    delay(100);
    while(digitalRead(button4)==HIGH);
  } 
  //////////////////////////////////////////////////

}//otp loop

pass[4] = '\0';
Serial.print(F("enterred password = ")); Serial.println(pass);
i = 0;

   if(strcmp(pass,pass1)==0)  
  {    
    Serial.println("pasworddd  matched.....");
  lcdstring (0,0,"PASSWORD MATCHED     ");
  lcdstring (0,1,"......................");
  delay(2000);


msg = m + "PASSWORD%20MATCHED%0APIR%20DEACTIVATED";
sendmsg ();

  lcdstring (0,0,"PIR DEACTIVATED     ");
  lcdstring (0,1,"......................");
  delay(2000);
flag = 0;
 }
 else    if(strcmp(pass,pass2)==0)  
  {    
    Serial.println("pasworddd  matched.....");
  lcdstring (0,0,"PASSWORD MATCHED     ");
  lcdstring (0,1,"......................");
  delay(2000);

msg = m + "PASSWORD%20MATCHED%0APIR%20ACTIVATED";
sendmsg ();

  lcdstring (0,0,"PIR ACTIVATED     ");
  lcdstring (0,1,"......................");
  delay(2000);
flag = 1;
  }
  else
  {
    Serial.println("wrong pasworddd");
  lcdstring (0,0,"WRONG PASSWORD     ");
  lcdstring (0,1,"TRY AGAIN           ");
    beep ();
 // iot = q + "&field2=" + "100";
//send2server ();

  msg = m + "PASSWORD%20NOT%20MATCHED%0ATRY%20AGAIN";
sendmsg ();
 delay(2000);    
}
 


}//loop


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
 
delay(50);
}
}
void lcdstring(int a,int b, String data1)
{
  lcd.setCursor(a,b);
  lcd.print(data1);
}
