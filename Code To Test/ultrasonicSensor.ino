#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04

#define FORWARD 1
#define BACKWARD -1
#define STOP  0

#define ENA_F 5
#define ENB_F 6

#define IN1_F 4
#define IN2_F 3
#define IN3_F 8
#define IN4_F 7

#define ENA_B 9
#define ENB_B 10

#define IN1_B 11
#define IN2_B 12
#define IN3_B 13
#define IN4_B 2

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

void setupMovement()
{
  pinMode(ENA_F, OUTPUT);
  pinMode(ENB_F, OUTPUT);

  pinMode(IN1_F, OUTPUT);
  pinMode(IN2_F, OUTPUT);
  pinMode(IN3_F, OUTPUT);
  pinMode(IN4_F, OUTPUT);

  pinMode(ENA_B, OUTPUT);
  pinMode(ENB_B, OUTPUT);

  pinMode(IN1_B, OUTPUT);
  pinMode(IN2_B, OUTPUT);
  pinMode(IN3_B, OUTPUT);
  pinMode(IN4_B, OUTPUT);
}

void stop(){
   digitalWrite(IN1_F, LOW);
   digitalWrite(IN2_F, LOW);
   digitalWrite(IN3_F, LOW);
   digitalWrite(IN4_F, LOW);

   digitalWrite(IN1_B, LOW);
   digitalWrite(IN2_B, LOW);
   digitalWrite(IN3_B, LOW);
   digitalWrite(IN4_B, LOW);

    digitalWrite(ENA_F, LOW);
    digitalWrite(ENA_B, LOW);
    digitalWrite(ENB_F, LOW);
    digitalWrite(ENB_B, LOW);
}

void moveForward(){
  digitalWrite(IN1_F, HIGH);
  digitalWrite(IN2_F, HIGH);
  digitalWrite(IN3_F, HIGH);
  digitalWrite(IN4_F, HIGH);    
  digitalWrite(IN1_B, HIGH);
  digitalWrite(IN2_B, HIGH);
  digitalWrite(IN3_B, HIGH);
  digitalWrite(IN4_B, HIGH);
  delay(100);
}

void setup() {
  setupMovement();
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor Test"); // print some text in Serial Monitor
}
void loop() {
  int d = getDistance();
  while(d > 10){
    moveForward();
    d = getDistance();
  }
  stop();
  Serial.println("reached object");
}



int getDistance(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  return distance;
}
