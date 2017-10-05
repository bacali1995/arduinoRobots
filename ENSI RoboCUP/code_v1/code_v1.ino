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
<<<<<<< HEAD
float Kp = 50;   
float Ki = 0;
float Kd = 0;
float P = 0,I = 0,D = 0;
int error = 0;
int previousError = 0;
int sensor[16];
int sensorReading[8];
int n = 0;
float power = 0;

int PWM_Right, PWM_Left;
=======
float Kp=0.001,Ki=1,Kd=1.5;
float error=0, P=0, I=0, D=0, PID_value=0;
float previous_error=0, previous_I=0;
uchar sensor[16];
>>>>>>> parent of 80d994f... version 1.0.7
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
    //test_distance();
    //test_light();
    //test_color();
<<<<<<< HEAD
    //delay(500);
=======
    motor_control();
    Serial.println("MOVE");
>>>>>>> parent of 80d994f... version 1.0.7
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
<<<<<<< HEAD
  sensor[2]+=8;
  for(int i=0; i<8; i++) 
    {
      sensorReading[i] = (sensor[2*i] <= whiteConst)? 1 : 0;
      n += pow(2,i)*sensorReading[i];
      Serial.print(sensorReading[i]);
    }

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

void PID_program()
{ 
    readSensor();
    switch(n){
      case 199:
      case 0:
        error = 0;
        break;
      /***************/
      case 227:
        error = 500;
        break;
      case 225:
        error = 1000;
        break;
      case 241:
        error = 1500;
        break;  
      case 240:
        error = 2000;
        break;
      case 248:
        error = 2500;
        break;
      case 252:
        error = 3000;
        break;  
      case 254:
        error = 3500;
        break;
      /***************/
     
      case 135:
        error = -1000;
        break;
      case 143:
        error = -1500;
        break;  
      case 15:
        error = -2000;
        break;
      case 31:
        error = -2500;
        break;
      case 63:
        error = -3000;
        break;  
      case 127:
        error = -3500;
        break;
      /***************/
      default: 
        if (previousError == 3500) error = 4000;
        else if (previousError == -3500) error = -4000;
        else error = previousError;
        break;
    }
    
    n = 0;
    
    previousError = error;

    P = error * Kp * 0.001;
    I += error;
    I *= Ki;
    D = (error-previousError)*Kd;
    
    power = P + I + D; 
    //Serial.print("   ");
    Serial.print(power);
    Serial.print("   ");
    if( power>100 ) { power = 100.0; }
    if( power<-100.0 ) { power = -100.0; }
    if( power<0 ) // Turn left
    {
      PWM_Right = 100 + abs(int(power));
      PWM_Left = 100 ;
    }
    
    else // Turn right
    {
      PWM_Right = 100 ;
      PWM_Left = 100 + int(power);
    }

    Serial.print("PWM_Right = ");
    Serial.print(PWM_Right);
    Serial.print("  PWM_Left = ");
    Serial.println(PWM_Left);
   
}

void lineFollow(void) {
   PID_program();
   analogWrite(4,0);
   analogWrite(5,PWM_Right);
   analogWrite(6,PWM_Left-5 < 0 ? 0 : PWM_Left-5);
   analogWrite(7,0);
=======
  Serial.print("sensor[0]:");
  Serial.println(sensor[0]);
  Serial.print("sensor[2]:");
  Serial.println(sensor[2]);
  Serial.println();
  Serial.print("sensor[6]:");
  Serial.println(sensor[6]);
  Serial.print("sensor[8]:");
  Serial.println(sensor[8]);
  Serial.println();
  Serial.print("sensor[12]:");
  Serial.println(sensor[12]);
  Serial.print("sensor[14]:");
  Serial.println(sensor[14]);
  delay(2000);
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
>>>>>>> parent of 80d994f... version 1.0.7
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

  if (distance<=10){
    analogWrite(4,0);
    analogWrite(5,0);
    analogWrite(6,0);
    analogWrite(7,0);
    Serial.println("STOP_DISTANCE");
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
    }while(distance<=10);
    delay(500);
  }
}

void test_light(){
    if (analogRead(A1)<=lc){
      analogWrite(4,0);
      analogWrite(5,0);
      analogWrite(6,0);
      analogWrite(7,0);
      Serial.println("STOP_LIGHT");
      do{
        delayMicroseconds(10);
      }while(analogRead(A1)<=lc);
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
      Serial.println("STOP_COLOR");
      delay(10000);
      analogWrite(4,initial_motor_speed-PID_value);
      analogWrite(5,0);
      analogWrite(6,0);
      analogWrite(7,initial_motor_speed+PID_value);
      delay(500);
  } 
  
}

