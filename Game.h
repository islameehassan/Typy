#pragma once
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

using namespace std;
using namespace sf;

/*
	Main class that wraps all methods and attributes required for running the game
*/

const int MAXWORDSONSCREEN = 8;
const int MAXWORDS = 2466;
const int MAXERRORS = 15;

const int AVERAGEWORDLENGTH = 6;

const int WINDOWHEIGHT = 400;
const int WINDOWWIDTH = 800;

/*
* Levels according to speed(WPM):
* 1. Newbie (0 - 10)
* 2. Pubil (11 - 20)
* 3. Specialist (21 - 30)
* 4. Expert (31 - 40)
* 5. Master (41 - 50)
* 6. GrandMaster ( > 50)
*/

class Game {
	RenderWindow window;
	Event ev;
	Clock* GameCLock;
	Time GameTime;

	vector<string> Words;
	vector<Text> WordsOnScreen;

	string wordEntered;
	string rank;
	float matchedWordCharacterLength;
	int correctAnswers;
	int wrongAnswers;
	int speed;
	
	
	// Fonts and Texts
	Font floatingWordsFont;
	Font userEnteredFont;
	Font guiFont;
	
	Text FloatingWordsText;
	Text UserEnteredText;
	Text TitleText;
	Text SpeedText;
	Text LevelText;
	Text Errors;
	Text GameOverText;
	Text ResetInstructionsText;


	/*bool gameOver;*/
	bool wordMatched;
	bool spacePressed;

	RectangleShape SeperationLine;
	RectangleShape GameBar;
	RectangleShape GameBarFrame;
	CircleShape TextStartSymbol; 

	SoundBuffer correctAnswerBuffer;
	SoundBuffer wrongAnswerBuffer;

	Sound CorrectAnswer;
	Sound WrongAnswer;

	void initText();
	void initSound();
	void initUI();

	bool gameover();
	void reset();

public:
	Game(vector<string> words);
	~Game();

	const bool isrunning() const;


	void pollevents();

	void updatefloatingwords(); // push new words to the screen
	void updatesound();
	void updateUI();
	void update();

	void renderUI(); 
	void render();
};