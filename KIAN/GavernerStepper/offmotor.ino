int exitOfMode = 0;

void offmotor() {

  if (digitalRead(offButton) == 0) {
    delay(100);
    if (digitalRead(offButton) == 0) {
      OffMode = 1; 
      while (1) {
        RPM();
        String show = String(currentRPM);
        My_Display.String_To_Buffer(show, Default_Brightness);
        for (int i = 0; i < 30; i++) stepDown();
        if (currentRPM <= 1000) {
          exitOfMode = 1;
          delay(60000);
          for (int i = 0; i < ZeroPos; i++) stepDown();
        }
        if (exitOfMode == 1) {
          exitOfMode = 0;
          break;
        }
      }
    }
  }
}