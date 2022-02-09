#include "controller_full_bridge.h"


ControllerFullBridge::ControllerFullBridge()
{
}

ControllerFullBridge::ControllerFullBridge(const int pinList[], bool enable_delta)
{
    AA1 = pinList[0];
    AA2 = pinList[1];
    BB1 = pinList[2];
    BB2 = pinList[3];
    CC1 = pinList[4];
    CC2 = pinList[5];

    adc = new MCP3008(CLOCK_PIN, MOSI_PIN, MISO_PIN, CS_PIN);

    this->enable_delta = enable_delta;

    pinMode(pinList[0], OUTPUT);
    pinMode(pinList[1], OUTPUT);
    pinMode(pinList[2], OUTPUT);
    pinMode(pinList[3], OUTPUT);
    pinMode(pinList[4], OUTPUT);
    pinMode(pinList[5], OUTPUT);
}


void ControllerFullBridge::calculate(unsigned long delay)
{
    if (enable_delta)
    {
        emA = adc->readADC(emfA);
        emB = adc->readADC(emfB);
        emC = adc->readADC(emfC);
        sum = (emA+emB+emC)/3;
    }

    unsigned long currentMillis = micros();


    if(currentMillis - previousMillis >= delay){

        previousMillis += delay;

        //Phase1 C-B
        switch(fase){
        case 1:
            digitalWrite(AA1,LOW);
            digitalWrite(AA2,LOW);
            digitalWrite(BB1,LOW);
            digitalWrite(CC2,LOW);
            digitalWrite(BB2,HIGH);
            digitalWrite(CC1,HIGH);
            if (enable_delta)
                delta = emA-sum;

            break;


            //Phase2 A-B
        case 2:
            digitalWrite(AA2,LOW);
            digitalWrite(BB1,LOW);
            digitalWrite(CC1,LOW);
            digitalWrite(CC2,LOW);
            digitalWrite(AA1,HIGH);
            digitalWrite(BB2,HIGH);
            if (enable_delta)
                delta = emC-sum;
            break;

            //Phase3 A-C
        case 3:
            digitalWrite(AA2,LOW);
            digitalWrite(BB1,LOW);
            digitalWrite(BB2,LOW);
            digitalWrite(CC1,LOW);
            digitalWrite(CC2,HIGH);
            digitalWrite(AA1,HIGH);
            if (enable_delta)
                delta = emB-sum;
            break;

            //Phase4 B-C
        case 4:
            digitalWrite(AA1,LOW);
            digitalWrite(AA2,LOW);
            digitalWrite(BB2,LOW);
            digitalWrite(CC1,LOW);
            digitalWrite(BB1,HIGH);
            digitalWrite(CC2,HIGH);
            if (enable_delta)
                delta = emA-sum;
            break;

            //Phase5 B-A
        case 5:
            digitalWrite(AA1,LOW);
            digitalWrite(BB2,LOW);
            digitalWrite(CC1,LOW);
            digitalWrite(CC2,LOW);
            digitalWrite(AA2,HIGH);
            digitalWrite(BB1,HIGH);
            if (enable_delta)
                delta = emC-sum;
            break;

            //Phase6 C-A
        case 6:
            digitalWrite(AA1,LOW);
            digitalWrite(BB1,LOW);
            digitalWrite(BB2,LOW);
            digitalWrite(CC2,LOW);
            digitalWrite(CC1,HIGH);
            digitalWrite(AA2,HIGH);
            if (enable_delta)
                delta = emB-sum;
            break;
        }

        if (enable_delta)
        {
            if (last_delta < 0){
                if (delta > 0)
                {
                    last_delta=delta; //save the last delta
                    fase= fase + 1;
                    if (fase > 6) {
                        fase = 1;
                    }
                }
            }//Zero cross from - to +

            if (last_delta > 0){
                if (delta < 0)
                {
                    last_delta=delta;
                    fase= fase + 1;
                    if (fase > 6) {
                        fase = 1;
                    }
                }
            }//Zero cross from + to -
        }
        else
        {
            if (fase<6){
                fase=fase+1;}
            else{
                fase=1;
            }
        }
    }//Case ends
}
