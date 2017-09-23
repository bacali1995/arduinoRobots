void setup() {
 // put your setup code here, to run once:
 Serial.begin(9600);
  pinMode(13,OUTPUT);
}
void loop() {
 // put your main code here, to run repeatedly:
digitalWrite(13,HIGH);
 Serial.print("AD0:");
 Serial.print(analogRead(A0));
Serial.print(" \t ");
 Serial.print("AD1:");
 Serial.print(analogRead(A1));
Serial.print(" \t ");
 Serial.print("AD2:");
 Serial.println(analogRead(A2));
 delay(500);
}
