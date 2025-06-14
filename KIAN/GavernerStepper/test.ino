

void test() {
  sowichMode = 1;
  digitalWrite(led, 0);
  //right
  if (digitalRead(buttUP) == 0) {
    while (1) {
      if (digitalRead(buttUP) == 1) break;
      for (int i = 0; i < 10; i++) stepUp();
    }
    delay(200);
  }
  //left
  if (digitalRead(buttDown) == 0) {
    while (1) {
      if (digitalRead(buttDown) == 1) break;
      for (int i = 0; i < 50; i++) stepDown();
    }
    delay(200);
  }

  String show = String(currentRPM);
  My_Display.String_To_Buffer(show, Default_Brightness);
}