// doFor example sketch by farmerkeith

// ------------------------------------
// I want to write lines in loop() as follows:
// if (condition) doFor (duration, action);
// and have action() performed for the specified duration in milli seconds
// where action() of the type that requires start and stop changes

#include "repeatEvery.h" // library
#include "doFor.h"       // library
const long duration1 = 1000; // ms
const long duration2 = 1500; // ms
const long manager_interval=5000; // ms

class flagHolder {
    bool f1 = 1, f2 = 1;
  public:
    void on1 () {
      f1 = 1;
    }
    void off1 () {
      f1 = 0;
    }
    void on2 () {
      f2 = 1;
    }
    void off2 () {
      f2 = 0;
    }
    bool flag1() {
      return f1;
    }
    bool flag2() {
      return f2;
    }
} flag ;

void manager (bool flag1, unsigned long & Time) {
  static unsigned long lastTime;
  if (flag1) {
    lastTime = Time;
    // --------------------------------------------------
    flag.on1();
    static int counter = 0;
    ++counter;
    // if (counter % 5 == 0) flag.off2();
    Serial.print ("\n\nPerforming manager at time ");
    Serial.print((float)millis() / 1000, 3);
    Serial.print (" manager counter=");
    Serial.print(counter);
    // --------------------------------------------------
  }
  Time = lastTime;
} // end of void manager()

unsigned long action1 (bool flag1, unsigned long & Time) {
  static unsigned long startTime=0;
  static unsigned long counter = 0;
  
  if (flag1) { // command to either start or stop
    // stop command has Time==0
    // start command has Time==millis() (non-zero usually)
    if (Time){ // start command
      startTime = Time; // save supplied Time into local variable startTime
    Serial.print ("\nPerforming action1 START at time ");
    Serial.print((float)millis() / 1000, 3);
    Serial.print (" counter1=");
    Serial.print(counter/1000);
    Serial.print (",");
    Serial.print(counter%1000);
      
    } else {   // stop command
      startTime = 0; // save 0 into local variable startTime
      flag.off1();
      flag.on2();
    Serial.print ("\nPerforming action1 STOP at time ");
    Serial.print((float)millis() / 1000, 3);
    Serial.print (" counter1=");
    Serial.print(counter/1000);
    Serial.print (",");
    Serial.print(counter%1000);
    }
    // --------------------------------------------------
  } else { // flag1 == 0, just send back local startTime
    Time = startTime;   // put local startTime value into supplied variable Time
                        // startTime is only updated when the test condition is true
    ++counter;
  }
  return counter;
} // end of void action1()

unsigned long action2 (bool flag1, unsigned long & Time) {
  static unsigned long startTime=0;
  static unsigned long counter = 0;
  
  if (flag1) { // command to either start or stop
    // stop command has Time==0
    // start command has Time==millis() (non-zero usually)
    if (Time){ // start command
      startTime = Time; // save supplied Time into local variable startTime
    Serial.print ("\nPerforming action2 START at time ");
    Serial.print((float)millis() / 1000, 3);
    Serial.print (" counter2=");
    Serial.print(counter/1000);
    Serial.print (",");
    Serial.print(counter%1000);
      
    } else {   // stop command
      flag.off2();
      startTime = 0; // save 0 into local variable startTime
    Serial.print ("\nPerforming action2 STOP at time ");
    Serial.print((float)millis() / 1000, 3);
    Serial.print (" counter2=");
    Serial.print(counter/1000);
    Serial.print (",");
    Serial.print(counter%1000);
    }
    // --------------------------------------------------
  } else { // flag1 == 0, just send back local startTime
    Time = startTime;   // put local startTime value into supplied variable Time
                        // startTime is only updated when the test condition is true
    ++counter;
  }
  return counter;
} // end of void action2()

void setup() {
  Serial.begin(115200);
  Serial.print("\n\n-------------------------------------");
  Serial.print("\ndoForDevelopment, time=");
  delay(1);
  Serial.print((float)millis()/1000,3);
  
}

void loop() {
  repeatEvery(manager_interval, manager);
  if (flag.flag1()) doFor(duration1, action1);
  if (flag.flag2()) doFor(duration2, action2);
}
