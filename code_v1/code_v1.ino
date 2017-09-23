#include <Wire.h>
#define uchar unsigned char
#define I1 4
#define I2 5
#define I3 6
#define I4 7
#define whiteConst 300
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
float Kp=0,Ki=0,Kd=0;
float error=0, P=0, I=0, D=0, PID_value=0;
float previous_error=0, previous_I=0;
uchar sensor[16];
uchar t;
int initial_motor_speed=100;

void read_sensor_values(void);
void caulate_pid(void);
void motor_control(void);
void test_distance(void);
void test_light(void);
void test_color(void);

void setup()
{
 Wire.begin();    
 t = 0;
 pinMode(4,OUTPUT); //Left Motor Pin 1
 pinMode(5,OUTPUT); //Left Motor Pin 2
 pinMode(6,OUTPUT); //Right Motor Pin 1
 pinMode(7,OUTPUT); //Right Motor Pin 2
 pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
 pinMode(echoPin, INPUT); // Sets the echoPin as an Input
 pinMode(S0, OUTPUT);
 pinMode(S1, OUTPUT);
 pinMode(S2, OUTPUT);
 pinMode(S3, OUTPUT);
 pinMode(sensorOut, INPUT);
 digitalWrite(S0,HIGH);
 digitalWrite(S1,LOW);
 Serial.begin(9600); //Enable Serial Communications
}

void loop()
{
    read_sensor_values();
    calculate_pid();
    test_distance();
    test_light();
    test_color();
    motor_control();
}

void read_sensor_values()
{
  Wire.requestFrom(9, 16);    // request 16 bytes from slave device #9
  while (Wire.available())   // slave may send less than requested
  {
    sensor[t] = Wire.read(); // receive a byte as character
    if (t < 15)
      t++;
    else
      t = 0;
  }
  
  if((sensor[0]<=whiteConst)&&(sensor[2]<=whiteConst)&&(sensor[6]<=whiteConst)&&(sensor[8]<=whiteConst)&&(sensor[12]<=whiteConst)&&(sensor[14]>whiteConst))
  error=5;
  else if((sensor[0]<=whiteConst)&&(sensor[2]<=whiteConst)&&(sensor[6]<=whiteConst)&&(sensor[8]<=whiteConst)&&(sensor[12]>whiteConst)&&(sensor[14]>whiteConst))
  error=4;
  else if((sensor[0]<=whiteConst)&&(sensor[2]<=whiteConst)&&(sensor[6]<=whiteConst)&&(sensor[8]<=whiteConst)&&(sensor[12]>whiteConst)&&(sensor[14]<=whiteConst))
  error=3;
  else if((sensor[0]<=whiteConst)&&(sensor[2]<=whiteConst)&&(sensor[6]<=whiteConst)&&(sensor[8]>whiteConst)&&(sensor[12]>whiteConst)&&(sensor[14]<=whiteConst))
  error=2;
  else if((sensor[0]<=whiteConst)&&(sensor[2]<=whiteConst)&&(sensor[6]<=whiteConst)&&(sensor[8]>whiteConst)&&(sensor[12]<=whiteConst)&&(sensor[14]<=whiteConst))
  error=1;
  else if((sensor[0]<=whiteConst)&&(sensor[2]<=whiteConst)&&(sensor[6]>whiteConst)&&(sensor[8]>whiteConst)&&(sensor[12]<=whiteConst)&&(sensor[14]<=whiteConst))
  error=0;
  else if((sensor[0]<=whiteConst)&&(sensor[2]<=whiteConst)&&(sensor[6]>whiteConst)&&(sensor[8]<=whiteConst)&&(sensor[12]<=whiteConst)&&(sensor[14]<=whiteConst))
  error=-1;
  else if((sensor[0]<=whiteConst)&&(sensor[2]>whiteConst)&&(sensor[6]>whiteConst)&&(sensor[8]<=whiteConst)&&(sensor[12]<=whiteConst)&&(sensor[14]<=whiteConst))
  error=-2;
  else if((sensor[0]<=whiteConst)&&(sensor[2]>whiteConst)&&(sensor[6]<=whiteConst)&&(sensor[8]<=whiteConst)&&(sensor[12]<=whiteConst)&&(sensor[14]<=whiteConst))
  error=-3;
  else if((sensor[0]>whiteConst)&&(sensor[2]>whiteConst)&&(sensor[6]<=whiteConst)&&(sensor[8]<=whiteConst)&&(sensor[12]<=whiteConst)&&(sensor[14]<=whiteConst))
  error=-4;
  else if((sensor[0]>whiteConst)&&(sensor[2]<=whiteConst)&&(sensor[6]<=whiteConst)&&(sensor[8]<=whiteConst)&&(sensor[12]<=whiteConst)&&(sensor[14]<=whiteConst))
  error=-5;
  else if((sensor[0]<=whiteConst)&&(sensor[1]<=whiteConst)&&(sensor[2]<=whiteConst)&&(sensor[4]<=whiteConst)&&(sensor[4]<=whiteConst))
    if(error==-5) error=-6;
    else error=6;
}

void calculate_pid()
{
    P = error;
    I = I + previous_I;
    D = error-previous_error;
    
    PID_value = (Kp*P) + (Ki*I) + (Kd*D);
    
    previous_I=I;
    previous_error=error;
}

void motor_control()
{
    // Calculating the effective motor speed:
    int left_motor_speed = initial_motor_speed-PID_value;
    int right_motor_speed = initial_motor_speed+PID_value;
    
    // The motor speed should not exceed the max PWM value
    constrain(left_motor_speed,0,255);
    constrain(right_motor_speed,0,255);
    
    //following lines of code are to make the bot move forward
    /*The pin numbers and high, low values might be different
    depending on your connections */
    analogWrite(4,initial_motor_speed-PID_value);
    analogWrite(5,0);
    analogWrite(6,0);
    analogWrite(7,initial_motor_speed+PID_value);
}

void test_distance(){
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
  distance= duration*0.034/2;

  if (distance<=5){
    analogWrite(4,0);
    analogWrite(5,0);
    analogWrite(6,0);
    analogWrite(7,0);
    do{
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
      distance= duration*0.034/2;
    }while(distance<=5);
    delay(500);
  }
}

void test_light(){
    if (analogRead(A1)>=lc){
      analogWrite(4,0);
      analogWrite(5,0);
      analogWrite(6,0);
      analogWrite(7,0);
      do{
        delayMicroseconds(10);
      }while(analogRead(A1)>=lc);
    }
}

void test_color(){
  // Setting red filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  red = frequency;

  // Setting Green filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  green = frequency;

  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  blue = frequency;
  
  if (red<100 && green>100 && blue>100){
      analogWrite(4,0);
      analogWrite(5,0);
      analogWrite(6,0);
      analogWrite(7,0);
      delay(10000);
  } 
}

