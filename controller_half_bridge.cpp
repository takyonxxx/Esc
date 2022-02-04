#include "controller_half_bridge.h"

ControllerHalfBridge::ControllerHalfBridge()
{
    pinMode(PWMA, OUTPUT);
    pinMode(PWMB, OUTPUT);
    pinMode(PWMC, OUTPUT);
    printf("Set Gpio PWM pinModes to output ok.\n");
    pwmLimit = 254;

    softPwmCreate(PWMA,0,pwmLimit);
    softPwmCreate(PWMB,0,pwmLimit);
    softPwmCreate(PWMC,0,pwmLimit);

    qDebug("SoftPwm Setup ok.");

    // Generate sin table for faster control
    sinArray.generate();
}

ControllerHalfBridge::~ControllerHalfBridge()
{
    softPwmWrite(PWMA, 0);
    softPwmWrite(PWMB, 0);
    softPwmWrite(PWMC, 0);
}

void ControllerHalfBridge::write(float angle)
{
    float real_angle = n_cycles * angle;

    int pwm1 = (float)power * (sinArray.getSinDegree(real_angle) + 1.) / 2.;
    int pwm2 = (float)power * (sinArray.getSinDegree(real_angle + 120) + 1.) / 2.;
    int pwm3 = (float)power * (sinArray.getSinDegree(real_angle + 240) + 1.) / 2.;

    softPwmWrite(PWMA, pwm1);
    softPwmWrite(PWMB, pwm2);
    softPwmWrite(PWMC, pwm3);
}

void ControllerHalfBridge::setOutputPower(int p)
{
    power = p;
}

void ControllerHalfBridge::setCycles(int n)
{
    n_cycles = n;
}
