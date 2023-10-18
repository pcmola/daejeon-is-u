#include <BleKeyboard.h>

BleKeyboard bleKeyboard;

#define TRIG_PIN 23 // ESP32 pin GIOP23 connected to Ultrasonic Sensor's TRIG pin
#define ECHO_PIN 22 // ESP32 pin GIOP22 connected to Ultrasonic Sensor's ECHO pin

float duration_us, distance_cm;

void setup() {
  // begin serial port
  Serial.begin (115200);

  // configure the trigger pin to output mode
  pinMode(TRIG_PIN, OUTPUT);
  // configure the echo pin to input mode
  pinMode(ECHO_PIN, INPUT);

  Serial.println("Starting BLE work!");
  bleKeyboard.begin();
}

void loop() {
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(ECHO_PIN, HIGH);

  // calculate the distance
  distance_cm = 0.017 * duration_us;

  // print the value to Serial Monitor
  Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  if(bleKeyboard.isConnected()) {
    if(distance_cm < 35) {
      Serial.println("Sending media volume up...");
      for(int i = 0 ; i < 10 ; i++) {
        bleKeyboard.write(KEY_MEDIA_VOLUME_UP);    //turn volume down to appropriate level
        delay(2);
      }
    }

    if(distance_cm >= 35) {
      Serial.println("Sending media volume down...");
      for(int i = 0 ; i < 10 ; i++) {
        bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);    //turn volume down to appropriate level
        delay(2);
      }
    }
  }
  delay(100);
}