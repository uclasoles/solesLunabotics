  #include <Arduino.h>
  #include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

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
#define MAX_MSPCM 54.7645125958379
#define COOLDOWN_TIME  200


Adafruit_MPU6050 mpu;


const int MPU = 0x68;
float yaw = 0;
float GyroZ, gyroAngleZ, GyroErrorZ;
float elapsedTime, currentTime, previousTime;
int c = 0;

float read_yaw() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  previousTime = currentTime;

  currentTime = millis();
  elapsedTime = (currentTime - previousTime) / 1000;
  
  
  GyroZ = (g.gyro.z);
  
  GyroZ = GyroZ;
  //Serial.println(GyroZ);

  yaw = yaw + GyroZ * elapsedTime;
  //Serial.println(elapsedTime);
  return yaw;
}

float calculate_IMU_error() {
    while (c < 200) {
        Wire.beginTransmission(MPU);
        Wire.write(0x47);
        Wire.requestFrom(MPU, 2, true);
        
        GyroZ = Wire.read() << 8 | Wire.read();

        Serial.print(GyroZ);

        GyroErrorZ = GyroErrorZ + (GyroZ);

        c++;
        delay(10);
    }
    GyroErrorZ = GyroErrorZ / 200;
    return GyroErrorZ;
}

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


void turnDegrees(double degrees){
    float initialYaw = read_yaw();
    float targetYaw = initialYaw - degrees;
    targetYaw = -1*targetYaw;
    Serial.println("turnDegrees");
    analogWrite(ENA_F, 128);
        analogWrite(ENA_B, 128);
        analogWrite(ENB_F, 128);
        analogWrite(ENB_B, 128);
    while(abs(((read_yaw()*180)/3.14) - targetYaw) > 2){
        // turning left
        Serial.print("Read Yaw: ");
        Serial.println(((read_yaw()*180)/3.14));
        Serial.print("Target Yaw: ");
        Serial.println(targetYaw);
        digitalWrite(IN1_F, LOW);
        digitalWrite(IN2_F, HIGH);
        digitalWrite(IN3_F, HIGH);
        digitalWrite(IN4_F, LOW);
        
        digitalWrite(IN1_B, LOW);
        digitalWrite(IN2_B, HIGH);
        digitalWrite(IN3_B, HIGH);
        digitalWrite(IN4_B, LOW);
    }
    stop();
 
    Serial.println("turnDegrees");
    Serial.print("Initial Yaw: ");
    Serial.println(initialYaw);
    Serial.print("Target Yaw: ");
    Serial.println(targetYaw);
    Serial.print("Final Yaw: ");
    Serial.println(read_yaw());
}


void setup() {

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.println("");
  delay(100);
  
  delay(1000);
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission(true);
  calculate_IMU_error();
  delay(1000);
  setupMovement();
  turnDegrees(180);
}

void loop () {  
  }
