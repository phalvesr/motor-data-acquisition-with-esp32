#ifndef __INFLUXDB_H__
#define __INFLUXDB_H__

#include "MetricDatum.h"

void ConfigureInfluxDbClient();
void SendMetrics(MetricDatum *metrics);
#endif