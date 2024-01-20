#ifndef __ARDUINO_IOT_CLOUD__
#define __ARDUINO_IOT_CLOUD__

#if (ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "MetricDatum.h"

void SetupArduinoIotCloud(unsigned long intervalMs, void (*onTerminalChanged)(), MetricDatum* (*onMetricsRequested)());
void ExecuteArduinoIotActions();

#endif