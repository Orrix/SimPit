#include <Encoder.h>
#include <Joystick.h>
#include <Keypad.h>


// Rotary Encoder Inputs
#define CLK 4
#define DT 3
#define SW 2

#define VRX_PIN A3
int xAxis;
int xValue = 0;

int counter = 0;
int currentStateCLK;
int lastStateCLK;
String currentDir ="";
unsigned long lastButtonPress = 0;

// Create the Joystick
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_JOYSTICK,
  19, 0,                  // Button Count, Hat Switch Count
  true, false, false,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering



const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {0,1,2,3},
  {4,5,6,7},
  {8,9,10,11},
  {12,13,14,15}
};
byte rowPins[ROWS] = {14, 15, 16, 18}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 6, 7, 8}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
	// Set encoder pins as inputs
	pinMode(CLK,INPUT);
	pinMode(DT,INPUT);
	pinMode(SW, INPUT_PULLUP);

  Serial.begin(9600);
  lastStateCLK = digitalRead(CLK);
  Joystick.begin();
}
  
void loop(){
  char customKey = customKeypad.getKey();
  
  if (customKey){
    Serial.println(customKey);
    Joystick.setButton(customKey,1);
    delay(50);
    Joystick.setButton(customKey,0);
  }

// Read the current state of CLK
	currentStateCLK = digitalRead(CLK);

	// If last and current state of CLK are different, then pulse occurred
	// React to only 1 state change to avoid double count
	if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){

		// If the DT state is different than the CLK state then
		// the encoder is rotating CCW so decrement
		if (digitalRead(DT) != currentStateCLK) {
			counter --;
			currentDir ="CCW";
      Joystick.setButton(18,1);
      delay(10);
      Joystick.setButton(18,0);
		} else {
			// Encoder is rotating CW so increment
			counter ++;
			currentDir ="CW";
      Joystick.setButton(16,1);
      delay(10);
      Joystick.setButton(16,0);
		}

		Serial.print("Direction: ");
		Serial.print(currentDir);
		Serial.print(" | Counter: ");
		Serial.println(counter);
	}

	// Remember last CLK state
	lastStateCLK = currentStateCLK;

	// Read the button state
	int btnState = digitalRead(SW);

	//If we detect LOW signal, button is pressed
	if (btnState == LOW) {
		//if 50ms have passed since last LOW pulse, it means that the
		//button has been pressed, released and pressed again
		if (millis() - lastButtonPress > 50) {
			Serial.println("Button pressed!");
      Joystick.setButton(17,1);
      delay(10);
      Joystick.setButton(17, 0);
		}

		// Remember last button press event
		lastButtonPress = millis();
	}

    xValue = analogRead(VRX_PIN);
    Joystick.setXAxis(xValue);

	// Put in a slight delay to help debounce the reading
	delay(1);

}
