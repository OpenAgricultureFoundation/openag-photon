#include "dac5578.h"

SYSTEM_MODE(MANUAL);

String message;
byte data[6] = {255,255,255,255,255,255};
DAC5578 dac;

void setup() {
  Particle.variable("message", message);
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
}

void loop() {
  delay(100);
}

void receiveEvent(int howMany) {
  // Read in data
  // TODO: add in 'register', check for 6 bytes
  int i=0;
  while (Wire.available()) {
    data[i] = Wire.read();
    i++;
  }

  // Display data for photon
  message = "";
  for(int i=0; i<6; i++){
    message += String(data[i], HEX) + " ";
  }

  // Update DAC
  dac.setOutputRaw(0, data[0]); // Channel 1 | DAC Output A
  dac.setOutputRaw(2, data[1]); // Channel 2 | DAC Output C
  dac.setOutputRaw(4, data[2]); // Channel 3 | DAC Output E
  dac.setOutputRaw(6, data[3]); // Channel 4 | DAC Output G
  dac.setOutputRaw(7, data[4]); // Channel 5 | DAC Output H
  dac.setOutputRaw(5, data[5]); // Channel 6 | DAC Output F
}
