#include <WiFi.h>
#include <HTTPClient.h>
#include <LiquidCrystal.h>
#include <String.h>
 

LiquidCrystal lcd (15,2,4,16,17,5);

#define swI 18
#define swD 19
#define swS 21
#define relay 22
#define buzzer 23
#define level 13

int t = 0;

int i=0,j=0,k=0;
int count=0;

int count1 = 0;                                          // count = 0
char input[12];

 int amount = 500;
 int amount1 = 500;


// WiFi parameters to be configured
const char* ssid = "AMBEST Technologies"; // Hoofdlettergevoelig
const char* password = "AmBeSt@@321"; // Hoofdlettergevoelig
 
//const char* http_site = "http://sms.scubedigi.com/";
//const int http_port = 80;

String A ;
String B ;
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
  Serial.print("Bezig met verbinden");
  WiFi.begin(ssid, password); // Connect to WiFi
 lcd.begin(16,2);
 
lcd.clear();
lcd.setCursor(0,0);
        lcd.print("RFID BSD PREPAID");
        lcd.setCursor( 2,1);
         lcd.print("CARD FOR PETROL");
         delay(1000);

  pinMode(swI,INPUT);
  pinMode(swD,INPUT);
  pinMode(swS,INPUT);

 pinMode(buzzer,OUTPUT);
 pinMode(relay,OUTPUT); 
 pinMode(level,INPUT);
 
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
   // http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9652490222&from=MYDREM&message=RJANED;LKSDF"); //Specify request destination

  http.begin("http://projectsiot.xyz/IoTProjects/PrepaidCardPetrol/petrolcard.php?a=U&b=0&c=0");

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
   http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9652490222&from=MYDREM&message=WELCOME%20TO%20PROJECT"); //Specify request destination

  http.begin("http://projectsiot.xyz/IoTProjects/PrepaidCardPetrol/petrolcard.php?a=U&b=0&c=0");

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

lcd.setCursor(0,0);
    lcd.print("plz show card         ");
lcd.setCursor(0,1);
    lcd.print("                      ");

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
if (input[10]=='8')
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
}

else if (amount >(-1))
{

    if (amount <101)
{

    lcd.setCursor(4,1);
    lcd.print("LOW BALENCE");
      
}  
A = "http://projectsiot.xyz/IoTProjects/PrepaidCardPetrol/petrolcard.php?a=A&b=";
A += String(amount);
A += "&c=";
A += String(j);
A += "&d=";
A += String(j*10);

Serial.print("A = "); Serial.println(A);
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
    http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9652490222&from=MYDREM&message=RJANED;LKSDF"); //Specify request destination

   http.begin(A);

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}

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
    
digitalWrite (relay,HIGH);
//////////////////////////////

while ((digitalRead(level)==LOW)||(t>j))
{
  
  Serial.println(digitalRead(level));
Serial.print("t = "); Serial.println(t);

t++;
Serial.println("relay -- on");
delay(500);
}    
digitalWrite (relay,LOW);
delay(5000);
//////////////////////
   
}

} // 1st card
else if (input[10]=='4')
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
}

else if (amount1 >(-1))
{

    if (amount1 <101)
{

    lcd.setCursor(4,1);
    lcd.print("LOW BALENCE");
      
}  
B = "http://projectsiot.xyz/IoTProjects/PrepaidCardPetrol/petrolcard.php?a=B&b=";
B += String(amount1);
B += "&c=";
B += String(j);
B += "&d=";
B += String(j*10);

Serial.print("B = "); Serial.println(B);
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   // http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9652490222&from=MYDREM&message=RJANED;LKSDF"); //Specify request destination

   http.begin(B);

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}


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
    
digitalWrite (relay,HIGH);
//////////////////////////////

while ((digitalRead(level)==LOW)||(t>j))
{
  
  Serial.println(digitalRead(level));
Serial.print("t = "); Serial.println(t);

t++;
Serial.println("relay -- on");
delay(500);
}    
digitalWrite (relay,LOW);
delay(5000);
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
    
 Serial.println("http://projectsiot.xyz/IoTProjects/PrepaidCardPetrol/petrolcard.php?a=H&b=0&c=0");
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   // http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9652490222&from=MYDREM&message=RJANED;LKSDF"); //Specify request destination

   http.begin("http://projectsiot.xyz/IoTProjects/PrepaidCardPetrol/petrolcard.php?a=H&b=0&c=0");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}
    

}
   }  
  /*
Serial.println("loop Started");
String raj = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9652490222&from=MYDREM&message=RJANED;LKSDF";
//raj = raj + String(r) ;
  Serial.println(raj);
 if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   // http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9652490222&from=MYDREM&message=RJANED;LKSDF"); //Specify request destination

   http.begin(raj);
    
    int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
  } else {
    Serial.println("Error in WiFi connection");   
  }
  delay(3000); //Send a request every 30 seconds

r = r + 10;
  Serial.print("r = "); Serial.println(r);
raj = "\n";
*/
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
