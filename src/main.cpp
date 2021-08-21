#include <Arduino.h>
#include <BleKeyboard.h>
#include <HardwareSerial.h>

#define NUM_BUTTONS 3
#define KB_NAME "PageTurner"
#define LONG_PRESS_TIME 500 // ms
#define DEBOUNCE_TIME 100

int button_pins[3] = {18, 25, 34};
int button_states[3] = {0, 0, 0};
int last_pressed[3] = {0, 0, 0};

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
  if(bleKeyboard.isConnected()) {
    for (int i=0; i<NUM_BUTTONS; i++) {
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
  }
}