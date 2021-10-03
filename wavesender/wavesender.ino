/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo; 
int initdelay = 3000;
int pos = 0;
int datasize = 5;
byte data[] = {12, 34, 56, 78, 90};

int pulsetime = 100, ibpulsetime = 1500;

void setup() {
  myservo.attach(9);
  myservo.write(90);

  delay(initdelay);
  
  for (int i = 0; i < datasize; i++) {
    // send single number
    for (int b = 0; b < 8; b++) {
      if (data[i] & (1 << b)) { 
        pulse();
      } else {
        nopulse();
      }
      delay(ibpulsetime);
    }
  }
}

void pulse() {
  myservo.write(0);      
  delay(pulsetime - 50);           
  myservo.write(90);              
  delay(50);                       
}

void nopulse() {
  delay(pulsetime);
}

void loop() {
  
}
