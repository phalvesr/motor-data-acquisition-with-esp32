#ifndef __INFLUXDB_H__
#define __INFLUXDB_H__

#include "MetricDatum.h"

void ConfigureInfluxDbClient();
void AddMeasure(MetricDatum *metrics);
void SendMetrics();
void SendCurrentMode(char currentMode);
#endif