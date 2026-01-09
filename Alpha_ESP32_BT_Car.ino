#include "BluetoothSerial.h"

// =====================
// Alpha ESP32 Car
// =====================

// Left Motor 
int IN1 = 16; 
int IN2 = 17; 

// Right Motor 
int IN3 = 15; 
int IN4 = 2; 

// Headlights
int HEAD_L1 = 25;
int HEAD_L2 = 26;

// Tail Lights (RENAMED — B1 is reserved!)
int TAIL_L1 = 32;
int TAIL_L2 = 33;

// Ultrasonic Pins (not used yet)
int trig = 12;
int echo = 14;

//Status LED
int NRF_ST = 35;
int ST_LED = 27;

BluetoothSerial SerialBT;
char SBT;

// =====================
// MOTOR FUNCTIONS
// =====================

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopCar() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// =====================
// LIGHT FUNCTIONS
// =====================

void headLightsOn() {
  digitalWrite(HEAD_L1, HIGH);
  digitalWrite(HEAD_L2, HIGH);
}

void headLightsOff() {
  digitalWrite(HEAD_L1, LOW);
  digitalWrite(HEAD_L2, LOW);
}

void tailLightsOn() {
  digitalWrite(TAIL_L1, HIGH);
  digitalWrite(TAIL_L2, HIGH);
}

void tailLightsOff() {
  digitalWrite(TAIL_L1, LOW);
  digitalWrite(TAIL_L2, LOW);
}

void lights(char data)
{
  switch (data){
    case 'U' :   digitalWrite(HEAD_L1, HIGH);digitalWrite(HEAD_L2, HIGH); break;
    case 'u' :   digitalWrite(HEAD_L2, LOW);digitalWrite(HEAD_L2, LOW); break;
    case 'W' :   digitalWrite(TAIL_L1, HIGH);digitalWrite(TAIL_L2, HIGH); break;
    case 'w' :   digitalWrite(TAIL_L2, LOW);digitalWrite(TAIL_L2, LOW); break;
    default : break;
  }
}

// =====================
// SETUP
// =====================

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_Car");

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(HEAD_L1, OUTPUT);
  pinMode(HEAD_L2, OUTPUT);
  pinMode(TAIL_L1, OUTPUT);
  pinMode(TAIL_L2, OUTPUT);

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  stopCar();
}

// =====================
// LOOP
// =====================

void loop() {
  if (SerialBT.available()) {
    SBT = SerialBT.read();
    Serial.println(SBT);

    switch (SBT) {
      case 'F': moveForward(); break;
      case 'B': moveBackward(); break;
      case 'L': turnLeft(); break;
      case 'R': turnRight(); break;
      case 'S': stopCar(); break;
      case 'U': headLightsOn(); break;
      case 'u': headLightsOff(); break;
      case 'W': tailLightsOn(); break;
      case 'w': tailLightsOff(); break;
      default: break;
    }
  }
}
