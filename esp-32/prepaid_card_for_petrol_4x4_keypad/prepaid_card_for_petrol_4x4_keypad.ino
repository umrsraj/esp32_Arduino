#include <Keypad.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <LiquidCrystal.h>
#include <String.h>
#include <stdlib.h>

//LiquidCrystal lcd(15,2,0,4,16,17);
LiquidCrystal lcd(19, 21, 25, 33, 26, 27);

#define relay 12
#define buzzer 14
#define level 32
#define gasPin 35
#define rled 22
#define gled 13

char pswd2[5] = "4321";
char pswd1[5] = "1234";
char pswd3[5] = "0000";
char comp[5];
char keyy = '\0';

int gas = 0;
int t = 0;
int i = 0;
int count1 = 0;                                          // count = 0
char input[12];
int k = 0;
int j = 0;
int amount = 500;
int amount1 = 500;
int lv = 0;

const byte numRows = 4; //number of rows on the keypad
const byte numCols = 4; //number of columns on the keypad
char keypressed;
char keymap[numRows][numCols] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[numRows] = {15, 2, 0, 4}; //Rows 0 to 3
byte colPins[numCols] = {16, 17, 5, 18}; //Columns 0 to 3

Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);


// WiFi parameters to be configured
const char* ssid = "project12"; // Hoofdlettergevoelig
const char* password = "project123456"; // Hoofdlettergevoelig

String A ;
String B ;
String msg ;

//=============================
void match_pswd1()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" ENTER UR PSWD ");
  lcd.setCursor(0, 1);
  i = 0;
  //----------------------------------------
  while (i < 4)
  {

    comp[i] = myKeypad.getKey();

    if (comp[i] != NO_KEY)
    {
      lcd.write(comp[i]);
      Serial.print(comp[i]);
      i++;
    }
  } //---------------------------------------
  comp[i] = '\0';
}//match_pswd1
void enter_liter ()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ENTR Lts>PRESS #");
  lcd.setCursor(0, 1);
  i = 0;
  while (myKeypad.getKey() != '#')
  {
    comp[i] = myKeypad.getKey();

    if(comp[i] == '#')
    {
      break;
    }

    else if (comp[i] != NO_KEY)
    {
      lcd.write(comp[i]);
      Serial.print(comp[i]);
      i++;
    }
  }
  comp[i] = '\0';
  j = atoi(comp);
  Serial.print("j = "); Serial.println(j);
}//enter_liter
void healthcheck ()
{
  digitalWrite(gled,HIGH);
  digitalWrite(rled,HIGH);
  delay(500);
  digitalWrite(rled,LOW);
  digitalWrite(gled,LOW);
  delay(500);
  digitalWrite(gled,HIGH);
  digitalWrite(rled,HIGH);
  delay(500);
  digitalWrite(rled,LOW);
  digitalWrite(gled,LOW);
  delay(100);
}
//============================
void beep ()
{
  Serial.println("**** beep ****");
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);
  delay(100);
}



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  Serial.println("power up");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("RFID BSD PREPAID");
  lcd.setCursor( 0, 1);
  lcd.print("CARD FOR PETROL");
  delay(2000);

  Serial.print("Bezig met verbinden");
  WiFi.begin(ssid, password); // Connect to WiFi

  pinMode(buzzer, OUTPUT);
  pinMode(relay, OUTPUT);
pinMode(rled,OUTPUT);
pinMode(gled,OUTPUT);

healthcheck ();
  
  digitalWrite(relay, LOW);
  // while wifi not connected yet, print '.'
  // then after it connected, get out of the loop
  while (WiFi.status() != WL_CONNECTED) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("connecting to");
    lcd.setCursor( 2, 1);
    lcd.print(ssid);
    delay(500);
    Serial.print(".");
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("connected to ");
  lcd.setCursor( 2, 1);
  lcd.print(ssid);
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
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status

    HTTPClient http; //Declare an object of class HTTPClient
    // http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=8897056626&from=MYDREM&message=RJANED;LKSDF"); //Specify request destination

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
  Serial.println("smssssssss");
    HTTPClient http; //Declare an object of class HTTPClient
   http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=8897056626&from=MYDREM&message=WELCOME%20TO%20PROJECT"); //Specify request destination

  //http.begin("http://projectsiot.xyz/IoTProjects/PrepaidCardPetrol/petrolcard.php?a=U&b=0&c=0");

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(2000);
}
delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:

