#include "controller_three_phase.h"

void ControllerThreePhase::attach(int p1, int p2, int p3)
{
  // Set output pins
  pins[0] = p1;
  pins[1] = p2;
  pins[2] = p3;
  pinMode(p1, OUTPUT);
  pinMode(p2, OUTPUT);
  pinMode(p3, OUTPUT);

  // Generate sin table for faster control
  sinArray.generate();
}

void ControllerThreePhase::write(float angle)
{
  float real_angle = n_cycles * angle;

  int pwm1 = (float)power * (sinArray.getSinDegree(real_angle) + 1.) / 2.;
  int pwm2 = (float)power * (sinArray.getSinDegree(real_angle + 120) + 1.) / 2.;
  int pwm3 = (float)power * (sinArray.getSinDegree(real_angle + 240) + 1.) / 2.;

  // Set PWMs
  analogWrite(pins[0], pwm1);
  analogWrite(pins[1], pwm2);
  analogWrite(pins[2], pwm3);
}

void ControllerThreePhase::setOutputPower(int p)
{
  power = p;
}

void ControllerThreePhase::setCycles(int n)
{
  n_cycles = n;
}
