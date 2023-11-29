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

 https://docs.arduino.cc/learn/electronics/lcd-displays

*/

// include the library code:

#include <LiquidCrystal.h>
#define AOUT_PIN A0
#define RELAY_PIN 7

int watertime = 5;  // how long it will be watering (in seconds)
int waittime = 1;   // how long to wait between watering (in minutes)
int currentMode = 0;
int dryClicked = 0, lowClicked = 0, medClicked = 0, highClicked = 0;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  pinMode(RELAY_PIN, OUTPUT);
  lcd.begin(16, 2);
  pinMode(6, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  Serial.begin(9600);
}

void loop() {
  int moisturePin = analogRead(AOUT_PIN);                  // read the analog value from sensor
  int moisture = (100 - ((moisturePin / 1023.00) * 100));  //convert analog value to percentage

  Serial.println(moisture);

  if (digitalRead(6) == HIGH) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("You Chose 0-20% ");
    lcd.setCursor(0, 1);
    lcd.print("Water Level     ");
    currentMode = 1;
    dryClicked++;
    lowClicked = 0, medClicked = 0, highClicked = 0;
    delay(500);
  } else if (digitalRead(8) == HIGH) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("You Chose 21-40%");
    lcd.setCursor(0, 1);
    lcd.print("Water Level     ");
    currentMode = 2;
    lowClicked++;
    dryClicked = 0, medClicked = 0, highClicked = 0;
    delay(500);
  } else if (digitalRead(9) == HIGH) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("You Chose 41-60%");
    lcd.setCursor(0, 1);
    lcd.print("Water Level     ");
    currentMode = 3;
    medClicked++;
    lowClicked = 0, dryClicked = 0, highClicked = 0;
    delay(500);
  } else if (digitalRead(10) == HIGH) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("You Chose 61-80%");
    lcd.setCursor(0, 1);
    lcd.print("Water Level     ");
    currentMode = 4;
    highClicked++;
    lowClicked = 0, medClicked = 0, dryClicked = 0;
    delay(500);
  }

  if (currentMode == 0) {
    lcd.setCursor(0, 0);
    lcd.print("Choose Your     ");
    lcd.setCursor(0, 1);
    lcd.print("Plant Type      ");
    digitalWrite(RELAY_PIN, HIGH);
  } else {
    if (dryClicked == 2 || lowClicked == 2 || medClicked == 2 || highClicked == 2) {
      switch (currentMode) {
        case 1:
          lcd.setCursor(0, 0);
          lcd.print("Dry Plant       ");
          if (moisture < 10) {
            lcd.setCursor(0, 1);
            lcd.print("Dispensing...   ");
            digitalWrite(RELAY_PIN, LOW);
          } else {
            digitalWrite(RELAY_PIN, HIGH);
            lcd.setCursor(0, 1);
            lcd.print("No water needed ");
          }

          break;

        case 2:
          lcd.setCursor(0, 0);
          lcd.print("Low Water Plant ");
          if (moisture < 20) {
            lcd.setCursor(0, 1);
            lcd.print("Dispensing...   ");
            digitalWrite(RELAY_PIN, LOW);
          } else {
            digitalWrite(RELAY_PIN, HIGH);
            lcd.setCursor(0, 1);
            lcd.print("No water needed ");
          }
          break;
        case 3:
          lcd.setCursor(0, 0);
          lcd.print("Mid Water Plant ");
          if (moisture < 40) {
            lcd.setCursor(0, 1);
            lcd.print("Dispensing...   ");
            digitalWrite(RELAY_PIN, LOW);
          } else {
            digitalWrite(RELAY_PIN, HIGH);
            lcd.setCursor(0, 1);
            lcd.print("No water needed ");
          }
          break;

        case 4:
          lcd.setCursor(0, 0);
          lcd.print("Moist Plant Type");
          if (moisture < 60) {
            lcd.setCursor(0, 1);
            lcd.print("Dispensing...   ");
            digitalWrite(RELAY_PIN, LOW);
          } else {
            lcd.setCursor(0, 1);
            lcd.print("No water needed ");
            digitalWrite(RELAY_PIN, HIGH);
          }

          break;
      }
    } else if (dryClicked > 2 || lowClicked > 2 || medClicked > 2 || highClicked > 2) {
      currentMode = 0;
      digitalWrite(RELAY_PIN, HIGH);
      dryClicked = 0, lowClicked = 0, dryClicked = 0, highClicked = 0;
    }
  }
}