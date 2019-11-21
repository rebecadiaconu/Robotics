const int activeBuzzerPin = 11;
const int knockSensor = A0;
const int buttonPin = 2;
const int threshold = 470 ;

int buzzerState = 0;
int sensorReading = 0;
int buttonState = 0;
int previousButtonState = 0;

int ok = 0;
int buzzerValue = 0;
int knockTime = 0;
int lastDebounceTime = 0;
int debounceDelay = 50;

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(activeBuzzerPin, OUTPUT);
  pinMode(knockSensor, INPUT);

  Serial.begin(9600);
}

void loop() {
  sensorReading = analogRead(knockSensor);
 // Serial.println(sensorReading);
  if (sensorReading > threshold) {
        Serial.println("Knock!");
        ok = 1;
        knockTime = millis();
        buzzerValue = sensorReading;
  }
  
  if (ok == 1) {
    if (millis() - knockTime > 5000){
          tone(activeBuzzerPin, buzzerValue);
          buzzerState = 1;
        }
  }

  int reading = digitalRead(buttonPin);
  
  if (reading != previousButtonState){
    lastDebounceTime = millis();
  }

  if (millis() - lastDebounceTime > debounceDelay) 
    if (reading != buttonState){
      buttonState = reading;
    }

      
  if (buttonState == LOW && buzzerState == 1){
        noTone(activeBuzzerPin);
        buzzerState = 0;
        ok = 0;
      }

  previousButtonState = reading;

  delay(100);
}
