#include <PS2X_lib.h>  //for v1.6

PS2X ps2x; // create PS2 Controller Class

#define IN_11  3        // L298N #1 in 1 motor Front Right
#define IN_12  5        // L298N #1 in 2 motor Front Right
#define IN_21  6       // L298N #2 in 1 motor Front Left
#define IN_22  9        // L298N #2 in 2 motor Front Left

#define E1 10
#define E2 11

#define speedMedium 100

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

void setup(){
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(A3,OUTPUT);
  
 Serial.begin(9600);

 //CHANGES for v1.6 HERE!!! *************PAY ATTENTION************
  
 error = ps2x.config_gamepad(8,4,7,2, true, true);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
 
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
  
}

void loop(){
   /* You must Read Gamepad to get new values
   Read GamePad and set vibration values
   ps2x.read_gamepad(small motor on/off, larger motor strenght from 0-255)
   if you don't enable the rumble, use ps2x.read_gamepad(); with no values
   
   you should call this at least once a second
   */
   
   
   
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
         
    
    if(ps2x.ButtonPressed(PSB_PAD_RIGHT)){             //will be TRUE if button was JUST pressed
         /*****LEFT MOTORS****/

      // motor Front Left
      analogWrite(IN_22, speedMedium);
      analogWrite(IN_21, 0);
      
      analogWrite(E1, speedMedium);
      digitalWrite(A1, HIGH);
      digitalWrite(A0, LOW);

      /*****RIGHT MOTORS****/

      // motor Front Right
      
      analogWrite(IN_12, speedMedium);
      analogWrite(IN_11, 0);

      analogWrite(E2, speedMedium);
      digitalWrite(A3, LOW);
      digitalWrite(A2, HIGH);
    } else  if(ps2x.ButtonReleased(PSB_PAD_LEFT)) { 
      
      // motor Front Left
      analogWrite(IN_22, 0);
      analogWrite(IN_21, speedMedium);
      
      analogWrite(E1, speedMedium);
      digitalWrite(A1, LOW);
      digitalWrite(A0, HIGH);

      /*****RIGHT MOTORS****/

      // motor Front Right
      
      analogWrite(IN_12, 0);
      analogWrite(IN_11, speedMedium);

      analogWrite(E2, speedMedium);
      digitalWrite(A3, HIGH);
      digitalWrite(A2, LOW);
    } else if(ps2x.NewButtonState(PSB_PAD_DOWN))  {
        // motor Front Left
      analogWrite(IN_22, 0);
      analogWrite(IN_21, speedMedium);
      
      analogWrite(E1, speedMedium);
      digitalWrite(A1, LOW);
      digitalWrite(A0, HIGH);

      /*****RIGHT MOTORS****/

      // motor Front Right
      
      analogWrite(IN_12, speedMedium);
      analogWrite(IN_11, 0);

      analogWrite(E2, speedMedium);
      digitalWrite(A3, LOW);
      digitalWrite(A2, HIGH);
    } else if(ps2x.Button(PSB_PAD_UP)){
        // motor Front Left
      analogWrite(IN_22, speedMedium);
      analogWrite(IN_21, 0);
      
      analogWrite(E1, speedMedium);
      digitalWrite(A1, HIGH);
      digitalWrite(A0, LOW);

      /*****RIGHT MOTORS****/

      // motor Front Right
      
      analogWrite(IN_12, 0);
      analogWrite(IN_11, speedMedium);

      analogWrite(E2, speedMedium);
      digitalWrite(A3, HIGH);
      digitalWrite(A2, LOW);  
    } else {
      direction_value = 3*(ps2x.Analog(PSS_LX)-128)/2;
       
      speed_value = 2*(ps2x.Analog(PSS_RY)-128);
      speed_left = (direction_value >= 0) ? speed_value - direction_value : speed_value + abs(direction_value);
      speed_right = (direction_value < 0) ? speed_value - abs(direction_value) : speed_value + direction_value;

      /*****LEFT MOTORS****/

      // motor Front Left
      analogWrite(IN_22, (speed_left <= 0) ? min(abs(speed_left),255) : 0);
      analogWrite(IN_21, (speed_left > 0) ? min(speed_left,255) : 0);
      
      analogWrite(E1, min(abs(speed_left),255));
      digitalWrite(A1, (speed_left <= 0) ? HIGH : LOW);
      digitalWrite(A0, (speed_left > 0) ? HIGH : LOW);

      /*****RIGHT MOTORS****/

      // motor Front Right
      
      analogWrite(IN_12, (speed_right > 0) ? min(speed_right,255) : 0);
      analogWrite(IN_11, (speed_right <= 0) ? min(abs(speed_right),255) : 0);

      analogWrite(E2, min(abs(speed_right),255));
      digitalWrite(A3, (speed_right <= 0) ? HIGH : LOW);
      digitalWrite(A2, (speed_right > 0) ? HIGH : LOW);
    
    }
   
       
    
    
    if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) // print stick values if either is TRUE
    {
        Serial.print("Stick Values:");
        Serial.print(ps2x.Analog(PSS_LY)); //Left stick, Y axis. Other options: LX, RY, RX  
        Serial.print(",");
        Serial.print(ps2x.Analog(PSS_LX)); 
        Serial.print(",");
        Serial.print(ps2x.Analog(PSS_RY)); 
        Serial.print(",");
        Serial.println(ps2x.Analog(PSS_RX)); 
    } 
    
    
 }
 
 
 delay(50);
     
}
