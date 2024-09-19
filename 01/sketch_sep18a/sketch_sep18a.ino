/*
  LCD Library - display() and noDisplay()


 The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 11, en = 12, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {

  //initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  // Print a message to the LCD.
  lcd.print("_/(^-^)/-");

}


void loop() {

  //read the input on analog pin 0
  int sensorValue = analogRead(A0);
  
  float voltage = sensorValue * (5.0 / 1023.0);

   int led = sensorValue / 4;

  int brightness = map(sensorValue /10, 0, 1023, 0, 255);
  lcd.setCursor(0, 1);


  




  lcd.print("Brightness: ");
  lcd.print(led);
  
  
  analogWrite(9, brightness / 100);
  analogWrite(6, brightness);
  delay(brightness * 5);
  analogWrite(9, brightness);
  analogWrite(6, brightness / 100);
  delay(brightness * 5);
  analogWrite(6, brightness);
  delay(brightness * 5);
  analogWrite(9, brightness / 100);
  analogWrite(6, brightness);
  delay(50); //adds stability
}