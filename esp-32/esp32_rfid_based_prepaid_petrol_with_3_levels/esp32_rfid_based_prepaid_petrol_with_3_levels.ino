#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <HTTPClient.h>
#include <LiquidCrystal.h>
#include <String.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "f9d4b43dbced43169cc5d9d36f65326c";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "AMBEST Technologies";
char pass[] = "AmBeSt@@321";

 WidgetLCD lcd1(V0);

LiquidCrystal lcd (15,2,4,16,17,5);

#define swI 18
#define swD 19 
#define swS 21
#define relay 22
#define buzzer 23
#define lv1 34
#define lv2 35
#define lv3 32

int t = 0;
int level = 0;

int i=0,j=0,k=0;
int count=0;

int count1 = 0;                                          // count = 0
char input[12];

 int amount = 500;
 int amount1 = 500;

String msg ;

void beep ()
{
  digitalWrite(buzzer,HIGH);
  delay(1000);
  digitalWrite(buzzer,LOW);
  delay(100);
}void alarmSet(void);

 
void setup(void) { 
  Serial.begin(9600);
  Serial.println("power up");
 lcd.begin(16,2);
 
lcd.clear();
lcd.setCursor(0,0);
        lcd.print("RFID BSD PREPAID");
        lcd.setCursor( 2,1);
         lcd.print("CARD FOR PETROL");
         delay(2000);

  pinMode(swI,INPUT);
  pinMode(swD,INPUT);
  pinMode(swS,INPUT);

 pinMode(buzzer,OUTPUT);
 pinMode(relay,OUTPUT); 
 pinMode(lv1,INPUT); 
 pinMode(lv2,INPUT); 
 pinMode(lv3,INPUT);

  Blynk.begin(auth, ssid, pass);

Serial.println("sending welcome message............");
 
 if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
 
   http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9652490222&from=MYDREM&message=WELCOME%20TO%20PROJECT"); //Specify request destination

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
  }
    http.end(); //Close connection
 
delay(500);
 lcd1.clear();
    lcd1.print(0,0,"RFID BSD PREPAID");
    lcd1.print(0,1,"CARD FOR PETROL");
    delay(1000);
}
Blynk.notify("KIT STARTED"); delay(1000);
}
 
