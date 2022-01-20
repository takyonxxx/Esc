#ifndef ESC_H
#define ESC_H

#include <QThread>
#include "constants.h"
#include "controller_half_bridge.h"

class Esc: public QThread
{
    Q_OBJECT

public:
    explicit Esc(QObject *parent = nullptr);
    ~Esc();

    static Esc* getInstance();   
private:

    bool initPwm();    
    std::mutex mutex_loop;
    bool m_stop{false};
    ControllerHalfBridge *m_controllerHalfBridge{};

    static Esc *theInstance_;

protected:
    void run() override;

};

#endif // ESC_H
