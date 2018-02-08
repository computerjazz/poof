/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo servo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int BUTTON_PIN = 8;
int LEDPIN = 13;
int SENSOR_PIN = 4;
int SERVO_PIN = 9;

int sensorState = 0, lastState = 0;


void setup() {
  Serial.begin(115200);
  
  servo.attach(SERVO_PIN);  
  pinMode(BUTTON_PIN, INPUT);
  pinMode(SENSOR_PIN, INPUT);     
  digitalWrite(BUTTON_PIN, LOW);
  digitalWrite(SENSOR_PIN, HIGH); // turn on the pullup
  pinMode(LEDPIN, OUTPUT);      

  Serial.println("setup complete");
  
}

void loop() {
  
  if (digitalRead(BUTTON_PIN) == HIGH) {
    sweep();
  }
  
  sensorState = digitalRead(SENSOR_PIN);
  
  if (sensorState && !lastState) {
    Serial.println("Unbroken!");
  }
  
  if (!sensorState && lastState) {
    Serial.println("Broken!");
    sweep();
  }
  
  lastState = sensorState;
}

void sweep() {
    servo.write(180);
    delay(1000);
    servo.write(0);
  }
