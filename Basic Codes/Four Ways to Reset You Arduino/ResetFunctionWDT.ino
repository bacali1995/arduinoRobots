#include <avr/wdt.h>

void setup() {
  wdt_disable();
  Serial.begin(9600);
  Serial.println("Setup! Check the LED.");
  pinMode(13, OUTPUT);
  delay(5000);
  wdt_enable(WDTO_2S);
}

void loop() {
  Serial.println("Main Loop!");
  for (int cnt = 0; cnt < 5; cnt++) {
    Serial.println(cnt);
    delay(500);
    digitalWrite(13, LOW);
    delay(500);
    digitalWrite(13, HIGH);
    wdt_reset();
  }

  Serial.println("Reset by Watch Dog?");
  delay(3000);

  // Code should never get to here
  Serial.println("Reset failed");
}
