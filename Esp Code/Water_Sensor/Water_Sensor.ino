#include <OneWire.h>
#include <DallasTemperature.h>

// Pin Definitions
#define PH_PIN         32
#define TDS_PIN        33
#define TURBIDITY_PIN  34
#define TEMP_PIN       25

// Constants
const float PH_SLOPE = 12.863;
const float PH_INTERCEPT = -17.026;
const float Aref = 3.3;
const float ecCal = 1.0;
const float tdsCalibrationFactor = 0.6;

// OneWire and DallasTemperature
OneWire oneWire(TEMP_PIN);
DallasTemperature tempSensor(&oneWire);

// Read average voltage
float readAveragedVoltage(int pin, int samples = 10) {
  long total = 0;
  for (int i = 0; i < samples; i++) {
    total += analogRead(pin);
    delay(10);
  }
  return (total / (float)samples) * (Aref / 4095.0);  // 12-bit ADC
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  tempSensor.begin();
}

void loop() {
  // Temperature
  tempSensor.requestTemperatures();
  float waterTemp = tempSensor.getTempCByIndex(0);

  // pH
  float phVoltage = readAveragedVoltage(PH_PIN);
  float pHValue = PH_SLOPE * phVoltage + PH_INTERCEPT;

  // TDS
  float tdsVoltage = readAveragedVoltage(TDS_PIN);
  float tempCoeff = 1.0 + 0.02 * (waterTemp - 25.0);
  float ecValue = (tdsVoltage / tempCoeff) * ecCal;
  unsigned int tdsValue = (133.42 * pow(ecValue, 3)
                        - 255.86 * pow(ecValue, 2)
                        + 857.39 * ecValue) * 0.5;
  tdsValue *= tdsCalibrationFactor;

  // Turbidity
  int turbidityRaw = analogRead(TURBIDITY_PIN);
  int turbidityValue = map(turbidityRaw, 0, 4095, 100, 0);

  // CSV Output: temp, pH, TDS, turbidity
  Serial.print(waterTemp, 2);     Serial.print(",");
  Serial.print(pHValue, 2);       Serial.print(",");
  Serial.print(tdsValue);         Serial.print(",");
  Serial.println(turbidityValue);

  delay(5000);  // 5 seconds delay
}
