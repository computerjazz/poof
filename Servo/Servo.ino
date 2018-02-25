#include <Servo.h>

int SENSOR_PIN = A0;
int LED_PIN = 13;
int SERVO_PIN = 9;

#define PREV_LEN 100
#define CUR_LEN 20
#define THRESHOLD 15

Servo servo;

int prevVals[PREV_LEN];
int prevAvg;
int curAvg;
unsigned long timer;

boolean broken = false;

void setup() {

  pinMode(SENSOR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  for (int i = 0; i < PREV_LEN; i++) {
    prevVals[i] = 0;
  }
  servo.attach(SERVO_PIN);
  servo.writeMicroseconds(1200);

  Serial.begin(115200);

}

void loop() {
  prevAvg = 0;
  curAvg = 0;

  for (int i = CUR_LEN; i < PREV_LEN; i++) {
    prevAvg += prevVals[i];
  }
  prevAvg = prevAvg / (PREV_LEN - CUR_LEN);

  for (int i = 0; i < CUR_LEN; i++) {
    curAvg += prevVals[i];
  }
  curAvg = curAvg / CUR_LEN;

  int sensorVal = analogRead(SENSOR_PIN);

  int diff = prevAvg - curAvg;
//  Serial.println(sensorVal);

  if (diff > THRESHOLD && !broken) {
    broken = true;
    timer = millis();
    // Cat broke the beam! Do something!
    Serial.println("BROKEN!");
  } else if (diff < -THRESHOLD && broken) {
    Serial.println("UNBROKEN");
    broken = false;
    if (millis() - timer < 5000) {
      Serial.println("POOF!");
      sweep();
    }
  }

  if (broken) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
 }

  // shift array and add current value
  for (int i = PREV_LEN - 1; i > 0; i--) {
    prevVals[i] = prevVals[i - 1];
  }
  prevVals[0] = sensorVal;

  delay(5);
}

void sweep() {
  servo.writeMicroseconds(1000);
  delay(100);
  servo.writeMicroseconds(1200);
}
