/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo ccwServo;  // create servo object to control a servo
Servo cwServo;
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int BUTTON_PIN = 8;
int LEDPIN = 13;
int SENSOR_PIN = 4;
int CW_SERVO_PIN = 9;

int sensorState = 0, lastState = 0;


void setup() {
   Serial.begin(9600);
  cwServo.attach(CW_SERVO_PIN);  
  pinMode(BUTTON_PIN, INPUT);
  pinMode(SENSOR_PIN, INPUT);     
  digitalWrite(BUTTON_PIN, LOW);
  digitalWrite(SENSOR_PIN, HIGH); // turn on the pullup
  pinMode(LEDPIN, OUTPUT);      

  Serial.println("setup complete");
  
}

void loop() {

  if (digitalRead(BUTTON_PIN) == HIGH) {
    digitalWrite(LEDPIN, HIGH);  
    Serial.println("BUTTON!");
    sweep();

   } else {
        digitalWrite(LEDPIN, LOW);  

    }


     // read the state of the pushbutton value:
  sensorState = digitalRead(SENSOR_PIN);
  //Serial.println(sensorState);
  // check if the sensor beam is broken
  // if it is, the sensorState is LOW:
  if (sensorState == LOW) {     
    // turn LED on:
    //digitalWrite(LEDPIN, HIGH);  
    //˜sweep();
  } 
  else {
    // turn LED off:
    // digitalWrite(LEDPIN, LOW); 
  }
  
  if (sensorState && !lastState) {
    Serial.println("Unbroken");
  } 
  if (!sensorState && lastState) {
    Serial.println("Broken");
  }
  lastState = sensorSta0te;

}

void sweep() {
    cwServo.writeMicroseconds(500);
    delay(1000);
    cwServo.write(2500);
  }
