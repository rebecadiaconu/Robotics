const int activeBuzzerPin = 8;
const int knockSensor = A0;
const int buttonPin = 2;
const int threshold = 430;

int buzzerState = 0;
int sensorReading = 0;
int buttonState = 0;
int previousButtonValue = 0;

int ok = 0;
int knockTime = 0;
int lastDebounceTime = 0;
int debounceDelay = 50;

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT);
  pinMode(activeBuzzerPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorReading = analogRead(knockSensor);

  if (sensorReading > threshold) {
        Serial.println("Knock!");
        ok = 1;
  }

  knockTime = millis();
  if (ok == 1)
     if (millis() - knockTime > 5000){
           tone(activeBuzzerPin, sensorReading);
           buzzerState = 1;
        }

  int reading = digitalRead(buttonPin);
  
  if (reading != previousButtonValue){
    lastDebounceTime = millis();
  }

  if (millis() - lastDebounceTime > debounceDelay) 
    if (reading != buttonState){
      buttonState = reading;
    }

      
  if (buttonState == HIGH && buzzerState == 1){
        noTone(activeBuzzerPin);
        buzzerState = 0;
      }

  previousButtonValue = reading;

  Serial.println(sensorReading);
  delay(100);
}
