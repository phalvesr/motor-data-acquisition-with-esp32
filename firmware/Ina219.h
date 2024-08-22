#ifndef __INA_219_H__
#define __INA_219_H__

#if (ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

void SetupIna219();
float GetCurrentInAmpere();
float GetLoadVoltageInVolts();
float GetPowerInWatts();

#endif
