#ifndef __METRIC_DATUM_H__
#define __METRIC_DATUM_H__

#if (ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

struct MetricDatum {
  float Voltage;
  float Current;
  float RotationsPerSecond;
  float Power;
  u_int DutyCycle;
};

#endif