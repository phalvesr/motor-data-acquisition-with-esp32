#define ENCODER_INPUT_A 32
#define ENCODER_INPUT_B 33

#include "EncoderInterruption.h"

int encoderChanges = 0;

// Should be checked on the motor specification
const float PULSES_PER_REVOLUTION = 823.1;

void onEncoderInterruption() {

  int encoderAState = digitalRead(ENCODER_INPUT_A);
  int encoderBState = digitalRead(ENCODER_INPUT_B);

  if (encoderAState == HIGH && encoderBState == LOW) {
    encoderChanges--;
  } else if(encoderAState == LOW && encoderBState == HIGH) {
    encoderChanges++;
  }
}

void setupEncoderInterruption() {

  attachInterrupt(digitalPinToInterrupt(ENCODER_INPUT_A), onEncoderInterruption, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER_INPUT_B), onEncoderInterruption, RISING);
}

float getRotations() {

  float changesSinceLastCall = encoderChanges;
  encoderChanges = 0;

  float revolutions = changesSinceLastCall / PULSES_PER_REVOLUTION;

  return revolutions;
}
