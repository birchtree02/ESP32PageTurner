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
      if(millis() - last_pressed[i] > DEBOUNCE_TIME) {
        if (digitalRead(button_pins[i]) == LOW && button_states[i] == 0) {
          last_pressed[i] = millis();
          button_states[i] = 1;

        } else if (button_states[i] == 1 && digitalRead(button_pins[i]) == HIGH) {
          Serial.print(i);

          if (i==0) {
            if (millis() - last_pressed[i] > LONG_PRESS_TIME) {
              bleKeyboard.press(KEY_SHIFT);
            }
            bleKeyboard.press(KEY_LEFT_CTRL);
            bleKeyboard.press(KEY_TAB);
          } else if (i==1) {
            for (int x=0; x<6; x++) {
              bleKeyboard.press(KEY_UP_ARROW);
              delay(100);
            }
          } else if (i==2) {
            for (int x=0; x<6; x++) {
              bleKeyboard.press(KEY_DOWN_ARROW);
              delay(100);
            }
          }
          bleKeyboard.releaseAll();
          
          
          button_states[i] = 0;
          
        }
      }
      
    }
  }
}