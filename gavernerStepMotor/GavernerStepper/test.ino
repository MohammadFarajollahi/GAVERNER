

void test() {
  sowichMode = 1;
  digitalWrite(led, 0);
  adcAngle = analogRead(A4);
  AngleUser = map(adcAngle, 0, 1024, 0, maxAngle);

  adcCurrent = analogRead(A3);
  minRPM = map(adcCurrent, 0, 1024, 900, maxRPM);

  int adcValue = analogRead(A2);
  checkTime = map(adcValue, 0, 1024, 1, 200);

  if (digitalRead(buttUP) == 0) {
    for (int i = 0; i < AngleUser; i++) stepUp();
    delay(100);
    Serial.println("up");
    while (1) {
      if (digitalRead(buttUP) == 1) break;
    }
  }
  if (digitalRead(buttDown) == 0) {
     Serial.println("Down");
    for (int i = 0; i < AngleUser; i++) stepDown();
    delay(100);
    while (1) {
      if (digitalRead(buttDown) == 1) break;
    }
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
}