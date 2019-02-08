#include <SoftwareSerial.h>
SoftwareSerial BTSerial(0, 1); // RX | TX

#define IN_11  3        // L298N #1 in 1 motor Front Right
#define IN_12  5        // L298N #1 in 2 motor Front Right
#define IN_21  6       // L298N #2 in 1 motor Front Left
#define IN_22  9        // L298N #2 in 2 motor Front Left

#define fact 3

int sm = 100;

void forward() {
  /*****LEFT MOTORS****/
  analogWrite(IN_22, 0);
  analogWrite(IN_21, sm);

  /*****RIGHT MOTORS****/
  analogWrite(IN_12, sm);
  analogWrite(IN_11, 0);
}

void forward_left() {
  /*****LEFT MOTORS****/
  analogWrite(IN_22, 0);
  analogWrite(IN_21, sm / fact);

  /*****RIGHT MOTORS****/
  analogWrite(IN_12, sm);
  analogWrite(IN_11, 0);
}

void forward_right() {
  /*****LEFT MOTORS****/
  analogWrite(IN_22, 0);
  analogWrite(IN_21, sm);

  /*****RIGHT MOTORS****/
  analogWrite(IN_12, sm / fact);
  analogWrite(IN_11, 0);
}

void back() {
  /*****LEFT MOTORS****/
  analogWrite(IN_22, sm);
  analogWrite(IN_21, 0);

  /*****RIGHT MOTORS****/
  analogWrite(IN_12, 0);
  analogWrite(IN_11, sm);
}

void back_left() {
  /*****LEFT MOTORS****/
  analogWrite(IN_22, sm / fact);
  analogWrite(IN_21, 0);

  /*****RIGHT MOTORS****/
  analogWrite(IN_12, 0);
  analogWrite(IN_11, sm);
}

void back_right() {
  /*****LEFT MOTORS****/
  analogWrite(IN_22, sm);
  analogWrite(IN_21, 0);

  /*****RIGHT MOTORS****/
  analogWrite(IN_12, 0);
  analogWrite(IN_11, sm / fact);
}

void left() {
  /*****LEFT MOTORS****/
  analogWrite(IN_22, sm);
  analogWrite(IN_21, 0);

  /*****RIGHT MOTORS****/
  analogWrite(IN_12, sm);
  analogWrite(IN_11, 0);
}

void right() {
  /*****LEFT MOTORS****/
  analogWrite(IN_22, 0);
  analogWrite(IN_21, sm);

  /*****RIGHT MOTORS****/
  analogWrite(IN_12, 0);
  analogWrite(IN_11, sm);
}

void stop() {
  /*****LEFT MOTORS****/
  analogWrite(IN_22, 0);
  analogWrite(IN_21, 0);

  /*****RIGHT MOTORS****/
  analogWrite(IN_12, 0);
  analogWrite(IN_11, 0);
}

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
}

void loop() {
  if (BTSerial.available()) {
    char c = BTSerial.read();
    if (c != 'S') {
      Serial.write(c);
      Serial.write('\n');
    }
    if (c >= '0' && c <= '9') {
      int speed = (c - '0') + 1;
      sm = 25 * speed;
    }
    if (c == 'F') {
      forward();
    }
    if (c == 'G') {
      forward_left();
    }
    if (c == 'I') {
      forward_right();
    }
    if (c == 'B') {
      back();
    }
    if (c == 'H') {
      back_left();
    }
    if (c == 'J') {
      back_right();
    }
    if (c == 'R') {
      right();
    }
    if (c == 'L') {
      left();
    }
    if (c == 'S') {
      stop();
    }
  }

}
