
/*
  GP2Y0A41SK0F Proximity Detector
  Copyright 2020 Gary Hallberg
  Licensed under MIT https://github.com/ghallberg-nbtt/scaling-train/blob/master/LICENSE
*/

const int GREEN_LED = 8;
const int CLEAR_LED1 = 9;
const int CLEAR_LED2 = 10;
const int CLEAR_LED3 = 11;
const int RED_LED = 12;
const int BUZZER = 3;
const int SENSOR_PIN = 0; //analog pin 0 for output of sensor
int value = 0; //holds ADC value

void setup() {
  pinMode (GREEN_LED, OUTPUT);
  pinMode (CLEAR_LED1, OUTPUT);
  pinMode (CLEAR_LED2, OUTPUT);
  pinMode (CLEAR_LED3, OUTPUT);
  pinMode (RED_LED, OUTPUT);
  Serial.begin (9600); //initialize serial monitor
}

void loop() {
  value = analogRead (SENSOR_PIN); //read sensor
  Serial.println(value);
  if (value < 141) { //ADC value for 20cm
    digitalWrite (GREEN_LED, HIGH); //Turn on green LED
    digitalWrite (CLEAR_LED1, LOW); //Turn off 1st clear LED
    digitalWrite (CLEAR_LED2, LOW); //Turn off 2nd clear LED
    digitalWrite (CLEAR_LED3, LOW); //Turn off 3rd clear LED
    digitalWrite (RED_LED, LOW); //Turn off red LED
    delay (1000);
    //no sound
    noTone(BUZZER);
  } else if (value < 163 && value >= 141) { //>16cm and <=20cm
    digitalWrite (GREEN_LED, LOW); //Turn off green LED
    digitalWrite (CLEAR_LED1, HIGH); //Turn on 1st clear LED
    digitalWrite (CLEAR_LED2, LOW); //Turn off 2nd clear LED
    digitalWrite (CLEAR_LED3, LOW); //Turn off 3rd clear LED
    digitalWrite (RED_LED, LOW); //Turn off red LED
    //1 short beep every second
    tone (BUZZER, 880, 150); // 880Hz for 0.15s
    delay (1000); //wait for 0.85 second after tone finishes
  } else if (value < 203 && value >= 163) { //>12cm and <=16cm
    digitalWrite (GREEN_LED, LOW); //Turn of green LED
    digitalWrite (CLEAR_LED1, LOW); //Turn off 1st clear LED
    digitalWrite (CLEAR_LED2, HIGH); //Turn on 2nd clear LED
    digitalWrite (CLEAR_LED3, LOW); //Turn off 3rd clear LED
    digitalWrite (RED_LED, LOW); //Turn off red LED
    //1 short beep every second
    tone (BUZZER, 880, 150); // 880Hz for 0.15s
    delay (1000); //wait for 0.85 second after tone finishes
  } else if (value < 301 && value >= 203) { //>8cm and <=12cm
    digitalWrite (GREEN_LED, LOW); //Turn off green LED
    digitalWrite (CLEAR_LED1, LOW); //Turn off 1st clear LED
    digitalWrite (CLEAR_LED2, LOW); //Turn off 2nd clear LED
    digitalWrite (CLEAR_LED3, HIGH); //Turn on 3rd clear LED
    digitalWrite (RED_LED, LOW); //Turn off red LED
    //2 short beeps every second
    tone (BUZZER, 988, 150); // 880Hz for 0.15s
    delay (300);
    tone (BUZZER, 988, 150); // 880Hz for 0.15s
    delay (700); //wait for 0.25 second
  } else if (value < 540 && value >= 301)//>4cm and <=8cm
  {
    digitalWrite (GREEN_LED, LOW); //Turn off green LED
    digitalWrite (CLEAR_LED1, LOW); //Turn off 1st clear LED
    digitalWrite (CLEAR_LED2, LOW); //Turn off 2nd clear LED
    digitalWrite (CLEAR_LED3, LOW); //Turn off 3rd clear LED
    digitalWrite (RED_LED, HIGH); //Turn on red LED
    //continuous beep
    tone (BUZZER, 988);
    delay (1000);
  }
}
