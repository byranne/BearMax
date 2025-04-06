#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //begin lcd screen and set up at respective pins

enum ButtonState {IDLE, PRESSED, RELEASED};
enum ButtonState2 {IDLE, PRESSED, RELEASED};
ButtonState buttonState = IDLE;
ButtonState buttonState2 = IDLE;

// basic setup for when device is turned on
void setup() {
  const int buttonPin = 10;
  const int buttonPin2 = 8;
  Serial.begin(9600); //have serial sensor detect baud rate of 9600
  lcd.begin(16, 2); //begin lcd display (16 columns and 2 rows)
  lcd.setcursor(0,0);
  lcd.println("Hello World")
  lcd.print("by BearMax :D")
  pinMode(buttonPin,INPUT_PULLUP);
  pinMode(buttonPin2,INPUT_PULLUP);

}

void loop() {
  static bool lastButtonState = HIGH;
  static bool lastButtonState2 = HIGH;
  bool buttonStateNow = digitalRead (buttonPin);
  bool buttonStateNow2 = digitalRead (buttonPin);

  switch (buttonState) {
    case IDLE:
      if (buttonStateNow == LOW && lastButtonState == HIGH){
        buttonState = PRESSED;
      }
      break;

    case PRESSED:
      if (buttonStateNow == LOW) {
        buttonState = RELEASED;
        lcd.print("Button1")
      }
      break;

    case RELEASED:
      if (buttonStateNow == HIGH){
        buttonState = IDLE; // Ready for next press
        lcd.clear();
      }
      break;
}

  switch (buttonState2) {
    case IDLE:
      if (buttonStateNow2 == LOW && lastButtonState2 == HIGH){
        buttonState2 = PRESSED;
      }
      break;

    case PRESSED:
      if (buttonStateNow2 == LOW) {
        buttonState2 = RELEASED;
        lcd.print("Button2")
      }
      break;

    case RELEASED:
      if (buttonStateNow2 == HIGH){
        buttonState2 = IDLE; // Ready for next press
        lcd.clear();
      }
      break;
}

lastButtonState = buttonStateNow;
lastButtonState2 = buttonStateNow2;
}


