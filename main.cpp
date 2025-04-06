#include <IRremote.h>
#include <LiquidCrystal.h>

IRrecv irrecv(2); //begin reciever at pin 2 (change later)
decode_results results;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //begin lcd screen and set up at respective pins

// basic setup for when device is turned on
void setup() {
  Serial.begin(9600); //have serial sensor detect baud rate of 9600
  lcd.begin(16, 2); //begin lcd display (16 columns and 2 rows)
  irrecv.enableIRIn(); //enables IR sensor
  lcd.print("Device is on!"); //prints when start just to test
}

//main loop
void loop(){
  //will keep looping until a button is pressed 
  if (irrecv.decode(&results)) { 
    unsigned long IRcode = results.value; //store results in variable IRcode
    Serial.print("Code: ");
    Serial.println(IRcode, HEX); // print out the code for the button
    //interpret(IRcode); - will be our main switch function to do things.
    irrecv.resume(); //starts looking for new readings after done
  }
}

/*void intepret (insigned long IRcode) {
  switch (Ircode){
    case <IrCode here>:
  }

}*/


