

void stepUp() {
  digitalWrite(stepEnable, LOW);
  digitalWrite(dirPin, 0);
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(1000); 
  digitalWrite(stepPin, LOW);
  delayMicroseconds(1000);  
  digitalWrite(stepEnable, HIGH);
}

void stepDown() {
  digitalWrite(stepEnable, LOW);
  digitalWrite(dirPin, 1);
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(1000);  
  digitalWrite(stepPin, LOW);
  delayMicroseconds(1000); 
  digitalWrite(stepEnable, HIGH);
}