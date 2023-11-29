// Blynk virtual pins
#define BLYNK_VOLTAGE_PIN V0
#define BLYNK_CURRENT_PIN V1
#define BLYNK_POWER_PIN V2
#define BLYNK_ROTATION_PIN V3
#define BLYNK_TERMINAL_PIN V4
#define BLYNK_DUTY_CYCLE_PIN V5

#include "MetricDatum.h"
// Blynk template credentials
#include "Credentials.h"
// Blynk specific dependencies
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

BlynkTimer timer;

MetricDatum* (*getMetrics)();
void (*onTerminalEventHandler)(String);

const float millissecondsOnAMinute = 60 * 1000;
float fromRotationsPerSecondToRotationsToMinuteFactor = 0;

BLYNK_WRITE(BLYNK_TERMINAL_PIN) {
  onTerminalEventHandler(param.asString());
}

void onBlynkInterval() {

  Blynk.beginGroup();

  MetricDatum* datum = getMetrics();

  Blynk.virtualWrite(BLYNK_VOLTAGE_PIN, datum->Voltage);
  Blynk.virtualWrite(BLYNK_CURRENT_PIN, datum->Current);
  Blynk.virtualWrite(BLYNK_ROTATION_PIN, datum->RotationsPerSecond * fromRotationsPerSecondToRotationsToMinuteFactor);
  Blynk.virtualWrite(BLYNK_POWER_PIN, datum->Power);

  Blynk.endGroup();

  Serial.printf("V: %f | A: %f | R: %f | P: %f \n", datum->Voltage, datum->Current, datum->RotationsPerSecond, datum->Power);
}

void setupBlynk(unsigned long interval, void (*onTerminalEvent)(String), MetricDatum* (*onIntervalMetricsProvider)()) {

  getMetrics = onIntervalMetricsProvider;
  onTerminalEventHandler = onTerminalEvent;

  fromRotationsPerSecondToRotationsToMinuteFactor = millissecondsOnAMinute / interval;

  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_NETWORK_SSID, WIFI_NETWORK_PASSWORD);
  timer.setInterval(interval, onBlynkInterval);
}

void notifyDutyCycle(unsigned int dutyCycle) {

  Blynk.virtualWrite(BLYNK_TERMINAL_PIN, String("Duty cycle setted at " + String(dutyCycle) + "%"));
}

void executeBlynkActions() {
  Blynk.run();
  timer.run();
}

