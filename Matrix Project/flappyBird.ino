#include <LedControl.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>

const int redLed = A1;

const int pinSW = 7;
const int pinX = A3;
const int pinY = A4;

const int buttonPin = 6;
const int buzzerPin = 13;

const int d4 = 5;
const int d5 = 4;
const int d6 = 3;
const int d7 = 2;
const int enable = 8;
const int RS = 9;

// ------ singASong() ------
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

// ------ chooseOption() ------
int ok = 0;
int pushed = 0;
int swstate = LOW;
int lastSwState = LOW;
int index = 0;
int xValue = 0;
int yValue = 0;
int minThreshold = 400;
int maxThreshold = 600;
bool joyMovedx = false;
bool joyMovedy = false;

// ------ PlayGame() ------
int livesValue = 3;
int levelValue = 1;
int numberObs = 0;
int score = 0;
int speedValue = 600;
int getScore = 0;
int sem = 0;
int cnt = 0;
int endGame = 0;
int gameDone = 0;
int levelUp = 0;
int startGame = 0;
int gameOver = 0;
int restart = 0;
int nextLevel = 0;
int gameFinished = 0;
int messagePeriod = 5000;
unsigned long winTime;
unsigned long loseTime;

// GameOpening() 
int openingDone = 0;
int counter = 0;
int k = 42;
int ind = 4;
int number =  1;
int timepassed = 1;
int change = 0;
unsigned long openingTime;

// setBird()
int L1 = 4;
int L2 = 3;
int C1 = 0;
int C2 = 1;
int reading;
int lastDebounceTime = 0;
int buttonState = LOW;
int lastBirdCommand = 0;
int birdFly = 0;
int periodFall = 300;
int periodfly = 20;
unsigned long currTimeFly = 0;
unsigned long currTimeFall = 0;


// setObs() 
int randNumber = 0;
int rand1 = 0;
int rand2 = 0;
int timepassed2 = 1;
int prevObs = 0;
unsigned long shiftTime = 0;


// Opened()
int opened = 0;
int buttonStateOp = LOW;
int lastButtonStateOp = LOW;
int lastDebounceTimeOpening = 0;
int readingOp;
int debounceDelay = 30;

// ------ Settings() ------ 
int setSelect = 0;
int indexSet = 0;

// setSound()
int sound = 1;
bool soundSet = false;


// Speed()
int speedLevel = 1;
bool speedSet = false;

// ------ HighScore() ------
int hscore1 = 0;
int hscore2 = 0;
int hscore3 = 0;

// ------ other stuff ------
int message1 = 0;
int message2 = 0;
int message3 = 0;
unsigned long currTime;

bool matrix[8][16] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // row1
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // row2
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // row3
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // row4
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // row5
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // row6
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // row7
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}  // row8 
};

bool play[8][42] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0}
};

bool sadFace[8][8] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 1, 0, 0, 1, 1, 0},
  {0, 1, 1, 0, 0, 1, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 1, 0, 0, 1, 0, 0},
  {0, 1, 0, 0, 0, 0, 1, 0},
  {0, 1, 0, 0, 0, 0, 1, 0}
};

bool happyFace[8][8] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 1, 0, 0, 1, 1, 0},
  {0, 1, 1, 0, 0, 1, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 0, 0, 0, 0, 1, 0},
  {0, 1, 0, 0, 0, 0, 1, 0},
  {0, 0, 1, 0, 0, 1, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0}
};

LiquidCrystal lcd(RS, enable, d4, d5, d6, d7);
LedControl lc = LedControl(12, 11, 10, 0);

void singASong() {
  if (sound == 1) {
      for (int thisNote = 0; thisNote < 8; thisNote++) {
      int noteDuration = 1000 / noteDurations[thisNote];
      tone(buzzerPin, melody[thisNote], noteDuration);
      
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
  
      noTone(buzzerPin);
    }
  }
  else {
    noTone(buzzerPin);
  }
}

void clearM() {
  for (int row = 0; row < 8; row++) {
    for (int coll = 0; coll < 8; coll++) {
      lc.setLed(0, coll, row, false);
    }
  }
}

