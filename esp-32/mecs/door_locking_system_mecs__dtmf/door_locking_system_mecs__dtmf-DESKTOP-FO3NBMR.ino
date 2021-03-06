// https://thingspeak.com/channels/730868

#include <WiFi.h>
#include <HTTPClient.h>
#include <LiquidCrystal.h>
#include <stdlib.h>
#include <String.h>

LiquidCrystal lcd (15,2,4,16,17,5);


#define fire 18
#define buzzer 19

#define button1 34
#define button2 35
#define button3 32
#define button4 33

#define en 25
#define d1 26
#define d2 27
#define d3 14
#define d4 12

#define m11 22
#define m12 23

// WiFi parameters to be configured
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig

char pass[5] = "\0";
char pass1[5] = "1234";
char pass2[5] = "4321";

int i = 0;

String m = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9652048046&from=MYDREM&message=";
String msg = "\0";
String q = "http://api.thingspeak.com/update?api_key=XDR4H783C68DNKC0";
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
        lcd.print("  DOOR LOCKING  ");
        lcd.setCursor( 2,1);
         lcd.print("     SYSTEM     ");
         delay(2000);

pinMode(en, INPUT);
pinMode(d1, INPUT);
pinMode(d2, INPUT);
pinMode(d3, INPUT);
pinMode(d4, INPUT);

pinMode(button1,INPUT);
pinMode(button2,INPUT);
pinMode(button3,INPUT);
pinMode(button4,INPUT);

pinMode(fire,INPUT);
pinMode(buzzer,OUTPUT);

pinMode(m11,OUTPUT);
pinMode(m12,OUTPUT);


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




/*
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=8790544557&from=MYDREM&message=KIT%20STARTED"); //Specify request destination

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
  if (digitalRead(en)==HIGH)
  {
    if((digitalRead(d1)==HIGH)&&(digitalRead(d2)==HIGH)&&(digitalRead(d3)==LOW))
    {
      Serial.println("dtmf -- BUTTON 3");
      pass[i]='3';
    lcd.setCursor(i,1);
    lcd.print(pass[i]);
    i++;
    delay(1000);
    while (digitalRead(en)==HIGH);
    }

    else if((digitalRead(d1)==HIGH)&&(digitalRead(d2)==LOW)&&(digitalRead(d3)==LOW)) 
    {
      Serial.println("dtmf -- BUTTON 1");
      pass[i]='1';
    lcd.setCursor(i,1);
    lcd.print(pass[i]);
    i++;
    delay(1000);
    while (digitalRead(en)==HIGH);
    }

    else if((digitalRead(d1)==LOW)&&(digitalRead(d2)==HIGH)&&(digitalRead(d3)==LOW)) 
    {
      Serial.println("dtmf -- BUTTON 2");
      pass[i]='2';
    lcd.setCursor(i,1);
    lcd.print(pass[i]);
    i++;
    delay(1000);
    while (digitalRead(en)==HIGH);
    }

    else if((digitalRead(d1)==LOW)&&(digitalRead(d2)==LOW)&&(digitalRead(d3)==HIGH)) 
    {
      Serial.println("dtmf -- BUTTON 4");
      pass[i]='4';
    lcd.setCursor(i,1);
    lcd.print(pass[i]);
    i++;
    delay(1000);
    while (digitalRead(en)==HIGH);
    } 
    }//en of dtmf
  
  /////////////////////////////////////////////////////
  else if (digitalRead(button1) == HIGH)
  {
      Serial.println("BUTTON --1");
    pass[i]='1';
    lcd.setCursor(i,1);
    lcd.print(pass[i]);
    i++;
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
    delay(100);
    while(digitalRead(button4)==HIGH);
  } 
  //////////////////////////////////////////////////
 else if (digitalRead(fire)==HIGH)
 {
  Serial.println("fire occured");
  lcdstring (0,0,"FIRE ALERT        ");
  lcdstring (0,1,"PLEASE CHECK         ");
  delay(20);
  beep ();
  iot = q + "&field3=" + "100";
send2server ();
  delay(3000);
  lcd.clear();
 }
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
  
  iot = q + "&field1=" + "100";
send2server ();

msg = m + "PASSWORD%20MATCHED%0ADOOR%20OPEN";
sendmsg ();

  lcdstring (0,0,"DOOR OPENING");
  lcdstring (0,1,"......................");
  delay(200);

  digitalWrite(m11,HIGH);
  digitalWrite(m12,LOW);
  delay(2000);
  digitalWrite(m11,LOW);
  digitalWrite(m12,LOW);
  lcdstring (0,0,"DOOR -- OPEN    ");
  lcdstring (0,1,"......................");
  delay(200);    
  }
  else    if(strcmp(pass,pass2)==0)  
  {    
    Serial.println("pasworddd  matched222.....");
  lcdstring (0,0,"PASSWORD MATCHED     ");
  lcdstring (0,1,"......................");
  delay(2000);


  iot = q + "&field1=" + "0";
send2server ();

msg = m + "PASSWORD%20MATCHED%0ADOOR%20CLOSE";
sendmsg ();

  lcdstring (0,0,"DOOR CLOSING");
  lcdstring (0,1,"......................");
  delay(200);

  digitalWrite(m11,LOW);
  digitalWrite(m12,HIGH);
  delay(2000);
  digitalWrite(m11,LOW);
  digitalWrite(m12,LOW);
  lcdstring (0,0,"DOOR -- CLOSE    ");
  lcdstring (0,1,"......................");
  delay(200);    
  }
  else
  {
    Serial.println("wrong pasworddd");
    beep ();
  iot = q + "&field2=" + "100";
send2server ();

    msg = m + "PASSWORD%20NOT%20MATCHED%0ATRY%20AGAIN";
sendmsg ();
  lcdstring (0,0,"WRONG PASSWORD      ");
  lcdstring (0,1,"TRY AGAIN             ");
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
 
delay(500);
}
}
void lcdstring(int a,int b, String data1)
{
  lcd.setCursor(a,b);
  lcd.print(data1);
}
