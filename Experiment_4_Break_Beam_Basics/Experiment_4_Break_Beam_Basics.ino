/*
  Break Beam Basics
  Copyright 2020 Gary Hallberg
  Licensed under MIT https://github.com/ghallberg-nbtt/scaling-train/blob/master/LICENSE
*/
const int RECEIVER_PIN = 2;
boolean sensorState = false;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); //Use internal LED
  pinMode (RECEIVER_PIN, INPUT);
  Serial.begin (9600);
  digitalWrite (LED_BUILTIN, LOW); //Turn off built-in LED
}

void loop() {
  sensorState = digitalRead (RECEIVER_PIN);
  if (!sensorState) {
    digitalWrite (LED_BUILTIN, HIGH); //Turn on LED
    Serial.println ("Beam Broken");
  } else {
    digitalWrite (LED_BUILTIN, LOW); //Turn off LED
    Serial.println ("Beam Unbroken");
  }
  delay (200); //Slow down for serial monitor
}
