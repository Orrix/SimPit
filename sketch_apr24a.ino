#include <Joystick.h>
#include <Keypad.h>
// Create the Joystick
Joystick_ Joystick;

//Joystick_ buttonCount=16; 
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {5,6,7,8}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {15,14,16,10}; //connect to the column pinouts of the keypad
 
//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
 
void setup(){
  Serial.begin(9600);
  Joystick.begin();

  int lastButtonState[4] = {0,0,0,0};

}
  
void loop(){


  char key = customKeypad.getKey();
   if (key) {
    
  Serial.println(key );
  //check to see if what key is pressed, output joystickbutton
  switch (key ) {
 
  case '1':
      Serial.println("Joystick.setButton(1)");
      Joystick.setButton(0,1);
      break;
  case '2':
      Serial.println("Joystick.setButton(2)");
      Joystick.setButton(1,1);
    break;  
  case '3':
      Serial.println("Joystick.setButton(3");
      Joystick.setButton(2,1);
    break;

  case '4':
      Serial.println("Joystick.setButton(4)");
      Joystick.setButton(3,1);
    break;
  case '5':
      Serial.println("Joystick.setButton(5)");
      Joystick.setButton(4,1);
    break;
  case '6':
      Serial.println("Joystick.setButton(6)");
      Joystick.setButton(5,1);
    break;
  case '7':
      Serial.println("Joystick.setButton(7)");
      Joystick.setButton(6,1);
    break;
  case '8':
      Serial.println("Joystick.setButton(8)");
      Joystick.setButton(7,1);
   break;
  case '*':
    Serial.println("Joystick.setButton(10)");
    Joystick.setButton(8,1);
    break;
  case '#':
    Serial.println("Joystick.setButton(11)");
    Joystick.setButton(9,1);
    break;
  case 'A':
    Serial.println("Joystick.setButton(12)");
    Joystick.setButton(10,1);
    break;
  case 'B':
    Serial.println("Joystick.setButton(13)");
    Joystick.setButton(11,1);
    break;
    case 'C':
    Serial.println("Joystick.setButton(14)");
    Joystick.setButton(12,1);
     break;
  case '9':
    Serial.println("Joystick.setButton(9)");
    Joystick.setButton(13,1);
    break;
  case 'D':
    Serial.println("Joystick.setButton(15)");
    Joystick.setButton(14,1);
     break;
  case '0':
    Serial.println("Joystick.setButton(16)");
    Joystick.setButton(15,1);
    break;
 default:
    Serial.println("Joystick.setButton()");
 /*     Joystick.setButton(0,0);
      Joystick.setButton(1,0);
      Joystick.setButton(2,0);
      Joystick.setButton(3,0);
      Joystick.setButton(4,0);
      Joystick.setButton(5,0);
      Joystick.setButton(6,0);
      Joystick.setButton(7,0);
      Joystick.setButton(8,0);
      Joystick.setButton(9,0);
      Joystick.setButton(10,0);
      Joystick.setButton(11,0);
      Joystick.setButton(12,0);
      Joystick.setButton(13,0);
      Joystick.setButton(14,0);
      Joystick.setButton(15,0);
      */
    break;
      delay(50);
  }
}
}