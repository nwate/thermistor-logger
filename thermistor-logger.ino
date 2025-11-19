/*
  Thermistor + LCD Thermometer
  Original example adapted from: 
  https://www.circuitbasics.com/arduino-thermistor-temperature-sensor-tutorial/

  Modifications:
  - Added LCD display
  - Added user input for F to C through a button
*/

#include <LiquidCrystal.h>

int buttonPin = 10;
bool FtoC = true;
int prevButtonState = HIGH;  

int ThermistorPin = 0;
int Vo;
float R1 = 10000;
float logR2, R2, T, Tf, Tc;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
Serial.begin(9600);
pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {

  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  Tf = (T * 9.0)/ 5.0 + 32.0; 
  Tc = T - 273.15;

  int currentState = digitalRead(buttonPin);

  // detect press (low = pressed)
  if (prevButtonState == HIGH && currentState == LOW) {
    FtoC = !FtoC;     // toggle mode
    delay(200); // debounce
  }

  prevButtonState = currentState;

  if (FtoC) {
  lcd.print("Temp = ");
  lcd.print(Tf);   
  lcd.print(" F");
  }  
  else {
  lcd.print("Temp = "); 
  lcd.print(Tc);
  lcd.print(" C"); 
  }
  delay(500);            
  lcd.clear();
}