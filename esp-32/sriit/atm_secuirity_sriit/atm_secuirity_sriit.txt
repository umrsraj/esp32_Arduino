
#include <WiFi.h>
#include <HTTPClient.h>
#include <LiquidCrystal.h>
#include <stdlib.h>
#include <String.h>

LiquidCrystal lcd (15,2,4,16,17,5);


#define vib 32
#define metal 33
#define buzzer 18

#define button1 34
#define button2 35
#define button3 25
#define button4 26

#define m1 22
#define m2 23


// WiFi parameters to be configured
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig

char pass[5] = "\0";
char pass1[5] = "1234";
char pass2[5] = "4321";

int i = 0,iron,vvv;
char v,m;

String R = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=8142624972&from=MYDREM&message=";
String msg = "\0";
String A = "http://projectsiot.xyz/IoTProjects/ATMSecurity/upload.php?a=";
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
        lcd.print("****ATM THEFT***");
        lcd.setCursor( 5,1);
         lcd.print("ALERT");
         delay(2000);

pinMode(button1,INPUT);
pinMode(button2,INPUT);
pinMode(button3,INPUT);
pinMode(button4,INPUT);

pinMode(vib,INPUT);
pinMode(metal,INPUT);
pinMode(buzzer,OUTPUT);

pinMode(m1,OUTPUT);
pinMode(m2,OUTPUT);


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





if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   http.begin("http://projectsiot.xyz/IoTProjects/ATMSecurity/upload.php?a=U"); //Specify request destination

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
  // put your main code here, to run repeatedly:

        analogReadResolution(10);
iron = analogRead(metal);
 int vvv = analogRead(vib);
Serial.println("vib = " +String(vvv));
Serial.println("metal = " +String(iron));
  
  lcd.clear ();
  lcdstring (0,0,"PLEASE ENTR PSWD");
  lcdstring (0,1,"****************");
  delay(2500);
 
  lcd.clear ();
  lcdstring (0,0,"    PASSWORD    ");

Serial.println("in password while loop");

while(i<4)
{
 if (digitalRead(button1) == HIGH)
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
 
}//otp loop

pass[4] = '\0';
Serial.print(F("enterred password = ")); Serial.println(pass);
i = 0;

   if(strcmp(pass,pass1)==0)  
  {
    
msg = R + "PASSWORD%20MATCHED%0ADOOR%20OPEN";
       sendmsg (); 
       
    lcd.setCursor(0,0);
          lcd.print("ATM DOOR UNLOCK");
          
         lcd.setCursor(0,1);
          lcd.print("                 ");
       
      open_door();    
          delay(2500);
            while(1)
            {
    //////////////////
   v='N';
        m='N';
        analogReadResolution(10);
iron = analogRead(metal);
  vvv = analogRead(vib);
Serial.println("vib = " +String(vvv));
Serial.println("metal = " +String(iron));


        
      if(vvv < 200 )
       {   Serial.println("THEFT ALERT");
              
msg = R + "THEFT%20DETECTED";
       sendmsg ();
        
       lcd.setCursor(0,0);
       lcd.print("ATM MOVEMENT");
v='Y';
   iot = A+m+"&b="+v;

       Serial.println(A+m+"&b="+v);
       send2server ();


       lcd.setCursor(0,1);
       lcd.print("               ");
       delay(1500);
       close_door();
       beep();
       lcd.setCursor(0,1);
       lcd.print("ATM DOOR LOCK  ");delay(1500);
       

       }
 
       else if(iron < 300)
       {   Serial.println("bomb ALERT");
        
msg = R + "METAL%20DETECTED";
       sendmsg ();
       
       lcd.setCursor(0,0);
       lcd.print("METAL DETECTED ");
       m='Y';

   iot = A+m+"&b="+v;

       Serial.println(A+m+"&b="+v);
       send2server ();
       
       lcd.setCursor(0,1);
       lcd.print("               ");
       delay(1500);
       close_door();
       beep();
       lcd.setCursor(0,1);
       lcd.print("ATM DOOR LOCK  ");

       
       delay(1500);
       }
   
       else
       {
        v='N';
        m='N';  
        iot = A+m+"&b="+v;

       Serial.println(A+m+"&b="+v);
       send2server ();
        delay(100);
         
        }



    ////////////////////////
            }
  }
    else
  {
       lcd.setCursor(0,0);
          lcd.print("Enter PWD:       ");
          
         lcd.setCursor(0,1);
          lcd.print("                 ");
            delay(2500);
      i=0;
  }
 delay(1000);    


}//loop

void open_door()
{
 // lcd.setCursor(11,1);
 // lcd.print("O");
  Serial.println("Door Open");
  digitalWrite(m1,LOW);
  digitalWrite(m2,HIGH);
  delay(5000);
//  Serial.println("HALT");
  digitalWrite(m1,LOW);
  digitalWrite(m2,LOW);
  delay(7000);
//  Serial.println("Gate Close");
}

void close_door()
{
    Serial.println("Door Closed");
    digitalWrite(m1,HIGH);
  digitalWrite(m2,LOW);
  delay(5000);
  //lcd.setCursor(11,1);
 // lcd.print("C");
//  Serial.println("HALT");
  digitalWrite(m1,LOW);
  digitalWrite(m2,LOW);

}

void check(void)
{
   v='N';
        m='N';
        analogReadResolution(10);
iron = analogRead(metal);
  vvv = analogRead(vib);
Serial.println("vib = " +String(vvv));
Serial.println("metal = " +String(iron));


        
      if(digitalRead(vib)==LOW)
       {   Serial.println("THEFT ALERT");
              
msg = R + "THEFT%20DETECTED";
       sendmsg ();
        
       lcd.setCursor(0,0);
       lcd.print("ATM MOVEMENT");


        v='Y';
   iot = A+m+"&b="+v;

       Serial.println(A+m+"&b="+v);
       send2server ();
       
       lcd.setCursor(0,1);
       lcd.print("               ");
       delay(1500);
       close_door();
       beep();
       lcd.setCursor(0,1);
       lcd.print("ATM DOOR LOCK  ");delay(1500);
      

       }
 
       else if(iron < 300)
       {   Serial.println("bomb ALERT");
        
msg = R + "METAL%20DETECTED";
       sendmsg ();
       
       lcd.setCursor(0,0);
       lcd.print("METAL DETECTED ");


       m='Y';
   iot = A+m+"&b="+v;

       Serial.println(A+m+"&b="+v);
       send2server ();
       
       lcd.setCursor(0,1);
       lcd.print("               ");
       delay(1500);
       close_door();
       beep();
       lcd.setCursor(0,1);
       lcd.print("ATM DOOR LOCK  ");

       
       delay(1500);
       }
  
       else
       {
        v='N';
        m='N';
        delay(100);
           iot = A+m+"&b="+v;

       Serial.println(A+m+"&b="+v);
       send2server ();
         
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
