/*
  GP2Y0A41SK0F Distance Measurements
  Copyright 2020 Gary Hallberg
  Licensed under MIT https://github.com/ghallberg-nbtt/scaling-train/blob/master/LICENSE
*/

const int SENSOR_PIN = 0; //Analog pin 0 for output of sensor
const int SWITCH = 2; //cm - inch button
int ADC_Values[6]; //Array to hold ADC value
boolean previousButton = HIGH; //Variable containing the previous button state
boolean currentButton = HIGH; //Variable containing the current button state
boolean unit = true;  //Flag for cm or inches

void setup() {
  Serial.begin (9600); //Initialize serial monitor
  pinMode (SWITCH, INPUT); //Set pin 2 as input
}

void loop() {
  //Read unit switch
  currentButton = digitalRead(SWITCH); //Read the switch state
  if (previousButton != currentButton)
  {
    delay(5);  // Wait 5ms - switch debounce
    currentButton = digitalRead(SWITCH);// Read switch again
  }
  if (previousButton == HIGH && currentButton == LOW) //Detect a button press
  {
    unit = !unit;  //Toggle between cm and inches
  }
  previousButton = currentButton;  //Reset button value

  for (int i = 0; i < 6; i++) {
    ADC_Values [i] = analogRead (SENSOR_PIN); //Read sensor 6 times
    delay (5); //Small delay to allow sensor to settle
  }
  //work out total sum of readings
  int ADC_Total_Value = 0;
  for (int i = 0; i < 6; i++) {
    ADC_Total_Value = ADC_Total_Value + ADC_Values [i];
  }
  int average_ADC_Value = round (ADC_Total_Value / 6); //calculate average
  //Calculate distance
  float distance = 12.08 * pow((5 * average_ADC_Value) / 1023, -1.058);
  //Convert to cm or inches
  if (unit == true) { //unit is cm
    Serial.print(distance); //By default serial monitor prints 2 decimal places
    Serial.println("cm");
  } else { //Unit is inches
    distance = distance / 2.54;
    Serial.print(distance); //By default serial monitor prints 2 decimal places
    Serial.println("inches");
  }
  delay (500);
}
