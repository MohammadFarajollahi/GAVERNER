
void test() {
  adcAngle = analogRead(A4);
  AngleUser = map(adcAngle, 0, 1024, 0, 20);

  adcCurrent = analogRead(A3);
  minRPM = map(adcCurrent, 0, 1024, 900, maxRPM);

  int adcValue = analogRead(A2);
  currentRPM = map(adcValue, 0, 1024, 1000, 1400);
  unsigned long now = millis();
  if (now - lastReadServo >= 100) {
    lastReadServo = now;
    ////////////////Servo Angle/////////////////


     throttleServo.write(AngleUser);
   // throttleServo.writeMicroseconds(AngleUser);

      Serial.print("RPM: ");
    Serial.print(currentRPM);
    Serial.print(" |angleUser: ");
    Serial.print(AngleUser);
    Serial.print(" |minRPM: ");
    Serial.print(minRPM);
    Serial.print(" |Angle: ");
    Serial.println(currentServoAngle);
    String show = String(currentRPM);
    My_Display.String_To_Buffer(show, Default_Brightness);
  }
}