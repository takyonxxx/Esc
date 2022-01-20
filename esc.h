#ifndef ESC_H
#define ESC_H

#include <QDebug>
#include <QThread>
#include "i2cdev.h"
#include <softPwm.h>
#include <wiringPi.h>
#include "sinarray.h"

//physcal pins

#define PWMA   11
#define PWMB   13
#define PWMC   15

#define PWMRANGE 255

class Esc: public QThread
{
    Q_OBJECT

public:
    explicit Esc(QObject *parent = nullptr);
    ~Esc();

    static Esc* getInstance();   
private:

    bool initPwm();
    void setPwm(float angle);
    void setOutputPower(int p);          // Set a power multiplier between 0 (min) and PWMRANGE (max)
    void setCycles(int n);               // Set how many sinusoide period are needed for a revolution

    std::mutex mutex_loop;
    bool m_stop{false};

    int power{PWMRANGE};
    int n_cycles{8};
    int pos{0};
    int pwmA{0}, pwmB{0}, pwmC{0};

    SinArray sinArray;
    uint32_t startTime{};

    // Arduino math function, Re-maps a number from one range to another.
    long map(long x, long in_min, long in_max, long out_min, long out_max)
    {
      return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }

    static Esc *theInstance_;

protected:
    void run() override;

};

#endif // ESC_H