void setMatrix() {
  for (int lin = 0; lin < 8; lin++) {
    for (int coll = 0; coll < 16; coll++){
      matrix[lin][coll] = 0;
    }
  }
}

// function that will return the button state, if it's pressed, it will light up the lcd and the matrix
int Opened() {
  readingOp = digitalRead(buttonPin);
  if (readingOp != lastButtonStateOp) {
    lastDebounceTimeOpening = millis();
  }

  if (millis() - lastDebounceTimeOpening > debounceDelay) {
    if (readingOp != buttonStateOp) {
      buttonStateOp = readingOp;
    }
    if (buttonStateOp == LOW) {
      opened = !opened;
    }
  }
  lastButtonStateOp = readingOp;

  return opened;
}

// function that returns the state of the switch button
int buttonPressed() {
  swstate = digitalRead(pinSW);
  if (swstate != lastSwState) {
    ok = 1;
    if (swstate == LOW) {
      pushed = !pushed;
    }
  }
  lastSwState = swstate;

  return pushed;
}

void chooseOption() {
  if (buttonPressed() == 0) {
    if (ok == 1) {
      lcd.clear();
      clearM();
      ok = 0;
    }

    showMenu();
  }

  yValue = analogRead(pinY);

  if (yValue > maxThreshold && joyMovedy == false && buttonPressed() == 0) {
    if (index > 0) {
      index--;
    }
    else {
      index = 3;
    }
    joyMovedy = true;
  }

  if (yValue < minThreshold && joyMovedy == false && buttonPressed() == 0) {
    if (index < 3) {
      index++;
    }
    else {
      index = 0;
    }
    joyMovedy = true;
  }

  if (yValue >= minThreshold && yValue <= maxThreshold) {
    joyMovedy = false;
  }

  if (index == 0) {
    lcd.setCursor(0, 0);
    lcd.print(">");
    lcd.setCursor(10, 0);
    lcd.print(" ");
    lcd.setCursor(0, 1);
    lcd.print(" ");
    lcd.setCursor(9, 1);
    lcd.print(" ");
  }

  if (index == 1) {
    lcd.setCursor(0, 0);
    lcd.print(" ");
    lcd.setCursor(10, 0);
    lcd.print(">");
    lcd.setCursor(0, 1);
    lcd.print(" ");
    lcd.setCursor(9, 1);
    lcd.print(" ");
  }

  if (index == 2) {
    lcd.setCursor(0, 0);
    lcd.print(" ");
    lcd.setCursor(10, 0);
    lcd.print(" ");
    lcd.setCursor(0, 1);
    lcd.print(">");
    lcd.setCursor(9, 1);
    lcd.print(" ");
  }

  if (index == 3) {
    lcd.setCursor(0, 0);
    lcd.print(" ");
    lcd.setCursor(10, 0);
    lcd.print(" ");
    lcd.setCursor(0, 1);
    lcd.print(" ");
    lcd.setCursor(9, 1);
    lcd.print(">");
  }

  if (buttonPressed() == 1) {
    if (index == 0) {
      lcd.clear();
      startGame = 1;
      PlayGame();
    }

    if (index == 1) {
      lcd.clear();
      Info();
    }

    if (index == 2) {
      lcd.clear();
      Settings();
    }

    if (index == 3) {
      lcd.clear();
      HighScore();
    }
  }

}


void showMenu() {
  lcd.setCursor(1, 0);
  lcd.print("PlayGame!");
  lcd.setCursor(11, 0);
  lcd.print("Info");
  lcd.setCursor(1, 1);
  lcd.print("Settings");
  lcd.setCursor(10, 1);
  lcd.print("HScore");
}

// function that checks if in the front of the bird exists an obstacle or not
int obsCheck() {
  int ok = 0;
  for (int row = 0; row < 8; row++) {
    for (int coll = 0; coll < 2; coll++) {
      if (matrix[row][coll] == 1) ok = 1;
    }
  }

  return ok;
}

void setScore() {
  int ok = 0;
  if (score > hscore1 && ok == 0) {
    hscore3 = hscore2;
    hscore2 = hscore1;
    hscore1 = score;
    ok = 1;
  }
  if (score > hscore2 && ok == 0) {
    hscore3 = hscore2;
    hscore2 = score;
    ok = 1;
}
  if (score > hscore3 && ok == 0) {
    hscore3 = score;
    ok = 1;
  }
  EEPROM.put(0, hscore1);
  EEPROM.put(4, hscore2);
  EEPROM.put(8, hscore3);
  
}