gas  = analogRead(gasPin);
Serial.print("gas = "); Serial.println(gas);
keyy = myKeypad.getKey();
Serial.print("keyy = "); Serial.println(keyy);
if (keyy != NO_KEY )
{
   // delay(6000);
}
  lcd.setCursor(0, 0);
  lcd.print("plz show card         ");
  lcd.setCursor(0, 1);
  lcd.print("                      ");

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
    Serial.print("input[10] is "); Serial.println(input[10]);
    //////////////////////////////
    if (input[10] == '8')
    {
      input[10] = '\0';
      
R:

  digitalWrite(gled,HIGH);
  digitalWrite(rled,LOW);
      match_pswd1 ();

      //----------------------COMPARE OTP PASSWORD --------------
      if (strcmp(comp, pswd1) == 0)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("PASSWORD MATCHED");
        lcd.setCursor( 0, 1);
        lcd.print(".................");
        delay(2000);
        enter_liter ();
        Serial.print("j -- "); Serial.println(j);
        amount = amount - (j * 10) ;

        if (amount < (-1))
        {
          digitalWrite(relay, LOW);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("UR BALENCE IS 0");
          lcd.setCursor(0, 1);
          lcd.print(" PLZ RECHARGE  ");
          delay(2000);
          
        }

        else if (amount > (-1))
        {

          if (amount < 101)
          {

            lcd.setCursor(4, 1);
            lcd.print("LOW BALENCE");
            delay(1500);
            
          }//if amount > -1
          A = "http://projectsiot.xyz/IoTProjects/PrepaidCardPetrol/petrolcard.php?a=A&b=";
          A += String(amount);
          A += "&c=";
          A += String(j);
          A += "&d=";
          A += String(j * 10);

          Serial.print("A = "); Serial.println(A);
          if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status

            HTTPClient http; //Declare an object of class HTTPClient
            // http.begin("http://sms.scubedigi.com/api.php?username=Myproject&password=password12&to=8897056626&from=MYDREM&message=RJANED;LKSDF"); //Specify request destination

            http.begin(A);

            int httpCode = http.GET(); //Send the request
            if (httpCode > 0) { //Check the returning code
              String payload = http.getString(); //Get the request response payload
              Serial.println(payload); //Print the response payload
            }
            http.end(); //Close connection

            delay(500);
          }// server send end

          Serial.println("sending message-----------");

msg = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=8897056626&from=MYDREM&message=";
msg += "CARD1%20DETECTED%10DEDUCTED%20AMOUNT=";
msg += String(j*10);
msg += "%10REMAINING%20BALANCE=";
msg += String(amount);
 Serial.print("msg = "); Serial.println(msg);
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   // http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=8897056626&from=MYDREM&message=RJANED;LKSDF"); //Specify request destination

  http.begin(msg);

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}

          digitalWrite (relay,HIGH);

  lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("  CARD1 MATCHED   ");  
    lcd.setCursor(0,1);
    lcd.print("RE BAL:");
       lcd.setCursor(8,1);
    lcd.print(amount);
   t = 0;
while (!((lv > 4000)||(t>j)))
{
  lv = analogRead(level);
  Serial.println(lv);
Serial.print("t = "); Serial.println(t);

t++;
Serial.println("relay -- on");
delay(500);
}    
digitalWrite (relay,LOW);
delay(5000);
   
          
        }// if amount > -1

      }//pswd1 comp
      else
      {
        
  digitalWrite(rled,HIGH);
  digitalWrite(gled,LOW);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(" WRONG PASSWORD ");
        lcd.setCursor( 0, 1);
        lcd.print(" PLZ TRY AGAIN ");
        delay(1600);
        goto R;
      }
    }//card-1
    
