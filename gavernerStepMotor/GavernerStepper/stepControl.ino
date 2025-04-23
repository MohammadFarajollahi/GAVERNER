

void stepUp() {
  digitalWrite(dirPin, 0);
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(1000);  // پالس بالا
  digitalWrite(stepPin, LOW);
  delayMicroseconds(1000);  // پالس پایین
}

void stepDown() {
  digitalWrite(dirPin, 1);
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(1000);  // پالس بالا
  digitalWrite(stepPin, LOW);
  delayMicroseconds(1000);  // پالس پایین
}