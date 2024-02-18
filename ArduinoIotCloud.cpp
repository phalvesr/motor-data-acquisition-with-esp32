#include "ArduinoIotCloud.h"
#include "Credentials.h"

#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

#define DEFAULT_UPDATE_INTERVAL (1 * SECONDS)

// Callbacks
MetricDatum* (*onMetricsRequestedCallback)();
void (*onTerminalChangedCallback)();

long sendDataIntervalMs = 0;

float Current = 0.0;
float Power = 0.0;
float RotationsPerSecond = 0.0;
float Voltage = 0.0;
int DutyCycle = 0.0;

float Kp = 0.0;
float Ki = 0.0;
float Kd = 0.0;

inline bool configuredIntervalHasPassed(unsigned long millisAtLastEvent);

void initProperties();
void updateMetrics();

WiFiConnectionHandler ArduinoIoTPreferredConnection(WIFI_NETWORK_SSID, WIFI_NETWORK_PASSWORD);

void SetupArduinoIotCloud(unsigned long intervalMs, void (*onTerminalChanged)(), MetricDatum* (*onMetricsRequested)()) {
  Serial.println("SETUP ARDUINO IOT CLOUD");

  sendDataIntervalMs = intervalMs;
  onMetricsRequestedCallback = onMetricsRequested;
  onTerminalChangedCallback = onTerminalChanged;

  initProperties();

  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void ExecuteArduinoIotActions() {
  ArduinoCloud.update();

  static unsigned long millisAtLastEvent = millis();

  if (!configuredIntervalHasPassed(millisAtLastEvent)) {
    return;
  }
  
  updateMetrics();
  
  millisAtLastEvent = millis();
}

inline bool configuredIntervalHasPassed(unsigned long millisAtLastEvent) {
  return (millis() - millisAtLastEvent) >= sendDataIntervalMs;
}

void updateMetrics() {
  MetricDatum* metrics = onMetricsRequestedCallback();

  Current = metrics->Current;
  Power = metrics->Power;
  RotationsPerSecond = metrics->RotationsPerSecond;
  Voltage = metrics->Voltage;
  DutyCycle = metrics->DutyCycle;
}

void initProperties() {

  ArduinoCloud.setBoardId(ARDUINO_IOT_DEVICE_ID);
  ArduinoCloud.setSecretDeviceKey(ARDUINO_IOT_SECRET_KEY);
  // TODO: Utilize the following line when needed be to update PID parameters
  // ArduinoCloud.addProperty(test, READWRITE, DEFAULT_UPDATE_INTERVAL, callback);

  ArduinoCloud.addProperty(Voltage, READ, DEFAULT_UPDATE_INTERVAL, onTerminalChangedCallback);
  ArduinoCloud.addProperty(Current, READ, DEFAULT_UPDATE_INTERVAL, onTerminalChangedCallback);
  ArduinoCloud.addProperty(RotationsPerSecond, READ, DEFAULT_UPDATE_INTERVAL, onTerminalChangedCallback);
  ArduinoCloud.addProperty(Power, READ, DEFAULT_UPDATE_INTERVAL, onTerminalChangedCallback);
  ArduinoCloud.addProperty(DutyCycle, READ, DEFAULT_UPDATE_INTERVAL, onTerminalChangedCallback);
}
