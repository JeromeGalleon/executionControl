// repeat Every example 

// ------------------------------------
// using the library repeatEvery.h
// the library supports writing lines in loop() as follows:
// repeatEvery (repeatTime, action);
// and have action() repeated once every repeatTime milli seconds

#include "repeatEvery.h"
const long repeatTime1 = 1000; // ms
const long repeatTime2 = 200; // ms

// global variables - none

void action1 (bool flag1, unsigned long & Time) {
  static unsigned long lastTime;
  static unsigned long counter = 0;
  if (flag1) {
    lastTime = Time;
    // --------------------------------------------------
    ++counter;
    Serial.print ("\n\nPerforming action1 at time ");
    Serial.print((float)millis() / 1000, 3);
    Serial.print (" counter1=");
    Serial.print(counter);
    // --------------------------------------------------
  }
  Time = lastTime;
} // end of void action1()

void action2 (bool flag1, unsigned long & Time) {
  static unsigned long lastTime;
  if (flag1) {
    lastTime = Time;
    // --------------------------------------------------
    Serial.print ("\nPerforming action2 at time ");
    Serial.print((float)millis() / 1000, 3);
    // --------------------------------------------------
  }
  Time = lastTime;
} // end of void action2()

void setup() {
  Serial.begin(115200);
  Serial.println("\n\nrepeatEvery02");
} // end of setup()

void loop() {
  repeatEvery(repeatTime1, action1);
  repeatEvery(repeatTime2, action2);
}

