#ifndef __BLYNK_H__
#define __BLYNK_H__

#if (ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "MetricDatum.h"

void executeBlynkActions();
void setupBlynk(unsigned long interval, void (*onTerminalEvent)(String), MetricDatum* (*onIntervalMetricsProvider)());
void notifyDutyCycle(unsigned int dutyCycle);
#endif