#define SEND_DATA_INTERVAL_MS 1000

// Modules
#include "MetricDatum.h"
#include "EncoderInterruption.h"
#include "Pwm.h"
#include "Ina219.h"
#include "Influxdb.h"

MetricDatum metrics;
unsigned long millisAtLastEvent = millis();

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
  SetPwmDuty(0);

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

void loop() {
  if (!configuredIntervalHasPassed()) {
    return;
  }

  Serial.println("Acao");
  SendMetrics(onMetricsRequsted());

  millisAtLastEvent = millis();
}

bool configuredIntervalHasPassed() {
  return (millis() - millisAtLastEvent) >= SEND_DATA_INTERVAL_MS;
}
