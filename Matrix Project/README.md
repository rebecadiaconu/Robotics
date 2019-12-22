FLAPPY BIRD ON ARDUINO

  	This project consists in an arduino game designed on a 8x8 LED matrix and a 16x2 LCD.

  	Name of the game: Flappy Bird
		
Hardware used on building the game: 

		1. 8x8 LED matrix
		2. LCD
		3. Joystick
		4. 1 potentiometers
		5. MAX7219 Driver
		6. a red LED
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
					
		In order to start the game the player must select the "Play game!" option on the LCD. You select an 
		option by pressing the button from the joystick and you scroll on the menu using the X axis of that.
		There will be 3 levels, the starting value being 1. From the settings, you can set the speed 
		level you will start with and after every level that you finished the speed will be increased, 
		making it harder. 
		The goal of the game is to arrive at the finish sign by avoiding the obstacles. You'll have 3 lives, 
		so you'll better take care out there! If you die, the game will revive you and you'll have to take the 
		level again from the begining. The level consists in helping Polly to fit into the gaps from the walls 
		that will appear. When you will pass the number of the obstacles (5xlevelValue) that is associated to
		the level, you will get to the next one.
		You'll be using the pushbutton to avoid the obstacles. Only if you push the button the bird will fly 
		higher, otherwise Polly's wings will stop working and she will fall. 
		The player will score more points (5 + the level of speed that you set) for every gap that he's going to
		fit the bird through.
		At the end of every level the buzzer will play a melody that will anounce you that you are moving forward 
		and when you will lose a life the red LED will blink.
		
		
GAME MENU STRUCTURE: 

	• Play Game:
		It will start the game, only after on the 8x8 matrix will be displayed an opening animation. You can exit 
		anytime from the game by pressing again the switch button from the joystick. After that, the game will
		start all over again.
	• Info:
		It will show on the LCD the game name (Flappy Bird), the creater name (Rebeca Diaconu) and the place when 
		the game have been built ( @UnibucRobotics).
	• Settings:
		Here we have two options: 
		Speed, when you can set the speed level, from 0 to 3. At the start of the game, the speed value will 
		be equal with 600 - 50*speedLevel and then will decrease with 100, making the obstacles move faster.
		Sound, when you can select if you want the buzzer to sound or not.
	• Highscore:
		The game will save the first 3 highscores on eeprom.
		
VIDEO OF THE GAME: https://www.youtube.com/watch?v=dYdPi0TmOB4&feature=youtu.be
		

		
	
		
		
		
				

	
