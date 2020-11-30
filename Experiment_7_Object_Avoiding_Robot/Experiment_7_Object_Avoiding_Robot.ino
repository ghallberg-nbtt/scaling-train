/*
  Object Avoiding Robot
  Copyright 2020 Gary Hallberg
  Licensed under MIT https://github.com/ghallberg-nbtt/scaling-train/blob/master/LICENSE
*/

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

float duration; //time of HC-SR04 pulse
float distance; // calculated distance

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
}

void loop() {
  //Take reading from HC-SR04
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance = (duration / 58);
  if (distance < 30) {
    brake ("left");
    brake ("right");
    delay (250); //stop for 1/4 second
    //reverse about 40cm
    reverse ("left", 255);
    reverse ("right", 255);
    delay (1300);
    int direction = random(2); //0 = left 1 = right
    if (direction == 0) {
      forward ("right", 255);
      brake ("left");
      delay (500);
    } else  {
      forward ("left", 255);
      brake ("right");
      delay (500);
    }
  } else {
    forward ("left", 255);
    forward ("right", 255);
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
