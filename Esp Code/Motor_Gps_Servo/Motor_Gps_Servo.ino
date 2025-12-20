#include <Servo.h>

// ------------------ Motor Pins ------------------
#define IN1 D1
#define IN2 D2
#define ENA D5

#define IN3 D6
#define IN4 D7
#define ENB D8

// ------------------ Servo Pin ------------------
#define SERVO_PIN D4
Servo myServo;

// ------------------ Obstacle & GPS Data ------------------
long values[6]; // TL, TR, L, R, LAT, LON
String inputData = "";

// ------------------ Waypoint Navigation ------------------
const int totalWaypoints = 4;
float waypoints[4][2] = {
  {26.122334, 91.132456},
  {26.122400, 91.132500},
  {26.122460, 91.132550},
  {26.122500, 91.132600}
};

int currentWaypointIndex = 0;
bool waitingAtWaypoint = false;
unsigned long waypointArrivalTime = 0;
const float arrivalThresholdMeters = 2.0; // Changed from 0.3 (30 cm) to 2.0 (2 meters)

// ------------------ Timing ------------------
unsigned long lastDataTime = 0;
const unsigned long timeoutMs = 3000;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(100);

  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT); pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT); pinMode(ENB, OUTPUT);

  myServo.attach(SERVO_PIN);
  myServo.write(90); // Neutral direction
  stopMotors();

  lastDataTime = millis();
}

void loop() {
  if (Serial.available()) {
    inputData = Serial.readStringUntil('\n');
    inputData.trim();

    if (parseInput(inputData)) {
      lastDataTime = millis();

      int TL = values[0];
      int TR = values[1];
      int L  = values[2];
      int R  = values[3];
      long LAT_raw = values[4];
      long LON_raw = values[5];

      float LAT = LAT_raw / 1000000.0;
      float LON = LON_raw / 1000000.0;

      Serial.println("TL: " + String(TL) + " TR: " + String(TR) + " L: " + String(L) + " R: " + String(R));
      Serial.println("LAT: " + String(LAT) + " LON: " + String(LON));

      // GPS missing or invalid
      if (LAT == -1 && LON == -1) {
        stopMotors();
        return;
      }

      // Calculate distance to current waypoint
      float targetLat = waypoints[currentWaypointIndex][0];
      float targetLon = waypoints[currentWaypointIndex][1];
      float distToTarget = distanceBetween(LAT, LON, targetLat, targetLon);

      Serial.println("Distance to waypoint #" + String(currentWaypointIndex) + ": " + String(distToTarget) + " m");

      // Arrived at current waypoint
      if (distToTarget < arrivalThresholdMeters && !waitingAtWaypoint) {
        stopMotors();
        waitingAtWaypoint = true;
        waypointArrivalTime = millis();
        Serial.println("Arrived at waypoint #" + String(currentWaypointIndex));
      }

      // Wait 5 seconds after reaching a waypoint
      if (waitingAtWaypoint) {
        if (millis() - waypointArrivalTime >= 5000) {
          waitingAtWaypoint = false;
          currentWaypointIndex++;
          if (currentWaypointIndex >= totalWaypoints) {
            Serial.println("Final waypoint reached.");
            stopMotors();
            while (true); // Stop forever
          }
        }
      } else {
        // Obstacle avoidance logic
        if (TL < 30 && TR < 30) {
          reverseMotors();
          myServo.write(90);
        }
        else if (TL < 50) {
          forwardSlow();
          myServo.write(180);  // Turn right
        }
        else if (TR < 50) {
          forwardSlow();
          myServo.write(0);    // Turn left
        }
        else if (L < 40) {
          reverseMotors();
          myServo.write(155);  // Adjust slightly right
        }
        else if (R < 40) {
          reverseMotors();
          myServo.write(25);   // Adjust slightly left
        }
        else {
          moveForward();
          myServo.write(90);   // Straight
        }
      }
    }
  } else {
    // If no data, stop after timeout
    if (millis() - lastDataTime > timeoutMs) {
      Serial.println("No values received");
      stopMotors();
      lastDataTime = millis();
    }
  }
}

// ------------------ GPS Distance Function ------------------
float distanceBetween(float lat1, float lon1, float lat2, float lon2) {
  const float R = 6371000; // Earth radius in meters
  float dLat = radians(lat2 - lat1);
  float dLon = radians(lon2 - lon1);
  float a = sin(dLat/2) * sin(dLat/2) +
            cos(radians(lat1)) * cos(radians(lat2)) *
            sin(dLon/2) * sin(dLon/2);
  float c = 2 * atan2(sqrt(a), sqrt(1-a));
  return R * c;
}

// ------------------ Helper Functions ------------------
bool parseInput(String data) {
  int index = 0, lastIndex = 0;
  for (int i = 0; i < 6; i++) {
    index = data.indexOf(',', lastIndex);
    String val = (index == -1) ? data.substring(lastIndex) : data.substring(lastIndex, index);
    if (val.length() == 0) return false;
    values[i] = val.toInt();
    if (index == -1 && i < 5) return false;
    lastIndex = index + 1;
  }
  return true;
}

void moveForward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, 255); analogWrite(ENB, 255);
}

void forwardSlow() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, 150); analogWrite(ENB, 150);
}

void reverseMotors() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  analogWrite(ENA, 200); analogWrite(ENB, 200);
}

void stopMotors() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  analogWrite(ENA, 0); analogWrite(ENB, 0);
}
