#include <WiFi.h>
#include <HTTPClient.h>
#include <String.h>
#include <LiquidCrystal.h>

#define button 19 
#define buzzer 34
#define m11 22
#define m12 23

#define RXD2 16
#define TXD2 17

// WiFi parameters to be configured
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig

String a = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=7337595055&from=MYDREM&message=";
String msg = "\0";
String r = "http://projectsiot.xyz/IoTProjects/SuperMarket/upload.php?a=";
String rs = "\0";

String items = "\0";
String items1 = "\0";
int count1 = 0; 
// count = 0
char input[12];

int  q = 0;

const int meat = 200;
const int oil = 100;
const int pen = 20;
const int soap = 50;
const int toy = 250;

int flag = 5;

int no = 0;
int no1 = 0;

int s = 0;
int m = 0;
int p = 0;
int t = 0;
int o = 0;


int amount = 1000;
int cost = 0;

LiquidCrystal lcd (15,2,0,4,5,18);

void beep ()
{
  digitalWrite(buzzer,HIGH);
  delay(1000);
  digitalWrite(buzzer,LOW);
  delay(100);
}


void setup()
{
  // Debug console
  Serial.begin(9600);
  
Serial.println("smart trolly for megamalls");

lcd.begin(16,2);
lcd.clear();
lcdstring(0,0," SMART SHOPPING  ");
lcdstring(0,1,"      CART       ");
delay(2000);

  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

pinMode(buzzer,OUTPUT);
pinMode(m11,OUTPUT);
pinMode(m12,OUTPUT);
pinMode(button,INPUT);


 
  Serial.print("Bezig met verbinden");
  WiFi.begin(ssid, password); // Connect to WiFi
 
  // while wifi not connected yet, print '.'
  // then after it connected, get out of the loop
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     lcd.clear();
  lcdstring(0,0," CONNECTING  TO ");
  lcdstring(0,1,ssid);
   //  delay(200);
     Serial.print(".");
  }

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
     lcd.clear();
  lcdstring(0,0,"  CONNECTED TO  ");
  lcdstring(0,1,ssid);
  delay(2000);

lcd.clear();
  lcdstring(0,0,"  SERVER INT.  ");
  lcdstring(0,1,"  PLEASE WAIT  ");
  delay(2000);
  Serial.print("A = "); Serial.println("http://projectsiot.xyz/IoTProjects/AirSoundPollution/pfupload.php?a=U&b=0");
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   
  http.begin("http://projectsiot.xyz/IoTProjects/SuperMarket/upload.php?a=U&b=&c=0&d=0");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}  
lcd.clear();
  lcdstring(0,0,"  SERVER INT.  ");
  lcdstring(0,1,"      DONE      ");
  delay(5000);
lcd.clear();    

Serial.println(F("PLEASE SHOW CARD "));

}//set up

