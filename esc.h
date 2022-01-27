#ifndef ESC_H
#define ESC_H

#include <QThread>
#include "constants.h"
#include "gattserver.h"
#include "controller_full_bridge.h"

class Esc: public QThread
{
    Q_OBJECT

public:
    explicit Esc(QObject *parent = nullptr);
    ~Esc();

    static Esc* getInstance();   
private:

    bool initPwm();
    bool parseMessage(QByteArray *data, uint8_t &command, QByteArray &value, uint8_t &rw);
    void createMessage(uint8_t msgId, uint8_t rw, QByteArray payload, QByteArray *result);

    void requestData(uint8_t command);
    void sendData(uint8_t command, uint8_t value);
    void sendString(uint8_t command, QString value);

    std::mutex mutex_loop;
    bool m_stop{false};
    float m_motorSpeed{0};
    ControllerFullBridge *m_controllerHalfBridge{};
    GattServer *gattServer{};
    Message message{};

    static Esc *theInstance_;
private slots:
    void onConnectionStatedChanged(bool state);
    void onDataReceived(QByteArray data);
protected:
    void run() override;

};

#endif // ESC_H
