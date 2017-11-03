/* @file EventSerialKeypad.pde
 || @version 1.0
 || @author Alexander Brevig
 || @contact alexanderbrevig@gmail.com
 ||
 || @description
 || | Demonstrates using the KeypadEvent.
 || #
 */
#include <Keypad.h>

#define A 12
#define B 11
#define C 10
#define D 9
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'}
};

byte rowPins[ROWS] = {2, 3, 4, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 7, 8}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
byte ledPin = 13; 

boolean blink = false;
boolean ledPin_state;

void setup(){
    Serial.begin(9600);
    pinMode(ledPin, OUTPUT);              // Sets the digital pin as output.
    digitalWrite(ledPin, HIGH);           // Turn the LED on.
    ledPin_state = digitalRead(ledPin);   // Store initial LED state. HIGH when LED is on.
    keypad.addEventListener(keypadEvent); // Add an event listener for this keypad
    pinMode(D, OUTPUT);
    pinMode(C, OUTPUT);
    pinMode(B, OUTPUT);
    pinMode(A, OUTPUT);
}

void loop(){
    char key = keypad.getKey();
    if (key) {
        Serial.println(key);
        switch(key) {
          case '0': 
            pinSet(1, 1, 1, 1);
            break;
          case '1':
            pinSet(0, 0, 0, 1);
            break;
          case '2': 
            pinSet(0, 0, 1, 0);
            break;
          case '3':
            pinSet(0, 0, 1, 1); 
            break;
          case '4': 
            pinSet(0, 1, 0, 0);
            break;
          case '5':
            pinSet(0, 1, 0, 1); 
            break;
          case '6': 
            pinSet(0, 1, 1, 0);
            break;
          case '7': 
            pinSet(0, 1, 1, 1);
            break;
          case '8': 
            pinSet(1, 0, 0, 0);
            break;
          case '9': 
            pinSet(1, 0, 0, 1);
            break;
          case '*': 
            pinSet(1, 0, 1, 0);
            break;
          case '#': 
            pinSet(1, 0, 1, 1);
            break;
          default:
            pinSet(0, 0, 0, 0);
        }
    }
    if (blink){
        digitalWrite(ledPin,!digitalRead(ledPin));    // Change the ledPin from Hi2Lo or Lo2Hi.
        delay(100);
    }
}

// Taking care of some special events.
void keypadEvent(KeypadEvent key){
    switch (keypad.getState()){
    case PRESSED:
        if (key == '#') {
            digitalWrite(ledPin,!digitalRead(ledPin));
            ledPin_state = digitalRead(ledPin);        // Remember LED state, lit or unlit.
        }
        break;

    case RELEASED:
        if (key == '*') {
            digitalWrite(ledPin,ledPin_state);    // Restore LED state from before it started blinking.
            blink = false;
        }
        break;

    case HOLD:
        if (key == '*') {
            blink = true;    // Blink the LED when holding the * key.
        }
        break;
    }
}

void pinSet(int a, int b, int c, int d) {
  if(a == 1)
    digitalWrite(A, HIGH);
   else
    digitalWrite(A, LOW);

   if(b == 1)
    digitalWrite(B, HIGH);
   else
    digitalWrite(B, LOW);

   if(c == 1)
    digitalWrite(C, HIGH);
   else
    digitalWrite(C, LOW);

   if(d == 1)
    digitalWrite(D, HIGH);
   else
    digitalWrite(D, LOW);
}

