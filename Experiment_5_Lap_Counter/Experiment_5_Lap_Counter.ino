/*
  Lap Counter Timer
  Copyright 2020 Gary Hallberg
  Licensed under MIT https://github.com/ghallberg-nbtt/scaling-train/blob/master/LICENSE
*/

#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the Arduino pin number it is connected to
// LiquidCrystal(rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd(6, 7, 11, 10, 9, 8);

const int TOTAL_LAPS = 12;
const int SENSOR = 2; //beam sensor on pin 2
const long minute = 60000; //60000 milliseconds in a minute
const int second =  1000; //1000 milliseconds in a second
const int tenthSecond = 100; //100 milliseconds in a tenth of a second
const int hundredthSecond = 10; //10 milliseconds in a hundredth of a second
int currentSensorState = LOW;
int lastSensorState = HIGH;
long lastTimer;
long currentTimer;
long updateTimer;
long startTimer; //timer at start
int lapCount = 0;
String elapsedTime; //total time

void setup() {
  pinMode (SENSOR, INPUT);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.clear(); //clear display
  lcd.print ("Ready");
  Serial.begin(9600);
}

void loop() {
  //Wait until beam is broken to start
  currentSensorState = digitalRead(SENSOR);
  if (currentSensorState == LOW && lastSensorState == HIGH) {
    lastSensorState = currentSensorState; //read only 1 beam break state
    startTimer = millis (); //set the initial timer
    lastTimer = startTimer;
    updateTimer = startTimer;
    //rewrite display
    lcd.clear();
    lcd.print ("Time");
    lcd.setCursor (0, 1); //move to second row
    lcd.print ("Lap");
    lcd.setCursor (4, 1); //move to second row
    lcd.print (lapCount);
    Serial.println("Start");
    while (lapCount < TOTAL_LAPS) {
      currentTimer = millis(); //get current time
      if (currentTimer > (updateTimer + 10)) {
        //updating total time only if at least 0.01s has passed
        elapsedTime = formatTime (currentTimer); //format at MM:SS.00
        lcd.setCursor (5, 0); //move to column 6 first row
        lcd.print (elapsedTime);
        updateTimer = millis (); // ready for next 10ms increment
      }
      //Look for beam break
      currentSensorState = digitalRead(SENSOR);
      if (currentSensorState == LOW && lastSensorState == HIGH) {
        //beam broken
        lapCount++; //increment lap count
        long lapTime = currentTimer - lastTimer; //work out laptime
        lastTimer = millis(); //reset lap timer
        String formattedLapTime = formatTime (lapTime); //format at MM:SS.00
        lcd.setCursor (4, 1); //move to second row
        lcd.print (lapCount);
        lcd.setCursor (8, 1);
        lcd.print (formattedLapTime); //print laptime
        Serial.print("Lap ");
        Serial.print (lapCount);
        Serial.print (" ");
        Serial.println (formattedLapTime);
        if (lapCount == 12) {
          Serial.print ("Total time: ");
          Serial.println (elapsedTime);
        }
      }
      lastSensorState = currentSensorState; //read only 1 beam break state
    }
  }

}


String formatTime(long timeToFormat) {

  int minutes = timeToFormat / minute; //number of minutes
  //the remainder from minutes division (in milliseconds) divided by seconds gives the full seconds
  int seconds = (timeToFormat % minute) / second;
  //the remainder from seconds division (in milliseconds) divided by tenthSecond to give full tenths of second
  int tenthSeconds =  ((timeToFormat % minute) % second) / tenthSecond ;
  //the remainder from tenth of a second division (in milliseconds) modulo hundredthSecond to give full hundredth of a second
  int hundredthSeconds = (((timeToFormat % minute) % second) % tenthSecond) / hundredthSecond;
  char formattedTime [9]; //8 chars needed for string + 1 null char
  // minutes + ":" + seconds + "." + hundredthSeconds
  sprintf_P(formattedTime, PSTR("%02d:%02d.%d%d"), minutes, seconds, tenthSeconds, hundredthSeconds);
  return formattedTime;
}
