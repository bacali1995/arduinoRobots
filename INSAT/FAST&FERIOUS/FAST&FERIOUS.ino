#define I1 11
#define I2 6
#define I3 5
#define I4 3
#define niv 700

int sR[8];

int a = 0;

int PWM_Right, PWM_Left;

void setup() {
  Serial.begin(9600);
  pinMode(I1, OUTPUT); //Left Motor Pin 1
  pinMode(I2, OUTPUT); //Left Motor Pin 2
  pinMode(I3, OUTPUT); //Right Motor Pin 1
  pinMode(I4, OUTPUT); //Right Motor Pin 2
  /*pinMode(E1, OUTPUT); 
  pinMode(E2, OUTPUT); */
}

void loop() {
  lineFollow();
  /*
  analogWrite(I1,0);
  analogWrite(I2,120);
  analogWrite(I3,0);
  analogWrite(I4,120);
  */
}
#define LEFT 111
#define RIGHT 222
int dir = LEFT;
void lineFollow() {
    readSensor();
    if (!sR[0] && !sR[1] && !sR[2] && !sR[4] && !sR[5] && !sR[6] && !sR[7]){
      if (dir==LEFT){
        PWM_Right = 80;
        PWM_Left = -80;
      }else if (dir==RIGHT){
        PWM_Right = -60;
        PWM_Left = 80;        
      }
      /*
    }else if((sR[0] && !sR[1] && !sR[2] && !sR[4] && !sR[5] && !sR[6] && !sR[7])
    || (sR[0] && sR[1] && !sR[2] && !sR[4] && !sR[5] && !sR[6] && !sR[7])
    || (sR[0] && sR[1] && sR[2]  && sR[4] && sR[5] && sR[6] && !sR[7])
    || (sR[0] && sR[1] && sR[2]  && sR[4] && sR[5] && !sR[6] && !sR[7])
    || (sR[0] && sR[1] && sR[2]  && sR[4] && !sR[5] && !sR[6] && !sR[7])){
    */
    } else if (sR[0] && !sR[7]){
        PWM_Right = 90;
        PWM_Left = 0;
        dir = LEFT;
    }else if (!sR[0] && sR[7]){
        PWM_Right = 0;
        PWM_Left = 90;
        dir = RIGHT;
    } else if(sR[0] && sR[1] && sR[2]  && !sR[4] && !sR[5] && !sR[6] && !sR[7]){
      PWM_Right = 110;
      PWM_Left = 70;
    }else if(!sR[0] && sR[1] && sR[2] && !sR[4] && !sR[5] && !sR[6] && !sR[7]){
      PWM_Right = 110;
      PWM_Left = 90;
    }else if((!sR[0] && !sR[1] && sR[2] && sR[4] && !sR[5] && !sR[6] && !sR[7])
    ||(!sR[0] && !sR[1] && !sR[2] && sR[4] && sR[5] && !sR[6] && !sR[7])){
        PWM_Right = 120;
        PWM_Left = 120;
    }else if(!sR[0] && !sR[1] && !sR[2]  && sR[4] && sR[5] && sR[6] && !sR[7]){
      PWM_Right = 90;
      PWM_Left = 110;
    }else if(!sR[0] && !sR[1] && !sR[2]  && !sR[4] && sR[5] && sR[6] && sR[7]){
      PWM_Right = 70;
      PWM_Left = 110;
      /*
    }else if((!sR[0] && !sR[1] && !sR[2]  && !sR[4] && !sR[5] && !sR[6] && sR[7])
    || (!sR[0] && !sR[1] && !sR[2]  && !sR[4] && !sR[5] && sR[6] && sR[7])
    || (!sR[0] && sR[1] && sR[2] && sR[4] && sR[5] && sR[6] && sR[7])
    || (!sR[0] && !sR[1] && sR[2] && sR[4] && sR[5] && sR[6] && sR[7])
    || (!sR[0] && !sR[1] && !sR[2] && sR[4] && sR[5] && sR[6] && sR[7])){*/
    } 
    /*
    digitalWrite(I1,PWM_Right>-1?LOW:HIGH);
    digitalWrite(I2,PWM_Right<0?LOW:HIGH);
    digitalWrite(I3,PWM_Left<0?LOW:HIGH);
    digitalWrite(I4,PWM_Left>-1?LOW:HIGH);
    analogWrite(E1,abs(PWM_Right));
    analogWrite(E2,abs(PWM_Left>0?PWM_Left-15:PWM_Left));*/
    analogWrite(I1,PWM_Left>-1?PWM_Left:0);
    analogWrite(I2,PWM_Left<0?abs(PWM_Left):0);
    analogWrite(I3,PWM_Right>-1?PWM_Right:0);
    analogWrite(I4,PWM_Right<0?abs(PWM_Right):0);
    /*if ((!sR[0] && !sR[1] && !sR[2]  && !sR[4] && !sR[5] && !sR[6] && sR[7]) 
    || (sR[0] && !sR[1] && !sR[2]  && !sR[4] && !sR[5] && !sR[6] && !sR[7])){
      delay(100);
    }*/ 
}

void readSensor() {
  sR[0] = analogRead(A0) < niv ? 1 : 0;
  sR[1] = analogRead(A1) < niv ? 1 : 0;
  sR[2] = analogRead(A2) < niv ? 1 : 0;
  //sR[3] = analogRead(A3) < niv ? 1 : 0;
  sR[4] = analogRead(A4) < niv ? 1 : 0;
  sR[5] = analogRead(A5) < niv ? 1 : 0;
  sR[6] = 1-digitalRead(4);
  sR[7] = 1-digitalRead(12);
  
    int i;
    
  //Serial.print("\t\t");
  for(i = 0;i<8;i++){
    Serial.print(sR[i]);
  }
  //Serial.print("   ");
  //Serial.print(a);
  Serial.println();

}
