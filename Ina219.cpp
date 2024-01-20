#include "Ina219.h"

// Adafruit ina219 dependencies
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;

void SetupIna219() {
  ina219.setCalibration_32V_1A();
  while(!ina219.begin());
}

float GetCurrentInAmpere() {
  return ina219.getCurrent_mA() / 1000.0;
}

float GetLoadVoltageInVolts() {
  return ina219.getBusVoltage_V();
}

float GetPowerInWatts() {
  return ina219.getPower_mW() / 1000.0;
}


