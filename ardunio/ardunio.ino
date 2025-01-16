// C++ code
//

const int ledPin = 4;
const int buttonPin = 5;
const int buzzerPin = 12;
const int trigPin = 10;
const int echoPin = 11;

long duration;
int distance;
bool buttonState;
bool state;

bool lightState;
int lightDelay = 200;
long currentMillis;
long delayMillis = currentMillis;

bool buzzerState;
int buzzerDelay = 400;

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop()
{  
  currentMillis = millis();
  buttonState = digitalRead(buttonPin);
  
  if (buttonState == HIGH) {
    state = !state;
  }

  if (!state) {
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
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
    if (distance < 10) {
      tone(buzzerPin, 1000, 1);
      if (currentMillis - delayMillis >= buzzerDelay) {
          if (buzzerState == 1) {
              noTone(buzzerPin);
              buzzerState = !buzzerState;
                Serial.print("buzzer off");
            } 
            else if (buzzerState == 0) {
              tone(buzzerPin, 1000);
              buzzerState = !buzzerState;
                Serial.print("buzzer on");
            }
        delayMillis = currentMillis;   // update for next 200ms delay 
      } 
    }
  }
  delay(5); // delay to ensure system can be turned off
}
