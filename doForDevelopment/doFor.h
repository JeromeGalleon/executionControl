// library funtions written by farmerkeith for use with Arduino C++ IDE

// include guard
#ifndef farmerkeith_doFor_h
#define farmerkeith_doFor_h 

// usage summary:
// in loop() use the statement
/*
if (condition) doFor (duration, myFunction); 
*/
// if you wish, replace duration with a number in milliseconds
// example if (condition) doFor (1000, myFunction);
// (condition) can be a global variable (eg a bool that is either 0 or 1)
// or (condition) can be a function that returns a bool, including a function of an object / class
// (condition) has to be visible to loop() and modifiable in myFunction() (see below)
// (condition) can (or must) be set when required by some logic external to doFor.
// It can be time or event driven, whatever is required.
// Different myFunctions can be chained in series by making the STOP of one set the (condition) of the next one
// There are 3 parts to myFunction: Start, Run and Stop.
// the definition of myFunction should be like this:
/*
void myFunction (bool flag, unsigned long & Time) {
  static unsigned long startTime;
  if (flag) { // command to either start or stop
    // stop command has Time==0
    // start command has Time==millis() (must be non-zero)
    if (Time){ // start command
      startTime = Time; // save supplied Time into local variable startTime
// -------------------------------
//     put your own code here to do what you want done at START
// -------------------------------
    } else {   // stop command
      startTime = 0; // save 0 into local variable startTime
      condition = 0; // this value means doFor will stop executing from loop()
// -------------------------------
//     put your own code here to do what you want done at STOP
// -------------------------------
    } // end of if (Time)
  } else { // flag1 == 0, just send back local startTime
    Time = startTime;   // put local startTime value into supplied variable Time
                        // startTime is only updated when the test condition is true
  }
} // end of void myFunction()
*/

void doFor (unsigned long duration, void ff(bool, unsigned long&)){
  unsigned long startTime;
  ff(0, startTime);   // execute the function, 0 flag
  // 0 flag receives ff's local startTime in the parameter variable (startTime)
  // if the received value is 0, it means the function has not started yet, and needs to be started
  if (startTime==0) { // function has to be started
    startTime=millis();
    ff(1, startTime); // command to start; stores millis() into function's local memory of startTime 
  } else { // function has started, need to check if allowed time has finished
    if (millis()-startTime>=duration){ // allowed time has elapsed
      startTime=0;
      ff(1, startTime); // command to stop; 
    } else {            // allowed time has not elapsed
      // do nothing
    }
  }
} // end of void doFor() 

#endif // for #ifndef farmerkeith_doFor_h
// end of file


