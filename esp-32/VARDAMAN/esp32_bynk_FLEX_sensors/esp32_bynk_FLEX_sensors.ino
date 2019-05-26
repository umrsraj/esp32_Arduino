/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
//char auth[] = "f9d4b43dbced43169cc5d9d36f65326c";
//char auth[] = "0f598421262840abaa86fd694c6387dd";
char auth[] = "7ecc14c70a60495988d203e27ebe7899";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "HTC";
char pass[] = "90101234";

WidgetLCD lcd(V0);


#define f1 34
#define f2 35
#define f3 32


#define v0 15
#define v1 2
#define v2 4
#define v3 5
#define v4 18

int a , b, c;



void setup()
{
  // Debug console
  Serial.begin(9600);
pinMode(f1,INPUT);
pinMode(f2,INPUT);
pinMode(f3,INPUT);

pinMode(v0,OUTPUT);
pinMode(v1,OUTPUT);
pinMode(v2,OUTPUT);
pinMode(v3,OUTPUT);
pinMode(v4,OUTPUT);


  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  //lcd.clear(); //Use it to clear the LCD Widget
 // lcd.print(4, 0, "Hello"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")
 // lcd.print(4, 1, "World");
  // Please use timed events when LCD printintg in void loop to avoid sending too many commands
  // It will cause a FLOOD Error, and connection will be dropped

Blynk.notify("kit started");
delay(1000);
}

void loop()
{
  Blynk.run();

  analogReadResolution(12);
a = analogRead(f1);
b = analogRead(f2);
c = analogRead(f3);
  
  Serial.println(a);
  Serial.println(b);
  Serial.println(c);
Serial.println("======================================");
delay(500);

if ((a < 300)&&(b < 300))
{
  Serial.println("i have some emergency please check...");
  Blynk.notify("I HAVE SOME EMERGENCY\nPLEASE HELP ME");
  delay(1500);
digitalWrite(v0,HIGH);
digitalWrite(v1,HIGH);
digitalWrite(v2,HIGH);
digitalWrite(v3,HIGH);
digitalWrite(v4,LOW);
  delay(200);
  
digitalWrite(v0,HIGH);
digitalWrite(v1,HIGH);
digitalWrite(v2,HIGH);
digitalWrite(v3,HIGH);
digitalWrite(v4,HIGH);
delay(100);
}
else if (a < 300)
{
 Serial.println("i need water ");
  Blynk.notify("I NEED WATER\nPLEASE HELP ME");
  delay(1500);
digitalWrite(v0,HIGH);
digitalWrite(v1,LOW);
digitalWrite(v2,HIGH);
digitalWrite(v3,HIGH);
digitalWrite(v4,HIGH);
  delay(200);
  
digitalWrite(v0,HIGH);
digitalWrite(v1,HIGH);
digitalWrite(v2,HIGH);
digitalWrite(v3,HIGH);
digitalWrite(v4,HIGH);
delay(100);
}
else if (b < 300)
{
 Serial.println("i need MEDICINE ");
  Blynk.notify("I NEED MEDICINE\nPLEASE HELP ME");
  delay(1500);
digitalWrite(v0,HIGH);
digitalWrite(v1,HIGH);
digitalWrite(v2,HIGH);
digitalWrite(v3,LOW);
digitalWrite(v4,HIGH);
  delay(200);
  
digitalWrite(v0,HIGH);
digitalWrite(v1,HIGH);
digitalWrite(v2,HIGH);
digitalWrite(v3,HIGH);
digitalWrite(v4,HIGH);
delay(100);
}

else if (c < 300)
{
 Serial.println("i need FOOD ");
  Blynk.notify("I NEED FOOD\nPLEASE HELP ME");
  delay(1500);
digitalWrite(v0,HIGH);
digitalWrite(v1,HIGH);
digitalWrite(v2,LOW);
digitalWrite(v3,HIGH);
digitalWrite(v4,HIGH);
  delay(200);
  
digitalWrite(v0,HIGH);
digitalWrite(v1,HIGH);
digitalWrite(v2,HIGH);
digitalWrite(v3,HIGH);
digitalWrite(v4,HIGH);
delay(100);
} 
else
{
digitalWrite(v0,HIGH);
digitalWrite(v1,HIGH);
digitalWrite(v2,HIGH);
digitalWrite(v3,HIGH);
digitalWrite(v4,HIGH);
delay(100);
}
}
