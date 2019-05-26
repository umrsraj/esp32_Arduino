#include <WiFi.h>
#include <HTTPClient.h>
#include <LiquidCrystal.h>
#include<stdlib.h>
#include <String.h>

LiquidCrystal lcd (15,2,4,16,17,5);

#define buzzer 14

#define buttonm 18
#define button1 19
#define button2 21
#define button3 13
#define button4 12

#define bt 34

#define m11 22
#define m12 23

// WiFi parameters to be configured
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig

unsigned int i = 0;
volatile int count = 0;
char pass[5] = "\0";
int flag;
unsigned int pin = 0;

String m = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=8790544557&from=MYDREM&message=";

//String m = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=8790544557&from=MYDREM&message=";
String msg = "\0";
String q = "http://projectsiot.xyz/IoTProjects/MedicalBox/upload.php?a=";
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

void forward ()
{
  digitalWrite(m11, HIGH);
  digitalWrite(m12, LOW);
  delay(50);
}
void backward ()
{
  digitalWrite(m12, HIGH);
  digitalWrite(m11, LOW);
  delay(50);
}

void stop_motor ()
{
  digitalWrite(m11, LOW);
  digitalWrite(m12, LOW);
  delay(50);
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
         lcd.print("  MEDICINE BOX   ");
         delay(2000);


pinMode(buttonm,INPUT);
pinMode(button1,INPUT);
pinMode(button2,INPUT);
pinMode(button3,INPUT);
pinMode(button4,INPUT);


pinMode(bt,INPUT);

pinMode(buzzer,OUTPUT);
 pinMode(m11, OUTPUT);
  pinMode(m12, OUTPUT);
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

 



if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   // http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=8790544557&from=MYDREM&message=RJANED;LKSDF"); //Specify request destination

  http.begin("http://projectsiot.xyz/IoTProjects/MedicalBox/upload.php?a=U&b=N&c=N&d=N&e=N");

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

//
// lcd.clear ();
//  lcd.setCursor (0,0);
//  lcd.print("PLEASE SET ALARM        ");
//  lcd.setCursor (0,1);
//  lcd.print("                     ");
//
//while(digitalRead(bt)==HIGH);
//
// lcd.clear ();
//  lcd.setCursor (0,0);
//  lcd.print("ALARM SET DONE       ");
//  lcd.setCursor (0,1);
//  lcd.print("                     ");
//delay(7000);


}

