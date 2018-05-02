void setup() {
  Serial.begin(9600);
  Serial.println("Setup");

  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);

  // Relay trigger (OUTPUT pin defaults to LOW state)
  pinMode(8, OUTPUT);
}

void loop() {
  Serial.println("loop...");

  for (int cnt = 0; cnt < 10; cnt++) {
    digitalWrite(13, !digitalRead(13));
    Serial.println("LED flash!");
    delay(200);
  }
  digitalWrite(13,HIGH);

  Serial.println("Reset all power?");
  delay(500);
  digitalWrite(8, HIGH);

  // Code should never get here
  delay(1000);
  Serial.println("No RESET!");
  digitalWrite(8, LOW);
  delay(1000);
}
