// repeat Every development version
// 

// ------------------------------------
// using the library repeatEvery.h
// the library supports writing lines in loop() as follows:
// repeatEvery (repeatTime, action);
// and have action() repeated once every repeatTime milli seconds

// now I want to write in loop()
// if (flag1) repeatEvery (repeatTime1, action1);
// if (flag2) repeatEvery (repeatTime2, action2);
// and have action1 and action2 able to change the values
// of flag1 and flag2

#include "repeatEvery.h"       // tab file
const long repeatTime1 = 1000; // ms
const long repeatTime2 = 200; // ms

class flagHolder {
    bool f1 = 1, f2 = 1;
  public:
    void off1 () {
      f1 = 0;
      f2 = 1;
    }
    void off2 () {
      f1 = 1;
      f2 = 0;
    }
    bool flag1() {
      return f1;
    }
    bool flag2() {
      return f2;
    }
} flag ;
// global variables

unsigned long action1 (bool flag1, unsigned long & Time) {
  static unsigned long lastTime;
  static unsigned long counter = 0;
  if (flag1) {
    lastTime = Time;
    // --------------------------------------------------
    ++counter;
    if (!(counter % 3)) {
      flag.off1();
      // counter = 0;
    }
    Serial.print ("\n\nPerforming action1 at time ");
    Serial.print((float)millis() / 1000, 3);
    Serial.print (" counter1=");
    Serial.print(counter);
    // --------------------------------------------------
  }
  Time = lastTime;
  return counter;
} // end of void action1()

void action2 (bool flag1, unsigned long & Time, long arg1) {
  static unsigned long lastTime;
  if (flag1) {
    lastTime = Time;
    // --------------------------------------------------
    static int counter = 0;
    ++counter;
    if (counter % 5 == 0) flag.off2();
    // arg1++;
    Serial.print ("\nPerforming action2 at time ");
    Serial.print((float)millis() / 1000, 3);
    Serial.print (" arg1=");
    Serial.print(arg1);
    Serial.print (" counter2=");
    Serial.print(counter);
    // --------------------------------------------------
  }
  Time = lastTime;
} // end of void action2()

void setup() {
  Serial.begin(115200);
  Serial.println("\n\nrepeatEveryDevelopment");
} // end of setup()

void loop() {
  static unsigned long RV1;
  if (flag.flag1()) RV1=repeatEvery(repeatTime1, action1);
  if (flag.flag2()) repeatEvery(repeatTime2, action2, RV1);
}

