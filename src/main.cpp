#include <Arduino.h>
#include <BleKeyboard.h>
#include <HardwareSerial.h>

#define NUM_BUTTONS 3
#define KB_NAME "PageTurner"
#define LONG_PRESS_TIME 500 // ms
#define DEBOUNCE_TIME 250

int button_pins[3] = {18, 25, 34};
int button_states[3] = {0, 0, 0};
int last_pressed[3] = {0, 0, 0};

String btn1a = "##btpt1##";
String btn1b = "##btpt2##";
String btn2a = "##btpt3##";
String btn2b = "##btpt4##";
String btn3a = "##btpt5##";
String btn3b = "##btpt6##";

String output;

int button_debounce[3][10] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
int debounce_index = -1;

BleKeyboard bleKeyboard(KB_NAME, "Ed.JD.Birchall");

int arrayCont0(int arr[], int n){
   for (int i=0; i<n; i++) {
     if (arr[i] == 0) {
       return true;
     }
   }
   return false;
}

void setup() {
  Serial.begin(9600);
  Serial.println("Starting BLE work!");
  bleKeyboard.begin();

  for (int i=0; i<NUM_BUTTONS; i++) {
    pinMode(button_pins[i], INPUT_PULLDOWN);
  }

}

void loop() {
  debounce_index += 1;
  debounce_index = debounce_index%10;
  if(bleKeyboard.isConnected()) {
    Serial.println("");
    for (int i=0; i<NUM_BUTTONS; i++) {
      Serial.print(digitalRead(button_pins[i]));

      if (digitalRead(button_pins[i]) == LOW) {
        button_debounce[i][debounce_index] = 0;
        if (button_states[i] == 0) {
          last_pressed[i] = millis();
          button_states[i] = 1;
        }

      } else if (button_states[i] == 1 && digitalRead(button_pins[i]) == HIGH) {
        button_debounce[i][debounce_index] = 1;
      }

      if (button_states[i] == 1 && !arrayCont0(button_debounce[i], 10)) {
        Serial.print(i);
        if (i==0) {
          if (millis() - last_pressed[i] > LONG_PRESS_TIME) {
            output = btn1a;
          } else {
            output = btn1b;
          }
        } else if (i==1) {
          if (millis() - last_pressed[i] > LONG_PRESS_TIME) {
            output = btn2a;
          } else {
            output = btn2b;
          }
        } else if (i==2) {
          if (millis() - last_pressed[i] > LONG_PRESS_TIME) {
            output = btn3a;
          } else {
            output = btn3b;
          }
        }
        
        bleKeyboard.print(output);  
        button_states[i] = 0;
        
      }
      
    }
  }
}