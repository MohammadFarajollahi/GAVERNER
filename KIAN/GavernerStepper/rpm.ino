

void RPM() {
  unsigned long now = millis();

  // --- RPM فقط برای اطلاع
  if (now - lastRPMTime >= 500) {
    lastRPMTime = now;

    unsigned long intervalCopy;
    noInterrupts();
    intervalCopy = pulseInterval;
    interrupts();

    if (intervalCopy > 0) {
      currentRPM = 60000000.0 / intervalCopy;
    } else {
      currentRPM = 0;
    }
    rpmCount++;
    if (rpmCount >= 2) {
      rpmCount = 0;
      currentRPM = 0;
      intervalCopy = 0;
      pulseInterval = 0;
    }

   
  }
}