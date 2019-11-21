const int pinSW = 1;
const int pinX = A0;
const int pinY = A2;

const int pinA = 12;
const int pinB = 8;
const int pinC = 5;
const int pinD = 3;
const int pinE = 2;
const int pinF = 11;
const int pinG = 6;
const int pinDP = 4;
const int pinD1 = 7;
const int pinD2 = 9;
const int pinD3 = 10;
const int pinD4 = 13;

const int segSize = 8;
const int noOfDigits = 10;
const int noOfDisplays = 4;

int digit1 = 0;
int digit2 = 0;
int digit3 = 0;
int digit4 = 0;
int locked = HIGH;
int minThreshold = 400;
int maxThreshold = 600;

int swstate = LOW;
int lastSwState = LOW;
int index = 0;
int xValue = 0;
int yValue = 0;
bool joyMovedx = false;
bool joyMovedy = false;

int segments[segSize] = {
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};

int displays[noOfDisplays] = {
  pinD1, pinD2, pinD3, pinD4
};

int digits[noOfDisplays] = {
  digit1, digit2, digit3, digit4
};

byte digitMatrix[noOfDigits][segSize - 1] = {
  // a b c d e f g
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9 
};

void displayNumber(byte digit, byte decimalpoint) {
  for(int i = 0; i < segSize - 1; i++) {
    digitalWrite(segments[i], digitMatrix[digit][i]);
  }

  digitalWrite(segments[segSize - 1], decimalpoint);
}

void showDigit(int index) {
  for (int i = 0; i < noOfDisplays; i++) {
    digitalWrite(displays[i], HIGH);
  }
  digitalWrite(displays[index], LOW);
}


void setup() {
 for (int i = 0; i < segSize; i++) {
    pinMode(segments[i], OUTPUT);
  }
  for (int i = 0; i < noOfDisplays; i++) {
    pinMode(displays[i], OUTPUT);
  }
  pinMode(pinSW, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  
   swstate = digitalRead(pinSW);
   if (swstate !=  lastSwState) {
      if (swstate == LOW) {
          locked = !locked;
      }
    }
   lastSwState = swstate;

   if(locked == HIGH){
     xValue = analogRead(pinX);

     if (xValue < minThreshold && joyMovedx == false) {
      if (index < 3) {
          index++;
      } 
      else {
          index = 0;
      }
      joyMovedx = true;
    }
    
    if (xValue > maxThreshold && joyMovedx == false) {
      if (index > 0) {
          index--;
      } 
      else {
          index = 3;
      }
      joyMovedx = true;
    }
    if (xValue >= minThreshold && xValue <= maxThreshold) {
      joyMovedx = false;
    }
  }

  if (locked == LOW){
    yValue = analogRead(pinY);
    
    if (yValue < minThreshold && joyMovedy == false) {
      if (digits[index] < 9) {
          digits[index]++;
      } 
      else {
          digits[index] = 0;
      }
      joyMovedy = true;
    }
    
    if (yValue > maxThreshold && joyMovedy == false) {
      if (digits[index] > 0) {
          digits[index]--;
      }
      else {
          digits[index] = 9;
      }
      joyMovedy = true;
    }

    if (yValue >= minThreshold && yValue <= maxThreshold) {
      joyMovedy = false;
    }
  }

  for(int i = 0; i < noOfDisplays; i++) {
    showDigit(i);
    displayNumber(digits[i], HIGH);
    if (i == index) {
      digitalWrite(segments[segSize - 1], HIGH);
    }
    else digitalWrite(segments[segSize - 1], LOW);
    delay(5);
  }
  
}
