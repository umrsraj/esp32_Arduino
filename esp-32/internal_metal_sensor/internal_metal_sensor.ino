/* 
 *  Copyright (c) 2018, circuits4you.com
 *  All rights reserved.
 * 
 * ESP32 Hall Sensor Example
 */

 #define LED 2
 
//================================================
//         Setup
//================================================
void setup() {
  Serial.begin(115200);
  pinMode(LED,OUTPUT);
}

//================================================
//         Loop
//================================================
void loop() { 
  int sensor = hallRead();  //Reads Hall sensor value
  Serial.print("Sensor Reading:");
  Serial.println(sensor);

  digitalWrite(LED,(sensor < 0) ? HIGH : LOW); //On board LED detects presence of magnet
  delay(500);
}
