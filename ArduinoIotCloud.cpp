#include "ArduinoIotCloud.h"
#include "Credentials.h"

#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

MetricDatum* (*onMetricsRequestedCallback)();
long sendDataIntervalMs = 0;

bool configuredIntervalHasPassed(unsigned long millisAtLastEvent);
void initProperties();

WiFiConnectionHandler ArduinoIoTPreferredConnection(WIFI_NETWORK_SSID, WIFI_NETWORK_PASSWORD);

// Public functions - they always start with Capital Letters (AKA follows PascalCase naming convention) 
void SetupArduinoIotCloud(unsigned long intervalMs, MetricDatum* (*onMetricsRequested)()) {
  Serial.println("SETUP ARDUINO IOT CLOUD");

  sendDataIntervalMs = intervalMs;
  onMetricsRequestedCallback = onMetricsRequested;

  initProperties();

  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void ExecuteArduinoIotActions() {
  ArduinoCloud.update();

  static unsigned long millisAtLastEvent = 0;

  if (!configuredIntervalHasPassed(millisAtLastEvent)) {
    return;
  }

  Serial.println("[ExecuteArduinoIotActions]");

  millisAtLastEvent = millis();
}

// "private" functions - they always start with lower case letters (AKA follows camelCase naming convention) 
bool configuredIntervalHasPassed(unsigned long millisAtLastEvent) {
  return (millis() - millisAtLastEvent) >= sendDataIntervalMs;
}

void initProperties() {

  ArduinoCloud.setBoardId(ARDUINO_IOT_DEVICE_ID);
  ArduinoCloud.setSecretDeviceKey(ARDUINO_IOT_SECRET_KEY);
  // TODO: Setup pins based on the panel I still need to create
  // ArduinoCloud.addProperty(test, READ, 1 * SECONDS, NULL);
}
