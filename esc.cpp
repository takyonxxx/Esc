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
    {
        qDebug() << "Pwm Setup failed!";
        return;
    }
    else
    {       
        m_controllerHalfBridge = new ControllerHalfBridge();
    }

    gattServer = GattServer::getInstance();
    QObject::connect(gattServer, &GattServer::connectionState, this, &Esc::onConnectionStatedChanged);
    QObject::connect(gattServer, &GattServer::dataReceived, this, &Esc::onDataReceived);
    gattServer->startBleService();

}

Esc::~Esc()
{
    m_stop = true;
    if (m_controllerHalfBridge)
        delete m_controllerHalfBridge;
    delete gattServer;
}

void Esc::onConnectionStatedChanged(bool state)
{
    if(state)
    {
        qDebug() << "Bluetooth connection is succesfull.";
    }
    else
    {
        qDebug() << "Bluetooth connection lost.";
    }
}

void Esc::onDataReceived(QByteArray data)
{
    uint8_t parsedCommand;
    uint8_t rw;
    QByteArray parsedValue;
    auto parsed = parseMessage(&data, parsedCommand, parsedValue, rw);

    if(!parsed)return;

    bool ok;
    int value =  parsedValue.toHex().toInt(&ok, 16);
    QString str_value = QString(parsedValue.data());

    if(rw == mRead)
    {
        switch (parsedCommand)
        {
        case mSpeed: //speed
        {
            sendData(mSpeed, m_motorSpeed);
            break;
        }
        default:
            break;
        }
    }
    else if(rw == mWrite)
    {
        switch (parsedCommand)
        {
        case mSpeed:
        {
            m_motorSpeed = str_value.toInt();
            break;
        }
        default:
            break;
        }
    }

    auto pidInfo = QString("Motor Speed Value : ")
            + QString::number(int(m_motorSpeed));

    qDebug() << pidInfo;

    //sendString(mData, pidInfo);
}

void Esc::createMessage(uint8_t msgId, uint8_t rw, QByteArray payload, QByteArray *result)
{
    uint8_t buffer[MaxPayload+8] = {'\0'};
    uint8_t command = msgId;

    int len = message.create_pack(rw , command , payload, buffer);

    for (int i = 0; i < len; i++)
    {
        result->append(buffer[i]);
    }
}

bool Esc::parseMessage(QByteArray *data, uint8_t &command, QByteArray &value,  uint8_t &rw)
{
    MessagePack parsedMessage;

    uint8_t* dataToParse = reinterpret_cast<uint8_t*>(data->data());
    QByteArray returnValue;

    if(message.parse(dataToParse, (uint8_t)data->length(), &parsedMessage))
    {
        command = parsedMessage.command;
        rw = parsedMessage.rw;

        for(int i = 0; i< parsedMessage.len; i++)
        {
            value.append(parsedMessage.data[i]);
        }

        return true;
    }
    return false;
}

void Esc::requestData(uint8_t command)
{
    QByteArray payload;
    QByteArray sendData;
    createMessage(command, mRead, payload, &sendData);
    gattServer->writeValue(sendData);
}

void Esc::sendData(uint8_t command, uint8_t value)
{
    QByteArray payload;
    payload[0] = value;

    QByteArray sendData;
    createMessage(command, mWrite, payload, &sendData);
    gattServer->writeValue(sendData);
}

void Esc::sendString(uint8_t command, QString value)
{
    QByteArray sendData;
    QByteArray bytedata;
    bytedata = value.toLocal8Bit();
    createMessage(command, mWrite, bytedata, &sendData);
    gattServer->writeValue(sendData);
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
        qDebug("WiringPiSetup Setup ok.");
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
            //auto speed = map(m_motorSpeed, 0, 1023, 0, 255);
            m_controllerHalfBridge->write(m_motorSpeed);
            //m_controllerFullBridge->spinCW(int(m_motorSpeed), 1);
        }

        QThread::msleep(5);
    }
}
