

void servo() {

  adcAngle = analogRead(A4);
  AngleUser = map(adcAngle, 0, 1024, 0, maxAngle);

  adcCurrent = analogRead(A3);
  minRPM = map(adcCurrent, 0, 1024, 900, maxRPM);

  unsigned long now = millis();
  if (now - lastReadServo >= 500) {
    lastReadServo = now;
    ////////////////Servo Angle/////////////////
    //  if (currentRPM <= (maxRPM - rpmThreshold)) {

    currentServoAngle = map(currentRPM, maxRPM, minRPM, 0, AngleUser);

    if (lastAngle > currentServoAngle && currentRPM >= (maxRPM - rpmThreshold) && currentRPM <= (maxRPM + rpmThreshold)) currentServoAngle = lastAngle;

    lastAngle = currentServoAngle;

    if (currentServoAngle < 0) currentServoAngle = 0;
    if (currentServoAngle > maxAngle) currentServoAngle = maxAngle;

    if (currentRPM < 500) currentServoAngle = 0;

    throttleServo.write(currentServoAngle);

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
    //  }
  }
}