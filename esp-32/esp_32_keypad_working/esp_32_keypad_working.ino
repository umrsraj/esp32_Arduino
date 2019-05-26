/*4x4 Matrix Keypad connected to Arduino
This code prints the key pressed on the keypad to the serial port*/

#include <Keypad.h>

const byte numRows= 4; //number of rows on the keypad
const byte numCols= 4; //number of columns on the keypad

//keymap defines the key pressed according to the row and columns just as appears on the keypad
char keymap[numRows][numCols]=
{
{'1', '2', '3', 'A'},
{'4', '5', '6', 'B'},
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};

//byte rowPins[numRows] = {D7,D6,D5,D4}; //Rows 0 to 3

//byte colPins[numCols]= {D3,D2,D1,D0}; //Columns 0 to 3

byte rowPins[numRows] = {12,13,14,27}; //Rows 0 to 3
byte colPins[numCols]= {26,25,35,34}; //Columns 0 to 3



//byte rowPins[numRows] = {15,2,0,4}; //Rows 0 to 3
//byte colPins[numCols]= {16,17,5,18}; //Columns 0 to 3

//initializes an instance of the Keypad class

Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

void setup()
{
Serial.begin(9600);
}

//If key is pressed, this key is stored in 'keypressed' variable
//If key is not equal to 'NO_KEY', then this key is printed out
//if count=17, then count is reset back to 0 (this means no key is pressed during the whole keypad scan process
void loop()
{
char keypressed = myKeypad.getKey();
if (keypressed != NO_KEY)
{
Serial.print(keypressed);
}
}
