// Motor A control pins (Alum)
const int IN1 = D1;  // GPIO5
const int IN2 = D2;  // GPIO4
const int ENA = D3;  // GPIO0 (PWM)

// Motor B control pins (Carbon)
const int IN3 = D5;  // GPIO14
const int IN4 = D6;  // GPIO12
const int ENB = D7;  // GPIO13 (PWM)

// Motor C control pins (Baking Soda)
// const int IN5 = D0;  // Example pin
// const int IN6 = D8;  // Example pin
// const int ENC = D9;  // Example PWM pin

// Motor D control pins (Bleach)
// const int IN7 = D10;  // Example pin
// const int IN8 = D11;  // Example pin
// const int END = D12;  // Example PWM pin

String inputString = "";
unsigned long motorA_endTime = 0;
unsigned long motorB_endTime = 0;
// unsigned long motorC_endTime = 0;
// unsigned long motorD_endTime = 0;

bool motorA_running = false;
bool motorB_running = false;
// bool motorC_running = false;
// bool motorD_running = false;

void setup() {
  Serial.begin(115200);

  // Setup Motor A
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  // Setup Motor B
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Setup Motor C (commented)
//   pinMode(IN5, OUTPUT);
//   pinMode(IN6, OUTPUT);
//   pinMode(ENC, OUTPUT);

  // Setup Motor D (commented)
//   pinMode(IN7, OUTPUT);
//   pinMode(IN8, OUTPUT);
//   pinMode(END, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    inputString = Serial.readStringUntil('\n');
    inputString.trim();
    Serial.println("[ESP8266] Received: " + inputString);

    float alum, carbon, bakingSoda, bleach;
    int parsed = sscanf(inputString.c_str(), "%f,%f,%f,%f", &alum, &carbon, &bakingSoda, &bleach);
    if (parsed == 4) {
      Serial.printf("[ESP8266] Parsed → Alum: %.2f, Carbon: %.2f, BakingSoda: %.2f, Bleach: %.2f\n",
                    alum, carbon, bakingSoda, bleach);

      unsigned long currentTime = millis();

      // Scale dosing time: adjust multiplier if needed
      unsigned long alumTime   = min((unsigned long)(alum * 100), 180000UL);
      unsigned long carbonTime = min((unsigned long)(carbon * 100), 180000UL);
      // unsigned long sodaTime   = min((unsigned long)(bakingSoda * 100), 180000UL);
      // unsigned long bleachTime = min((unsigned long)(bleach * 100), 180000UL);

      // Start Motor A
      if (alum > 0) {
        Serial.println("[ESP8266] Starting Motor A (Alum)");
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        analogWrite(ENA, 512);
        motorA_endTime = currentTime + alumTime;
        motorA_running = true;
      }

      // Start Motor B
      if (carbon > 0) {
        Serial.println("[ESP8266] Starting Motor B (Carbon)");
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        analogWrite(ENB, 512);
        motorB_endTime = currentTime + carbonTime;
        motorB_running = true;
      }

      // Start Motor C (commented)
//       if (bakingSoda > 0) {
//         Serial.println("[ESP8266] Starting Motor C (Baking Soda)");
//         digitalWrite(IN5, HIGH);
//         digitalWrite(IN6, LOW);
//         analogWrite(ENC, 512);
//         motorC_endTime = currentTime + sodaTime;
//         motorC_running = true;
//       }

      // Start Motor D (commented)
//       if (bleach > 0) {
//         Serial.println("[ESP8266] Starting Motor D (Bleach)");
//         digitalWrite(IN7, HIGH);
//         digitalWrite(IN8, LOW);
//         analogWrite(END, 512);
//         motorD_endTime = currentTime + bleachTime;
//         motorD_running = true;
//       }
    } else {
      Serial.println("[ESP8266] ❌ Failed to parse input.");
    }
  }

  unsigned long now = millis();

  if (motorA_running && now >= motorA_endTime) {
    analogWrite(ENA, 0);
    motorA_running = false;
    Serial.println("[ESP8266] Stopped Motor A");
  }

  if (motorB_running && now >= motorB_endTime) {
    analogWrite(ENB, 0);
    motorB_running = false;
    Serial.println("[ESP8266] Stopped Motor B");
  }

  // Stop Motor C (commented)
//   if (motorC_running && now >= motorC_endTime) {
//     analogWrite(ENC, 0);
//     motorC_running = false;
//     Serial.println("[ESP8266] Stopped Motor C");
//   }

  // Stop Motor D (commented)
//   if (motorD_running && now >= motorD_endTime) {
//     analogWrite(END, 0);
//     motorD_running = false;
//     Serial.println("[ESP8266] Stopped Motor D");
//   }
}
