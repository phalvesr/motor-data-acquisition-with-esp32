#define ACQUIRE_DATA_INTERVAL_MS 200
#define SEND_DATA_INTERVAL_MS 1000
//
#define PLUS_BUTTON 1
#define MINUS_BUTTON 2
#define START_STOP_BUTTON 3

// Modules
#include "MetricDatum.h"
#include "EncoderInterruption.h"
#include "Pwm.h"
#include "Ina219.h"
#include "Influxdb.h"

MetricDatum metrics;

unsigned long millisAtLastEvent = millis();
unsigned long millisAtDataAcquisition = millis();

// Flags
bool flagPlus = false;
bool flagMinus = false;
bool flagStartStop = false;

bool start = false;

u_int dutyCycle = 0;

MetricDatum* onMetricsRequsted();
void onTerminalChanged();
void setCurrentMode();

void tryUpdateDutyCycle();
void tryUpdateStartStop();
void executeFreeRunMode();

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
  SetPwmDuty(dutyCycle);

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
  tryUpdateDutyCycle();
  tryUpdateStartStop();

  if (!start) {
    return;
  } 

  executeFreeRunMode();
}

void tryUpdateDutyCycle() {
  if (!digitalRead(PLUS_BUTTON)) {
    flagPlus = true;
  }

  if (digitalRead(PLUS_BUTTON) && flagPlus) {
    flagPlus = false;
    dutyCycle += 10;
  }

  if (!digitalRead(MINUS_BUTTON)) {
    flagMinus = true;
  }

  if (digitalRead(MINUS_BUTTON) && flagMinus) {
    flagMinus = false;
    dutyCycle -= 10;
  }

  if (dutyCycle > 100) {
    dutyCycle = 100;
  }

  if (dutyCycle < 0) {
    dutyCycle = 0;
  }
}

void tryUpdateStartStop() {
  if (!digitalRead(START_STOP_BUTTON)) {
    flagStartStop = true;
  }

  if (digitalRead(START_STOP_BUTTON) && flagStartStop) {
    flagStartStop = false;
    start = !start;
  }
}

void executeFreeRunMode() {
  if (acquireDataIntervalHasPassed()) {
    AddMeasure(onMetricsRequsted());
    
    millisAtDataAcquisition = millis();
  }

  if (configuredIntervalHasPassed()) {
    SendMetrics();

    millisAtLastEvent = millis();
  }
}

inline bool acquireDataIntervalHasPassed() {
  return (millis() - millisAtDataAcquisition) >= ACQUIRE_DATA_INTERVAL_MS;
}

inline bool configuredIntervalHasPassed() {
  return (millis() - millisAtLastEvent) >= SEND_DATA_INTERVAL_MS;
}
