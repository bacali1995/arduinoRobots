#include <Wire.h>
#define uchar unsigned char
#define I1 4
#define I2 5
#define I3 6
#define I4 7
#define whiteConst 95
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
float activeSensor = 0; // Count active sensors
float totalSensor = 0; // Total sensor readings
float avgSensor = 4.5; // Average sensor reading

float Kp = 72; // Max deviation = 8-4.5 = 3.5 ||  255/3.5 = 72
float Ki = 0.00015;
float Kd = 5;

float error = 0;
float previousError = 0;
float totalError = 0;
float power = 0;

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
    //test_light();
    //test_color();
    //delay(500);
}

void readSensor() {
    Wire.requestFrom(9, 16); // request 16 bytes from slave device #9
    while (Wire.available()) // slave may send less than requested
    {
        sensor[t] = map(Wire.read(), 0, 255, 0, 1024);
        if (t < 15)
            t++;
        else
            t = 0;
    }
    sensor[2] += 8;
    for (int i = 0; i < 8; i++) {
        sensorReading[i] = (sensor[2 * i] <= whiteConst) ? 1 : 0;
        Serial.print(sensorReading[i]);
        if (sensorReading[i] == 1) {
            activeSensor += 1;
        }
        totalSensor += sensorReading[i] * (i + 1);
    }

    avgSensor = totalSensor / activeSensor;
    activeSensor = 0;
    totalSensor = 0;

    /*Serial.print("[0]: ");
   Serial.print(sensor[0]);
  Serial.print("  [2]: ");
   Serial.print(sensor[2]);
   Serial.print("  [4]: ");
   Serial.print(sensor[4]);
   Serial.print("  [6]: ");
   Serial.print(sensor[6]);
   Serial.print("  [8]: ");
   Serial.print(sensor[8]);
   Serial.print("  [10]: ");
   Serial.print(sensor[10]);
   Serial.print("  [12]: ");
   Serial.print(sensor[12]);
   Serial.print("  [14]: ");
   Serial.println(sensor[14]);*/

    Serial.print("  ");
    //Serial.print(n);
    /*Serial.println(currentPos);*/
}

void PID_program() {
    readSensor();
    previousError = error; // save previous error for differential 
    error = avgSensor - 4.5; // Count how much robot deviate from center
    totalError += error; // Accumulate error for integral

    power = (Kp * error) + (Kd * (error - previousError)) + (Ki * totalError);

    //Serial.print("   ");
    Serial.print(power);
    Serial.print("   ");
    if (power > 100) {
        power = 100.0;
    }
    if (power<-100.0) {
        power = -100.0;
    }
    if (power < 0) // Turn left
    {
        PWM_Right = 100 + abs(int(power));
        PWM_Left = 100;
    } else // Turn right
    {
        PWM_Right = 100;
        PWM_Left = 100 + int(power);
    }

    Serial.print("PWM_Right = ");
    Serial.print(PWM_Right);
    Serial.print("  PWM_Left = ");
    Serial.println(PWM_Left);

}

void lineFollow(void) {
    PID_program();
    analogWrite(4, 0);
    analogWrite(5, PWM_Right);
    analogWrite(6, PWM_Left - 5 < 0 ? 0 : PWM_Left - 5);
    analogWrite(7, 0);
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
        Serial.println("STOP_DISTANCE");
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

void test_light() {
    if (analogRead(A1) <= lc) {
        analogWrite(4, 0);
        analogWrite(5, 0);
        analogWrite(6, 0);
        analogWrite(7, 0);
        Serial.println("STOP_LIGHT");
        do {
            delayMicroseconds(10);
        } while (analogRead(A1) <= lc);
    }
}

void test_color() {
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

    if (red < 100 && green > 100 && blue > 100) {
        analogWrite(4, 0);
        analogWrite(5, 0);
        analogWrite(6, 0);
        analogWrite(7, 0);
        Serial.println("STOP_COLOR");
        delay(10000);
        analogWrite(4, PWM_Right);
        analogWrite(5, 0);
        analogWrite(6, 0);
        analogWrite(7, PWM_Left);
        delay(500);
    }

}
