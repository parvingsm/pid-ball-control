#include <Servo.h>

int trig = 7;
int echo = 6;

float Kp = 0.8;
float Ki = 0.1;
float Kd = 0.1;

float set = 9;  

float old_error = 0;
float integral = 0;
unsigned long old_time = 0;

Servo moto;  

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  myServo.attach(9);  
  Serial.begin(9600);
}

void loop() {

  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  int duration = pulseIn(echo, HIGH);
  float distance = (duration * 0.034) / 2.0;

  float error = set - distance;
  unsigned long current_time = millis();
  float dt = (current_time - old_time) / 1000.0;

  integral += error * dt;
  float derivative = (error - old_error) / dt;
  float output = Kp * error + Ki * integral + Kd * derivative;

  int angle = constrain(output, 0, 120);
  moto.write(angle);

  Serial.print("Distance: "); Serial.print(distance);
  Serial.print("Angle: "); Serial.println(angle);

  old_error = error;
  old_time = current_time;

  delay(50);
}
