#include <Wire.h>
#define uchar unsigned char
#define I1 4
#define I2 5
#define I3 6
#define I4 7
#define whiteConst 6
#define lc 300
#define trigPin 9
#define echoPin 10
#define S0 30
#define S1 31
#define S2 32
#define S3 33
#define sensorOut 34

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

void setup() {
    Wire.begin();
    t = 0;
    pinMode(4, OUTPUT); //Left Motor Pin 1
    pinMode(5, OUTPUT); //Left Motor Pin 2
    pinMode(6, OUTPUT); //Right Motor Pin 1
    pinMode(7, OUTPUT); //Right Motor Pin 2
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT); // Sets the echoPin as an Input
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);
    pinMode(sensorOut, INPUT);
    digitalWrite(S0, HIGH);
    digitalWrite(S1, LOW);
    Serial.begin(9600); //Enable Serial Communications
}

void loop() {
    lineFollow();
    //test_distance();
    test_light();
    //test_color();
    //delay(500);
}

void lineFollow() {
    readSensor();
    if (sensorReading[3] == 0 && sensorReading[4] == 1) {
        PWM_Right = 150;
        PWM_Left = 120;
    }

    if (sensorReading[3] == 0 && sensorReading[4] == 0) {
        PWM_Right = 150;
        PWM_Left = 150;
    }

    if (sensorReading[3] == 1 && sensorReading[4] == 0) {
        PWM_Right = 120;
        PWM_Left = 150;
    }

    if (sensorReading[0] == 0 && sensorReading[1] == 0) {
        PWM_Right = 200;
        PWM_Left = 0;
    }

    if (sensorReading[6] == 0 && sensorReading[7] == 0) {  
        PWM_Right = 0;
        PWM_Left = 200;
    }

    if (sensorReading[0] == 1 && sensorReading[1] == 0 && sensorReading[3] == 0 && sensorReading[4] == 1) {  
        PWM_Right = 150;
        PWM_Left = 40;
    }

    if (sensorReading[3] == 1 && sensorReading[4] == 0 && sensorReading[6] == 0 && sensorReading[7] == 1) {
        PWM_Right = 40;
        PWM_Left = 150;
    }

    if (activeSensor == 0) {      
        PWM_Right = 150;
        PWM_Left = 150;
    }
    analogWrite(4, PWM_Right);
    analogWrite(5, 0);
    analogWrite(6, 0);
    analogWrite(7, PWM_Left);
}

void readSensor() {
    activeSensor = 0;
    Wire.requestFrom(9, 16); // request 16 bytes from slave device #9
    while (Wire.available()) // slave may send less than requested
    {
        //sensor[t] = map(Wire.read(), 0, 255, 0, 1024);
        sensor[t] = Wire.read();
        if (t < 15)
            t++;
        else
            t = 0;
    }
    for (int i = 0; i < 8; i++) {
        sensorReading[i] = (sensor[2 * i] <= whiteConst) ? 1 : 0;
       // Serial.print(sensorReading[i]);
        if (sensorReading[i] == 1) {
            activeSensor += 1;
        }
    }
    //Serial.println();
       /*Serial.print("[0]: ");
       Serial.print(sensor[0]);
       Serial.print("  [2]: ");
       Serial.print(sensor[2]);
       Serial.print("      [6]: ");
       Serial.print(sensor[6]);
       Serial.print("  [8]: ");
       Serial.print(sensor[8]);
       Serial.print("      [12]: ");
       Serial.print(sensor[12]);
       Serial.print("  [14]: ");
       Serial.println(sensor[14]);*/
}

/********************************************************/

void test_distance() {
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);

    // Calculating the distance
    distance = duration * 0.034 / 2;

    if (distance <= 10) {
        analogWrite(4, 0);
        analogWrite(5, 0);
        analogWrite(6, 0);
        analogWrite(7, 0);
        do {
            // Clears the trigPin
            digitalWrite(trigPin, LOW);
            delayMicroseconds(2);

            // Sets the trigPin on HIGH state for 10 micro seconds
            digitalWrite(trigPin, HIGH);
            delayMicroseconds(10);
            digitalWrite(trigPin, LOW);

            // Reads the echoPin, returns the sound wave travel time in microseconds
            duration = pulseIn(echoPin, HIGH);

            // Calculating the distance
            distance = duration * 0.034 / 2;
        } while (distance <= 10);
        delay(500);
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

void test_color() {
    // Setting red filtered photodiodes to be read
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);
    // Reading the output frequency
    frequency = pulseIn(sensorOut, LOW);
    red = frequency;

//  Serial.print("red = ");
//  Serial.print(red);

    // Setting Green filtered photodiodes to be read
    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);
    // Reading the output frequency
    frequency = pulseIn(sensorOut, LOW);
    green = frequency;

//  Serial.print("   green= ");
//  Serial.print(green);
    // Setting Blue filtered photodiodes to be read
    digitalWrite(S2, LOW);
    digitalWrite(S3, HIGH);
    // Reading the output frequency
    frequency = pulseIn(sensorOut, LOW);
    blue = frequency;

//  Serial.print("   blue = ");
//  Serial.println(blue);
    if (red < 120 && green > 120 && blue > 120) {
        analogWrite(4, 0);
        analogWrite(5, 0);
        analogWrite(6, 0);
        analogWrite(7, 0);
        delay(10000);
        analogWrite(4, PWM_Right);
        analogWrite(5, 0);
        analogWrite(6, 0);
        analogWrite(7, PWM_Left);
        
    }

}
