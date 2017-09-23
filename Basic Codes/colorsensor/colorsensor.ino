/*     Arduino Color Sensing Tutorial
 *      
 *  by Dejan Nedelkovski, www.HowToMechatronics.com
 *  
 */
 
#define S0 30
#define S1 31
#define S2 32
#define S3 33
#define sensorOut 34

int red = 0;
int blue = 0;
int green = 0;
int frequency = 0;

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  
  // Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  digitalWrite(LED_BUILTIN,LOW);
  Serial.begin(9600);
}

void loop() {
  // Setting red filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  red = frequency;
  // Printing the value on the serial monitor
  /*Serial.print("R= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");*/

  // Setting Green filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  green = frequency;
  // Printing the value on the serial monitor
  /*Serial.print("G= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");*/

  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  blue = frequency;
  // Printing the value on the serial monitor
  /*Serial.print("B= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.println("  ");*/
  if (red<100 && green>100 && blue>100){
    digitalWrite(LED_BUILTIN,HIGH);
  } else {
    digitalWrite(LED_BUILTIN,LOW);
  }
}
