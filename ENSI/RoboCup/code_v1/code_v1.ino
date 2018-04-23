#include <Wire.h>
#define uchar unsigned char
#define I1 3
#define I2 5
#define I3 6
#define I4 9
#define whiteConst 200
#define lc 300
#define trigPin 12
#define echoPin 13
#define S0 2
#define S1 4
#define S2 10
#define S3 11
#define sensorOut 7

int red = 0;
int blue = 0;
int green = 0;
int frequency = 0;
long duration;
int distance;
int sensor[16];
int sensorReading[8];
int activeSensor = 0;

int PWM_Right, PWM_Left;
uchar t;
int i = 0;

void setup() {
    Wire.begin();
    t = 0;
    pinMode(4, OUTPUT); //Left Motor Pin 1
    pinMode(5, OUTPUT); //Left Motor Pin 2
    pinMode(6, OUTPUT); //Right Motor Pin 1
    pinMode(7, OUTPUT); //Right Motor Pin 2
    pinMode(8, OUTPUT); //red light
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT); // Sets the echoPin as an Input
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);
    pinMode(22, OUTPUT);
    pinMode(sensorOut, INPUT);

    digitalWrite(8,LOW);
    digitalWrite(22,LOW);
    Serial.begin(9600); //Enable Serial Communications
}

void loop() {    
    digitalWrite(8,LOW);
    lineFollow();
//    i++;
//    if (i == 700){
//      test_distance();
//      //Serial.println("ok");
//      i=0;
//    } 
    //test_light();
    test_color();
    //delay(500);
}

void lineFollow() {
    readSensor();
    if (sensorReading[1] == 0 && sensorReading[2] == 1) {
        PWM_Right = 120;
        PWM_Left = 100;
        digitalWrite(22,LOW);
    }

    if (sensorReading[1] == 0 && sensorReading[2] == 0) {
        PWM_Right = 120;
        PWM_Left = 120;
        //Serial.println("avant");
        digitalWrite(22,LOW);
    }

    if (sensorReading[1] == 1 && sensorReading[2] == 0) {
        PWM_Right = 100;
        PWM_Left = 120;
        digitalWrite(22,LOW);
    }

    if (sensorReading[0] == 0 && sensorReading[1] == 1) {
        PWM_Right = 140;
        PWM_Left = 0;
        digitalWrite(22,LOW);
    }

    if (sensorReading[2] == 1 && sensorReading[3] == 0) {  
        PWM_Right = 0;
        PWM_Left = 140;
        digitalWrite(22,LOW);
    }

    if (sensorReading[0] == 0 && sensorReading[1] == 0 && sensorReading[2] == 0 && sensorReading[3] == 0) {      
        PWM_Right = 120;
        PWM_Left = 120;
        digitalWrite(22,LOW);
    }

//    if ((PWM_Right == 200 && PWM_Left == 0) || (PWM_Right == 0 && PWM_Left == 200)){
//      i++;
//    if (i == 80){
//      i=0;
//    } if (i <= 40){
//        digitalWrite(22,HIGH);
//        Serial.println(i);
//    } else if (i >= 40){
//        digitalWrite(22,LOW);
//        Serial.println(i);
//    } 
//    }
    
    analogWrite(3, PWM_Right);
    analogWrite(5, 0);
    analogWrite(6, 0);
    analogWrite(9, PWM_Left);
}

void readSensor() {
  sensorReading[0] = (analogRead(A0) <= whiteConst) ? 1 : 0;
  sensorReading[1] = (analogRead(A1) <= whiteConst) ? 1 : 0;
  sensorReading[2] = (analogRead(A2) <= whiteConst) ? 1 : 0;
  sensorReading[3] = (analogRead(A3) <= whiteConst) ? 1 : 0;
Serial.print(analogRead(A0));
Serial.print("   ");
Serial.print(analogRead(A1));
Serial.print("   ");
Serial.print(analogRead(A2));
Serial.print("   ");
Serial.print(analogRead(A3));

Serial.print("   ");
    for (int i = 0; i < 4; i++) {
//      Serial.print(sensorReading[i]);
        if (sensorReading[i] == 1) {
            activeSensor += 1;
        }
    }
//    Serial.print("    ");
//       Serial.print("[0]: ");
//       Serial.print(sensor[0]);
//       Serial.print("  [2]: ");
//       Serial.print(sensor[2]);
//       Serial.print("      [6]: ");
//       Serial.print(sensor[6]);
//       Serial.print("  [8]: ");
//       Serial.print(sensor[8]);
//       Serial.print("      [12]: ");
//       Serial.print(sensor[12]);
//       Serial.print("  [14]: ");
//       Serial.println(sensor[14]);
}

/********************************************************/

void test_distance() {


 digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW); 
  duration = pulseIn(echoPin, HIGH);
   
  distance = duration / 58; 
//  Serial.print("distance = ");
//  Serial.print(distance);
//  Serial.println("   ");  
    if (distance <= 40) {
        analogWrite(3, 0);
        analogWrite(5, 0);
        analogWrite(6, 0);
        analogWrite(9, 0);
        digitalWrite(8,HIGH);
        do {
            // Sets the trigPin on HIGH state for 10 micro seconds
            digitalWrite(trigPin, HIGH); 
            delayMicroseconds(10); 
            digitalWrite(trigPin, LOW); 
            duration = pulseIn(echoPin, HIGH);
             
            distance = duration / 58; 
//            Serial.print("while =     ");
//            Serial.print(distance);
//            Serial.println("   ");  
        } while (distance <= 30);
        analogWrite(3, 0);
        analogWrite(5, 0);
        analogWrite(6, 0);
        analogWrite(9, 0);
        delay(2000);
    }
}

/********************************************************/

void test_light() {
  Serial.println(analogRead(A1));
    if (analogRead(A1) <= lc) {
        analogWrite(4, 0);
        analogWrite(5, 0);
        analogWrite(6, 0);
        analogWrite(7, 0);
        do {
            delayMicroseconds(10);
        } while (analogRead(A1) <= lc);
    }
}

/********************************************************/

int color() {
    // Setting red filtered photodiodes to be read
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);
    // Reading the output frequency
    frequency = pulseIn(sensorOut, LOW);
    red = frequency;


    // Setting Green filtered photodiodes to be read
    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);
    // Reading the output frequency
    frequency = pulseIn(sensorOut, LOW);
    green = frequency;

    // Setting Blue filtered photodiodes to be read
    digitalWrite(S2, LOW);
    digitalWrite(S3, HIGH);
    // Reading the output frequency
    frequency = pulseIn(sensorOut, LOW);
    blue = frequency;

    return (((blue + green)/2 - red));
}

void test_color(){
  
  int x1 = color();
  int x2 = color();
  int x = (x1+x2)/2;
  Serial.print("color = ");
  Serial.print(x);
  if (x > 55){
    Serial.print("stopped = ");
    Serial.println(x);
    analogWrite(3, 0);
        analogWrite(5, 0);
        analogWrite(6, 0);
        analogWrite(9, 0);
        digitalWrite(8,HIGH);
        delay(10000);
        analogWrite(3, PWM_Right);
        analogWrite(5, 0);
        analogWrite(6, 0);
        analogWrite(9, PWM_Left);
  }else{
    Serial.println();
  }
}


