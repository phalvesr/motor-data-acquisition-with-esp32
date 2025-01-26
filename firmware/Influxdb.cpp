#include "Influxdb.h"
#include "Credentials.h"

#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>

#if defined(ESP32)
  #include <WiFiMulti.h>
  WiFiMulti wifiMulti;
  #define DEVICE "ESP32"
#elif defined(ESP8266)s
  #include <ESP8266WiFiMulti.h>
  ESP8266WiFiMulti wifiMulti;
  #define DEVICE "ESP8266"
#endif

// Time zone info
#define TZ_INFO "UTC-3"

// Internal variables
// Influxdb client iniciado com os valores de "Credentials.h"
InfluxDBClient _client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert);
// Point _sensor("device_status");

// Internal functions
void connectToWifi();
void addConfigurationToInfluxDbClient();

void ConfigureInfluxDbClient() {
  connectToWifi();
  addConfigurationToInfluxDbClient();
}

void AddMeasure(MetricDatum *metrics) {
  Point sensor("device_status");

  sensor.addTag("motor_dc", DEVICE);
  sensor.addField("current", metrics->Current);
  sensor.addField("duty_cycle", metrics->DutyCycle);
  sensor.addField("power", metrics->Power);
  sensor.addField("rotations_per_second", metrics->RotationsPerSecond);
  sensor.addField("voltage", metrics->Voltage);

  _client.writePoint(sensor);
}

void SendMetrics() {  
  _client.flushBuffer();
}

void connectToWifi() {
  wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);

  while (wifiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  
  if (_client.validateConnection()) {
    Serial.print("Connected to InfluxDB: ");
    Serial.println(_client.getServerUrl());
  } else {
    Serial.print("InfluxDB connection failed: ");
    Serial.println(_client.getLastErrorMessage());
  }
}

void addConfigurationToInfluxDbClient() {
  _client.setWriteOptions(WriteOptions().batchSize(10));
  _client.setHTTPOptions(HTTPOptions().connectionReuse(true));

  timeSync(TZ_INFO, "pool.ntp.org", "time.nis.gov");
}
