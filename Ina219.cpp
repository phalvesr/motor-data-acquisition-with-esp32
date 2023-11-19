#include "Ina219.h"

// Adafruit ina219 dependencies
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;

void setupIna219() {
  ina219.setCalibration_32V_1A();
  while(!ina219.begin());
}

float getCurrentInAmpere() {
  return ina219.getCurrent_mA() / 1000.0;
}

float getLoadVoltageInVolts() {
  return ina219.getBusVoltage_V();
}

float getPowerInWatts() {
  return ina219.getPower_mW() / 1000.0;
}


