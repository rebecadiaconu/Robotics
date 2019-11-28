#include <LiquidCrystal.h>

const int pinSW = 10;
const int pinX = A0;
const int pinY = A2;
const int RS = 12;
const int enable = 11;
const int d4 = 5;
const int d5 = 4;
const int d6 = 3;
const int d7 = 2;

int pushed = 0;
int ok = 0;
int minThreshold = 400;
int maxThreshold = 600;
int xValue = 0;
int yValue = 0;
int swstate = LOW;
int lastSwState = LOW;

int index = 0;
int clear1 = 0;
int clear2 = 0;
int clear3 = 0;
int highScore = 0;
int startingLevelValue;
int score = 0;
int levelChanged = 0;
int gameFinished = 0;
bool joyMovedx = false;
bool joyMovedy = false;
bool levelUp1 = false;
bool levelUp2 = false;
unsigned long currTime = 0;

LiquidCrystal lcd(RS, enable, d4, d5, d6, d7);

void chooseOption(){

  if (buttonPressed() == 0){
    if (ok == 1) {
      lcd.clear();
      ok = 0;
    }
    showMenu();
  }

  xValue = analogRead(pinX);
    
  if (xValue < minThreshold && joyMovedx == false && buttonPressed() == 0) {
    if (index < 2) {
      index++;
    } 
    else {
      index = 0;
    }
    joyMovedx = true;
  }
      
  if (xValue > maxThreshold && joyMovedx == false && buttonPressed() == 0) {
    if (index > 0) {
      index--;
    } 
    else {
      index = 2;
    }
    joyMovedx = true;
  }
    
  if (xValue >= minThreshold && xValue <= maxThreshold) {
    joyMovedx = false;
  }

  if (index == 0) {
      lcd.setCursor(0, 1);
      lcd.print(" ");
      lcd.setCursor(2, 0);
      lcd.print(">");
      lcd.setCursor(9, 1);
      lcd.print(" ");
    }
  if (index == 1) {
    lcd.setCursor(0, 1);
    lcd.print(">");
    lcd.setCursor(2, 0);
    lcd.print(" ");
    lcd.setCursor(9, 1);
    lcd.print(" ");
  }
  if (index == 2) {
    lcd.setCursor(0, 1);
    lcd.print(" ");
    lcd.setCursor(2, 0);
    lcd.print(" ");
    lcd.setCursor(9, 1);
    lcd.print(">");
  }

  if (buttonPressed() == 1) {
    if (index == 0) {
      lcd.clear();
      startGame();
    }
    if (index == 1) {
      lcd.clear();
      settings();
    }
    if (index == 2) {
      lcd.clear();
      HighScore();
    }
  }
}

int buttonPressed() {
  swstate = digitalRead(pinSW);
    if (swstate !=  lastSwState) {
        ok = 1;
        if (swstate == LOW) {
          pushed = !pushed;
        }
      }
    lastSwState = swstate;

    return pushed;
}

void showMenu(){
  lcd.setCursor(3, 0);
  lcd.print("Start game!");
  lcd.setCursor(1, 1);
  lcd.print("Settings");
  lcd.setCursor(10, 1);
  lcd.print("HScore");
}

void startGame(){
  levelUp2 = 0;
  levelUp1 = 0;
  currTime = millis();

  clear1 = 0;
  clear2 = 0;
  clear3 = 0;
  
  if (levelChanged == 0) {
    startingLevelValue = 0;
  }
  while (buttonPressed() == 1){
    if (millis() - currTime < 11000) {
      lcd.setCursor(0, 0);
      lcd.print("Lives:3");
      lcd.setCursor(8, 0);
      lcd.print("Level:");
      lcd.setCursor(14, 0);
      lcd.print(startingLevelValue);
      lcd.setCursor(0, 1);
      lcd.print("Score: ");
      score = 3*startingLevelValue;
      lcd.print(score);
  
      if (highScore < score) {
        highScore = score;
      }
    }
    if (millis() - currTime > 5000 && millis() - currTime <= 10000){
      if(levelUp1 == 0) {
        startingLevelValue++;
        levelUp1 = 1;
      }
    }
  
    if (millis() - currTime > 10000 && millis() - currTime <= 11000){
      if(levelUp2 == 0) {
        startingLevelValue++;
        levelUp2 = 1;
      }
    }
  
  
  if (millis() - currTime > 11000 && millis() - currTime <= 12000){
    if(clear1 == 0){
      lcd.clear();
      clear1 = 1;
    }
    lcd.setCursor(0, 0);
    lcd.print("Congratulations");

    startingLevelValue = 0;
  }

  if (millis() - currTime > 13000 && millis() - currTime <= 14000) {
    if(clear2 == 0){
      lcd.clear();
      clear2 = 1;
    }
    lcd.setCursor(0, 0);
    lcd.print("You finished");
    lcd.setCursor(3, 1);
    lcd.print("the game!");
  }
  
  if (millis() - currTime > 14000) {
    if(clear3 == 0){
      lcd.clear();
      clear3 = 1;
    }
    lcd.setCursor(0, 0);
    lcd.print("Press button");
    lcd.setCursor(3, 1);
    lcd.print("to exit.");
    gameFinished = 1;
    levelChanged = 0;
  }
 } 
}

void settings(){
  levelChanged = 0;
  if (gameFinished == 1) {
    startingLevelValue = 0;
  }
  while(buttonPressed() == 1){
    yValue = analogRead(pinY);
    
    if (yValue < minThreshold && joyMovedy == false) {
      if (startingLevelValue > 0) {
        startingLevelValue--;
      }
  
      levelChanged = 1;
      joyMovedy = true;
    } 
    if (yValue > maxThreshold && joyMovedy == false) {
      if (startingLevelValue < 97) {
        startingLevelValue++;
      } 
      else {
        startingLevelValue = 0;
      }
      levelChanged = 1;
      joyMovedy = true;
    }
  
    if (yValue >= minThreshold && yValue <= maxThreshold) {
      joyMovedy = false;
    }
    lcd.setCursor(0, 0);
    lcd.print("Choose level:");
    if (startingLevelValue/10 < 1) {
      lcd.setCursor(1, 1);
      lcd.print(" ");
    }
    lcd.setCursor(0, 1);
    lcd.print(startingLevelValue);
  }
  
}

void HighScore(){
  while(buttonPressed() == 1) {
    lcd.setCursor(0, 0);
    lcd.print("Highscore: ");
    lcd.setCursor(0, 1);
    lcd.print(highScore);
  }
}

void setup() {
  pinMode(pinSW,INPUT_PULLUP);
  lcd.begin(16, 2);

  Serial.begin(9600);
}

void loop() {
  chooseOption();
}