void PlayGame() {
  while (buttonPressed() == 1) {
    while (openingDone == 0) {
      GameOpening();
    }
    if (startGame == 1) {
      clearM();
      setMatrix();
      speedValue = 600 - 50*speedLevel;
      livesValue = 3;
      score = 0;
      levelValue = 1;
      numberObs = 5*levelValue;
      cnt = 0;
      L1 = 4;
      L2 = 3;
      levelUp = 0;
      gameOver = 0;
      gameFinished = 0;
      startGame = 0;
      nextLevel = 0;
      restart = 0;
    }

    if (restart == 1) {
      L1 = 4;
      L2 = 3;
      cnt = 0;
      restart = 0;  
      numberObs = 5*levelValue;    
    }

    while (buttonPressed() == 1 && (livesValue > 0 && cnt < numberObs && levelValue < 4) && gameOver == 0 && gameFinished == 0) {
      lcd.setCursor(0, 0);
      lcd.print("Lives:");
      lcd.setCursor(6, 0);
      lcd.print(livesValue);
      lcd.setCursor(9, 0);
      lcd.print("Level:");
      lcd.setCursor(15, 0);
      lcd.print(levelValue);
      lcd.setCursor(0, 1);
      lcd.print("Score:");
      lcd.setCursor(6, 1);
      lcd.print(score);
      
      setBird();
      setObs();

      if (obsCheck() == 1 && sem == 0) {
        sem = 1;
        if (matrix[L1][C1] == 1 || matrix[L2][C2] == 1) {
          if (livesValue == 1) {
            getScore = 1;
            livesValue--;
            L1 = 4;
            L2 = 3;
            gameOver = 1;
            endGame = 1;
          }
          else {
            livesValue = livesValue - 1;
            blinkBlink();
            L1 = 4;
            L2 = 3;
            restart = 1;
          }
        }
        else {
          score = score + 5 + speedLevel;
          cnt++;
        }
      }
      if (obsCheck() == 0) {
         sem = 0;
      }

      if (L1 == 7 && L2 == 6) {
        if (livesValue == 1) {
          getScore = 1;
          livesValue--;
          L1 = 4;
          L2 = 3;
          gameOver = 1;
          endGame = 1;
        }
        else {
          livesValue = livesValue - 1;
          blinkBlink();
          L1 = 4;
          L2 = 3;
          restart = 1;
        }
      }
    }
    
    if (cnt == numberObs) {
      levelUp = 1;
    }

    if (levelUp == 1) {
      levelUp = 0;
      nextLevel = 1;
    }

    if (nextLevel == 1) {
      singASong();
      clearM();
      L1 = 4;
      L2 = 3;
      speedValue = speedValue - 100;
      levelValue++;
      cnt = 0;
      numberObs = 5*levelValue;
      periodFall = periodFall - 10;
      nextLevel = 0;
    }

    if (levelValue == 4) {
      levelValue = 1;
      getScore = 1;
      gameFinished = 1;
      gameDone = 0;
    }
    
    if (gameOver == 1) {
      loseTime = millis();
      
    }

    while (gameOver == 1) {
      if (endGame == 1) {
        clearM();
        endGame = 0;       
      }
      if (getScore == 1) {
        setScore();
        getScore = 0;
      }
      message1 = 0;
      message2 = 0;
      message3 = 0;

      for (int row = 0; row < 8; row++) {
        for (int coll = 0; coll < 8; coll++) {
          lc.setLed(0, row, coll, sadFace[row][coll]);
        }
      }
      
      if (millis() - loseTime <= 2000) {
        if(message1 == 0){
          lcd.clear();
          message1 = 1;
        }
        lcd.setCursor(0, 0);
        lcd.print("Congratulations");
      }
      if (millis() - loseTime > 3000 && millis() - loseTime <= 5000) {
        if(message2 == 0){
          lcd.clear();
          message2 = 1;
        }
        if (levelValue == 1) {
          lcd.setCursor(0, 0);
          lcd.print("Want to try");
          lcd.setCursor(3, 1);
          lcd.print("again? ");
        }
        else {
          lcd.setCursor(0, 0);
          lcd.print("You made it past");
          lcd.setCursor(1, 1);
          lcd.print("level ");
          lcd.setCursor(8, 1);
          int x = levelValue - 1;
          lcd.print(x);
          lcd.setCursor(10, 1);
          lcd.print("!");
        }
      }
      if (millis() - loseTime > 6000) {
        if(message3 == 0){
          lcd.clear();
          message3 = 1;
        }
        if (levelValue == 1) {
          lcd.setCursor(2, 0);
          lcd.print("Then press ");
          lcd.setCursor(3, 1);
          lcd.print("the button!");
          gameOver = 0;
        }
        else {
          lcd.setCursor(0, 0);
          lcd.print("Press the button");
          lcd.setCursor(0, 1);
          lcd.print("to try again.");
          gameOver = 0;
        }
      }
    }

    if (gameFinished == 1) {
      winTime = millis();
    }

    while (gameFinished == 1) {
      if (gameDone == 1) {
        clearM();
        gameDone = 0;
      }
      if (getScore == 1) {
        setScore();
        getScore = 0;
      }
      message1 = 0;
      message2 = 0;
      message3 = 0;

      for (int row = 0; row < 8; row++) {
        for (int coll = 0; coll < 8; coll++) {
          lc.setLed(0, row, coll, happyFace[row][coll]);
        }
      }
      
      if (millis() - winTime <= 2000) {
        if(message1 == 0){
          lcd.clear();
          message1 = 1;
        }
        lcd.setCursor(0, 0);
        lcd.print("Congratulations");
      }
      if (millis() - winTime > 3000 && millis() - winTime <= 5000) {
        if(message2 == 0){
          lcd.clear();
          message2 = 1;
        }
        lcd.setCursor(0, 0);
        lcd.print("You scored");
        lcd.setCursor(1, 1);
        lcd.print(score);
        lcd.setCursor(4, 1);
        lcd.print(" points!");
      }
      if (millis() - winTime > 6000) {
        if(message3 == 0){
          lcd.clear();
          message3 = 1;
        }
        lcd.setCursor(0, 0);
        lcd.print("Press the button");
        lcd.setCursor(3, 1);
        lcd.print("to exit!");
        gameFinished = 0;
        levelValue = 5;
      }
    }
    clearM();
  }  
}

