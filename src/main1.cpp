// /**
//  * This example turns the ESP32 into a Bluetooth LE keyboard that writes the words, presses Enter, presses a media key and then Ctrl+Alt+Delete
//  */
// #include <BleKeyboard.h>
// #include <HardwareSerial.h>

// BleKeyboard bleKeyboard("PageTurner", "ed.jd.birchall");

// void setup() {
//   Serial.begin(9600);
//   Serial.println("Starting BLE work!");
//   bleKeyboard.begin();
// }

// void loop() {
//   if(bleKeyboard.isConnected()) {
//       bleKeyboard.write(KEY_RIGHT_ARROW);
//       delay(1000);
//       bleKeyboard.write(KEY_LEFT_ARROW);
//       delay(1000);
//       bleKeyboard.write(KEY_DOWN_ARROW);
//       delay(1000);
//       bleKeyboard.write(KEY_UP_ARROW);
//       delay(1000);
//   }

//   Serial.println("Waiting 5 seconds...");
//   delay(5000);
// }
