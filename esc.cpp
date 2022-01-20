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
    if(!initPwm())
        qDebug() << "3 phase pwm not started!";
    else
        qDebug() << "3 phase pwm started.";
}

Esc::~Esc()
{
    m_stop = true;

    softPwmWrite(PWMA, 0);
    softPwmWrite(PWMB, 0);
    softPwmWrite(PWMC, 0);
}

bool Esc::initPwm()
{
    if (wiringPiSetupPhys () < 0)
    {
        fprintf (stderr, "Unable to setup wiringPiSetupGpio: %s\n", strerror (errno)) ;
        return false;
    }
    else
    {
        power = PWMRANGE;
        n_cycles = 8;
        pos = 0;

        softPwmCreate(PWMA,0,power);
        softPwmCreate(PWMB,0,power);
        softPwmCreate(PWMC,0,power);

        pwmA = 0;
        pwmB = 0;
        pwmC = 0;

        softPwmWrite(PWMA, pwmA);
        softPwmWrite(PWMB, pwmB);
        softPwmWrite(PWMC, pwmC);

        sinArray.generate();

        qDebug("Pwm Setup ok.");
    }

    return true;
}


void Esc::setPwm(float angle)
{
    float real_angle = n_cycles * angle;

    pwmA = (float)power * (sinArray.getSinDegree(real_angle) + 1.) / 2.;
    pwmB = (float)power * (sinArray.getSinDegree(real_angle + 120) + 1.) / 2.;
    pwmC = (float)power * (sinArray.getSinDegree(real_angle + 240) + 1.) / 2.;

    softPwmWrite(PWMA, pwmA);
    softPwmWrite(PWMB, pwmB);
    softPwmWrite(PWMC, pwmC);
}

void Esc::setOutputPower(int p)
{
    power = p;
}

void Esc::setCycles(int n)
{
    n_cycles = n;
}

void Esc::run()
{
    startTime = micros();

    while (!m_stop)
    {
        const std::lock_guard<std::mutex> lock(mutex_loop);

        int val = 512; // reads the value of the potentiometer (value between 0 and 1023)
        int angle = map(val, 0, 1023, 0, 180); // scale it to use it with the servo (value between 0 and 180)
        setPwm(angle); // sets the brushless position according to the scaled value

        QThread::msleep(15); // waits for the brushless servo to get there


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
    }
}