// light up the red LED
void blinkBlink() {
  unsigned long blinkTime = millis();
  while (blinkTime + 40 > millis()) {
    analogWrite(redLed, 128);
  }
  analogWrite(redLed, 0);
}

void setBird() {
  int buttonState = digitalRead(buttonPin);

  if (buttonState == LOW) {
    birdFly = 1;
  }
  if (buttonState == HIGH) {
    birdFly = 0;
  }
  if (birdFly == 1) {
    birdJump();
  }
  else {
    birdFall();
  }
}

void birdFall() {
  if (currTimeFly + periodFall < millis()) {
    currTimeFly = millis();

    if (L1 < 7) {
      lc.setLed(0, L1, C1, 0);
      lc.setLed(0, L2, C2, 0);

      L1++;
      L2++;
    }
    
    lc.setLed(0, L1, C1, 1);
    lc.setLed(0, L2, C2, 1);
  }
}

void birdJump() {
  if (currTimeFly + periodfly < millis()) {
    currTimeFly = millis();

    if (L2 > 0) {
      lc.setLed(0, L1, C1, 0);
      lc.setLed(0, L2, C2, 0);
      
      L1--;
      L2--;
    }

    lc.setLed(0, L1, C1, 1);
    lc.setLed(0, L2, C2, 1);
  }
}

int VerMatrixObs() {
  int ok = 1;
  for (int row = 0; row < 8; row++) {
    for (int coll = 8; coll < 14; coll++) {
      if (matrix[row][coll] == 1) ok = 0;
    }
  }

  return ok;
}

