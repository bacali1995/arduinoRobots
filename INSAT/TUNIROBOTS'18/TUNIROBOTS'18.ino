#include <Servo.h>
#include <PS2X_lib.h>  //for v1.6

#define ll long long
#define speedMedium 90
#define speedVal 110
PS2X ps2x; // create PS2 Controller Class
Servo servo1;

#define IN_11  3        // L298N #1 in 1 motor Front Right
#define IN_12  5        // L298N #1 in 2 motor Front Right
#define IN_21  6       // L298N #2 in 1 motor Front Left
#define IN_22  11        // L298N #2 in 2 motor Front Left

//right now, the library does NOT support hot pluggable controllers, meaning 
//you must always either restart your Arduino after you conect the controller, 
//or call config_gamepad(pins) again after connecting the controller.
int error = 0; 
byte type = 0;
byte vibrate = 0;
int direction_value;
int speed_value;
int speed_left;
int speed_right;
int i = 0;
int oldVal;
int oldValRight;
int oldValLeft;
double dirPower = 1.1;
double speedPower = 1.3;
bool servo = false;

void setup(){
  
 Serial.begin(9600);
 servo1.attach(9);
 servo1.write(130);
 pinMode(A4,OUTPUT);
 pinMode(A5,OUTPUT);

 //CHANGES for v1.6 HERE!!! *************PAY ATTENTION************
  
 error = ps2x.config_gamepad(8,4,7,2, true, true);   
 //GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
 
 if(error == 0){
   Serial.println("Found Controller, configured successful");
   Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
  Serial.println("holding L1 or R1 will print out the analog stick values.");
  Serial.println("Go to www.billporter.info for updates and to report bugs.");
 }
   
  else if(error == 1)
   Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  else if(error == 2)
   Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
   
  else if(error == 3)
   Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
   
   //Serial.print(ps2x.Analog(1), HEX);
   
   type = ps2x.readType(); 
     switch(type) {
       case 0:
        Serial.println("Unknown Controller type");
       break;
       case 1:
        Serial.println("DualShock Controller Found");
       break;
       case 2:
         Serial.println("GuitarHero Controller Found");
       break;
     }
    digitalWrite(A4,HIGH);
    digitalWrite(A5,HIGH);
    delay(500);
    digitalWrite(A4,LOW);
    digitalWrite(A5,LOW);
    delay(500);
    digitalWrite(A4,HIGH);
    digitalWrite(A5,HIGH);
    delay(500);
    digitalWrite(A4,LOW);
    digitalWrite(A5,LOW);
    oldVal = analogRead(A0);
    oldValRight = analogRead(A1);
    oldValLeft = analogRead(A2);
}

bool mode = true;

void loop(){ 
  
  //Serial.println(lazerDecoder());
  //Serial.println(analogRead(A0));
  /*if (lazerPID()==1){
    Serial.println("ok");
  }*/
  if (mode){
    guided();
  }else{
    lazerFollower();
  } 
}


