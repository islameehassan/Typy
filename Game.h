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

const int WINDOWHEIGHT = 400;
const int WINDOWWIDTH = 800;

class Game {
	RenderWindow window;
	Event ev;

	vector<string> Words;
	vector<Text> WordsOnScreen;

	string wordEntered;
	int matchedWords;
	
	
	// Fonts and Texts
	Font floatingWordsFont;
	Font userEnteredFont;
	Font guiFont;
	
	Text FloatingWordsText;
	Text UserEnteredText;
	Text TitleText;
	Text LevelText;

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

public:
	Game(vector<string> words);
	~Game();

	const bool isrunning() const;
	const bool gameover() const;

	void updatefloatingwords(); // push new words to the screen
	void updatesound();
	void updateUI();
	void pollevents();
	void update();
	void render();
	void renderUI();
};