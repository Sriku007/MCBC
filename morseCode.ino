/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int CLOCK_DELAY = 738;
const int inpPin = 10;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(inpPin, INPUT);
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
}

void loop() {
  // put your main code here, to run repeatedly:
  while(digitalRead(inpPin) == LOW){}
  delay(CLOCK_DELAY);
  int sensorVal[8] = {0};
  for(int i=0; i<7; i++){
    int inp = (int)(digitalRead(inpPin) == HIGH);
    sensorVal[i] = inp;
    delay(CLOCK_DELAY);  
    Serial.println("GOT\t" + String(inp));
  }
  Serial.println(decode(sensorVal));
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(decode(sensorVal));
}

char decode(int sensorVal[])
{
  char ans;
  int start = 0;
  int end=-1;
  for (int i = 6; i >= start; i--)
  {
    if (sensorVal[i - 1] == 1 && sensorVal[i] == 0)
    {
      end = i - 1;
      break;
    }
  }
  int length = end - start;
  if(end==-1||length==0)
  {
    return '@';
  }
  if (length > 5)
  {
    ans = '!';
  }
   else if (length == 1)
  {
    if (sensorVal[start] == 0)
    {
      ans = 'E';
    }
    if (sensorVal[start] == 1)
    {
      ans = 'T';
    }
  }
  else if (length == 2)
  {
    if (sensorVal[start] == 0 && sensorVal[start + 1] == 0)
    {
      ans = 'I';
    }
    else if (sensorVal[start] == 0 && sensorVal[start + 1] == 1)
    {
      ans = 'A';
    }
    else if (sensorVal[start] == 1 && sensorVal[start + 1] == 0)
    {
      ans = 'N';
    }
    else if (sensorVal[start] == 0 && sensorVal[start + 1] == 1)
    {
      ans = 'M';
    }
  }
  else if (length == 3)
  {
    if (sensorVal[start] == 0 && sensorVal[start + 1] == 0 && sensorVal[start + 2] == 0)
    {
      ans = 'S';
    }
    else if (sensorVal[start] == 0 && sensorVal[start + 1] == 0 && sensorVal[start + 2] == 1)
    {
      ans = 'U';
    }
    else if (sensorVal[start] == 0 && sensorVal[start + 1] == 1 && sensorVal[start + 2] == 0)
    {
      ans = 'R';
    }
    else if (sensorVal[start] == 0 && sensorVal[start + 1] == 1 && sensorVal[start + 2] == 1)
    {
      ans = 'W';
    }
    else if (sensorVal[start] == 1 && sensorVal[start + 1] == 0 && sensorVal[start + 2] == 0)
    {
      ans = 'D';
    }
    else if (sensorVal[start] == 1 && sensorVal[start + 1] == 0 && sensorVal[start + 2] == 1)
    {
      ans = 'K';
    }
    else if (sensorVal[start] == 1 && sensorVal[start + 1] == 1 && sensorVal[start + 2] == 0)
    {
      ans = 'G';
    }
    else if (sensorVal[start] == 1 && sensorVal[start + 1] == 1 && sensorVal[start + 2] == 1)
    {
      ans = 'O';
    }
  }

  else if (length == 4)
  {
    if (sensorVal[start] == 0 && sensorVal[start + 1] == 0 && sensorVal[start + 2] == 0 && sensorVal[start + 3] == 0)
    {
      ans = 'H';
    }
    else if (sensorVal[start] == 1 && sensorVal[start + 1] == 0 && sensorVal[start + 2] == 0 && sensorVal[start + 3] == 0)
    {
      ans = 'B';
    }
    else if (sensorVal[start] == 1 && sensorVal[start + 1] == 0 && sensorVal[start + 2] == 1 && sensorVal[start + 3] == 0)
    {
      ans = 'C';
    }
    else if (sensorVal[start] == 0 && sensorVal[start + 1] == 0 && sensorVal[start + 2] == 1 && sensorVal[start + 3] == 0)
    {
      ans = 'F';
    }
    else if (sensorVal[start] == 0 && sensorVal[start + 1] == 1 && sensorVal[start + 2] == 1 && sensorVal[start + 3] == 1)
    {
      ans = 'J';
    }
    else if (sensorVal[start] == 0 && sensorVal[start + 1] == 1 && sensorVal[start + 2] == 0 && sensorVal[start + 3] == 0)
    {
      ans = 'L';
    }
    else if (sensorVal[start] == 0 && sensorVal[start + 1] == 1 && sensorVal[start + 2] == 1 && sensorVal[start + 3] == 0)
    {
      ans = 'P';
    }
    else if (sensorVal[start] == 1 && sensorVal[start + 1] == 1 && sensorVal[start + 2] == 0 && sensorVal[start + 3] == 1)
    {
      ans = 'Q';
    }
    else if (sensorVal[start] == 0 && sensorVal[start + 1] == 0 && sensorVal[start + 2] == 0 && sensorVal[start + 3] == 1)
    {
      ans = 'V';
    }
    else if (sensorVal[start] == 1 && sensorVal[start + 1] == 0 && sensorVal[start + 2] == 0 && sensorVal[start + 3] == 1)
    {
      ans = 'X';
    }
    else if (sensorVal[start] == 1 && sensorVal[start + 1] == 0 && sensorVal[start + 2] == 1 && sensorVal[start + 3] == 1)
    {
      ans = 'Y';
    }
    else if (sensorVal[start] == 1 && sensorVal[start + 1] == 1 && sensorVal[start + 2] == 0 && sensorVal[start + 3] == 0)
    {
      ans = 'Z';
    }
    else
    {
      ans = '@';
    }
  }
  else if (length == 5)
  {
    if (sensorVal[start] == 0 && sensorVal[start + 1] == 0 && sensorVal[start + 2] == 0 && sensorVal[start + 3] == 0 && sensorVal[start + 4] == 0)
    {
      ans = '5';
    }
    else if (sensorVal[start] == 1 && sensorVal[start + 1] == 0 && sensorVal[start + 2] == 0 && sensorVal[start + 3] == 0 && sensorVal[start + 4] == 0)
    {
      ans = '6';
    }
    else if (sensorVal[start] == 1 && sensorVal[start + 1] == 1 && sensorVal[start + 2] == 0 && sensorVal[start + 3] == 0 && sensorVal[start + 4] == 0)
    {
      ans = '7';
    }
    else if (sensorVal[start] == 1 && sensorVal[start + 1] == 1 && sensorVal[start + 2] == 1 && sensorVal[start + 3] == 0 && sensorVal[start + 4] == 0)
    {
      ans = '8';
    }
    else if (sensorVal[start] == 1 && sensorVal[start + 1] == 1 && sensorVal[start + 2] == 1 && sensorVal[start + 3] == 1 && sensorVal[start + 4] == 0)
    {
      ans = '9';
    }
    else if (sensorVal[start] == 1 && sensorVal[start + 1] == 1 && sensorVal[start + 2] == 1 && sensorVal[start + 3] == 1 && sensorVal[start + 4] == 1)
    {
      ans = '0';
    }
    else if (sensorVal[start] == 0 && sensorVal[start + 1] == 0 && sensorVal[start + 2] == 0 && sensorVal[start + 3] == 0 && sensorVal[start + 4] == 1)
    {
      ans = '4';
    }
    else if (sensorVal[start] == 0 && sensorVal[start + 1] == 0 && sensorVal[start + 2] == 0 && sensorVal[start + 3] == 1 && sensorVal[start + 4] == 1)
    {
      ans = '3';
    }
    else if (sensorVal[start] == 0 && sensorVal[start + 1] == 0 && sensorVal[start + 2] == 1 && sensorVal[start + 3] == 1 && sensorVal[start + 4] == 1)
    {
      ans = '2';
    }
    else if (sensorVal[start] == 0 && sensorVal[start + 1] == 1 && sensorVal[start + 2] == 1 && sensorVal[start + 3] == 1 && sensorVal[start + 4] == 1)
    {
      ans = '1';
    }
    else
    {
      ans = '@';
    }
  }
  return ans;
}
