#include "constants.h"
#include "MCP3008.h"

#define PWMHA   31
#define PWMLA   33

#define PWMHB   35
#define PWMLB   37

#define PWMHC   38
#define PWMLC   40

#pragma once

static int delta= 0;
static int last_delta= -1;

class ControllerFullBridge
{
public:
    ControllerFullBridge();
    ControllerFullBridge(const int pinList[], bool enable_delta);
    void calculate(unsigned long delay);

private:

    MCP3008 *adc{};

    unsigned long previousMillis = 0;
	
    bool enable_delta{true};

    int AA1, AA2, BB1, BB2, CC1, CC2;

    int emfA=0;
    int emfB=1;
    int emfC=2;

    int fase=1;
    int emA=0;
    int emB=0;
    int emC=0;
    int sum=0;
};

