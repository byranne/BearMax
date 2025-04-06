#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // LCD pin setup

// Button pins
const int buttonPin = 10;
const int buttonPin2 = 8;

// Button states
enum ButtonState { IDLE, PRESSED, RELEASED };
ButtonState buttonState = IDLE;
ButtonState buttonState2 = IDLE;

// Setup runs once
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Hello World");
  lcd.setCursor(0, 1);
  lcd.print("by BearMax :D");

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
}

// Loop runs forever
void loop() {
  static bool lastButtonState = HIGH;
  static bool lastButtonState2 = HIGH;

  bool buttonStateNow = digitalRead(buttonPin);
  bool buttonStateNow2 = digitalRead(buttonPin2);

  // First Button
  switch (buttonState) {
    case IDLE:
      if (buttonStateNow == LOW && lastButtonState == HIGH) {
        buttonState = PRESSED;
      }
      break;
    case PRESSED:
      if (buttonStateNow == HIGH) {
        buttonState = RELEASED;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Button 1 Pressed");
        Serial.println("Button 1 Pressed");
      }
      break;
    case RELEASED:
      if (buttonStateNow == LOW) {
        buttonState = IDLE;
      }
      break;
  }

  // Second Button
  switch (buttonState2) {
    case IDLE:
      if (buttonStateNow2 == LOW && lastButtonState2 == HIGH) {
        buttonState2 = PRESSED;
      }
      break;
    case PRESSED:
      if (buttonStateNow2 == HIGH) {
        buttonState2 = RELEASED;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Button 2 Pressed");
        Serial.println("Button 2 Pressed");
      }
      break;
    case RELEASED:
      if (buttonStateNow2 == LOW) {
        buttonState2 = IDLE;
      }
      break;
  }

  // Update previous states
  lastButtonState = buttonStateNow;
  lastButtonState2 = buttonStateNow2;
}


