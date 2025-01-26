#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;

void setup() {
 Serial.begin(115200);
 
 while (!ina219.begin());
 ina219.setCalibration_32V_1A();
}
void loop() {
    float busVoltage = ina219.getBusVoltage_V();
    float current_mA = ina219.getCurrent_mA();
    float power_mW = ina219.getPower_mW();
    Serial.print("Tensao: ");
    Serial.print(busVoltage, 2);
    Serial.println("V");
    Serial.print("Corrente: ");
    Serial.print(current_mA);
    Serial.println("mA");
    Serial.print("Potencia: ");
    Serial.print(power_mW, 2);
    Serial.println("mW");
    delay(1000);
}