#include <Servo.h>

const int TRIG_PIN = 9;
const int ECHO_PIN = 10;
const int ENA = 5;
const int IN1 = 6;
const int IN2 = 7;
const int ENB = 2;
const int IN3 = 4;
const int IN4 = 3;
const int SERVO_PIN = 11;

const int OBSTACLE_DISTANCE = 15;  // cm - threshold for obstacle detection
const int MOTOR_SPEED = 80;        // PWM speed (0-255)

Servo myServo;
long duration;
float distance;

float getDistance();
void moveForward();
void moveBackward();
void turnLeft();
void turnRight();
void stopCar();

void setup() {
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  myServo.attach(SERVO_PIN);
  myServo.write(90);
  delay(500);
}

void loop() {
  for (int angle = 15; angle <= 165; angle += 15) {
    myServo.write(angle);
    delay(200);
    distance = getDistance();
    Serial.print("Angle: ");
    Serial.print(angle);
    Serial.print("°  Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    if (distance < OBSTACLE_DISTANCE) {
      Serial.println("object found ");
      stopCar();
      delay(3000);
      moveBackward();
      delay(1000);
      turnRight();
      delay(1000);
      stopCar();
    } else {
      moveForward();
      delay(1000);
      stopCar();
      delay(1000);
    }
  }

  // Sweep back from right (165°) to left (15°)
  for (int angle = 165; angle >= 15; angle -= 15) {
    myServo.write(angle);
    delay(200);
    distance = getDistance();
    Serial.print("Angle: ");
    Serial.print(angle);
    Serial.print("°  Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    if (distance < OBSTACLE_DISTANCE) {
      Serial.println("object found ");
      stopCar();
      delay(3000);
      moveBackward();
      delay(1000);
      turnLeft();
      delay(1000);
      stopCar();
    } else {
      moveForward();
      delay(1000);
      stopCar();
      delay(1000);
    }
  }
}

float getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH, 30000);
  float d = duration * 0.034 / 2;
  if (d == 0 || d > 400) d = 400;
  return d;
}

void moveForward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);
}

void moveBackward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);
}

void turnLeft() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);
}

void turnRight() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);
}

void stopCar() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
