#include <WiFi.h>
#include <HTTPClient.h>
#include <LiquidCrystal.h>
#include<stdlib.h>
#include <String.h>

LiquidCrystal lcd (15,2,0,4,16,17);

#define irp 5
#define irb 18
#define buzzer 19

#define button1 34
#define button2 35
#define button3 32
#define button4 33

#define gled 25
#define rled 26

// WiFi parameters to be configured
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig

unsigned int i = 0;
volatile int count = 0;
char pass[5] = "\0";
char pass1[5] = "1111";

unsigned int pin = 0;

String m = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=8790544557&from=MYDREM&message=";

//String m = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=8790544557&from=MYDREM&message=";
String msg = "\0";
String q = "http://projectsiot.xyz/IoTProjects/LetterBox/letterupload.php?a=";
String iot = "\0";
unsigned int no = 0;
/*
String otp[10]  ={"1234","2423","3122",
      "2341","1224","1224",
      "3431","1423","4321",
      "4342"  };
      */
  char otp[10][5]  ={"1234","2423","3122",
      "2341","1224","1224",
      "3431","1423","4321",
      "4342"  };
 

void beep ()
{
 digitalWrite(buzzer,HIGH); delay(1000);
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
        lcd.print("  INTELLIGENT  ");
        lcd.setCursor( 2,1);
         lcd.print("  LETTER BOX   ");
         delay(2000);


pinMode(irp, INPUT);
pinMode(irb, INPUT);

pinMode(button1,INPUT);
pinMode(button2,INPUT);
pinMode(button3,INPUT);
pinMode(button4,INPUT);

pinMode(rled,OUTPUT);
pinMode(gled,OUTPUT);

pinMode(buzzer,OUTPUT);

//attachInterrupt (irb,pinisr,RISING);

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

digitalWrite(rled,LOW);
digitalWrite(gled,LOW);
 



if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   // http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=8790544557&from=MYDREM&message=RJANED;LKSDF"); //Specify request destination

  http.begin("http://projectsiot.xyz/IoTProjects/LetterBox/letterupload.php?a=U&b=0&c=0");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}
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

  
//no = random(11);
 no=rand()%10;

if (digitalRead(irb) == HIGH)
{
  count++;
  Serial.print("letter count = "); Serial.println(count);
   iot = q + String(count) ;
send2server ();
}

//pin = toInt();
//Serial.println(pin);

else if (digitalRead(irp) == HIGH)
{
  //msg = m + "Your%20Intelligent%20Letter%20Box%20OTP%20IS" + otp[no];
 msg = m+otp[no];

//pin = otp[no].toInt();
Serial.print("pin = "); Serial.println(pin);
 
 // sendmsg ();
//==========================================================
Serial.println("sending message-----------");

 Serial.print("msg = "); Serial.println(msg);
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
    msg = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=8790544557&from=MYDREM&message=";
msg += otp[no];
  http.begin(msg);

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}
//=========================================================
  
  lcd.clear ();
  lcdstring (0,0,"PLEASE ENTER OTP");
  lcdstring (0,1,"SENT TO**********");
  delay(2000);
  
 Serial.println("in while loop");
 
  lcd.clear ();
  lcdstring (0,0,"    PASSWORD    ");

while(i<4)
{
  if (digitalRead(button1) == HIGH)
  {
    pass[i]='1';
    lcd.setCursor(i,1);
    lcd.print(pass[i]);
    i++;
    delay(100);
    while(digitalRead(button1)==HIGH);
  }
  else if (digitalRead(button2) == HIGH)
  {
    pass[i]='2';
    lcd.setCursor(i,1);
    lcd.print(pass[i]);
    i++;
    delay(100);
    while(digitalRead(button2)==HIGH);
  }
   else if (digitalRead(button3) == HIGH)
  {
    pass[i]='3';
    lcd.setCursor(i,1);
    lcd.print(pass[i]);
    i++;
    delay(100);
    while(digitalRead(button3)==HIGH);
  }
  else if (digitalRead(button4) == HIGH)
  {
    pass[i]='4';
    lcd.setCursor(i,1);
    lcd.print('4');
    i++;
    delay(100);
    while(digitalRead(button4)==HIGH);
  } 
 
}
pass[4] = '\0';
Serial.print(F("enterred password = ")); Serial.println(pass);
i = 0;

   if((strcmp(pass,otp[no])==0)||(strcmp(pass,pass1)==0))
  
  {
    count = 0;
   digitalWrite(rled,LOW);
   digitalWrite(gled,HIGH);
    lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("PASSWORD MATCHED");
        lcd.setCursor(0,1);
        lcd.print(">>-ACCESSED-->>>");
        Serial.print("Pwd MATCHED :\n");
 msg = m + "Your%20Intelligent%20Letter%20Box%20ACCESS%20GRANTED";
//  sendmsg ();
//==========================================================
Serial.println("sending message-----------");

 Serial.print("msg = "); Serial.println(msg);
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
    msg = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=8790544557&from=MYDREM&message=";
msg += "ACCESS%20GRANTED";
  http.begin(msg);

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}
//=========================================================


  iot = q + String(count) + "&b=" + 'Y';
send2server ();

        
        delay(1500);    
  }
  else
  {
    digitalWrite(gled,LOW);
   digitalWrite(rled,HIGH);
    lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("PSWD NOT MATCHED");
        lcd.setCursor(0,1);
        lcd.print("PLEASE TRY AGAIN");
        Serial.print("Pwd NOT MATCHED :\n");
beep ();

//==========================================================
Serial.println("sending message-----------");

 Serial.print("msg = "); Serial.println(msg);
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
    msg = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=8790544557&from=MYDREM&message=";
msg += "ACCESS%20DENIED";
  http.begin(msg);

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}
//=========================================================


   iot = q + String(count) + "&b=" + 'N';
send2server ();
        
        delay(1500); 
  }

}// if irp detected
else
{
  lcd.clear ();
  lcd.setCursor (0,0);
  lcd.print("LETTER COUNT= ");
  lcd.setCursor (14,0);
  lcd.print(count);
  delay(500);
  
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
