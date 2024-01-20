#ifndef __ENCODER_INTERRUPTION_H__
#define __ENCODER_INTERRUPTION_H__

#if (ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

void SetupEncoderInterruption();
float GetRotations();

#endif