#include <Servo.h>

const int ledPin = 4;
const int buttonPin = 2;
const int servoPin = 11;
const int buzzerPin = 12;
const int trigPin = 9;
const int echoPin = 10;

Servo Servo1;

void setup()
{
    Servo1.attach(servoPin);
    pinMode(trigPin, OUTPUT);
    pinMode(trigPin, INPUT);
    pinMode(ledPin, OUTPUT);
    pinMode(buzzerPin, OUTPUT);
}

void loop()
{

}
