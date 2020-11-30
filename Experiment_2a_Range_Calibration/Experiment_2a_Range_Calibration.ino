
/*
  GP2Y0A41SK0F Calibration
  Copyright 2020 Gary Hallberg
  Licensed under MIT https://github.com/ghallberg-nbtt/scaling-train/blob/master/LICENSE
*/

const int SENSOR_PIN = 0; //analog pin 0 for output of sensor
int value = 0; //holds ADC value

void setup() {
  Serial.begin (9600); //initialize serial monitor
}

void loop() {
  value = analogRead (SENSOR_PIN); //read sensor
  Serial.println(value);
  delay (1000);
}
