#define PWM_PIN 16
#define PWM_CHANEL 0

#include "Pwm.h"

u_int frequency = 1000;
const int resolution = 8;

u_int currentDutyCycle = 0;

void setupPwm(u_int frequency) {
  ledcSetup(PWM_CHANEL, frequency, resolution);
  ledcAttachPin(PWM_PIN, PWM_CHANEL);
}

void pwmSetDuty(u_int dutyCycle) {

  u_int value = (int)(255.0 * dutyCycle / 100.0); 
  currentDutyCycle = dutyCycle;

  ledcWrite(PWM_CHANEL, value);
}

u_int pwmGetDuty() {
  return currentDutyCycle;
}