void loop()
{

lcd.setCursor(0, 0);
  lcd.print("Please show card          ");
  lcd.setCursor(0, 1);
  lcd.print("                          ");

if (digitalRead(button) == HIGH)
{

Serial.println("BUTTON -- PRESSED ");

lcd.setCursor(0, 0);
  lcd.print("Please show card          ");
  lcd.setCursor(0, 1);
  lcd.print("                          ");
if (flag == 1)
{
openn ();
delay(2000);
stopp ();
}

 if (Serial.available())
  {
    count1 = 0;
    while (Serial.available() && count1 < 12)         // Read 12 characters and store them in input array
    {
      input[count1] = Serial.read();
      count1++;
      delay(5);
    }//WHILE
    //

    Serial.println(input);                           // Print RFID tag number
    Serial.print(F("input[10] is ")); Serial.println(input[10]);

 if (input[10]=='C')
    {

    if(m > 0)
    {
      m--;
      
    
    Serial.print("meat = "); Serial.println(m);
      cost = cost - meat;
   Serial.println(F("you REMOVED -- MEAT = 500 "));
   Serial.print(F("total bill = ")); Serial.println(cost);
    //  terminal.println(F("you REMOVED -- MEAT : 500 "));
 // //  delay(200);
    //  terminal.print("total cost = "+String(cost));
//  //  delay(200);
   
lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("   MEAT : 500   "); 
  lcdstring(0,1,"TOTAL BILL="); 
  lcdstring(12,1,String(cost));
  delay(2000);
}
closee ();
delay(2000);
stopp ();
    }
else if (input[10]=='E')
    {
    
    if(o > 0)
    {
      o--;
      
    
    Serial.print("oil = "); Serial.println(o);

    cost = cost - oil;
    
   Serial.println(F("you REMOVED -- OIL = 100 "));
   Serial.print(F("total bill = ")); Serial.println(cost); 
   
    //  terminal.println(F("you REMOVED -- OIL : 100 "));
//  //  delay(200);
    //  terminal.print("total cost = "+String(cost)); 
//  //  delay(200);
    
lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("   OIL : 100    "); 
  lcdstring(0,1,"TOTAL BILL="); 
  lcdstring(12,1,String(cost));
  delay(2000);
}
closee ();
delay(2000);
stopp ();
    }
else if (input[10]=='2')
    {

    if(p > 0)
    {
      p--;
      
    
    Serial.print("pen = "); Serial.println(p);
      
    cost = cost - pen;
    
   Serial.println(F("you REMOVED --  PEN = 20 "));
   Serial.print(F("total bill = ")); Serial.println(cost);  

   
    //  terminal.println(F("you REMOVED -- PEN : 20 "));
  //  delay(200);
    //  terminal.print("total cost = "+String(cost)); 
  //  delay(200);
    
lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("   PEN : 20    "); 
  lcdstring(0,1,"TOTAL BILL="); 
  lcdstring(12,1,String(cost));
  delay(2000);
}
closee ();
delay(2000);
stopp ();
    }
else if (input[10]=='D')
    {

        if(t > 0)
    {
      t--;
      
    
    Serial.print("toy = "); Serial.println(t);
  
    cost = cost - toy;
    
   Serial.println(F("you REMOVED --  TOY = 250 "));
   Serial.print(F("total bill = ")); Serial.println(cost);
   
    //  terminal.println(F("you REMOVED -- TOY : 250 "));
  //  delay(200);
    //  terminal.print("total cost = "+String(cost)); 
  //  delay(200); 
    
lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("   TOY : 250    "); 
  lcdstring(0,1,"TOTAL BILL="); 
  lcdstring(12,1,String(cost));
  delay(2000);
}
closee ();
delay(2000);
stopp ();
    }
else if (input[10]=='7')
    {

     if(s > 0)
    {
      s--;
      
    
    Serial.print("soap = "); Serial.println(s);
     
    cost = cost - soap;
    
   Serial.println(F("you REMOVED --  SOAP = 50 "));
   Serial.print(F("total bill = ")); Serial.println(cost); 

    
    //  terminal.println(F("you REMOVED -- SOAP : 50 "));
  //  delay(200);
    //  terminal.print("total cost = "+String(cost)); 
  //  delay(200);
    
lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("   SOAP : 50    "); 
  lcdstring(0,1,"TOTAL BILL="); 
  lcdstring(12,1,String(cost));
  delay(2000);
}
closee ();
delay(2000);
stopp ();
    }
/*
for (q = 0; q <60; q++)
{
 if( items[no] == '$')
 {
  Serial.println("$ found-removing null");
  items.remove(no, 1);
 }
}//for loop
*/

  
}// serial available for button

}//if button
    
else if (Serial.available())
  {
    count1 = 0;
    while (Serial.available() && count1 < 12)         // Read 12 characters and store them in input array
    {
      input[count1] = Serial.read();
      count1++;
      delay(5);
    }//WHILE
    //

    Serial.println(input);                           // Print RFID tag number
    Serial.print(F("input[10] is ")); Serial.println(input[10]);

 if (input[10]=='C')
    {
      
openn ();
delay(2000);
stopp ();
      m++;
      Serial.print("meats = "); Serial.println(m);
      //items += "meat%2C";
      //Serial.print(F("items = ")); Serial.println(items);
      cost = cost + meat;
   Serial.println(F("you enterred -- MEAT = 500 "));
   Serial.print(F("total bill = ")); Serial.println(cost);  
   
    //  terminal.println(F("you ADDED -- MEAT : 500 "));
  //  delay(200);
    //  terminal.println("total cost = "+String(cost)); 
  //  delay(200);

   
lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("   MEAT : 500   "); 
  lcdstring(0,1,"TOTAL BILL="); 
  lcdstring(12,1,String(cost));
  delay(2000);
}
else if (input[10]=='E')
    {
      
openn ();
delay(2000);
stopp ();
      o++;
      Serial.print("oil = "); Serial.println(o);
    //items += "oil%2C";
      //Serial.print(F("items = ")); Serial.println(items);
    cost = cost + oil;
    
   Serial.println(F("you enterred -- OIL = 100 "));
   Serial.print(F("total bill = ")); Serial.println(cost);   
   
    //  terminal.println(F("you ADDED -- OIL : 100 "));
  //  delay(200);
    //  terminal.println("total cost = "+String(cost)); 
  //  delay(200);
   
    
lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("   OIL : 100    "); 
  lcdstring(0,1,"TOTAL BILL="); 
  lcdstring(12,1,String(cost));
  delay(2000);
}
else if (input[10]=='2')
    {
      
openn ();
delay(2000);
stopp ();
    //   items += "pen%2C";
     // Serial.print(F("items = ")); Serial.println(items);
     
      p++;
      Serial.print("pens = "); Serial.println(p); 
    cost = cost + pen;
    
   Serial.println(F("you enterred --  PEN = 20 "));
   Serial.print(F("total bill = ")); Serial.println(cost);   
   
    //  terminal.println(F("you ADDED -- PEN : 20 "));
  //  delay(200);
    //  terminal.println("total cost = "+String(cost)); 
  //  delay(200);

   
    
lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("   PEN : 20    "); 
  lcdstring(0,1,"TOTAL BILL="); 
  lcdstring(12,1,String(cost));
  delay(2000);
}
else if (input[10]=='D')
    {
      
openn ();
delay(2000);
stopp ();
 //   items += "toy%2C";
 //     Serial.print(F("items = ")); Serial.println(items);
   
      t++;
      Serial.print("toys = "); Serial.println(t);   
    cost = cost + toy;
    
   Serial.println(F("you enterred --  TOY = 250 "));
   Serial.print(F("total bill = ")); Serial.println(cost);  
   
    //  terminal.println(F("you ADDED -- TOY : 250 "));
  //  delay(200);
    //  terminal.println("total cost = "+String(cost));  
  //  delay(200);

    
    
lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("   TOY : 250    "); 
  lcdstring(0,1,"TOTAL BILL="); 
  lcdstring(12,1,String(cost));
  delay(2000);
}

else if (input[10]=='7')
    {
      
openn ();
delay(2000);
stopp ();
    //items += "soap%2C";
     Serial.print(F("items = ")); Serial.println(items);
      
      s++;
      Serial.print("soap = "); Serial.println(s);
    cost = cost + soap;
    
   Serial.println(F("you enterred --  SOAP = 50 "));
   Serial.print(F("total bill = ")); Serial.println(cost);   
   
    //  terminal.println(F("you ADDED -- SOAP : 50 "));
  //  delay(200);
    //  terminal.println("total cost = "+String(cost)); 
  //  delay(200);
   
    
lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("   SOAP : 50    "); 
  lcdstring(0,1,"TOTAL BILL="); 
  lcdstring(12,1,String(cost));
  delay(2000);
}

else if (input[10]=='9')
{

lcd.clear();
lcdstring(0,0,"CARD  AUTHERIZED");
lcdstring(0,1,"****************");
delay(2000);
 //  terminal.println("***************************");
  //  delay(200);
 //  terminal.println("CARD AUTHERIZED");
 delay(500);

lcd.clear();
lcdstring(0,0,"FINAL BILL: ");
lcdstring(12,0,String(cost));
delay(2000);

 //  terminal.println("FINAL BILL: "+String(cost));

 if ((amount < cost)|| (amount <= 0))
{
  lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("insufficient bal");
       lcd.setCursor(0,1);
    lcd.print(" PLZ RECHARGE  ");
    delay(1000);
    beep ();
 msg = a + "INSUFFICIENT%20BALANCE";   
  //  sendsms ();
   //  terminal.println("**** INSUFFICIENT BALANCE ****");
  //  delay(200);
}
else if (amount >= cost)
{

lcd.clear();

if (amount <101)
{
   //  terminal.println("*** LOW BALANCE ***");
  //  delay(200);
    lcd.setCursor(0,1);
    lcd.print("    LOW BALANCE  ");      
}  
  Serial.print(F("amount = ")); Serial.println(amount);
  amount = amount - cost;
  Serial.print(F("cost = ")); Serial.println(cost);
  Serial.print(F("amount****** = ")); Serial.println(amount);

lcdstring(0,0,"RE CARD BAL=");
lcdstring(12,0,String(amount));
delay(1000);
beep ();



}
if(m>0)
{
  items += "Meat-";
  items += String(m);
  items += "%2C";

  items1 += "Meat-";
  items1 += String(m);
  items1 += ",";
}
if(s>0)
{
  items += "Soap-";
  items += String(s);
  items += "%2C";

  items1 += "Soap-";
  items1 += String(s);
  items1 += ",";
}
if(p>0)
{
  items += "Pen-";
  items += String(p);
  items += "%2C";

  items1 += "Pen-";
  items1 += String(p);
  items1 += ",";
}
if(o>0)
{
  items += "Oil-";
  items += String(o);
  items += "%2C";

  items1 += "Oil-";
  items1 += String(o);
  items1 += ",";
}
if(t>0)
{
  items += "Toy-";
  items += String(t);
  items += "%2C";

  items1 += "Toy-";
  items1 += String(t);
  items1 += ",";
}
Serial.print("items = "); Serial.println(items);
rs = r +'A' + "&b=" + items + "&c=" + String(cost) + "&d=" + String (amount);
Serial.println(rs);
        send2server ();

Serial2.println("TROLLY-1\nITEMS LIST:"+String(items1)+"\nTOTAL COST:"+String(cost));
delay(2000);  
 msg = a + "TOTAL%20COST:"+String(cost)+"%0AR.BAL:"+String(amount);   
   sendsms ();
}

else
{

  lcd.clear ();
  lcd.setCursor (0,0);
  lcd.print("INVALID CARD");
  lcd.setCursor (0,1);
  lcd.print("PLEASE CHECK......");
      delay(200);
    beep ();
    delay(1000);
  
}

if (flag == 0)
{
  closee ();
  delay(2000);
  stopp ();
}
  } // Serial.available ()



}//loop
void lcdstring(int a, int b, String data)
{
  lcd.setCursor(a,b);
  lcd.print(data);
}
void openn ()
{
  flag = 0;
  digitalWrite(m11,HIGH);
  digitalWrite(m12,LOW);
  delay(50);
}
void closee ()
{
  flag = 1;
  digitalWrite(m11,LOW);
  digitalWrite(m12,HIGH);
  delay(50);
}

void stopp ()
{
  digitalWrite(m11,LOW);
  digitalWrite(m12,LOW);
  delay(50);
}
 void send2server ()
{
  Serial.print("length of rs = "); Serial.println(rs.length());
Serial.print("rs = "); Serial.println(rs);
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
 http.begin(rs);

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}
}
 void sendsms ()
{
  Serial.print("length of msg = "); Serial.println(msg.length());
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
 
delay(500);
}
}
