/*
 * Created by ArduinoGetStarted, https://arduinogetstarted.com
 *
 * Arduino - Ultrasonic Sensor HC-SR04
 *
 * Wiring: Ultrasonic Sensor -> Arduino:
 * - VCC  -> 5VDC
 * - TRIG -> Pin 9
 * - ECHO -> Pin 8
 * - GND  -> GND
 *
 * Tutorial is available here: https://arduinogetstarted.com/tutorials/arduino-ultrasonic-sensor.php
 */

int trigPin = 9;
int echoPin = 8;

int initdelay = 3000;
int pulsetime = 100, ibpulsetime = 1500;

float duration_us;
int samplesize = 10, receivetime = pulsetime + ibpulsetime;
float samples[10];

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  delay(initdelay);
}

bool receive() {
  long long starttime = millis();
  float s = 0;
  for (int i = 0; i < samplesize; i++) {
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      duration_us = pulseIn(echoPin, HIGH);
      samples[i] = 0.017 * duration_us;
      s += samples[i];
      //Serial.println(samples[i]);
      delay((starttime + (receivetime*(double(i+1)/double(samplesize)))) - millis());
  }

  float mean = s/samplesize;
  for (int i = 0; i < samplesize; i++) {
    if (abs(samples[i] - mean) > 0.3) {
      return true;
    }
  }

  return false;
}


void loop() {
  int n = 0;
  bool res;
  for (int b = 0; b < 8; b++) {
    res = receive();
    Serial.print((int)res);
    if (res) {
      n |= 1 << b;
    }
    //Serial.println(("yes");
  }
  Serial.print(" : ");
  Serial.println(n);
}
