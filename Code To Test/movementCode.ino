#include <Arduino.h>


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

#define MAX_SPEED_RAD 5.23598775 
#define MAX_SPEED_RPM 50

#define MAX_SPEED_MPS .157077


#define WHEEL_CIRCUMFERENCE_CM 22


 
#define MAX_CMPS  18.26
#define MAX_SPCM 0.0547645125958379

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



void moveTimeDirection(int ms, int mspeed, int direction)
{
  switch (direction) {
    case FORWARD:
      digitalWrite(IN1_F, HIGH);
      digitalWrite(IN2_F, LOW);
      digitalWrite(IN3_F, HIGH);
      digitalWrite(IN4_F, LOW);
      
      digitalWrite(IN1_B, HIGH);
      digitalWrite(IN2_B, LOW);
      digitalWrite(IN3_B, HIGH);
      digitalWrite(IN4_B, LOW);
      break;
    case BACKWARD:
      digitalWrite(IN1_F, LOW);
      digitalWrite(IN2_F, HIGH);
      digitalWrite(IN3_F, LOW);
      digitalWrite(IN4_F, HIGH);

      digitalWrite(IN1_B, LOW);
      digitalWrite(IN2_B, HIGH);
      digitalWrite(IN3_B, LOW);
      digitalWrite(IN4_B, HIGH);
      break;
    case STOP:
      digitalWrite(IN1_F, LOW);
      digitalWrite(IN2_F, LOW);
      digitalWrite(IN3_F, LOW);
      digitalWrite(IN4_F, LOW);

      digitalWrite(IN1_B, LOW);
      digitalWrite(IN2_B, LOW);
      digitalWrite(IN3_B, LOW);
      digitalWrite(IN4_B, LOW);
  }
  
  analogWrite(ENA_F, mspeed);
  analogWrite(ENB_F, mspeed);
  analogWrite(ENA_B, mspeed);
  analogWrite(ENB_B, mspeed);
  delay(ms);
  analogWrite(ENA_F, 0);
  analogWrite(ENB_F, 0);
  analogWrite(ENA_B, 0);
  analogWrite(ENB_B, 0);
}

void moveCmDirection(double cm, double mspeed, int direction=FORWARD) {
 moveTimeDirection(cm * MAX_SPCM, mspeed, direction);
}

void setup() {
  setupMovement();
  moveTimeDirection(1000, 255, FORWARD);
  moveCmDirection(50, 255, FORWARD);
}

void loop () {}
