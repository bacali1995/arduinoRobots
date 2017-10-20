#define I1 3
#define I2 5
#define I3 6
#define I4 9
#define whiteConst 850

int sensorReading[6];

int PWM_Right, PWM_Left;

void setup() {
    pinMode(3, OUTPUT); //Left Motor Pin 1
    pinMode(5, OUTPUT); //Left Motor Pin 2
    pinMode(6, OUTPUT); //Right Motor Pin 1
    pinMode(9, OUTPUT); //Right Motor Pin 2
    Serial.begin(9600); //Enable Serial Communications
}

void loop() {    
    lineFollow();
}

void lineFollow() {
    readSensor();
    if (sensorReading[0] == 1 && sensorReading[1] == 1 &&
        sensorReading[2] == 1 && sensorReading[3] == 1 &&
        sensorReading[4] == 1 && sensorReading[5] == 0){
          PWM_Right = 0;
          PWM_Left = 100;
    } else if (sensorReading[0] == 1 && sensorReading[1] == 1 &&
        sensorReading[2] == 1 && sensorReading[3] == 1 &&
        sensorReading[4] == 0 && sensorReading[5] == 0){
          PWM_Right = 30;
          PWM_Left = 100;
    } else if (sensorReading[0] == 1 && sensorReading[1] == 1 &&
        sensorReading[2] == 1 && sensorReading[3] == 0 &&
        sensorReading[4] == 0 && sensorReading[5] == 0){
          PWM_Right = 60;
          PWM_Left = 100;
    } else if (sensorReading[0] == 1 && sensorReading[1] == 1 &&
        sensorReading[2] == 0 && sensorReading[3] == 0 &&
        sensorReading[4] == 0 && sensorReading[5] == 0){
          PWM_Right = 80;
          PWM_Left = 100;
    } else if (sensorReading[0] == 1 && sensorReading[1] == 0 &&
        sensorReading[2] == 0 && sensorReading[3] == 0 &&
        sensorReading[4] == 0 && sensorReading[5] == 1){
          PWM_Right = 100;
          PWM_Left = 100;
    }else /***/ if (sensorReading[0] == 0 && sensorReading[1] == 0 &&
        sensorReading[2] == 0 && sensorReading[3] == 0 &&
        sensorReading[4] == 1 && sensorReading[5] == 1){
          PWM_Right = 100;
          PWM_Left = 80;
    } else if (sensorReading[0] == 0 && sensorReading[1] == 0 &&
        sensorReading[2] == 0 && sensorReading[3] == 1 &&
        sensorReading[4] == 1 && sensorReading[5] == 1){
          PWM_Right = 100;
          PWM_Left = 60;
    } else if (sensorReading[0] == 0 && sensorReading[1] == 0 &&
        sensorReading[2] == 1 && sensorReading[3] == 1 &&
        sensorReading[4] == 1 && sensorReading[5] == 1){
          PWM_Right = 100;
          PWM_Left = 30;
    } else if (sensorReading[0] == 0 && sensorReading[1] == 1 &&
        sensorReading[2] == 1 && sensorReading[3] == 1 &&
        sensorReading[4] == 1 && sensorReading[5] == 1){
          PWM_Right = 100;
          PWM_Left = 0;
    }
    
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
  sensorReading[4] = (analogRead(A4) <= whiteConst) ? 1 : 0;
  sensorReading[5] = (analogRead(A5) <= whiteConst) ? 1 : 0;
  int i;
  for(i = 0;i<6;i++){
    Serial.print(sensorReading[i]);
  }
  Serial.println();
/*Serial.print(analogRead(A0));
Serial.print("   ");
Serial.print(analogRead(A1));
Serial.print("   ");
Serial.print(analogRead(A2));
Serial.print("   ");
Serial.print(analogRead(A3));
Serial.print("   ");
Serial.print(analogRead(A4));
Serial.print("   ");
Serial.println(analogRead(A5));*/
}
