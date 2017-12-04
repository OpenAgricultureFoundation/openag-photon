SYSTEM_MODE(MANUAL);

void setup() {
    // Set the speed of the I2C port on the Photon and start it.
   Wire.begin();
   Serial.begin(9600);
}

void loop() {
    bool devicesFound = false;
    String newDevices = "";
    // Step through all 127 possible I2C addresses to scan for devices on the I2C bus.
    for(int i = 1; i < 128; i++){
        // Make a general call to device at the current address to see if anything responds.
        Wire.beginTransmission(i);
        byte status = Wire.endTransmission();
        if(status == 0){
            // Device found so append it to our device list event string
            newDevices.concat("0x" + String(i, HEX) + "  ");
            devicesFound = true;
        }

    }
    if(devicesFound){
        Particle.publish("New Devices", newDevices);
        Serial.println(newDevices);
    }else{
        Particle.publish("New Devices", "No Devices Found");
        Serial.println("No Devices Found");
    }

    delay(2000);
}
