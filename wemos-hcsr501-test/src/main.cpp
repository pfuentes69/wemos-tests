#include <Arduino.h>

boolean active = false; //Declare intermediate variable 
int pin = D4; // Set data pin
int movement = 0;

void setup() {
  pinMode(pin, INPUT); // Set Pin7 as input 
  Serial.begin(115200); // Serial monitor at a baud rate of 115200
}

void loop() {
  movement = digitalRead(pin); // Read Sensor
  // a new movement was detected
  if(movement == HIGH && active == false) { 
    active = true;
    Serial.println("Motion detected");
  }
  // no motion after motion is detected
  if(movement == LOW && active == true) {
    active = false;
    Serial.println("No movement");
  }
  delay(100); 
}