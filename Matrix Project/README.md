FLAPPY BIRD ON ARDUINO

  	This project consists in an arduino game designed on a 8x8 LED matrix and a 16x2 LCD.

  	Name of the game: Flappy Bird
		
Hardware used on building the game: 

		1. 8x8 LED matrix
		2. LCD
		3. Joystick
		4. 2 x potentiometers
		5. MAX7219 Driver
		6. RGB led
		7. pushbutton
		8. active buzzer
		9. 10UF 50V
		10. 104 ceramic capacitor
	
HOW TO PLAY:

		This is basically the "Flappy bird" game that all of you have played at least once, but this one 
		has a story: 
			The bird's name is Polly and you have to help her to get her babies back home. The villain, 
		Mr. Malcolm, took them away because of their tweet. Apparently, Polly's babies have a special 
		chitter that can make every human being be under their control and Mr. Malcolm want to take 
		adventage on that and conquer the world. 
			Can you help Polly save her little birds?
		
		In order to start the game the player must select the "Play game!" option on the LCD. You select an option by pressing
		the button from the joystick and you scroll on the meniu using the X axis of that.
		There will be 10 levels, starting with the one that you choose from the settings- if you did, if you didn't
		the starting level is by default 1. After every level that
		you finished the speed will be increased, making it harder. 
		The goal of the game is to arrive at the finish sign by avoiding the obstacles. You'll have 3 lives, 
		so you'll better take care out there! If you die, the game will revive you and you'll have to take the 
		level again from the begining.
		You'll be using the pushbutton to avoid the obstacles. Only if you push the button the bird will fly 
		higher, otherwise Polly's wings will stop working and she will fall. 
		The player will score 5 more points for every gap that he's going to fit the bird through and 10 more after he finishes the level.
		If the starting level is greater than 1, the points that he gains for every gap or obstacle will be 5 + startingLevelValue%10.
	
		
		
		
				

	
