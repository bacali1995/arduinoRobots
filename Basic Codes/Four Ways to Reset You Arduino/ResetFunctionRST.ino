#define rstPin 7

void setup() {
  digitalWrite(rstPin, HIGH);
  pinMode(rstPin, OUTPUT);

  Serial.begin(9600);
  Serial.println("Setup! Check the LED state.");
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

  Serial.println("Reset by RST?");
  delay(3000);
  digitalWrite(rstPin, LOW);

  // Code should never get to here
  Serial.println("Reset failed");
}
