#define I1 3
#define I2 5
#define I3 6
#define I4 9
#define niv 800

int sR[8];

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
     /* 
    Serial.print(digitalRead(2));
    Serial.print("   ");
    Serial.println(digitalRead(4));*/
}

void lineFollow() {
    readSensor();
    if (sR[0] == 1 && sR[1] == 1 && sR[2] == 1 && sR[3] == 1 && sR[4] == 1 && sR[5] == 1 && sR[6] == 1 && sR[7] == 1){
       PWM_Right = 120;
       PWM_Left = 120;
    } else if ((sR[0] == 1 && sR[1] == 1 && sR[2] == 1 && sR[3] == 0 && sR[4] == 0 && sR[5] == 0 && sR[6] == 0 && sR[7] == 0) ||
               (sR[0] == 1 && sR[1] == 1 && sR[2] == 0 && sR[3] == 0 && sR[4] == 0 && sR[5] == 0 && sR[6] == 0 && sR[7] == 0) ||
               (sR[0] == 1 && sR[1] == 0 && sR[2] == 0 && sR[3] == 0 && sR[4] == 0 && sR[5] == 0 && sR[6] == 0 && sR[7] == 0)){
       PWM_Right = 100;
       PWM_Left = -30;
    } else if((sR[0] == 1 && sR[1] == 1 && sR[2] == 1 && sR[3] == 1 && sR[4] == 1 && sR[5] == 1 && sR[6] == 0 && sR[7] == 0) ||
              (sR[0] == 1 && sR[1] == 1 && sR[2] == 1 && sR[3] == 1 && sR[4] == 1 && sR[5] == 0 && sR[6] == 0 && sR[7] == 0)){
       PWM_Right = 100;
       PWM_Left = -100;
    } else if((sR[0] == 0 && sR[1] == 0 && sR[2] == 0 && sR[3] == 0 && sR[4] == 0 && sR[5] == 1 && sR[6] == 1 && sR[7] == 1) ||
              (sR[0] == 0 && sR[1] == 0 && sR[2] == 0 && sR[3] == 0 && sR[4] == 0 && sR[5] == 0 && sR[6] == 1 && sR[7] == 1) ||
              (sR[0] == 0 && sR[1] == 0 && sR[2] == 0 && sR[3] == 0 && sR[4] == 0 && sR[5] == 0 && sR[6] == 0 && sR[7] == 1)){
      PWM_Right = -30;
      PWM_Left = 100;
    } else if((sR[0] == 0 && sR[1] == 0 && sR[2] == 1 && sR[3] == 1 && sR[4] == 1 && sR[5] == 1 && sR[6] == 1 && sR[7] == 1) ||
              (sR[0] == 0 && sR[1] == 0 && sR[2] == 0 && sR[3] == 1 && sR[4] == 1 && sR[5] == 1 && sR[6] == 1 && sR[7] == 1)){
       PWM_Right = -100;
       PWM_Left = 100;
    } else if (sR[0] == 0 && sR[1] == 0 && sR[2] == 0 && sR[3] == 1 && sR[4] == 1 && sR[5] == 1 && sR[6] == 1 && sR[7] == 0){
       PWM_Right = 80;
       PWM_Left = 120;
    } else if (sR[0] == 0 && sR[1] == 0 && sR[2] == 1 && sR[3] == 1 && sR[4] == 1 && sR[5] == 1 && sR[6] == 0 && sR[7] == 0){
       PWM_Right = 120;
       PWM_Left = 120;
    } else if (sR[0] == 0 && sR[1] == 1 && sR[2] == 1 && sR[3] == 1 && sR[4] == 1 && sR[5] == 0 && sR[6] == 0 && sR[7] == 0){
       PWM_Right = 100;
       PWM_Left = 80;
    }

        
    analogWrite(3, PWM_Right >= 0 ? PWM_Right : 0);
    analogWrite(5, PWM_Right < 0 ? abs(PWM_Right) : 0);
    analogWrite(6, PWM_Left < 0 ? abs(PWM_Left) : 0);
    analogWrite(9, PWM_Left >= 0 ? PWM_Left : 0);
}

void readSensor() {
  sR[0] = analogRead(A0) > niv ? 1 : 0;
  sR[1] = analogRead(A1) > niv ? 1 : 0;
  sR[2] = digitalRead(11);
  sR[3] = analogRead(A2) > niv ? 1 : 0;
  sR[4] = analogRead(A3) > niv ? 1 : 0;
  sR[5] = digitalRead(12);
  sR[6] = analogRead(A4) > niv ? 1 : 0;
  sR[7] = analogRead(A5) > niv ? 1 : 0;
  int i;
  Serial.print("\t\t");
  for(i = 0;i<8;i++){
    Serial.print(sR[i]);
  }
  Serial.println();

}
