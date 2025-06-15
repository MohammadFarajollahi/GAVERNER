#define stepPin 9
#define dirPin 10
#include <ArduinoJson.h>
#define RPM_INPUT_PIN 2
const int sensorPin = 2;  // سنسور RPM
#include <SPI.h>
#define Number_MAX7219 1      // 3 chips = 24 digits
#define MAX7219_CS 5          // pin the MAX7219's CS pin is connected to
#define Default_Brightness 4  // brightness level 0-15
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

int ledRPM = 3;
int buttonTest = A0;
int buttUP = 6;
int buttDown = 4;
int led = A5;
int stepEnable = 7;
int offButton = 8;

int CurrentUser;
int AngleUser;
int adcAngle;
int adcCurrent;
unsigned long lastReadServo;
int currentServoAngle;


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
int stepMove;
int Up;
int Down;
int lowRpmCheck;
int sowichMode;
int angleStart;
int OffMode = 1;

int ZeroPos = 3000;
void setup() {
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(sensorPin), pulseDetected, FALLING);
  pinMode(stepPin, OUTPUT);
  pinMode(ledRPM, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(stepEnable, OUTPUT);
  pinMode(buttonTest, INPUT);
  pinMode(offButton, INPUT);
  pinMode(buttUP, INPUT);
  pinMode(buttDown, INPUT);
  // for (int i = 0; i < ZeroPos; i++) stepDown();
  digitalWrite(stepEnable, HIGH);
  digitalWrite(led, HIGH);

  Serial.println("****start***");
}

void loop() {
  offmotor();
  RPM();
  if (digitalRead(buttonTest) == 0 && OffMode == 0) {
    if (sowichMode == 1) {

      while (1) {
        RPM();
        String show = String(currentRPM);
        My_Display.String_To_Buffer(show, Default_Brightness);
        if (digitalRead(buttonTest) == 1) break;
        if (currentRPM >= 1000) break;
      }
      if (digitalRead(buttonTest) == 0) {
        sowichMode = 0;
        angleStart = 0;
        for (int i = 0; i < ZeroPos; i++) stepDown();
        while (1) {
          RPM();
          String show = String(currentRPM);
          My_Display.String_To_Buffer(show, Default_Brightness);
          for (int i = 0; i < 30; i++) stepDown();
          if (currentRPM <= 1000) {
            delay(30000);
            break;
          }
        }
      }
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
  digitalWrite(ledRPM, !digitalRead(ledRPM));
}