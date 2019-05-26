#include <WiFi.h>
#include <HTTPClient.h>
#include <LiquidCrystal.h>
#include <String.h>
 
LiquidCrystal lcd (15,2,0,4,16,17);

#define tempa 34
#define tempb 35

#define button 32

#define buzzer 33
#define relay1 18
#define relay2 19
#define heart 21

int tt = 0;
String e_temp = "NORMAL";

float temp1=0.0;
unsigned int temp2 = 0;
float aa = 0.0;
unsigned int bb = 0;

String otp1[11] = {"37","36","30","28","36","32","37","29","33","39","39"} ;
String otp[11] = {"62","72","71","75","97","79","92","79","95","83","99"} ;
unsigned int no = 0;
unsigned hb = 0;
String hbvalue = "\0";

String H = "N";
String B = "N";

// WiFi parameters to be configured
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig 

String q = "http://projectsiot.xyz/IoTProjects/SolderHeath/upload.php?a=";
String iot = "\0";
String m = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydream123&to=9493206867&from=MYDREM&message=";
String msg = "\0";
String gas2 = "\0";
String p1 = "Normal";


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
        lcd.print("INTELLIGENT");
        lcd.setCursor(0,1);
         lcd.print(" SOLDER HEALTH   ");
         delay(2000);
         
lcd.clear();
lcd.setCursor(0,0);
        lcd.print("SECUIRITY COMM'N");
        lcd.setCursor(0,1);
         lcd.print("   USING IOT       ");
         delay(2000);

          pinMode(tempa,INPUT);
          pinMode(tempb,INPUT);
         pinMode(button,INPUT);
         pinMode(heart,INPUT);
          
          pinMode(buzzer,OUTPUT);
          pinMode(relay1,OUTPUT);
          pinMode(relay2,OUTPUT);
          
  // while wifi not connected yet, print '.'
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
     delay(1000);
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

  http.begin("http://projectsiot.xyz/IoTProjects/SolderHeath/upload.php?a=U&b=N&c=N&d=N&e=N");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}
lcd.clear ();
}
 
void loop() {

e_temp = "NORMAL";
H = "N";
B = "N";
 no = random(11);
temp2 = analogRead(tempa);  
float V=temp2*(5/(4095.00));  
//float V=temp2*(5/(1023.00));  
  temp1=V*100;  

  temp1 = temp1;
Serial.print("body temperature is = "); Serial.println(temp1);
delay(50);

bb = analogRead(tempb);  
float VV=bb*(5/(4095.00));  
//float V=temp2*(5/(1023.00));  
  aa=VV*100;  

  aa = aa ;
Serial.print("temperature is = "); Serial.println(aa);
delay(50);

Serial.println("button="+String(digitalRead(button)));
Serial.println("heart"+String(digitalRead(heart)));

//temp1 = 0.0;

if (aa < 45)
{
  e_temp = "N";
    delay(100);
 digitalWrite(relay1,HIGH);
//beep ();
iot =  q + String(temp1) + "&b=" + e_temp + "&c=" + H + "&d=" + B ;
send2server ();
delay(4000);
}
/*
if ((temp1 > 55)||(aa > 55))
{
  
    lcdstring(0,0,"T:"+String(temp1));
    lcdstring(8,0,"BT:"+String(aa));
     lcdstring(0,1,"HB: "+String(H));
     lcdstring(8,1,"EB: "+String(B));
     delay(100);
 digitalWrite(relay1,HIGH);
beep ();
iot =  q + String(temp1) + "&b=" + String(aa) + "&c=" + H + "&d=" + B ;
send2server ();


 // msg = p +"Temperature%20Alert%0AT: "+String(temp1);
// sendmsg();
  delay(2000);
}
*/
else
{
  e_temp = "Y";
 digitalWrite(relay1,LOW);
  beep ();
  
}
/*
if ((temp1 < 25)||(aa < 25))
{
  
    lcdstring(0,0,"T:"+String(temp1));
    lcdstring(8,0,"BT:"+String(aa));
     lcdstring(0,1,"HB: "+String(H));
     lcdstring(8,1,"EB: "+String(B));
     delay(100);
beep ();
 digitalWrite(relay2,HIGH);

iot =  q + String(temp1) + "&b=" + String(aa) + "&c=" + H + "&d=" + B ;
send2server ();


 // msg = p +"Temperature%20Alert%0AT: "+String(temp1);
// sendmsg();
  delay(2000);
}

else
{
 digitalWrite(relay2,LOW);
}
*/
//if (!(digitalRead(heart)))
if ((digitalRead(heart)))
{
  lcd.clear();
     lcd.setCursor(0,0);
    lcd.print(" PLZ PUT YOUR  ");
      lcd.setCursor(0,1);
    lcd.print("FINGER PROPERLY");
    delay(1800);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("CALCULATING.....");
  delay(2000);

  hb = otp[no].toInt();
 Serial.print("otp is = "); Serial.println(hb);

  H = String(hb);
  tt = otp1[no].toInt(); 
  temp1 = float(tt);
Serial.println("temp1 = "+String(temp1));

  if ((hb>95)||(hb<70))
  {
    H = "Y";
Serial.println("****** heart alert *********");
    lcd.clear();
  lcd.print("HEART BEAT ALERT");
    lcd.setCursor(0,1);
    lcd.print("HB = ");
    lcd.setCursor(6,1);
    lcd.print(hb);
beep ();
//msg = a + "HEART%20BEAT%20ALERT%20PLEASE%20CHECK";
// sendsms ();
iot =  q + String(temp1) + "&b=" + e_temp + "&c=" + H + "&d=" + B ;
send2server ();
delay(5000);
}
  else
  {
    
  hbvalue = "\0";   
  lcd.clear();
  lcd.print("HEART BEAT NORMAL");
    lcd.setCursor(0,1);
    lcd.print("H BEAT = ");
    lcd.setCursor(10,1);
    lcd.print(hb);
    iot =  q + String(temp1) + "&b=" + e_temp + "&c=" + H + "&d=" + B ;
send2server ();
  delay(5000);
  
  }
  
}//heart beat

if (digitalRead(button)==LOW)
{
  B= "Y";
 
  lcd.clear();
    lcdstring(0,0,"T:"+String(temp1));
     lcdstring(0,1,"HB: "+String(H));
     lcdstring(8,1,"EB: "+String(B));
     delay(100);
     
iot =  q + String(temp1) + "&b=" + e_temp + "&c=" + H + "&d=" + B ;
send2server ();
beep ();
delay(4000);
}
else
{
  B = "N";
}
  lcd.clear();
     lcdstring(0,0,"T:"+String(temp1));
     lcdstring(8,0,"ET:"+String(e_temp));
     lcdstring(0,1,"HB: "+String(H));
     lcdstring(8,1,"EB: "+String(B));
     delay(100);
iot =  q + String(temp1) + "&b=" + e_temp + "&c=" + H + "&d=" + B ;
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
 
delay(100);
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
