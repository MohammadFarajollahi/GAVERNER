#include <Servo.h>
#define RPM_INPUT_PIN 2
const int sensorPin = 2;  // سنسور RPM
#define SERVO_PIN 9
#define CURRENT_SENSOR_PIN A0
#include <SPI.h>
#define Number_MAX7219 1      // 3 chips = 24 digits
#define MAX7219_CS 5          // pin the MAX7219's CS pin is connected to
#define Default_Brightness 8  // brightness level 0-15
#include <MAX7219_8_Digit_Driver.h>
MAX7219_8_Digit_Driver My_Display(MAX7219_CS, Number_MAX7219);
float current;
const int sampleCount = 300;
volatile unsigned long pulseInterval = 0;
volatile unsigned long pulseCount = 0;
unsigned long lastRPMTime = 0;
int currentRPM = 0;
int servoAngle = 0;
Servo throttleServo;
volatile unsigned long lastPulseTime = 0;
int rpmCount;



int CurrentUser;
int AngleUser;
int adcAngle;
int adcCurrent;
unsigned long lastReadServo;
int currentServoAngle;

int maxCurrent = 60;

int maxAngle = 10;
int maxRPM = 1360;
int minRPM;
int lastAngle;
int rpmThreshold = 50;
void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(sensorPin), pulseDetected, FALLING);
  throttleServo.attach(SERVO_PIN);
  throttleServo.write(0);
  delay(1000);
}

void loop() {

  RPM();
  servo();

  //test();
}


void pulseDetected() {
  unsigned long now = micros();
  pulseInterval = now - lastPulseTime;
  lastPulseTime = now;
  rpmCount = 0;
}