else if (input[10] == '4')
    {
      input[10] = '\0';
J:

  digitalWrite(gled,HIGH);
  digitalWrite(rled,LOW);
      match_pswd1 ();

      //----------------------COMPARE OTP PASSWORD --------------
      if (strcmp(comp, pswd2) == 0)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("PASSWORD MATCHED");
        lcd.setCursor( 0, 1);
        lcd.print(".................");
        delay(2000);
        enter_liter ();
        Serial.print("j -- "); Serial.println(j);
        amount1 = amount1 - (j * 10) ;

        if (amount1 < (-1))
        {
          digitalWrite(relay, LOW);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("UR BALENCE IS 0");
          lcd.setCursor(0, 1);
          lcd.print(" PLZ RECHARGE  ");
          delay(2000);
          
        }

        else if (amount1 > (-1))
        {

          if (amount1 < 101)
          {

            lcd.setCursor(4, 1);
            lcd.print("LOW BALENCE");
            delay(1500);
            
          }//if amount1 > -1
          A = "http://projectsiot.xyz/IoTProjects/PrepaidCardPetrol/petrolcard.php?a=B&b=";
          A += String(amount1);
          A += "&c=";
          A += String(j);
          A += "&d=";
          A += String(j * 10);

          Serial.print("A = "); Serial.println(A);
          if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status

            HTTPClient http; //Declare an object of class HTTPClient
            // http.begin("http://sms.scubedigi.com/api.php?username=Myproject&password=password12&to=8897056626&from=MYDREM&message=RJANED;LKSDF"); //Specify request destination

            http.begin(A);

            int httpCode = http.GET(); //Send the request
            if (httpCode > 0) { //Check the returning code
              String payload = http.getString(); //Get the request response payload
              Serial.println(payload); //Print the response payload
            }
            http.end(); //Close connection

            delay(500);
          }// server send end

          
Serial.println("sending message-----------");

msg = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9618668446&from=MYDREM&message=";
msg += "CARD2%20DETECTED%10DEDUCTED%20AMOUNT=";
msg += String(j*10);
msg += "%10REMAINING%20BALANCE=";
msg += String(amount1);

 Serial.print("msg = "); Serial.println(msg);
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   // http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=8897056626&from=MYDREM&message=RJANED;LKSDF"); //Specify request destination

  http.begin(msg);

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}


          digitalWrite (relay,HIGH);

  lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("  CARD2 MATCHED   ");  
    lcd.setCursor(0,1);
    lcd.print("RE BAL:");
       lcd.setCursor(8,1);
    lcd.print(amount1);
   t = 0;
while (!((lv > 4000)||(t>j)))
{
  lv = analogRead(level);
  Serial.println(lv);
Serial.print("t = "); Serial.println(t);

t++;
Serial.println("relay -- on");
delay(500);
}    
digitalWrite (relay,LOW);
delay(1000);
   
          
        }// if amount1 > -1

      }//pswd2 comp
      else
      {
       
  digitalWrite(rled,HIGH);
  digitalWrite(gled,LOW);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(" WRONG PASSWORD ");
        lcd.setCursor( 0, 1);
        lcd.print(" PLZ TRY AGAIN ");
        delay(1600);
        goto J;
      }
    }//card-2
    
    else
    {
      
  digitalWrite(rled,HIGH);
  digitalWrite(gled,LOW);
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
   // http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=8897056626&from=MYDREM&message=RJANED;LKSDF"); //Specify request destination

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
  }// if serial available
 
