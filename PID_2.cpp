#include <Arduino.h>

// HCSR04
#define echoPin 3 
#define trigPin 2

// motor
#define pin_1 4 
#define pin_2 5 
#define pin_3 6 
#define pin_4 7 

long duration; 
int distance; 

float pid_val;
float pid_out;

long sum_e;
float kp = 0.3,ki = 0.1,kd = 0.1;
int last_e;
int now_e;


void setup() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT); 
    Serial.begin(115200); 
}

void loop() {

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;

    now_e = distance - pid_val;
    sum_e += now_e; 
    pid_out = kp*now_e + ki*sum_e + kd*(last_e - now_e);
    last_e = now_e;
    pid_val += pid_out;

    float val = map(pid_val, 0, 60, 0, 255);

    analogWrite(pin_1, val);
    analogWrite(pin_2, 0);
    analogWrite(pin_3, val);
    analogWrite(pin_4, 0);

    Serial.print(distance);
    Serial.print("   ");
    Serial.println(pid_val);
    delay(50); 

}

