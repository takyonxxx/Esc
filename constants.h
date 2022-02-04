#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QDebug>

#include <math.h>
#include "i2cdev.h"
#include <softPwm.h>
#include <wiringPi.h>
#include <message.h>

// Arduino math function, Re-maps a number from one range to another.
static long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


#endif // CONSTANTS_H
