#ifndef __PWM_H__
#define __PWM_H__

#if (ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

void SetupPwm(u_int frequency);
void SetPwmDuty(u_int value);
u_int GetPwmDuty();

#endif