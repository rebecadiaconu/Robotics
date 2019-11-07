const int potPin1 = A0;
const int potPin2 = A2;
const int potPin3 = A5;
const int ledPin1 = 9;
const int ledPin2 = 10;
const int ledPin3 = 11;
int potValue1 = 0;
int potValue2 = 0;
int potValue3 = 0;
int ledValue1 = 0;
int ledValue2 = 0;
int ledValue3 = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(potPin1, INPUT);
  pinMode(potPin2, INPUT);
  pinMode(potPin3, INPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  potValue1 = analogRead(potPin1);
  potValue2 = analogRead(potPin2);
  potValue3 = analogRead(potPin3);
  ledValue1 = map(potValue1, 0, 1023, 0, 255);
  ledValue2 = map(potValue2, 0, 1023, 0, 255);
  ledValue3 = map(potValue3, 0, 1023, 0, 255);
  analogWrite(ledPin1, ledValue1);
  analogWrite(ledPin2, ledValue2);
  analogWrite(ledPin3, ledValue3);

}
