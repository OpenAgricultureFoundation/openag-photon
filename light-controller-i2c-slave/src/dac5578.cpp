#include "dac5578.h"

bool DAC5578::begin(){
    Wire.begin();
    Wire.beginTransmission(address);
    byte status = Wire.endTransmission();
    if(status == 0){
        return true;
    }else{
        return false;
    }
}

bool DAC5578::setOutputVoltage(int channel, float voltage){
    float voltsPerStep = inputVoltage/255;

    int setPoint = voltage/voltsPerStep;
    return setOutputRaw(channel, setPoint);
}

bool DAC5578::setOutputRaw(int channel, int point){
    if(0 > channel > 7){
        return false;
    }
    if(0 > point > 255){
        return false;
    }

    Wire.beginTransmission(address);
    Wire.write(writeAndUpdateCmd + channel); // Command-Address Byte (4 bits each)
    Wire.write(point); // Data byte
    Wire.write(0x00); // Don't care byte
    byte status = Wire.endTransmission();

    if(status == 0){
        return true;
    }else{
        return false;
    }
}
