
void Steper() {
  digitalWrite(led, HIGH);
  adcAngle = analogRead(A4);
  AngleUser = map(adcAngle, 0, 1024, 0, maxAngle);
  AngleUser = 1;

  adcCurrent = analogRead(A3);
  minRPM = map(adcCurrent, 0, 1024, 900, maxRPM);
  minRPM = 900;

  int adcValue = analogRead(A2);
  checkTime = map(adcValue, 0, 1024, 1, 200);
  checkTime = 2;

  int adcValue2 = analogRead(A5);
  adcSampleTime = map(adcValue2, 0, 1024, 1, 15);
  if (adcSampleTime < 0) adcSampleTime = 0;
  adcSampleTime = 7;

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
      //+++++++++++++++++++++++++++Up++++++++++++++++++++++++++++++++
      if (CheckTime == 0) {
        if (currentRPM <= (maxRPM - rpmThreshold) && currentRPM >= 1150) {
          Up = 1;
          stepMove = 1;
          CheckTime = 1;
          ++angle;
        }

        if (currentRPM <= 1150 && currentRPM >= 1140) {
          Up = 3;
          stepMove = 1;
          CheckTime = 1;
          angle += 2;
        }

        if (currentRPM <= 1140 && currentRPM > 1100) {
          Up = 4;
          stepMove = 1;
          CheckTime = 1;
          angle += 3;
        }

        if (currentRPM <= 1100 && currentRPM >= 500) {
          Up = 5;
          stepMove = 1;
          CheckTime = 1;
          angle += 4;
        }

        if (currentRPM <= (1100) && angleStart == 0) {
          Serial.println("First Up");
          Up = 5;
          angleStart = 1;
          stepMove = 1;
          CheckTime = 1;
          angle += 10;
        }
      }

      if (CheckTime == 1) ++readTime;
      if (CheckTime == 1 && readTime >= adcSampleTime) {  // 30
        CheckTime = 0;
        readTime = 0;
      }
      //------------------------Down----------------------------------
      if (CheckTime2 == 0) {
        if (currentRPM > (maxRPM)) {
          Down = 1;
          stepMove = 1;
          CheckTime2 = 1;
          angle--;
        }

        if (currentRPM >= (maxRPM + rpmThreshold)) {
          Down = 2;
          stepMove = 1;
          CheckTime2 = 1;
          readTime2 = 0;
          angle -= 2;
        }

        if (currentRPM >= (1300) && currentRPM < (1400)) {
          Down = 5;
          stepMove = 1;
          CheckTime2 = 1;
          readTime2 = 0;
          angle -= 4;
        }
        if (currentRPM >= (1400) && currentRPM < (1500)) {
          Down = 6;
          stepMove = 1;
          CheckTime2 = 1;
          readTime2 = 0;
          angle -= 5;
        }
        if (currentRPM >= (1500) && currentRPM < (1600)) {
          Down = 7;
          stepMove = 1;
          CheckTime2 = 1;
          readTime2 = 0;
          angle -= 6;
        }
        if (currentRPM >= (1600) && currentRPM < (5000)) {
          Down = 8;
          stepMove = 1;
          CheckTime2 = 1;
          readTime2 = 0;
          angle -= 7;
        }
      }

      if (CheckTime2 == 1) ++readTime2;
      if (readTime2 >= adcSampleTime) {  //30
        CheckTime2 = 0;
        readTime2 = 0;
      }
      ////////////////////////////دور مناسب تغییرات نده///////////////////////////////
      if (currentRPM <= (maxRPM + rpmThreshold) && currentRPM >= (maxRPM - rpmThreshold)) {
        Down = 0;
        stepMove = 0;
        Up = 0;
        angle = lastAngle;
      }

      lastAngle = angle;

      if (angle < 0) angle = 0;

      //*************************گاز خاموش وقتی دور موتور خوابید**********************
      if (currentRPM <= 500 && lowRpmCheck == 0) {
        angleStart = 0;
        lowRpmCheck = 1;
        Down = 0;
        Up = 0;
        stepMove = 0;
        angle = 0;
        checkrpm = 0;
        RPMok = 0;
        for (int i = 0; i < ZeroPos; i++) stepDown();
      }

      if (currentRPM >= minRPM && lowRpmCheck == 1) {
        lowRpmCheck = 0;
      }


      //************************move**********************
      if (stepMove == 1) {
        stepMove = 0;

        if (Up > 0) {
          for (int i = 0; i < Up; i++) {
            for (int i = 0; i < AngleUser; i++) stepUp();
          }
          Up = 0;
          Serial.print("up:");
          Serial.println(Up);
        }
        //*********************down******************************
        if (Down > 0) {
          for (int i = 0; i < Down; i++) {
            for (int i = 0; i < AngleUser; i++) stepDown();
          }
          Down = 0;
          Serial.print("down:");
          Serial.println(Down);
        }
      }
      //***************************************************
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
    Serial.print(" |SamoleTime: ");
    Serial.print(adcSampleTime);
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