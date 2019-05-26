/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


#define pir D1
#define fire D2
#define light D3
#define buzzer D4
#define relay D5
#define m11 D6
#define m12 D7
#define ldrPin A0

int ldr = 0;
int r1 = 0;
int r2 = 0;
int r3 = 0;


volatile int buttonState = 0;
volatile int buttonState1 = 0;
volatile int buttonState2 = 0;

int count1 = 0;                                          // count = 0
char input[12];

void forward ()
{
  digitalWrite(m11,HIGH);
  digitalWrite(m12,LOW);
  delay(50);  
}
void backward ()
{
  digitalWrite(m12,HIGH);
  digitalWrite(m11,LOW);
  delay(50);  
}
void stop_motor ()
{
  digitalWrite(m11,LOW);
  digitalWrite(m12,LOW);
  delay(50);  
}
void beep ()
{
  digitalWrite(buzzer,HIGH);
  delay(1000);
  digitalWrite(buzzer,LOW);
  delay(100);
}
 

WidgetLCD lcd1(V0);

BLYNK_WRITE(V1)
{
   buttonState = param.asInt();
  Serial.print(F("buttonState = ")); Serial.println(buttonState);
}
BLYNK_WRITE(V2)
{
   buttonState1 = param.asInt();
  Serial.print(F("buttonState1 = ")); Serial.println(buttonState1);
}
/*
BLYNK_WRITE(V3)
{
   buttonState2 = param.asInt();
  Serial.print(F("buttonState2 = ")); Serial.println(buttonState2);
}
*/

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
//char auth[] = "31a4c852f9dd4245910df7173fa98d5f";
//char auth[] = "f9d4b43dbced43169cc5d9d36f65326c";//(my own)

 char auth[] = "d916772b5e3e4abe8480602ed6e2ed61";


// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "project12";
char pass[] = "project123456";

// This function will be called every time Slider Widget
// in Blynk app writes values to the Virtual Pin V1

void setup()
{
  // Debug console
  Serial.begin(9600);

  Serial.println("power up");

pinMode(ldrPin,INPUT);
pinMode(pir,INPUT);
pinMode(fire,INPUT);
pinMode(light,OUTPUT);
pinMode(buzzer,OUTPUT);
pinMode(relay,OUTPUT);
pinMode(m11,OUTPUT);
pinMode(m12,OUTPUT);



  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);


  Blynk.notify("KIT STARTED");
  delay(100);

lcd1.clear();
lcd1.print(0,0,"  WELL COME TO  ");
lcd1.print(0,1,"ADVANCED IOT BSD");
delay(2000);

lcd1.clear();
lcd1.print(0,0,"COMBINED REMOTE ");
lcd1.print(0,1,"HOME AUTOMATION");
delay(2000);

lcd1.clear();
lcd1.print(0,0,"AND ALERT SYSTEM");
lcd1.print(0,1,"................");
delay(2000);

  
lcd1.clear();
}

void loop()
{
  Blynk.run();
/////////////////////////////////////////

if (digitalRead(pir) == HIGH)
{
ldr = analogRead(ldrPin);
Serial.println("ldr = "+String(ldr));
if(ldr > 770)
{
  Serial.println("day detected");
  digitalWrite(light,HIGH);
}
else
{
  Serial.println("night detected");
  digitalWrite(light,LOW);
}
}//pir
  
else if(digitalRead(fire)==HIGH)
{
  Blynk.notify("FIRE DETECTED\nPLEASE CHECK..."); delay(100);
  Serial.println("fire detected");
  beep ();
}
else 
{

    lcd1.print(0,0,"plz show card         ");
    lcd1.print(0,1,"                      ");

if(Serial.available())
   {
      count1 = 0;
      while(Serial.available() && count1 < 12)          // Read 12 characters and store them in input array
      {
         input[count1] = Serial.read();
         count1++;
         delay(5);
      }//WHILE

 Serial.println(input);                           // Print RFID tag number 
   Serial.print("input[10] is "); Serial.println(input[10]);
if (input[10]=='D')
{
  Serial.println("card matched..................");
delay(1000);
/*
if (buttonState == 1)
{
Serial.println("fan on");
digitalWrite(relay,HIGH);
delay(500);
}
else if (buttonState == 0)
{
Serial.println("fan off");
digitalWrite(relay,LOW);
delay(500);
}
*/
if (buttonState1 == 1)
{
  forward ();
  delay(1500);
  stop_motor();
  delay(2000);
  backward ();
  delay(1500);
  stop_motor ();
  delay(100);
}
}//card
else
{
  beep ();
}
}//serial available
}//else
}//loop
