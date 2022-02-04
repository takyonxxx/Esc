#include "controller_full_bridge.h"


ControllerFullBridge::ControllerFullBridge()
{
}

ControllerFullBridge::ControllerFullBridge(const int pinList[])
{
    phaseX.phaseHPin = pinList[0];
    phaseX.phaseLPin = pinList[1];
    phaseY.phaseHPin = pinList[2];
    phaseY.phaseLPin = pinList[3];
    phaseZ.phaseHPin = pinList[4];
    phaseZ.phaseLPin = pinList[5];

    pinMode(pinList[0], OUTPUT);
    pinMode(pinList[1], OUTPUT);
    pinMode(pinList[2], OUTPUT);
    pinMode(pinList[3], OUTPUT);
    pinMode(pinList[4], OUTPUT);
    pinMode(pinList[5], OUTPUT);
}

int ControllerFullBridge::getPosition()
{
    return 0;
}

void ControllerFullBridge::spinCW(int speed, float torque)
{	    
    phaseX = clacPhaseState(phaseX, speed);
    phaseY = clacPhaseState(phaseY, speed);
    phaseZ = clacPhaseState(phaseZ, speed);

    setPhaseState(phaseX);
    setPhaseState(phaseY);
    setPhaseState(phaseZ);
}

phase ControllerFullBridge::clacPhaseState(phase inPhase, int freq)
{
    int time = micros() % INTERVAL;

    double sinWave = sin((freq * micros()) +  ( (inPhase.phaseNum * (2 * M_PI) )/3) );

    double dutyCycle = torque * sinWave;

    if ((double(time) / INTERVAL) > dutyCycle)
    {
        if (sinWave > 0)
        {
            inPhase.nextState = high;
        }
        else
        {
            inPhase.nextState = low;
        }
    }
    else
    {
        inPhase.nextState = off;
    }

    return inPhase;
}

void ControllerFullBridge::setPhaseState(phase &inPhase)
{        
    switch (inPhase.nextState)
    {
        case high: {
            digitalWrite(inPhase.phaseLPin, LOW);
            digitalWrite(inPhase.phaseHPin, HIGH);
        }

        case low: {
            digitalWrite(inPhase.phaseHPin, LOW);
            digitalWrite(inPhase.phaseLPin, HIGH);
        }

        case off: {

            digitalWrite(inPhase.phaseHPin, LOW);
            digitalWrite(inPhase.phaseLPin, LOW);
        }
    }
}