void loop() {

 Blynk.run();
 
lcd.setCursor(0,0);
    lcd.print("plz show card         ");
lcd.setCursor(0,1);
    lcd.print("                      ");

     lcd1.clear();
    lcd1.print(0,0,"PLEASE SHOW CARD");
    lcd1.print(0,1,".................");
    delay(1000);

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
//////////////////////////////
if (input[10]=='0')
{
  
alarmSet() ;

  input[10]='\0';
amount = amount - (j*10) ;
//amount = amount - (10) ;

if (amount <(-1))
{
  digitalWrite(relay,LOW);
   lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("UR BALENCE IS 0");
       lcd.setCursor(0,1);
    lcd.print(" PLZ RECHARGE  ");
    delay(2000);

    lcd1.clear();
    lcd1.print(0,0,"UR BALENCE IS 0");
    lcd1.print(0,1," PLZ RECHARGE  ");
    delay(1000);
}

else if (amount >(-1))
{

    if (amount <101)
{

    lcd.setCursor(4,1);
    lcd.print("LOW BALENCE");
    
    lcd1.clear();
    lcd1.print(0,0,"LOW Balence");
    lcd1.print(0,1,"             ");
    delay(1000);
      
}  
/*
A = "http://projectsiot.xyz/IoTProjects/PrepaidCardPetrol/petrolcard.php?a=A&b=";
A += String(amount);
A += "&c=";
A += String(j);
A += "&d=";
A += String(j*10);
*/
tank_level ();
Blynk.virtualWrite(V1,String(amount)); delay(100);
Blynk.virtualWrite(V2,j); delay(100);
Blynk.virtualWrite(V3,(j*10)); delay(100);
Blynk.virtualWrite(V4,level); delay(100);

Serial.println("sending message-----------");

msg = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9652490222&from=MYDREM&message=";
msg += "CARD1%20DETECTED%10DEDUCTED%20AMOUNT=";
msg += String(j*10);
msg += "%10REMAINING%20BALANCE=";
msg += String(amount);

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



  lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("  CARD1 MATCHED   ");  
    lcd.setCursor(0,1);
    lcd.print("RE BAL:");
       lcd.setCursor(8,1);
    lcd.print(amount);

 lcd1.clear();
    lcd1.print(0,0,"  CARD1 MATCHED   ");
    lcd1.print(0,1,"RE BAL:");
    lcd1.print(8,1,String(amount));
    delay(1000);
    
digitalWrite (relay,HIGH);
//////////////////////////////
t = 0;
while (t<=j)
{
  if(digitalRead(lv3)==LOW)
  {
    beep ();
  break;
  }
  Serial.println(digitalRead(lv3));
Serial.print("t = "); Serial.println(t);

t++;
Serial.println("relay -- on");
delay(500);
}    
digitalWrite (relay,LOW);
delay(5000);
//////////////////////
   
tank_level ();
Blynk.virtualWrite(V1,amount); delay(100);
Blynk.virtualWrite(V2,j); delay(100);
Blynk.virtualWrite(V3,(j*10)); delay(100);
Blynk.virtualWrite(V4,level); delay(100);

}

} // 1st card
else if (input[10]=='B')
{
  
alarmSet() ;

  input[10]='\0';
amount1 = amount1 - (j*10) ;
//amount = amount - (10) ;

if (amount1 <(-1))
{
  digitalWrite(relay,LOW);
   lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("UR BALENCE IS 0");
       lcd.setCursor(0,1);
    lcd.print(" PLZ RECHARGE  ");
    delay(2000);
    
     lcd1.clear();
    lcd1.print(0,0,"UR BALENCE IS 0");
    lcd1.print(0,1," PLZ RECHARGE  ");
    delay(1000);
}

else if (amount1 >(-1))
{

    if (amount1 <101)
{

    lcd.setCursor(4,1);
    lcd.print("LOW BALENCE");

     lcd1.clear();
    lcd1.print(0,0,"LOW BALENCE");
    lcd1.print(0,1,"                ");
    delay(1000);
      
}  
/*
B = "http://projectsiot.xyz/IoTProjects/PrepaidCardPetrol/petrolcard.php?a=B&b=";
B += String(amount1);
B += "&c=";
B += String(j);
B += "&d=";
B += String(j*10);
*/


tank_level ();
Blynk.virtualWrite(V1,amount1);delay(100);
Blynk.virtualWrite(V2,j);delay(100);
Blynk.virtualWrite(V3,(j*10));delay(100);
Blynk.virtualWrite(V4,level);delay(100);




Serial.println("sending message-----------");

msg = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=7013974146&from=MYDREM&message=";
msg += "CARD2%20DETECTED%10DEDUCTED%20AMOUNT=";
msg += String(j*10);
msg += "%10REMAINING%20BALANCE=";
msg += String(amount1);

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

  lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("  CARD2 MATCHED   ");  
    lcd.setCursor(0,1);
    lcd.print("RE BAL:");
       lcd.setCursor(8,1);
    lcd.print(amount1);

     lcd1.clear();
    lcd1.print(0,0,"  CARD2 MATCHED   ");
    lcd1.print(0,1,"RE BAL:");
    lcd1.print(8,1,String(amount1));
    delay(1000);
    
    
digitalWrite (relay,HIGH);
//////////////////////////////
t = 0;
while (t<=j)
{
  if(digitalRead(lv3)==LOW)
  {
  beep ();
  break;
  
  }
  Serial.println(digitalRead(lv3));
Serial.print("t = "); Serial.println(t);

t++;
Serial.println("relay -- on");
delay(500);
}    
digitalWrite (relay,LOW);
delay(5000);
//////////////////////
   
tank_level ();
Blynk.virtualWrite(V1,amount1);delay(100);
Blynk.virtualWrite(V2,j);delay(100);
Blynk.virtualWrite(V3,(j*10));delay(100);
Blynk.virtualWrite(V4,level);delay(100);
delay(2000);
//////////////////////

    
    
}

} // 2nd card

else
{
   lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("  INVALID CARD  ");
    delay(1600);
    lcd.setCursor(0,1);
    lcd.print("***PLZ CHECK***");
    beep  ();
    delay(700);
}
   }  
 
}
void alarmSet()
{
  
  i = 0;
  j = 0;
  count=0;
  Serial.println("in setting petrol;;;;;;;;;;;;;");
  lcd.clear(); //Use it to clear the LCD Widget
    lcd.setCursor(0,0);
        lcd.print("Pls SET LIMIT FOR");
        lcd.setCursor( 0,1);
         lcd.print(" PETROL IN Ltrs ");
        delay(2000);

while(count<1)   //********************
{  
  //++ INCREMENT
if(digitalRead(swI)==0)
{
i++;
         lcd.clear(); //Use it to clear the LCD Widget
         lcd.setCursor(4,0);
        lcd.print("Ltrs++");
        lcd.setCursor(4, 1);                                           // Set LCD cursor position (column,row) 
         lcd.print(i);
        delay(200);
 }

  //-- DECREMENT
if(digitalRead(swD)==0)
{
i--;
         lcd.clear(); //Use it to clear the LCD Widget
         lcd.setCursor(4,0);
        lcd.print("Ltrs--");
        lcd.setCursor(4, 1);                                           // Set LCD cursor position (column,row) 
            lcd.print(i);
        delay(200);
 }

  //SET H
if(digitalRead(swS)==0)
{
j=i;
count++;
         lcd.clear(); //Use it to clear the LCD Widget
         lcd.setCursor(4,0);
        lcd.print("SET Ltrs :");
        lcd.setCursor(4, 1);                                           // Set LCD cursor position (column,row) 
           lcd.print(j);
        delay(200);
 } 

    //SET M
}//while closed
Serial.print("LITERS --"); Serial.println(j);
delay(2000);
    lcd.clear(); //Use it to clear the LCD Widget
    lcd.setCursor(0,0);
        lcd.print("PETROL SET AT");
        lcd.setCursor( 1,1);
         lcd.print(" Ltrs: ");
           lcd.print(j);
        delay(2000); lcd.clear(); //Use it to clear the LCD Widget

}
//-----------------------------------------------------------------
void tank_level ()
{
  if((digitalRead(lv1) == LOW)&&(digitalRead(lv2) == LOW)&&(digitalRead(lv3) == LOW))
  {
    level = 3;
  }
  else if((digitalRead(lv1) == LOW)&&(digitalRead(lv2) == LOW)&&(digitalRead(lv3) == HIGH))
  {
    level = 2;
  }
  else if((digitalRead(lv1) == LOW)&&(digitalRead(lv2) == HIGH)&&(digitalRead(lv3) == HIGH))
  {
    level = 1;
  }
  else if((digitalRead(lv1) == HIGH)&&(digitalRead(lv2) == HIGH)&&(digitalRead(lv3) == HIGH))
  {
    level = 0;
  }
}
