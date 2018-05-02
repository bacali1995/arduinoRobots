void (* resetFunc) (void) = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Setup! But check the LED state.");
  pinMode(13, OUTPUT);
  delay(5000);
}

void loop() {
  Serial.println("Main Loop!");
  for (int cnt = 0; cnt < 5; cnt++) {
    Serial.println(cnt);
    delay(500);
    digitalWrite(13, LOW);
    delay(500);
    digitalWrite(13, HIGH);
  }

  Serial.println("Reset?");
  delay(2000);
  resetFunc();

  // Code should never get to here
  Serial.println("Reset failed");
}
