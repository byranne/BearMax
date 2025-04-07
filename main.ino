#include <LiquidCrystal.h>
#include <Servo.h>

// Display two strings on LCD (line 1 and line 2)
void printLCD(const String& line1, const String& line2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
}

// Display string, float value, and unit on LCD
void printLCD(const String& line1, float value, const String& unit) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(value);
  lcd.print(" ");
  lcd.print(unit);
}

// LCD and servo object initialization
LiquidCrystal lcd(7, 6, 5, 4, 3, 2); 
Servo servo;

// Button pin definitions
const int buttonPin = 10;
const int buttonPin2 = 8;

// Motor delay limits and initial delay (controls speed)
float minDelay = 17;
float maxDelay = 85;
float currDelay = maxDelay;

// Variables for timing and servo movement
unsigned long previousTime = 0;
int servoAngle = 90;        // starting angle
int angleStep = 1;          // amount of angle change per update

// States for each button (for debouncing and detecting press/release)
enum ButtonState { IDLE, PRESSED, RELEASED };
ButtonState buttonState = IDLE;
ButtonState buttonState2 = IDLE;

// Setup runs once at power-up
void setup() {
  Serial.begin(9600);             // start serial monitor
  lcd.begin(16, 2);               // initialize LCD size
  printLCD("Blood Bag Shaker", "by BearMax :D");  // splash screen
  servo.attach(9);               // attach servo to pin 9

  pinMode(buttonPin, INPUT_PULLUP);   // left button
  pinMode(buttonPin2, INPUT_PULLUP);  // right button
}

// Main loop runs forever
void loop() {
  // Track button states to detect press transitions
  static bool lastButtonState = HIGH;
  static bool lastButtonState2 = HIGH;

  // Read button pin states
  bool buttonStateNow = digitalRead(buttonPin);
  bool buttonStateNow2 = digitalRead(buttonPin2);

  // Left button logic (increase speed)
  switch (buttonState) {
    case IDLE:
      if (buttonStateNow == HIGH && lastButtonState == LOW) {
        buttonState = PRESSED;  // detect rising edge
      }
      break;

    case PRESSED:
      if (buttonStateNow == HIGH) {
        buttonState = RELEASED;
        currDelay -= 17;  // decrease delay = increase frequency
        if (currDelay < minDelay) {
          lcd.print(" reached max");  // already at max speed
          currDelay = minDelay;
          delay(2000);
          printLCD("frequency:", 1 / (currDelay / 17), "Hz");
          break;
        }
        printLCD("frequency:", 1 / (currDelay / 17), "Hz");
      }
      break;

    case RELEASED:
      if (buttonStateNow == LOW) {
        buttonState = IDLE;  // wait for next press
      }
      break;
  }

  // Right button logic (decrease speed)
  switch (buttonState2) {
    case IDLE:
      if (buttonStateNow2 == HIGH && lastButtonState2 == LOW) {
        buttonState2 = PRESSED;
      }
      break;

    case PRESSED:
      if (buttonStateNow2 == HIGH) {
        buttonState2 = RELEASED;
        currDelay += 17;  // increase delay = reduce frequency
        if (currDelay > maxDelay) {
          lcd.print(" reached min");  // already at min speed
          currDelay = maxDelay;
          delay(2000);
          printLCD("frequency:", 1 / (currDelay / 17), "Hz");
          break;
        }
        printLCD("frequency:", 1 / (currDelay / 17), "Hz");
      }
      break;

    case RELEASED:
      if (buttonStateNow2 == LOW) {
        buttonState2 = IDLE;
      }
      break;
  }

  // Update button history for next loop
  lastButtonState = buttonStateNow;
  lastButtonState2 = buttonStateNow2;

  // Servo movement logic (oscillating motion)
  unsigned long currentTime = millis();
  if (currentTime - previousTime >= currDelay) {
    servo.write(servoAngle);  // move servo to current angle
    servoAngle += angleStep;  // increment angle

    // Reverse direction when limits are reached
    if (servoAngle <= 85 || servoAngle >= 115) {
      angleStep = -angleStep;
    }

    previousTime = currentTime; // update last movement time
  }
}
