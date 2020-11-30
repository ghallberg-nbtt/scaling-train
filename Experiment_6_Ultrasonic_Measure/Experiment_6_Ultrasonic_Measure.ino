/*
  Ultrasonic Measure
  Copyright 2020 Gary Hallberg
  Licensed under MIT https://github.com/ghallberg-nbtt/scaling-train/blob/master/LICENSE
*/

#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the Arduino pin number it is connected to
// LiquidCrystal(rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd(6, 7, 11, 10, 9, 8);

// pin assignments for the HC-SR04
const int TRIG = 12;
const int ECHO = 13;
// pin assignments for switches
const int START_MEASURE = 3;
const int UNITS = 2;
const float BB_WIDTH_CM = 5.4;
const float BB_WIDTH_INCHES = 2.25;
// variables for HC-SR04
float duration; //time of HC-SR04 pulse
float distance; // calculated distance
boolean unit = true; //true = cm, false = inches
boolean previousUnitsButton = HIGH;
boolean currentUnitsButton = HIGH;
boolean updatedDistanceDisplay = false; //ensure we only update LCD once for distance
boolean updatedReadyDisplay = false; //ensure we only update LCD once for 'Ready'
boolean previousMeasureButton = LOW;
boolean currentMeasureButton = LOW;

void setup() {
  pinMode (TRIG, OUTPUT);
  pinMode (ECHO, INPUT);
  pinMode (START_MEASURE, INPUT);
  pinMode (UNITS, INPUT);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
}

void loop() {
  //check for cm or inches
  currentUnitsButton = digitalRead(UNITS); //Read the switch state
  if (previousUnitsButton != currentUnitsButton)
  {
    delay(5);  // Wait 5ms - switch debounce
    currentUnitsButton = digitalRead(UNITS);// Read switch again
  }
  if (previousUnitsButton == HIGH && currentUnitsButton == LOW) //Detect a button press
  {
    unit = !unit;  //Toggle between cm and inches
  }
  previousUnitsButton = currentUnitsButton;  //Reset button value

  //read status of measurement switch
  boolean takeMeasurement = digitalRead (START_MEASURE);
  if (takeMeasurement) {
    //take a reading from HC-SR04
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);
    duration = pulseIn(ECHO, HIGH);
    if (!updatedDistanceDisplay) {
      updatedDistanceDisplay = true; //stop flicker of display
      if (unit == true) {
        // display cm
        distance = (duration / 58) + BB_WIDTH_CM;
        lcd.clear();
        lcd.print (distance);
        lcd.print("cm");    
      } else {
        distance = (duration / 148) + BB_WIDTH_INCHES;
        lcd.clear();
        lcd.print (distance);
        lcd.print("in");
      }     
    }
  } else {
    if (!updatedReadyDisplay) {
      updatedReadyDisplay = true;
      lcd.clear(); //clear display
      lcd.print ("Ready");
    }
  }

  //stop display flicker by only updating display when needed
  currentMeasureButton = digitalRead(START_MEASURE); //Read the switch state
  if (previousMeasureButton != currentMeasureButton)
  {
    delay(5);  // Wait 5ms - switch debounce
    currentMeasureButton = digitalRead(START_MEASURE);// Read switch again
  }
  if (previousMeasureButton == HIGH && currentMeasureButton == LOW) //Detect a button release
  {
    updatedReadyDisplay = false;
    updatedDistanceDisplay = false;
  }
  previousMeasureButton = currentMeasureButton;  //Reset button value

}
