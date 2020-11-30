
/*
  Follow Me Robot
  Copyright 2020 Gary Hallberg
  Licensed under MIT https://github.com/ghallberg-nbtt/scaling-train/blob/master/LICENSE
*/

#include <Servo.h>

//HC-SR04 pins
const int TRIG = 2;
const int ECHO = 3;
//H-Bridge pins
const int ENABLE1 = 5;
const int INPUT1 = 8;
const int INPUT2 = 9;
const int ENABLE2 = 6;
const int INPUT3 = 10;
const int INPUT4 = 11;
//servo pin
const int SERVO = 12; //Servo on Pin 12

float distanceLeft = 0;
float distanceRight = 0;
Servo myServo;

void setup() {
  //Set up HC-SR04
  pinMode (TRIG, OUTPUT);
  pinMode (ECHO, INPUT);
  //Set H-Bridge
  pinMode (ENABLE1, OUTPUT);
  pinMode (INPUT1, OUTPUT);
  pinMode (INPUT2, OUTPUT);
  pinMode (ENABLE2, OUTPUT);
  pinMode (INPUT3, OUTPUT);
  pinMode (INPUT4, OUTPUT);
  //Force stop both motors
  brake ("left");
  brake ("right");
  myServo.attach(SERVO);
}

void loop() {
  myServo.write (60); //move servo to the left
  distanceLeft = distanceReading ();
  delay (100);
  myServo.write (120); //move servo to the right
  distanceRight = distanceReading ();
  delay (100);

  if ((distanceLeft > 70) && (distanceRight > 70)) {
    //stop and wait for object
    brake ("left");
    brake ("right");
  }  else if ((distanceLeft >= 25) && (distanceRight >= 25)) {
    //follow object
    forward ("left", 255);
    forward ("right", 255);
    delay (100);
  } else if ((distanceLeft <= 15) && (distanceRight <= 15)) {
    //back away from object
    reverse ("left", 255);
    reverse ("right", 255);
    delay (100);
  } else if ((distanceRight - 3) > distanceLeft) {
    //turn left
    forward ("right", 255);
    brake ("left");
    delay (10);
  } else if ((distanceRight + 3) < distanceLeft) {
    //turn right
    forward ("left", 255);
    brake ("right");
    delay (10);
  } else {
    brake ("left");
    brake ("right");
  }
}

void forward (String motor, int speed)
{

  if (motor == "left") {
    digitalWrite (ENABLE1, LOW); //Disable H-Bridge
    digitalWrite (INPUT1, HIGH);
    digitalWrite (INPUT2, LOW);
    analogWrite (ENABLE1, speed); //PWM to drive left motor
    Serial.println (speed);
  } else {
    digitalWrite (ENABLE2, LOW); //Disable H-Bridge
    digitalWrite (INPUT3, HIGH);
    digitalWrite (INPUT4, LOW);
    analogWrite (ENABLE2, speed); //PWM to drive right motor
    Serial.println (speed);
  }
}

//Drive motor backward at the specified speed (0 – 255)
void reverse (String motor, int speed)
{
  if (motor == "left") {
    digitalWrite (ENABLE1, LOW); //Disable H-Bridge
    digitalWrite (INPUT1, LOW);
    digitalWrite (INPUT2, HIGH);
    analogWrite (ENABLE1, speed); //PWM to drive left motor
  } else {
    digitalWrite (ENABLE2, LOW); //Disable H-Bridge
    digitalWrite (INPUT3, LOW);
    digitalWrite (INPUT4, HIGH);
    analogWrite (ENABLE2, speed); //PWM to drive right motor
  }
}

//Stop motor
void brake (String motor)
{
  if (motor == "left") {
    digitalWrite (ENABLE1, LOW); //Disable H-Bridge
    digitalWrite (INPUT1, LOW);
    digitalWrite (INPUT2, LOW);
    analogWrite (ENABLE1, HIGH); //Brake left motor
  } else {
    digitalWrite (ENABLE2, LOW); //Disable H-Bridge
    digitalWrite (INPUT3, LOW);
    digitalWrite (INPUT4, LOW);
    analogWrite (ENABLE2, HIGH); //Brake right motor
  }
}

float distanceReading () {
  float duration; //time of HC-SR04 pulse
  float distance; // calculated distance
  //Take reading from HC-SR04
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance = (duration / 58);
  return distance;
}