void loop() {
  // put your main code here, to run repeatedly:



  
//no = random(11);
// no=rand()%10;

if (digitalRead(bt)==LOW)
{
  lcd.clear ();
 lcd.setCursor (0,0);
  lcd.print("ALARM SET DONE       ");
  lcd.setCursor (0,1);
 lcd.print("                     ");
delay(7000);

beep ();



}

if (digitalRead(buttonm) == LOW)
{
  
  lcd.clear ();
  lcd.setCursor (0,0);
  lcd.print(" MEDICINE BOX   ");
  lcd.setCursor (0,1);
  lcd.print("    OPEN          ");
  Serial.print("letter count = "); Serial.println(count);
  
  if(flag==1)
  {
    flag=0;
  forward();
  delay(2000);
  stop_motor();
  iot = q +'Y'+ "&b=" + 'N' + "&c=" + 'N' + "&d=" + 'N' + "&e=" + 'N';
  send2server ();
  }       if(digitalRead(button1) == HIGH)
          {
                lcd.clear ();
                lcd.setCursor (0,0);
                lcd.print(" MEDICINE 1    ");
                lcd.setCursor (0,1);
                lcd.print("    TAKEN          ");
                Serial.print("letter count = "); Serial.println(count);
                iot = q +'Y'+ "&b=" + 'Y' + "&c=" + 'N' + "&d=" + 'N' + "&e=" + 'N'; ;
                send2server ();
                       if(digitalRead(button2) == HIGH)
                       {
                      lcd.clear ();
                      lcd.setCursor (0,0);
                      lcd.print(" MEDICINE 2    ");
                      lcd.setCursor (0,1);
                      lcd.print("    TAKEN          ");
                      Serial.print("letter count = "); Serial.println(count);
                      iot = q +'Y'+ "&b=" + 'Y' + "&c=" + 'Y' + "&d=" + 'N' + "&e=" + 'N';
                      send2server ();  
                                  if(digitalRead(button3) == HIGH)
                                 {
                                lcd.clear ();
                                lcd.setCursor (0,0);
                                lcd.print(" MEDICINE 3    ");
                                lcd.setCursor (0,1);
                                lcd.print("    TAKEN          ");
                                Serial.print("letter count = "); Serial.println(count);
                                iot = q +'Y'+ "&b=" + 'Y' + "&c=" + 'Y' + "&d=" + 'Y' + "&e=" + 'N';
                                send2server ();                                                         
                                                 if(digitalRead(button4) == HIGH)
                                                 {
                                                lcd.clear ();
                                                lcd.setCursor (0,0);
                                                lcd.print(" MEDICINE 4   ");
                                                lcd.setCursor (0,1);
                                                lcd.print("    TAKEN          ");
                                                Serial.print("letter count = "); Serial.println(count);
                                                iot = q +'Y'+ "&b=" + 'Y' + "&c=" + 'Y' + "&d=" + 'Y' + "&e=" + 'Y';
                                                send2server (); 
                                                 }//M4
                                                 else
                                                 {
                                                  iot = q +'Y'+ "&b=" + 'Y' + "&c=" + 'Y' + "&d=" + 'Y' + "&e=" + 'N';
                                                send2server (); 
                                                
                                                 }
                                                 
                                 }//M3
                                 
                                else if((digitalRead(button4) == HIGH))
                                {
                                      lcd.clear ();
                                      lcd.setCursor (0,0);
                                      lcd.print(" WRONG MEDICINE     ");
                                      lcd.setCursor (0,1);
                                      lcd.print("                   ");
                                      Serial.print("letter count = "); Serial.println(count);
                                      iot = q +'Y'+ "&b=" + 'Y' + "&c=" + 'Y' + "&d=" + 'N' + "&e=" + 'N'; ;
                                    //  send2server ();
                                      beep();
                                }
                                              
                       }//M2
                       else if((digitalRead(button3) == HIGH)||(digitalRead(button4) == HIGH))
                          {
                                lcd.clear ();
                                lcd.setCursor (0,0);
                                lcd.print(" WRONG MEDICINE     ");
                                lcd.setCursor (0,1);
                                lcd.print("                   ");
                                Serial.print("letter count = "); Serial.println(count);
                                iot = q +'Y'+ "&b=" + 'Y' + "&c=" + 'N' + "&d=" + 'N' + "&e=" + 'N'; ;
                                //send2server ();
                                beep();
                          }
                       
          }//M1
          else if((digitalRead(button2) == HIGH)||(digitalRead(button3) == HIGH)||(digitalRead(button4) == HIGH))
          {
                lcd.clear ();
                lcd.setCursor (0,0);
                lcd.print(" WRONG MEDICINE     ");
                lcd.setCursor (0,1);
                lcd.print("                   ");
                Serial.print("letter count = "); Serial.println(count);
                iot = q +'Y'+ "&b=" + 'N' + "&c=" + 'N' + "&d=" + 'N' + "&e=" + 'N'; ;
               // send2server ();
                beep();
          }
          

}//box
else 
{
  flag=1;
  lcd.clear ();
  lcd.setCursor (0,0);
  lcd.print("MEDICINE BOX   ");
  lcd.setCursor (0,1);
  lcd.print("***SYSTEM***  ");
  delay(500);
  iot = q +'N'+ "&b=" + 'N' + "&c=" + 'N' + "&d=" + 'N' + "&e=" + 'N'; ;
  send2server ();
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