void setObs() {
  if (VerMatrixObs() == 1)  {
    randNumber = random(1, 4);
    if (randNumber == prevObs) randNumber = random(1, 4);
    if (randNumber == 1) {
        rand1 = random(1, 4);
        rand2 = 4 - rand1;
  
        for (int row = 0; row < rand1; row++) {
          matrix[row][13] = 1;
        }
        for (int row = 7 - rand2 + 1; row < 8; row++) {
          matrix[row][13] = 1;
        }
      }
  
    if (randNumber == 2) {
      rand1 =  random(1, 5);
      for (int row = 0; row < rand1; row++) {
        matrix[row][13] = 1;
      }
    }
  
    if (randNumber == 3) {
      rand2 = random(1, 5);
      for (int row = 7 - rand2 + 1; row < 8; row++) {
        matrix[row][13] = 1;
      }
    }
    prevObs = randNumber;
  }

   if (shiftTime + speedValue < millis()) {
    shiftTime = millis();
    
    for (int coll = 0; coll < 13; coll++) {
      for (int row = 0; row < 8; row++) {
        matrix[row][coll] = matrix[row][coll + 1];
      }
    }

    for (int row = 0; row < 8; row++) {
      matrix[row][13] = 0;
    }
  }
  for (int row = 0; row < 8; row++) {
     for (int coll = 0; coll < 8; coll++) {
      lc.setLed(0, row, coll, matrix[row][coll]);
    }
  }
}

void GameOpening() {
  openingTime = millis();
  while (counter < 3 && openingDone == 0) {
    if (timepassed == 1) {
      change = 0;
      setMatrix();

      for (int coll = ind - 1; coll < ind + number; coll++) {
        matrix[ind - 1][coll] = 1;
        matrix[ind + number - 1][coll] = 1;
      }
  
      for (int lin = ind; lin < ind + number - 1; lin++) {
        matrix[lin][ind - 1] = 1;
        matrix[lin][ind + number - 1] = 1;
      }

      number += 2;
      ind--;
  
      if (ind == 0) {
        ind = 4;
        change = 1;
      }
  
      if (number == 9) {
        number = 1;
        change = 1;
      }
  
      if (change == 1) {
        counter++;
      }

      for (int lin = 0; lin < 8; lin++) {
        for (int coll = 0; coll < 8; coll++) {
          lc.setLed(0, lin, coll, matrix[lin][coll]);
        }
      }
      
      timepassed = 0;
    }

    if (millis() - openingTime > 250) {
      timepassed = 1;
    }

    if (timepassed == 1) {
      openingTime = millis();
    }
  }

  if (counter == 3) {
    setMatrix();
    clearM();
  }

  while (k > 0) {
    for (int row = 0; row < 8; row++) {
      for (int coll = 0; coll < 41; coll++) {
        play[row][coll] = play[row][coll + 1];
      }
    }
    k--;
    
    for (int row = 0; row < 8; row++) {
      for (int coll = 0; coll < 8; coll++) {
        lc.setLed(0, row, coll, play[row][coll]);
      }
    }
  }

  clearM();
  openingDone = 1;
}

void Info() {
  int message1 = 0;
  int message2 = 0;
  int message3 = 0;
  currTime = millis();

  while (buttonPressed() == 1) {
    if (millis() - currTime <= 3000) {
      lcd.setCursor(3, 0);
      lcd.print("Game name:");
      lcd.setCursor(3, 1);
      lcd.print("FlappyBird");
    }

    if (millis() - currTime > 4000 && millis() - currTime <= 6000) {
      if (message1 == 0) {
        lcd.clear();
        message1 = 1;
      }
      lcd.setCursor(1, 0);
      lcd.print("Creater name:");
      lcd.setCursor(1, 1);
      lcd.print("Rebeca Diaconu");
    }

    if (millis() - currTime > 6500 && millis() - currTime <= 9000) {
      if (message2 == 0) {
        lcd.clear();
        message2 = 1;
      }
      lcd.setCursor(4, 0);
      lcd.print("Made at");
      lcd.setCursor(0, 1);
      lcd.print("@UniBucRobotics");
    }
    if (millis() - currTime > 10000) {
      if(message3 == 0){
        lcd.clear();
        message3 = 1;
      }
      lcd.setCursor(0, 0);
      lcd.print("Press the button");
      lcd.setCursor(4, 1);
      lcd.print("to exit!");
    }
  } 
}

