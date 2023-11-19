#ifndef __PWM_H__
#define __PWM_H__

#if (ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

void setupPwm(u_int frequency);
void pwmSetDuty(u_int value);
u_int pwmGetDuty();

#endif