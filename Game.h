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

/*
* Levels according to speed(WPM):
* 1. Newbie (0 - 10)
* 2. Pubil (11 - 20)
* 3. Specialist (21 - 30)
* 4. Expert (31 - 40)
* 5. Master (41 - 50)
* 6. GrandMaster ( > 50)
*/


const int MAX_WORDS_ONSCREEN = 8;
const int MAX_WORDS = 2466;
const int MAX_ErrorsText = 15;
const int AVERAGEWORD_LENGTH = 6;
const int WINDOW_HEIGHT = 400;
const int WINDOW_WIDTH = 800;

class Game {
	RenderWindow window;
	Event ev;
	Clock* GameClock;
	Time GameTime;

	vector<string> Words;
	vector<Text> WordsOnScreen;

	set<string> UncorrectedErrors;

	string wordEntered;
	string rank;
	float matchedWordCharacterLength;
	int correctAnswers;
	int wrongAnswers;
	int speed;
	
	
	// Fonts and Texts
	Font arialFont;
	Font guiFont;
	
	Text FloatingWordsText;
	Text UserEnteredText;
	Text SuggestedWordText;
	Text TitleText;
	Text SpeedText;
	Text LevelText;
	Text ErrorsText;
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
	bool checkMatching(string src, string dst);
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