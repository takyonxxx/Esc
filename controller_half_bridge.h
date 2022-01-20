#include "constants.h"

#pragma once
enum phaseState
{	
	high, off, low
};

struct phase
{
	phaseState nextState;
	phaseState currentState;
	short phState;
	int phaseNum;
	int phaseHPin;
	int phaseLPin;
};


class ControllerHalfBridge
{
public:
    ControllerHalfBridge();
	// pinList: WireXH, WireXL, WireYH, WireYL, WireZH, WireZL;
    ControllerHalfBridge(const int pinList[]);
	
	
	int getPosition();
	void spinCW(int speed, float torque);


	phase clacPhaseState(phase inPhase, int freq);
	void setPhaseState(phase &inPhase);

private:

	const int SWITCH_BUFFER = 1;
	const int DUTY_CYCLE_FREQ = 100; // microSeconds
	const int INTERVAL = 10000; // microSeconds
	
	double torque = 1;
	

	
	int WireYH;
	int WireYL;
	int WireZH;
	int WireZL;

	phase phaseX;
	phase phaseY;
	phase phaseZ;

	//unsigned int time = 0;

	
	

};

