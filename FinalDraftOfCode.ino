#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // LCD pin setup

float maxVolt = 17;
float currVolt = 85;
float minVolt=85;

const unsigned long eventInterval = 120;
unsigned long previousTime = 0;
int num=90;
int numstep=1;
#include <Servo.h>
Servo servo;

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
  lcd.print("Blood Bag Shaker");
  lcd.setCursor(0, 1);
  lcd.print("by BearMax :D");
  servo.attach(9);

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
      if (buttonStateNow == HIGH && lastButtonState == LOW) {
        buttonState = PRESSED;
      }
      break;
    case PRESSED:
      if (buttonStateNow == HIGH) {
        buttonState = RELEASED;
        // Checks max volt
        if(currVolt <= maxVolt) {
          lcd.print(" reached max");
          currVolt = 17;
          delay(2000);
          lcd.clear();
          break;
        }
        currVolt = currVolt - 17;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Increasing");
        lcd.setCursor(0, 1);
        lcd.print("voltage by 100");
        Serial.println("Button 1 Pressed");
        lcd.clear();
         lcd.print("frequency:");
        lcd.setCursor(0, 1);
        lcd.print(1/(currVolt/17));
        lcd.print(" Hz");

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
      if (buttonStateNow2 == HIGH && lastButtonState2 == LOW) {
        buttonState2 = PRESSED;
      }
      break;
    case PRESSED:
      if (buttonStateNow2 == HIGH) {
        buttonState2 = RELEASED;
        // Checks max volt
        if(currVolt >= minVolt) {
          lcd.print(" reached min");
          currVolt = minVolt;
          delay(2000);
          lcd.clear();
          break;
        }
        currVolt = currVolt + 17;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Decreasing");
        lcd.setCursor(0, 1);
        lcd.print("voltage by 100");
        Serial.println("Button 2 Pressed");
        lcd.clear();
        lcd.print("frequency:");
        lcd.setCursor(0, 1);
        lcd.print(1/(currVolt/17));
        lcd.print(" Hz");
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
   unsigned long currentTime = millis();

  if (currentTime - previousTime >= currVolt){
    servo.write(num);
    num=num+numstep;
    if(num<=85||num>=115){
  numstep=-1*numstep;
}

    previousTime = currentTime;
  }

}