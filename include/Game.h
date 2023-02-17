#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include "config.h"

using namespace std;
using namespace sf;

/*
	Main class that wraps all methods and attributes required for running the game
*/

/*
* Levels according to speed(WPM):
* 1. Newbie (0 - 20)
* 2. Pubil (21 - 40)
* 3. Specialist (40 - 60)
* 4. Expert (61 - 70)
* 5. Master (71 - 80)
* 6. GrandMaster ( > 80)
*/


const int MAX_WORDS_ONSCREEN = 8;
const int MAX_WORDS = 2466;
const int MAX_Errors = 15;
const int AVERAGEWORD_LENGTH = 4;
const int WINDOW_HEIGHT = 400;
const int WINDOW_WIDTH = 800;

const string RESOURCES_LOCATION = RESOURCE_PATH;

class Game {
	RenderWindow window;
	Event ev;
	Clock* GameClock;
	Time GameTime;
	
	
	// Fonts and Texts
	Font arialFont;
	Font guiFont;
	
	Text FloatingWordsText;
	Text UserEnteredText;
	Text SuggestedWordText;
	Text TitleText;
	Text SpeedText;
	Text RankText;
	Text ErrorsText;
	Text GameOverText;
	Text ResetInstructionsText;

	//Shapes
	RectangleShape SeperationLine;
	CircleShape TextStartSymbol; 

	//Sound
	SoundBuffer correctAnswerBuffer;
	SoundBuffer wrongAnswerBuffer;

	Sound CorrectAnswer;
	Sound WrongAnswer;

	//Variables and containers
	vector<string> Words;
	vector<Text> WordsOnScreen;
	set<string> UncorrectedErrors;

	string wordEntered;
	string rank;
	float matchedWordCharacterLength;
	int correctAnswers;
	int wrongAnswers;
	int speed;
	bool wordMatched;
	bool spacePressed;


	// Private Methods
	void initText();
	void initSound();
	void initUI();
	void reset(); // reset the game

	bool gameover();
	bool checkMatching(string src, string dst); // check if src is substring of dst, starting from the first character.

public:
	Game(vector<string> words);
	~Game();

	const bool isrunning() const;

	//handle events
	void pollevents();

	//update the window
	void updatefloatingwords(); //push new words to the screen
	void updatesound();
	void updateUI();

	void update();
	void render();
};
