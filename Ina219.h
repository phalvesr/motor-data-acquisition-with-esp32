#ifndef __INA_219_H__
#define __INA_219_H__

#if (ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

void setupIna219();
float getCurrentInAmpere();
float getLoadVoltageInVolts();
float getPowerInWatts();

#endif