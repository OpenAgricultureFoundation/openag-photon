#include "Particle.h"

class DAC5578{
  public:
    bool begin();
    bool setOutputVoltage(int channel, float voltage);
    bool setOutputRaw(int channel, int point);

private:
  int address = 0x4c;
  float inputVoltage = 3.3;
  int writeAndUpdateCmd = 0x30;
};
