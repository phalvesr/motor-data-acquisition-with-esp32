#define PWM_PIN 16
#define PWM_FREQUENCY 1000
#define PWM_RESOLUTION 8
#define PWM_DUTY_CYCLE_80_PCT 204

void setup() {
    ledcSetup(0, PWM_FREQUENCY, PWM_RESOLUTION);
    ledcAttachPin(PWM_PIN, 0);

    ledcWrite(0, PWM_DUTY_CYCLE_80_PCT);
}

void loop() {}