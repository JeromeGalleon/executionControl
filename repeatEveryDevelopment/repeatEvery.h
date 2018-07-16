// repeatEvery.h development version
// library funtions written by farmerkeith for use with Arduino C++ IDE
// include guard
#ifndef farmerkeith_repeatEvery_h
#define farmerkeith_repeatEvery_h

// usage summary:
// in loop() use the statement
// repeatEvery (myTimer, myFunction); // if you wish, just replace myTimer with a number in milliseconds
// example repeatEvery (1000, myFunction);
// the definition of myFunction should be like this:
// void myFunction (bool flag, unsigned long & Time) {
//   static unsigned long lastTime;
//   if (flag) {
//     lastTime = Time;
// -------------------------------
//     put your own code here to do what you want done every myTimer milliseconds
// -------------------------------
//   }                             // end of functional procedure
//   Time = lastTime;              // required by repeatEvery
// } // end of void myFunction
// 
// myFunction can return nothing (void), an unsigned long, or a float.
// that is why there are 3 versions of repeatEvery in this header file.

void repeatEvery (unsigned long repeatTime, float ff(bool, unsigned long&)){
  unsigned long lastTime;
  float v1= ff(0, lastTime); // execute the function, 0 flag
     // 0 flag writes the current value of ff's local lastTime into the parameter variable
  if (millis()-lastTime>=repeatTime){ // time has elapsed
      while (millis()-lastTime>=repeatTime) lastTime += repeatTime; // update latest execution time
      v1= ff(1,lastTime); // execute the function, 1 flag
     // 1 flag updates ff's local lastTime to the new value
  }
}

unsigned long repeatEvery (unsigned long repeatTime, unsigned long ff(bool, unsigned long&)){
  unsigned long lastTime;
  unsigned long v1= ff(0, lastTime); // execute the function, 0 flag
     // 0 flag writes the current value of ff's local lastTime into the parameter variable
  if (millis()-lastTime>=repeatTime){ // time has elapsed
      while (millis()-lastTime>=repeatTime) lastTime += repeatTime; // update latest execution time
      v1= ff(1,lastTime); // execute the function, 1 flag
     // 1 flag updates ff's local lastTime to the new value
  }
  return v1;
}

void repeatEvery (unsigned long repeatTime, void ff(bool, unsigned long&)){
  unsigned long lastTime;
  ff(0, lastTime); // execute the function, 0 flag
     // 0 flag writes the current value of ff's local lastTime into the parameter variable
  if (millis()-lastTime>=repeatTime){ // time has elapsed
      while (millis()-lastTime>=repeatTime) lastTime += repeatTime; // update latest execution time
      ff(1,lastTime); // execute the function, 1 flag
     // 1 flag updates ff's local lastTime to the new value
  }
}

void repeatEvery (unsigned long repeatTime, void ff(bool, unsigned long&, long), long arg1){
  unsigned long lastTime;
  ff(0, lastTime, arg1); // execute the function, 0 flag
     // 0 flag writes the current value of ff's local lastTime into the parameter variable
  if (millis()-lastTime>=repeatTime){ // time has elapsed
      while (millis()-lastTime>=repeatTime) lastTime += repeatTime; // update latest execution time
      ff(1,lastTime, arg1); // execute the function, 1 flag
     // 1 flag updates ff's local lastTime to the new value
  }
}

#endif // for #ifndef farmerkeith_repeatEvery_h
// end of file