//else if (myKeypad.getKey() == 'B')
else if (keyy == 'B')
  {
    match_pswd1 ();
 
   //----------------------COMPARE OTP PASSWORD --------------
      if (strcmp(comp, pswd3) == 0)
      {
        
  digitalWrite(gled,HIGH);
  digitalWrite(rled,LOW);
  delay(100);
    lcd.clear ();
    lcd.setCursor(0,0);
    lcd.print("RECHARGE FR V-2");
    lcd.setCursor(0,1);
    i = 0;
  while (myKeypad.getKey() != '#')
  {
    comp[i] = myKeypad.getKey();

    if(comp[i] == '#')
    {
      break;
    }

    else if (comp[i] != NO_KEY)
    {
      lcd.write(comp[i]);
      Serial.print(comp[i]);
      i++;
    }//if
  }//while
  comp[i] = '\0';
  k = atoi(comp);
  amount1 = k+amount1;
  k = 0;
  Serial.print("amount1 = "); Serial.println(amount1);
   lcd.clear ();
    lcd.setCursor(0,0);
    lcd.print("RECHARGE DONE");
    lcd.setCursor(0,1);
    lcd.print("BAL FR V-2: ");
    lcd.setCursor(12,1);
    lcd.print(amount1); 
    delay(1000);
    
Serial.println("sending message-----------");

msg = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=9618668446&from=MYDREM&message=";
msg += "CARD2%20RECHARGE%20DONE%20CARD2%20BALANCE=";
msg += String(amount1);

 Serial.print("msg = "); Serial.println(msg);
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   // http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=8897056626&from=MYDREM&message=RJANED;LKSDF"); //Specify request destination

  http.begin(msg);

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}
delay(6000);
      }
      else
      {
        
  digitalWrite(rled,HIGH);
  digitalWrite(gled,LOW);
  delay(100);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("WRONG PASSWORD");
        lcd.setCursor(0,1);
        lcd.print("****************");
        delay(1600);
      }
}//else if

// else if (myKeypad.getKey() == 'A')
 else if (keyy == 'A')
  {
     match_pswd1 ();

      //----------------------COMPARE OTP PASSWORD --------------
      if (strcmp(comp, pswd3) == 0)
      {
  digitalWrite(gled,HIGH);
  digitalWrite(rled,LOW);
  delay(100);
    lcd.clear ();
    lcd.setCursor(0,0);
    lcd.print("RECHARGE FR V-1");
    lcd.setCursor(0,1);
    i = 0;
  while (myKeypad.getKey() != '#')
  {
    comp[i] = myKeypad.getKey();

    if(comp[i] == '#')
    {
      break;
    }

    else if (comp[i] != NO_KEY)
    {
      lcd.write(comp[i]);
      Serial.print(comp[i]);
      i++;
    }//if
  }//while
  comp[i] = '\0';
  k = atoi(comp);
  amount = amount + k;
  k = 0;
  Serial.print("amount = "); Serial.println(amount);
   lcd.clear ();
    lcd.setCursor(0,0);
    lcd.print("RECHARGE DONE");
    lcd.setCursor(0,1);
    lcd.print("BAL FR V-1: ");
    lcd.setCursor(12,1);
    lcd.print(amount);
    delay(1000);
    
Serial.println("sending message-----------");

msg = "http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=8897056626&from=MYDREM&message=";
msg += "CARD1%20RECHARGE%20DONE%20CARD1%20BALANCE=";
msg += String(amount);

 Serial.print("msg = "); Serial.println(msg);
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
  
    HTTPClient http; //Declare an object of class HTTPClient
   // http.begin("http://sms.scubedigi.com/api.php?username=Mydreamacd&password=Mydre@m123&to=8897056626&from=MYDREM&message=RJANED;LKSDF"); //Specify request destination

  http.begin(msg);

int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
 
delay(500);
}
delay(6000);
      }
      else
      {
  digitalWrite(rled,HIGH);
  digitalWrite(gled,LOW);
  delay(100);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("WRONG PASSWORD");
        lcd.setCursor(0,1);
        lcd.print("****************");
        delay(1600);
      }
}//else if

else if (gas > 1990)
{
  
  digitalWrite(rled,HIGH);
  digitalWrite(gled,LOW);
  delay(100);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" SMOKE DETECTED ");
  lcd.setCursor(0,1);
  lcd.print("PLEASE CHECK......");
  beep ();
  delay(1000);
}
}//loop


