// Modules
#include "MetricDatum.h"
#include "EncoderInterruption.h"
#include "Blynk.h"
#include "Pwm.h"
#include "Ina219.h"

MetricDatum metrics;

MetricDatum* onMetricsRequsted();
void onTerminalChanged(String data);

void setup() {

  Serial.begin(115200);
  Serial.println("Iniciando projeto");

  Serial.println("Configurando ina219...");
  setupIna219();

  Serial.println("Configurando blynk...");
  setupBlynk(1000, onTerminalChanged, onMetricsRequsted);

  Serial.println("Configurando interrupcoes...");
  setupEncoderInterruption();

  Serial.println("Configurando PWM...");
  setupPwm(1000);
  pwmSetDuty(0);
  notifyDutyCycle(0);
  
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, HIGH);
}

void onTerminalChanged(String data) {
  Serial.println(data);

  int newDutyCycle = data.toInt();

  pwmSetDuty(newDutyCycle);
  notifyDutyCycle(newDutyCycle);
}

MetricDatum* onMetricsRequsted() {

  metrics.Current = getCurrentInAmpere();
  metrics.Power = getPowerInWatts();
  metrics.RotationsPerSecond = getRotations();
  metrics.Voltage = getLoadVoltageInVolts();
  metrics.DutyCycle = pwmGetDuty();

  return &metrics;
}

void loop() {

  executeBlynkActions();
}


