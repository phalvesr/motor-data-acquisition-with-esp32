#define ACQUIRE_DATA_INTERVAL_MS 200
#define SEND_DATA_INTERVAL_MS 1000

// Modules
#include "MetricDatum.h"
#include "EncoderInterruption.h"
#include "Pwm.h"
#include "Ina219.h"
#include "Influxdb.h"

MetricDatum metrics;
unsigned long millisAtLastEvent = millis();
unsigned long millisAtDataAcquisition = millis();

MetricDatum* onMetricsRequsted();
void onTerminalChanged();

void setup() {

  Serial.begin(115200);
  Serial.println("Iniciando projeto");

  Serial.println("Configurando ina219...");
  SetupIna219();

  Serial.println("Configurando InfluxDB...");
  ConfigureInfluxDbClient();

  Serial.println("Configurando interrupcoes...");
  SetupEncoderInterruption();

  Serial.println("Configurando PWM...");
  SetupPwm(1000);
  SetPwmDuty(100);

  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, HIGH);
}

MetricDatum* onMetricsRequsted() {
  metrics.Current = GetCurrentInAmpere();
  metrics.Power = GetPowerInWatts();
  metrics.RotationsPerSecond = GetRotations();
  metrics.Voltage = GetLoadVoltageInVolts();
  metrics.DutyCycle = GetPwmDuty();

  return &metrics;
}

bool start = false;

void loop() {

  if (!acquireDataIntervalHasPassed()) {
    return;
  } else {
    
  }

  if (!configuredIntervalHasPassed()) {
    return;
  }

  SendMetrics(onMetricsRequsted());

  millisAtLastEvent = millis();
}

inline bool acquireDataIntervalHasPassed() {
  return (millis() - millisAtDataAcquisition) >= ACQUIRE_DATA_INTERVAL_MS;
}

inline bool configuredIntervalHasPassed() {
  return (millis() - millisAtLastEvent) >= SEND_DATA_INTERVAL_MS;
}
