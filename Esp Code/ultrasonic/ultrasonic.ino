// Define pins for 4 ultrasonic sensors
#define TRIG1 5
#define ECHO1 18

#define TRIG2 14
#define ECHO2 27

#define TRIG3 12
#define ECHO3 33

#define TRIG4 26
#define ECHO4 25

float readDistanceCM(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 25000); // timeout after 25ms
  float distance = duration * 0.034 / 2;

  if (duration == 0) {
    return -1;  // Sensor failed or out of range
  }

  return distance;
}

void setup() {
  Serial.begin(115200);

  pinMode(TRIG1, OUTPUT); pinMode(ECHO1, INPUT);
  pinMode(TRIG2, OUTPUT); pinMode(ECHO2, INPUT);
  pinMode(TRIG3, OUTPUT); pinMode(ECHO3, INPUT);
  pinMode(TRIG4, OUTPUT); pinMode(ECHO4, INPUT);
}

void loop() {
  float d1 = readDistanceCM(TRIG1, ECHO1);
  float d2 = readDistanceCM(TRIG2, ECHO2);
  float d3 = readDistanceCM(TRIG3, ECHO3);
  float d4 = readDistanceCM(TRIG4, ECHO4);

  Serial.print("Sensor 1: ");
  Serial.print(d1);
  Serial.print(" cm | Sensor 2: ");
  Serial.print(d2);
  Serial.print(" cm | Sensor 3: ");
  Serial.print(d3);
  Serial.print(" cm | Sensor 4: ");
  Serial.print(d4);
  Serial.println(" cm");

  delay(500);
}
