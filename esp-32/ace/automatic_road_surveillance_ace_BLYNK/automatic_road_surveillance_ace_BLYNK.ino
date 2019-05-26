
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#include <LiquidCrystal.h>


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

//char auth[] = "f8f8ba1b807c435ebb6bd6ed63c0adb6";
char auth[] = "f9d4b43dbced43169cc5d9d36f65326c";


// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "project12";
char pass[] = "project123456";

int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 10; //Resolution 8, 10, 12, 15



#define ldrPin 34
#define led1 5
#define led2 18
#define led3 19
#define buzzer 21

#define ir1 35
#define ir2 32



int ldr = 0;
int count1 = 0;                                          // count = 0
char input[12];
int t = 0;
float spd = 0;

void beep ()
{
  digitalWrite(buzzer,HIGH);
  delay(1000);
  digitalWrite(buzzer,LOW);
  delay(100);
}



LiquidCrystal lcd (15,2,0,4,16,17);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("power up");
  lcd.begin(16,2);
  pinMode(buzzer,OUTPUT);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(ldrPin,INPUT);
  pinMode(ir1,INPUT);
  pinMode(ir2,INPUT);

// configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);
  
  // attach the channel to the GPIO2 to be controlled
  ledcAttachPin(led1, ledChannel);
  ledcAttachPin(led2, ledChannel);
  ledcAttachPin(led3, ledChannel);

beep ();

     lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("AUTOMATIC ROAD       ");
     lcd.setCursor(0,1);
   lcd.print("SURVEILLANCE        ");
   delay(2000);

  Blynk.begin(auth, ssid, pass);
delay(2000);
//   Blynk.notify("KIT STARTED!!!!");
//  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:

  Blynk.run();

ldr = analogRead(ldrPin);
Serial.println("ldr ="+String(ldr));

if (ldr > 500)
{
  Serial.println("night mode"); 
  ledcWrite(ledChannel, 102);
  delay(2000);
  analogWrite(led2,240);
  analogWrite(led3,240);
}
else
{
 Serial.println("day mode");
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);
}

  
  lcd.setCursor(0,0);
    lcd.print("Please show card          ");
   lcd.setCursor(0,1);
    lcd.print("                          ");
   
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


if (input[10]=='F')
{
  Serial.println("card matched ");

  
  lcdstring(0,0,"CARD MATCED      ");
  lcdstring(0,1,"V NO: TS07S1243  ");
  delay(500);
  
while((digitalRead(ir1)==LOW)&&(digitalRead(ir2)==LOW));

t = 0;

ldr = analogRead(ldrPin);
//Serial.println("ldr ="+String(ldr));

if (ldr > 500)
{
  //Serial.println("night mode");
  digitalWrite(led1,HIGH);
  digitalWrite(led2,HIGH);
  digitalWrite(led3,HIGH);
}
else
{
    //Serial.println("day mode");
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);
}

if (digitalRead(ir1)==HIGH);
{
  lcd.clear ();
   lcdstring(0,0,"CALCULATING THE  ");
  lcdstring(0,1,"SPEED..............");
  delay(5);
  Serial.println("count started");
  while(digitalRead(ir2)==LOW)
  {
    t++;
    Serial.println(t);
    if (digitalRead(ir2)==HIGH)
    {
      break;
    }
  }
  
}

Serial.println("time = "+String(t));
spd = 200.0/t;
spd = spd*100;
Serial.print("speed = "); Serial.println(spd);
lcd.clear ();
   lcdstring(0,0,"VEHICLE SPEED    ");
   lcdstring(0,1,"                  ");
  lcdstring(0,1,String(spd));
  delay(2000);

if (spd > 100)
{
  Serial.println("high speed alert");
  lcd.clear ();
   lcdstring(0,0,"HIGH SPEED ALERT");
   lcdstring(0,1,"V NO: TS07S1243  ");
  delay(500);
 Blynk.notify("HIGH SPEED ALERT\n Vehicle NO:TS07S1243");
 beep ();
 delay(1500);
}
  
}//card 1
else
{
  Serial.println("invalid card");
    lcd.clear ();
   lcdstring(0,0,"INVALID CARD      ");
   lcdstring(0,1,"PLEASE CHECK       ");
   beep ();
   delay(1000);
}
   }//serial available
   }//loop
void lcdstring(int a, int b, String data)
{
  lcd.setCursor(a,b);
  lcd.print(data);
}
