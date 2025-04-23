

void servo() {

  adcAngle = analogRead(A4);
  AngleUser = map(adcAngle, 0, 1024, 0, maxAngle);

  adcCurrent = analogRead(A3);
  minRPM = map(adcCurrent, 0, 1024, 900, maxRPM);

  int adcValue = analogRead(A2);
  checkTime = map(adcValue, 0, 1024, 50, 1500);

  unsigned long now = millis();
  if (now - lastReadServo >= checkTime) {
    lastReadServo = now;

    if (currentRPM <= (maxRPM + rpmThreshold) && currentRPM >= (minRPM - rpmThreshold) && RPMok == 0) ++checkrpm;
    if (currentRPM < (minRPM - rpmThreshold) && RPMok == 0) --checkrpm;
    if (checkrpm >= 10) {
      RPMok = 1;
      checkrpm = 10;
    }
    if (checkrpm < 0) checkrpm = 0;

    if (RPMok == 1) {
      ////////////////Servo Angle/////////////////
      //  if (currentRPM <= (maxRPM - rpmThreshold)) {

      currentServoAngle = map(currentRPM, maxRPM, minRPM, 0, AngleUser);

      if (lastAngle > currentServoAngle && currentRPM >= (maxRPM - rpmThreshold) && currentRPM <= (maxRPM + rpmThresholdHigh)) currentServoAngle = lastAngle;

      //***********تاخیر در دورهای خیلی پایین***********


      lastAngle = currentServoAngle;

      if (currentServoAngle < 0) currentServoAngle = 0;
      if (currentServoAngle > AngleUser) currentServoAngle = AngleUser;

      if (currentRPM < 500) currentServoAngle = 0;
      if (currentRPM > (maxRPM + rpmThresholdHigh)) currentServoAngle = 0;


      throttleServo.write(currentServoAngle);
    }

    if (currentRPM > 100) {
      lastminimumRPM = currentRPM;
      if (currentRPM > minimumRPM) lastminimumRPM = minimumRPM;
      minimumRPM = lastminimumRPM;
    }

    Serial.print(" |Angle: ");
    Serial.print(currentServoAngle);
    Serial.print(" |RPM: ");
    Serial.print(currentRPM);
    Serial.print(" |angleUser: ");
    Serial.print(AngleUser);
    Serial.print(" |minRPM: ");
    Serial.print(minRPM);
    Serial.print(" |minRPM: ");
    Serial.print(minimumRPM);
    Serial.print(" |Time: ");
    Serial.print(checkTime);
    Serial.print(" |LowRpm: ");
    Serial.print(LowRpm);
    if (RPMok == 0) {
      Serial.println(" |Not Ready");
    }
    if (RPMok == 1) {
      Serial.println(" |Ready");
    }
    String show = String(currentRPM);
    My_Display.String_To_Buffer(show, Default_Brightness);
    //  }
  }
}