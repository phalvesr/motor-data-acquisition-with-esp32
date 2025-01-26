#define INTERVAL_MS 2800

int pulseCount = 0;
unsigned long previousMillis = 0;

void onPulse() {
 pulseCount++;
}

void setup() {
    Serial.begin(115200);
    attachInterrupt(digitalPinToInterrupt(33), onPulse, RISING); 
}

void loop() {
    unsigned long currentMillis = millis(); 

    if (currentMillis - previousMillis >= INTERVAL_MS) {
        previousMillis = currentMillis; 

        Serial.print("Quantidade de pulsos: ");
        Serial.println(pulseCount);

        pulseCount = 0;
    }
}