void guided(){
  
 if(error == 1) //skip loop if no controller found
  return; 
  
 if(type == 2){ //Guitar Hero Controller
   
   ps2x.read_gamepad();          //read controller 
   
   if(ps2x.ButtonPressed(GREEN_FRET))
     Serial.println("Green Fret Pressed");
   if(ps2x.ButtonPressed(RED_FRET))
     Serial.println("Red Fret Pressed");
   if(ps2x.ButtonPressed(YELLOW_FRET))
     Serial.println("Yellow Fret Pressed");
   if(ps2x.ButtonPressed(BLUE_FRET))
     Serial.println("Blue Fret Pressed");
   if(ps2x.ButtonPressed(ORANGE_FRET))
     Serial.println("Orange Fret Pressed");
     

    if(ps2x.ButtonPressed(STAR_POWER))
     Serial.println("Star Power Command");
    
    if(ps2x.Button(UP_STRUM))          //will be TRUE as long as button is pressed
     Serial.println("Up Strum");
    if(ps2x.Button(DOWN_STRUM))
     Serial.println("DOWN Strum");
  
 
    if(ps2x.Button(PSB_START))                   //will be TRUE as long as button is pressed
         Serial.println("Start is being held");
    if(ps2x.Button(PSB_SELECT))
         Serial.println("Select is being held");

    
    if(ps2x.Button(ORANGE_FRET)) // print stick value IF TRUE
    {
        Serial.print("Wammy Bar Position:");
        Serial.println(ps2x.Analog(WHAMMY_BAR), DEC); 
    } 
 }

 else { //DualShock Controller
  
    ps2x.read_gamepad(false, vibrate);          //read controller and set large motor to spin at 'vibrate' speed
    
    if(ps2x.Button(PSB_START))                   //will be TRUE as long as button is pressed
         Serial.println("Start is being held");
    if(ps2x.Button(PSB_SELECT))
         Serial.println("Select is being held");
         
         
     if(ps2x.Button(PSB_PAD_UP)) {         //will be TRUE as long as button is pressed
       Serial.print("Up held this hard: ");
       Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
      }
      if(ps2x.Button(PSB_PAD_RIGHT)){
       Serial.print("Right held this hard: ");
        Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
      }
      if(ps2x.Button(PSB_PAD_LEFT)){
       Serial.print("LEFT held this hard: ");
        Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
      }
      if(ps2x.Button(PSB_PAD_DOWN)){
       Serial.print("DOWN held this hard: ");
     Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
      }   
  
    
      vibrate = ps2x.Analog(PSAB_BLUE);        //this will set the large motor vibrate speed based on 
                                              //how hard you press the blue (X) button    
    
    if (ps2x.NewButtonState())               //will be TRUE if any button changes state (on to off, or off to on)
    {
     
        if(ps2x.Button(PSB_L3))
         Serial.println("L3 pressed");
        if(ps2x.Button(PSB_R3))
         Serial.println("R3 pressed");
        if(ps2x.Button(PSB_L2))
         Serial.println("L2 pressed");
        if(ps2x.Button(PSB_R2))
         Serial.println("R2 pressed");
        if(ps2x.Button(PSB_GREEN))
         Serial.println("Triangle pressed");
         
    }   
         
    /*if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) // print stick values if either is TRUE
    {
        Serial.println("Stick Values:");
        dirPower = 0.5;
        speedPower = 0.7;
    } else {
        dirPower = 0.9;
        speedPower = 1.3;
    }*/
    
    if(ps2x.ButtonPressed(PSB_RED)){            
      if (servo){
        servo1.write(55);
      }else{
        servo1.write(130);
      }
      servo = 1 - servo;
    } else if(ps2x.ButtonPressed(PSB_PINK)) { 
      
      Serial.println("FORDECODE");
      Serial.println(lazerDecoder());        

    } else if(ps2x.ButtonPressed(PSB_BLUE))  {

    } else if(ps2x.ButtonPressed(PSB_GREEN)){
      mode = 1 - mode;
      digitalWrite(A4,HIGH);
      digitalWrite(A5,HIGH);
    }else if (ps2x.Analog(PSS_RY)<50){
      if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) {
        avance_high();
      }else{ avance();}
    }else if (ps2x.Analog(PSS_RY)>200){
      Recule(); 
    }else if (ps2x.Analog(PSS_LX)<50){
      if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) {
        virageDroite();
      }
      else {AngleDroite();}
    }else if (ps2x.Analog(PSS_LX)>200){
      if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) {
        virageGauche();
      }
      else {AngleGauche();}
    }else{
      stopp();
    }
    /*} else {
      direction_value = dirPower*(ps2x.Analog(PSS_LX)-128);
       
      speed_value = speedPower *(ps2x.Analog(PSS_RY)-128);
      speed_right = (direction_value >= 0) ? speed_value - direction_value : speed_value + abs(direction_value);
      speed_left = (direction_value < 0) ? speed_value - abs(direction_value) : speed_value + direction_value;

      // motor Front Left
      analogWrite(IN_21, (speed_left <= 0) ? min(abs(speed_left),255) : 0);
      analogWrite(IN_22, (speed_left > 0) ? min(speed_left,255) : 0);

      // motor Front Right
      
      analogWrite(IN_11, (speed_right > 0) ? min(speed_right,240) : 0);
      analogWrite(IN_12, (speed_right <= 0) ? min(abs(speed_right),240) : 0);
    
    }*/
    
    lazerPID();
    
 }
 
 
 delay(50);
}
void avance() {
  Serial.println("avance");
  analogWrite(IN_11,LOW);
  analogWrite(IN_12,speedVal-30);
  analogWrite(IN_21,speedVal);
  analogWrite(IN_22,LOW);
}
void avance_high() {
  analogWrite(IN_11,255);
  analogWrite(IN_12,LOW);
  analogWrite(IN_21,LOW);
  analogWrite(IN_22,255);
}
void virageGauche() { 
  Serial.println("gauche");
  analogWrite(IN_11,LOW);
  analogWrite(IN_12,LOW);
  analogWrite(IN_21,LOW);
  analogWrite(IN_22,250);  
}

