#define stepPin 9
#define dirPin 10

#define RPM_INPUT_PIN 2
const int sensorPin = 2;  // سنسور RPM
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
volatile unsigned long lastPulseTime = 0;
int rpmCount;



int CurrentUser;
int AngleUser;
int adcAngle;
int adcCurrent;
unsigned long lastReadServo;
int currentServoAngle;

int maxCurrent = 60;

int maxAngle = 20;
int maxRPM = 1230;  // 1240
int minRPM;
int lastAngle;
int rpmThreshold = 30;
int rpmThresholdHigh = 100;
int checkTime = 100;
int LowRpm;

int adcSampleTime;

int minimumRPM;
int lastminimumRPM;

int readTime;
int CheckTime;

int readTime2;
int CheckTime2;

int angle;

int RPMok;
int checkrpm;
int checkrpm2;

int buttonTest = A0;
int buttUP = A1;
int buttDown = 4;
int led = 7;

int stepMove;
int Up;
int Down;

int lowRpmCheck;

int sowichMode;

int angleStart;

int ZeroPos = 300;
void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(sensorPin), pulseDetected, FALLING);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(buttonTest, INPUT);
  pinMode(buttUP, INPUT);
  pinMode(buttDown, INPUT);
  for (int i = 0; i < ZeroPos; i++) stepDown();
  digitalWrite(led, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(500);               // wait for a second
  digitalWrite(led, LOW);   // turn the LED off by making the voltage LOW
  delay(500);
}

void loop() {

  RPM();
  if (digitalRead(buttonTest) == 0) {
    if (sowichMode == 1) {
      sowichMode = 0;
      angleStart = 0;
      for (int i = 0; i < ZeroPos; i++) stepDown();
    }
    Steper();
  }

  if (digitalRead(buttonTest) == 1) test();
}


void pulseDetected() {
  unsigned long now = micros();
  pulseInterval = now - lastPulseTime;
  lastPulseTime = now;
  rpmCount = 0;
}