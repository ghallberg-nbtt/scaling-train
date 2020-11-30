/*
  The PIR Sensor
  Copyright 2020 Gary Hallberg
  Licensed under MIT https://github.com/ghallberg-nbtt/scaling-train/blob/master/LICENSE
*/

int ledPin = 2; // LED output
int pirPin = 3; // Input for HC-S501
int pirState; // The PIR output

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);
  digitalWrite(ledPin, LOW); //Turn off LED
}

void loop() {
  // put your main code here, to run repeatedly:
  pirState = digitalRead(pirPin); //read the PIR State
  digitalWrite(ledPin, pirState); //turn on LED if sensor triggered
}