void virageDroite() { 
  Serial.println("droite");
  analogWrite(IN_11,250);
  analogWrite(IN_12,LOW);
  analogWrite(IN_21,LOW);
  analogWrite(IN_22,LOW);
}

void AngleGauche() { 
  analogWrite(IN_11,LOW);
  analogWrite(IN_12,150); 
  analogWrite(IN_21,LOW);
  analogWrite(IN_22,150);
}
void AngleDroite() { 
  analogWrite(IN_11,150);
  analogWrite(IN_12,LOW); 
  analogWrite(IN_21,150);
  analogWrite(IN_22,LOW); 
}
void Recule() {
  Serial.println("recule");
  analogWrite(IN_11,80);
  analogWrite(IN_12,LOW); 
  analogWrite(IN_21,LOW);
  analogWrite(IN_22,110); 
}
void stopp() {
  analogWrite(IN_11,LOW);
  analogWrite(IN_12,LOW);
  analogWrite(IN_21,LOW);
  analogWrite(IN_22,LOW);
}

void lazerFollower(){
  ps2x.read_gamepad(false, vibrate);  
  if (ps2x.ButtonPressed(PSB_GREEN)){
    mode = 1 - mode;
    digitalWrite(A4,LOW);
    digitalWrite(A5,LOW);
  }
  forward();
  if (lazerRight()){
    right();
  }else if (lazerLeft()){
    left();
  }
}

void forward() {
  analogWrite(IN_22, speedMedium);
  analogWrite(IN_21, 0);
  analogWrite(IN_12, 0);
  analogWrite(IN_11, speedMedium-30);
}

void right() {
  analogWrite(IN_22, speedMedium);
  analogWrite(IN_21, 0);
  analogWrite(IN_12, speedMedium-30);
  analogWrite(IN_11, 0);
  delay(550);
  analogWrite(IN_22, 0);
  analogWrite(IN_21, 0);
  analogWrite(IN_12, 0);
  analogWrite(IN_11, 0);
}

void left() {
  analogWrite(IN_22, 0);
  analogWrite(IN_21, speedMedium);
  analogWrite(IN_12, 0);
  analogWrite(IN_11, speedMedium-30);
  delay(550);
  analogWrite(IN_22, 0);
  analogWrite(IN_21, 0);
  analogWrite(IN_12, 0);
  analogWrite(IN_11, 0);
}

char lazerDecoder(){
  int i = 0;
  int dash = 0;
  int dot = 0;
  int tim = 0;
  while(i<4){
    if ((tim=getLazerTime())>240){
      dash++;
    }else{
      dot++;
    }
    Serial.println(tim);
    i++;
  }
  Serial.print(dot);Serial.print("  ");Serial.println(dash);
  if (dot>0){
    digitalWrite(A4,HIGH);
    digitalWrite(A5,LOW);
    return 'V';
  }else{
    digitalWrite(A4,LOW);
    digitalWrite(A5,HIGH);
    return 'O';
  }
}

int getLazerTime(){
  while(lazerPID()!=1);
  ll startTime = millis();
  while(lazerPID()!=2);
  return millis() - startTime;
}

int lazerPID(){
  int val = analogRead(A0);
  if (val-oldVal<-15){
    oldVal = val;
    return 2;
  }else if (val-oldVal>15){
    oldVal = val;
    return 1;
  }else{
    oldVal = val;
    return 0;
  }
}

int lazerRight(){
  int val = analogRead(A1);
  if (val-oldValRight>10){
    oldValRight = val;
    return 1;
  }else{
    oldValRight = val;
    return 0;
  }
}


int lazerLeft(){
  int val = analogRead(A2);
  if (val-oldValLeft>10){
    oldValLeft = val;
    return 1;
  }else{
    oldValLeft = val;
    return 0;
  }
}

