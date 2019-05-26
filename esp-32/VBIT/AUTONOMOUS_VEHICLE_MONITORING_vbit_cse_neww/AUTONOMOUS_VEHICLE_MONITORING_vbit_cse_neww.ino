#include <WiFi.h>
#include <HTTPClient.h>
#include <LiquidCrystal.h>
#include <String.h>


LiquidCrystal lcd (15,2,4,16,17,5);


// WiFi parameters to be configured
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig 

String q = "http://projectsiot.xyz/IoTProjects/AutonomusVeh/upload.php?a=";
String iot = "\0";
String p = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9493206867&from=MYDREM&message=";
String msg = "\0";

String ultra = "N";
String veh = "N";

String leftt = "N";
String rightt = "N";


#define trigPin 18
#define echoPin 19
#define buzzer 21
#define lir 22
#define rir 23

#define m11 13
#define m12 12
#define m21 14
#define m22 27

void forward ()
{
  Serial.println("moving forward.....");
  digitalWrite(m11,HIGH);
  digitalWrite(m12,LOW);
  digitalWrite(m21,HIGH);
  digitalWrite(m22,LOW);
  delay(50);
}
void backward ()
{
  Serial.println("moving backward.....");
  digitalWrite(m11,LOW);
  digitalWrite(m12,HIGH);
  digitalWrite(m21,LOW);
  digitalWrite(m22,HIGH);
  delay(50);
}
void left ()
{
  Serial.println("moving left.....");
  digitalWrite(m11,HIGH);
  digitalWrite(m12,LOW);
  digitalWrite(m21,LOW);
  digitalWrite(m22,HIGH);
  delay(50);
}
void right ()
{
  Serial.println("moving right.....");
   digitalWrite(m11,LOW);
  digitalWrite(m12,HIGH);
  digitalWrite(m21,HIGH);
  digitalWrite(m22,LOW);
  delay(50);
}
void stop_motor ()
{
  Serial.println("moving stoppp.....");
   digitalWrite(m11,LOW);
  digitalWrite(m12,LOW);
  digitalWrite(m21,LOW);
  digitalWrite(m22,LOW);
  delay(50);
}
void beep ()
{
  digitalWrite(buzzer,HIGH); delay(1000);
  digitalWrite(buzzer,LOW); delay(100);
}

long duration, distance,duration1,distance1;


 
void setup(void) { 
  
 Serial.begin(9600);
  Serial.print("Bezig met verbinden");
 WiFi.begin(ssid, password); // Connect to WiFi
 lcd.begin(16,2);
 
lcd.clear();
lcd.setCursor(0,0);
        lcd.print("AUTONOMOUS ROBOT");
        lcd.setCursor( 2,1);
         lcd.print(".................");
         delay(2000);
                  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(lir,INPUT);
  pinMode(rir,INPUT);
          
 pinMode(buzzer,OUTPUT);
          
 pinMode(m11,OUTPUT);
pinMode(m12,OUTPUT);
pinMode(m21,OUTPUT);
pinMode(m22,OUTPUT);
          
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

  http.begin("http://projectsiot.xyz/IoTProjects/AutonomusVeh/upload.php?a=U&b=N&c=N&d=N&e=N");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}


}//setup
 
void loop() {

ultra = "N";
veh = "Y";
  
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance= duration*0.034/2;
Serial.print("Distance: ");
Serial.println(distance);
delay(50);
Serial.print(F("distance = ")); Serial.println(distance);
if (distance > 230)
{
  distance = 230;
}
if (distance < 30)
{
Serial.println("ultrasonic obstacle***********");
ultra = "Y";
 lcdstring(0,0,"OBSTACLE DETECTED");
 lcdstring(0,1,"                   ");
if (digitalRead(lir)==LOW)
{
  
veh = "Y";
  lcdstring(0,0,"OBSTACLE DETECTED");
 lcdstring(0,1,"MOVING LEFT SIDE");
  ultra = "Y";
  leftt = "N";
  //rightt = "N";
  left ();
  delay(1500);
  forward ();
}
else if (digitalRead(rir)==LOW)
{
  
veh = "Y";
  lcdstring(0,0,"OBSTACLE DETECTED");
 lcdstring(0,1,"MOVING RIGHT SIDE");
  ultra = "Y";
 // leftt = "Y";
  rightt = "N";
  right ();
  delay(1500);
  forward ();
}
else
{
  
veh = "N";
  beep ();
  lcdstring(0,0,"OBSTACLE DETECTED");
 lcdstring(0,1,"      STOP        ");
  ultra = "Y";
  leftt = "Y";
  rightt = "Y";
stop_motor ();  
}
  
}//IF OBSTACLE
else 
{
 
veh = "N"; 
  lcdstring(0,0,"                       ");
  lcdstring(0,0,"Dist:"+String(distance));
 lcdstring(0,1,"MOVING FORWARD    ");
  ultra = "N";
  leftt = "N";
  rightt = "N";
  forward ();
}
 
  iot  = q + veh + "&b=" + ultra  ;
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
void lcdstring (int a, int b, String w)
{
  lcd.setCursor(a,b);
  lcd.print(w);
}
