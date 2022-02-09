#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QDebug>

#include <math.h>
#include "i2cdev.h"
#include <softPwm.h>
#include <wiringPi.h>
#include <message.h>

#define CS_PIN 24
#define CLOCK_PIN 23
#define MOSI_PIN 19
#define MISO_PIN 21

//MCP3008 VDD -> 3.3V (red)
//MCP3008 VREF -> 3.3V (red)
//MCP3008 AGND -> GND (black)
//MCP3008 CLK -> pin 23 (orange)
//MCP3008 DOUT -> pin 21(yellow)
//MCP3008 DIN -> pin 19 (blue)
//MCP3008 CS -> pin 24 (violet)
//MCP3008 DGND -> GND (black)

//sudo raspi-config
//enable SPI
//ls /dev/

//1. Two MOSFET IRF3205 transistors
//2. Three TSC428CPA drivers
//3. Three power diodes(
//4. One 100uF 25V capacitor
//5. Ten 0,1uF 0805 size capacitor
//6. Six 22uF capacitor
//7. Ten 22pF capacitor
//8. 0805 size resistor: 100, 1k 2k
//9. 5V ams1117 voltage regulator
//10. Female and male pcb pins
//11. Huge 4700uF 16V capacitor
//13. Wires, conectors, solder, soldering iron...

// Arduino math function, Re-maps a number from one range to another.
static long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


#endif // CONSTANTS_H
