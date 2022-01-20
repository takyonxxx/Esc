#include "esc.h"

Esc *Esc::theInstance_= nullptr;


Esc* Esc::getInstance()
{
    if (theInstance_ == nullptr)
    {
        theInstance_ = new Esc();
    }
    return theInstance_;
}

Esc::Esc(QObject *parent) : QThread(parent)
{
    if(!initwiringPi())
        qDebug() << "WiringPi not started!";
}

Esc::~Esc()
{
    m_stop = true;

    softPwmWrite(PWM1, 0);
    softPwmWrite(PWM2, 0);
    softPwmWrite(PWM3, 0);
    softPwmWrite(PWM4, 0);
    softPwmWrite(PWM5, 0);
    softPwmWrite(PWM6, 0);
}

bool Esc::initwiringPi()
{
    if (wiringPiSetupPhys () < 0)
    {
        fprintf (stderr, "Unable to setup wiringPiSetupGpio: %s\n", strerror (errno)) ;
        return false;
    }
    else
    {
        pwmLimit = 100;

        softPwmCreate(PWM1,0,pwmLimit);
        softPwmCreate(PWM2,0,pwmLimit);
        softPwmCreate(PWM3,0,pwmLimit);
        softPwmCreate(PWM4,0,pwmLimit);
        softPwmCreate(PWM5,0,pwmLimit);
        softPwmCreate(PWM6,0,pwmLimit);

        pwm1 = 0;
        pwm2 = 0;
        pwm3 = 0;
        pwm4 = 0;
        pwm5 = 0;
        pwm6 = 0;

        softPwmWrite(PWM1, pwm1);
        softPwmWrite(PWM2, pwm2);
        softPwmWrite(PWM3, pwm3);
        softPwmWrite(PWM4, pwm4);
        softPwmWrite(PWM5, pwm5);
        softPwmWrite(PWM6, pwm6);

        qDebug("wiringPi Setup ok.");
    }

    return true;
}


void Esc::setPwm()
{
    softPwmWrite(PWM1, pwm1);
    softPwmWrite(PWM2, pwm2);
    softPwmWrite(PWM3, pwm3);
    softPwmWrite(PWM4, pwm4);
    softPwmWrite(PWM5, pwm5);
    softPwmWrite(PWM6, pwm6);
}

void Esc::run()
{

    while (!m_stop)
    {
        const std::lock_guard<std::mutex> lock(mutex_loop);
        qDebug() << "running";
        QThread::msleep(1000);
    }
}
