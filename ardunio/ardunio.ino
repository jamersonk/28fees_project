//Copyright (c) 2024 JAMES KUANG ZHONGCHUAN
//Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

// CONSTANTS
const int ledPin = 2;
const int lightPin = 1;
const int buttonPin = 4;
const int buzzerPin = 12;
const int trigPin = 10;
const int echoPin = 11;
int ldrPin = A0;
const int cutoffDistance = 20;

// VARIABLES
long duration;
int distance;
bool buttonState;
bool state;

// flashing warning light variables
bool lightState;
int lightDelay = 200;
long currentMillis;
long delayMillis = currentMillis;

// headlight variables
int ldrState;
bool yellowLightState;

// buzzer variables
bool buzzerState;
int buzzerDelay = 250;
long buzzerDelayMillis = currentMillis;

// CODE BEGINS
void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(lightPin, OUTPUT);
  pinMode(ldrPin, INPUT);
}

void loop()
{

  if (state == LOW) {
    lightState = LOW;
    yellowLightState = LOW;
    digitalWrite(ledPin, lightState);
    digitalWrite(lightPin, yellowLightState);
    noTone(buzzerPin);
  }

  currentMillis = millis();
  buttonState = digitalRead(buttonPin);
  ldrState = analogRead(ldrPin);
  
  if (buttonState == HIGH) {
    state = !state;
    delay(500);
  }
  
  // active state
  if (state == HIGH) {
    // ultrasonic sensor code
    digitalWrite(trigPin, LOW);
  	delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
  	delayMicroseconds(10);
 	  digitalWrite(trigPin, LOW);
 	  duration = pulseIn(echoPin, HIGH);
 	  distance = duration * 0.034 / 2;
 	  Serial.print("Distance: ");
 	  Serial.println(distance);
    
    // led code
    if (currentMillis - delayMillis >= lightDelay) {
     	lightState = !lightState;
      	digitalWrite(ledPin, lightState);
   		delayMillis = currentMillis;
  	}  
    Serial.print(distance);
    
    // buzzer code
    if (distance < cutoffDistance) {
      if (currentMillis - buzzerDelayMillis >= buzzerDelay) {
     	  buzzerState = !buzzerState;
        if (buzzerState == LOW) {
          noTone(buzzerPin);
        }
        else if (buzzerState == HIGH) {
          tone(buzzerPin, 4000);
        }
   		buzzerDelayMillis = currentMillis;
  	  }  
    }
    else if (distance > cutoffDistance) {
      buzzerState = LOW;
      noTone(buzzerPin);
    }

    if (ldrState<=350){
      if (yellowLightState == LOW) {
        yellowLightState = HIGH;
        digitalWrite(lightPin, yellowLightState);
      } 
    }
    else {
        yellowLightState = LOW;
        digitalWrite(lightPin, yellowLightState);
    }
  }
}



