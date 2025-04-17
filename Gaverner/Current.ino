
void Current() {
  long sum = 0;
  for (int i = 0; i < sampleCount; i++) {
    int adcValue = analogRead(CURRENT_SENSOR_PIN);
    sum += adcValue;
    delayMicroseconds(500);
  }
  current = sum / sampleCount;
  current /= 8;

  // int adcValue = analogRead(A2);
  // current = map(adcValue, 0, 1024, 0, 50);
}