void Settings() {
  setSelect = 0;
  while (buttonPressed() == 1) {
    lcd.setCursor(5, 0);
    lcd.print("Speed");
    lcd.setCursor(5, 1);
    lcd.print("Sound");

    yValue = analogRead(pinY);
  
    if (yValue > maxThreshold && joyMovedy == false) {
      if (indexSet > 0) {
        indexSet--;
      }
      else {
        indexSet = 1;
      }
      joyMovedy = true;
    }
  
    if (yValue < minThreshold && joyMovedy == false) {
      if (indexSet < 1) {
        indexSet++;
      }
      else {
        indexSet = 0;
      }
      joyMovedy = true;
    }
  
    if (yValue >= minThreshold && yValue <= maxThreshold) {
      joyMovedy = false;
    }
  
    xValue = analogRead(pinX);
  
    if (xValue > maxThreshold && joyMovedx == false) {
      if (indexSet == 0) {
        if (speedLevel > 0) {
          speedLevel--;
        }
        else {
          speedLevel = 3;
        }
        speedSet = true;
      }
      if (indexSet == 1) {
        sound = !sound;
        soundSet = true;
      }
      joyMovedx = true;
    }

    if (xValue < minThreshold && joyMovedx == false) {
      if (indexSet == 0) {
        if (speedLevel < 3) {
          speedLevel++;
        }
        else {
          speedLevel = 0;
        }
        speedSet = true;
      }
      if (indexSet == 1) {
        sound = !sound; 
        soundSet = true;
      }
      joyMovedx = true;
    }
  
    if (xValue >= minThreshold && xValue <= maxThreshold) {
      joyMovedx = false;
      speedSet = false;
      soundSet = false;
    }
 
    if (indexSet == 0) {
      lcd.setCursor(0, 0);
      lcd.print(">");
      lcd.setCursor(14, 0);
      lcd.print(speedLevel);
      lcd.setCursor(0, 1);
      lcd.print(" ");
      lcd.setCursor(14, 1);
      lcd.print(" ");
    }
  
    if (indexSet == 1) {
      lcd.setCursor(0, 0);
      lcd.print(" ");
      lcd.setCursor(14, 0);
      lcd.print(" ");
      lcd.setCursor(0, 1);
      lcd.print(">");
      lcd.setCursor(14, 1);
      lcd.print(sound);
    }
  }
}

void HighScore() {
  message1 = 0;
  message2 = 0;
  message3 = 0;
  currTime = millis();
  
  while (buttonPressed() == 1) {
    if (millis() - currTime < 3000) {
      lcd.setCursor(0, 0);
      lcd.print("1st Highscore: ");
      lcd.setCursor(0, 1);
      EEPROM.get(0, hscore1);
      lcd.print(hscore1);
    }

    if (millis() - currTime > 3000 && millis() - currTime <= 6000) {
      if (message1 == 0) {
        lcd.clear();
        message1 = 1;
      }
      lcd.setCursor(0, 0);
      lcd.print("2nd Highscore: ");
      lcd.setCursor(0, 1); 
      EEPROM.get(4, hscore2);
      lcd.print(hscore2);
    }

    if (millis() - currTime > 7000 && millis() - currTime <= 9000) {
      if (message2 == 0) {
        lcd.clear();
        message2 = 1;
      }
      lcd.setCursor(0, 0);
      lcd.print("3rd Highscore: ");
      lcd.setCursor(0, 1);
      EEPROM.get(8, hscore3);
      lcd.print(hscore3);
    }

    if (millis() - currTime > 10000) {
      if(message3 == 0){
        lcd.clear();
        message3 = 1;
      }
      lcd.setCursor(0, 0);
      lcd.print("Press the button");
      lcd.setCursor(4, 1);
      lcd.print("to exit!");
    }
  }
}

void setup() {
  lcd.begin(16, 2);

  lc.shutdown(0, false);
  lc.setIntensity(0, 2);
  lc.clearDisplay(0);

  pinMode(pinSW, INPUT_PULLUP);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  pinMode(redLed, OUTPUT);
 
  clearM();

  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void loop() {
  if (Opened() == 1) {
    chooseOption();
  }
}
