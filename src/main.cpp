#include <Arduino.h>
#include <BleKeyboard.h>
#include <HardwareSerial.h>

#include <chrono>

#define NUM_BUTTONS 3
#define KB_NAME "PageTurner"
#define LONG_PRESS_TIME 500 // ms
#define DEBOUNCE_TIME 100

int button_pins[3] = {18, 25, 34};
int button_states[3] = {0, 0, 0};
int last_pressed[3] = {0, 0, 0};
std::chrono::high_resolution_clock::time_point t0;
std::chrono::high_resolution_clock::time_point t1;

BleKeyboard bleKeyboard(KB_NAME, "Ed.JD.Birchall");

void setup() {
  Serial.begin(9600);
  Serial.println("Starting BLE work!");
  bleKeyboard.begin();

  for (int i=0; i<NUM_BUTTONS; i++) {
    pinMode(button_pins[i], INPUT_PULLDOWN);
  }

}

void loop() {
  // if(bleKeyboard.isConnected()) {
    // Serial.println();
    for (int i=0; i<NUM_BUTTONS; i++) {
      // 
      // Serial.print(digitalRead(button_pins[i]));
      // 
      if(millis() - last_pressed[i] > 100) {
        last_pressed[i] = millis();
        if (digitalRead(button_pins[i]) == LOW && button_states[i] == 0) {
          button_states[i] = 1;
          Serial.print(i);
        } else {
          if (button_states[i] == 1 && digitalRead(button_pins[i]) == HIGH) {
            button_states[i] = 0;
          }
        }
      }
      
    }
  // }
}


// t0 = std::chrono::high_resolution_clock::now();
// while (digitalRead(button_pins[i]) == LOW) {} // wait for button to be unpressed
// t1 = std::chrono::high_resolution_clock::now();
// Serial.println(i);
// if (std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count() > LONG_PRESS_TIME) {

// } else {
  
// }