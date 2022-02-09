
#ifndef MCP3008_h
#define MCP3008_h
#include "constants.h"

class MCP3008
{
  public:
    MCP3008();
    MCP3008(int clockpin, int mosipin, int misopin, int cspin);
    int readADC(int adcnum);
  private:
      int _clockpin, _mosipin, _misopin, _cspin;
};


#endif
