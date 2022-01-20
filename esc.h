#ifndef ESC_H
#define ESC_H

#include <QDebug>
#include <QThread>

//#include "i2cdev.h"
//#include <softPwm.h>
//#include <wiringPi.h>


//physcal pins
#define PWM1   3
#define PWM2   5
#define PWM3   7
#define PWM4   11
#define PWM5   13
#define PWM6   15

class Esc: public QThread
{
    Q_OBJECT

public:
    explicit Esc(QObject *parent = nullptr);
    ~Esc();

    static Esc* getInstance();   
private:

    bool initwiringPi();
    void setPwm();

    std::mutex mutex_loop;
    bool m_stop{false};

    int pwmLimit{0};
    int pwm1{0}, pwm2{0}, pwm3{0}, pwm4{0}, pwm5{0}, pwm6{0};

    bool mpu_test{false};

    uint32_t timer{};

    static Esc *theInstance_;

protected:
    void run() override;

};

#endif // ESC_H
