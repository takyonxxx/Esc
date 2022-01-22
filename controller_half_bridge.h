#ifndef CONTROLLER_THREE_PHASE_h
#define CONTROLLER_THREE_PHASE_h

#include "sinarray.h"

#ifndef PWMRANGE     //PWMRANGE is defined on some microcontrollers such as ESP8266
#define PWMRANGE 255 // Default for ATMEGA328
#endif

class ControllerHalfBridge
{
public:
  void attach(int p1, int p2, int p3); // Initialization
  void write(float angle);             // Move to a angle in degree
  void setOutputPower(int p);          // Secont a power multiplier between 0 (min) and PWMRANGE (max)
  void setCycles(int n);               // Set how many sinusoide period are needed for a revolution

private:
  SinArray sinArray;
  int pins[3];
  int power = PWMRANGE;
  int n_cycles = 8;
};

/*int val = 512; // reads the value of the potentiometer (value between 0 and 1023)
int angle = map(val, 0, 1023, 0, 180); // scale it to use it with the servo (value between 0 and 180)
setPwm3Phase(angle); // sets the brushless position according to the scaled value

QThread::msleep(15); // waits for the brushless servo to get there*/


/*for (pos = 0; pos <= 180; pos += 1)
{   // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    setPwm(pos);              // tell servo to go to position in variable 'pos'
    QThread::msleep(15);      // waits 15ms for the servo to reach the position
}
for (pos = 180; pos >= 0; pos -= 1)
{   // goes from 180 degrees to 0 degrees
    setPwm(pos);              // tell servo to go to position in variable 'pos'
    QThread::msleep(15);      // waits 15ms for the servo to reach the position
}*/
#endif
