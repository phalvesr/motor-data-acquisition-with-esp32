// Modules
#include "MetricDatum.h"
#include "EncoderInterruption.h"
#include "Pwm.h"
#include "Ina219.h"
#include "ArduinoIotCloud.h"

#include <LiquidCrystal.h>

MetricDatum metrics;

MetricDatum* onMetricsRequsted();
void onTerminalChanged();

void setup() {

  Serial.begin(115200);
  Serial.println("Iniciando projeto");

  Serial.println("Configurando ina219...");
  SetupIna219();

  Serial.println("Configurando Arduino IOT Cloud...");
  SetupArduinoIotCloud(1000, onTerminalChanged, onMetricsRequsted);

  Serial.println("Configurando interrupcoes...");
  SetupEncoderInterruption();

  Serial.println("Configurando PWM...");
  SetupPwm(1000);
  SetPwmDuty(0);

  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, HIGH);
}

void onTerminalChanged() {
  Serial.println("Changed values");
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
  ExecuteArduinoIotActions();
}
