



void servo2() {

  adcAngle = analogRead(A4);
  AngleUser = map(adcAngle, 0, 1024, 0, maxAngle);

  adcCurrent = analogRead(A3);
  minRPM = map(adcCurrent, 0, 1024, 900, maxRPM);

  int adcValue = analogRead(A2);
  checkTime = map(adcValue, 0, 1024, 1, 200);

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
      //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
      if (CheckTime == 0) {
        if (currentRPM <= (maxRPM - rpmThreshold) && currentRPM >= (minRPM)) {
          currentServoAngle++;
          CheckTime = 1;
        }
      }

      if (CheckTime == 1) ++readTime;
      if (CheckTime == 1 && readTime >= 30) {
        CheckTime = 0;
        readTime = 0;
      }
      //--------------------------------------------------------------
      if (CheckTime2 == 0) {
        if (currentRPM >= (maxRPM + rpmThreshold)) {
          currentServoAngle--;
          CheckTime2 = 1;
          readTime2 = 0;
        }

        if (currentRPM >= (maxRPM + 30)) {
          currentServoAngle--;
          CheckTime2 = 1;
          readTime2 = 0;
        }

        if (currentRPM >= (maxRPM + 60)) {
          currentServoAngle--;
          CheckTime2 = 1;
          readTime2 = 0;
        }

        if (currentRPM >= (maxRPM + 200)) {
          currentServoAngle-=2;
          CheckTime2 = 1;
          readTime2 = 0;
        }
      }

      if (CheckTime2 == 1) ++readTime2;
      if (readTime2 >= 30) {
        CheckTime2 = 0;
        readTime2 = 0;
      }
      /////////////////////////////////////////////////////////////////////
      angle = currentServoAngle;
      if (currentRPM <= (maxRPM + rpmThreshold) && currentRPM >= (maxRPM - rpmThreshold)) {
        angle = lastAngle;
        currentServoAngle = lastAngle;
      }

      lastAngle = angle;


      if (angle < 0) {
        angle = 0;
        currentServoAngle = 0;
      }
      if (angle > AngleUser) {
        angle = AngleUser - 1;
        currentServoAngle = AngleUser - 1;
      }
      if (currentRPM < 500) {
        angle = 0;
        currentServoAngle = 0;
      }

      throttleServo.write(angle);
    }

    Serial.print(" |Angle: ");
    Serial.print(angle);
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