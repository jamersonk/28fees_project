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
const int ldrPin = A0;

// VARIABLES
long duration;
int distance;
bool buttonState;
bool state;

bool lightState;
int lightDelay = 200;
long currentMillis;
long delayMillis = currentMillis;
bool ldrState;
bool yellowLightState;

bool buzzerState;
int buzzerDelay = 5000;

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
  
  if (buttonState == HIGH) {
    state = !state;
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
    if (distance < 30) {
      tone(buzzerPin, 4000, 5);
    }

    ldrState = analogRead(ldrPin);

    if (ldrState <= 350)
    {
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

  delay(1000);
}



