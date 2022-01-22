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
        qDebug() << "Pwm Setup failed!";
    else
    {
        const int MOTOR_PIN_LIST[6] = { PWMHA, PWMLA, PWMHB, PWMLB, PWMHC, PWMLC };
        m_controllerHalfBridge = new ControllerFullBridge(MOTOR_PIN_LIST);
    }
}

Esc::~Esc()
{
    m_stop = true;
    if (m_controllerHalfBridge)
        delete m_controllerHalfBridge;
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
        qDebug("Pwm Setup ok.");
    }

    return true;
}

void Esc::run()
{
    while (!m_stop)
    {
        const std::lock_guard<std::mutex> lock(mutex_loop);

        if (m_controllerHalfBridge)
        {
            int speed = 512;

            double torque = 1;
            //map(speed, 0, 1023, 50, 500);
            m_controllerHalfBridge->spinCW(speed, torque);
        }

        QThread::msleep(15);
    }
}
