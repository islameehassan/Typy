#include "Game.h"

void Game::initText()
{
	// initialize fonts
	if (!floatingWordsFont.loadFromFile("Fonts/arial.ttf"))
		cout << "Could not load the floating words font!!!!\n";
	if (!userEnteredFont.loadFromFile("Fonts/arial.ttf"))
		cout << "Could not load the user entered font!!!!\n";
	if(!guiFont.loadFromFile("Fonts/Sunny Spells.ttf"))
		cout << "Could not load the GUI font!!!!\n";

	// initialize texts
	 
	
	//FloatingText
	FloatingWordsText.setFont(floatingWordsFont);
	FloatingWordsText.setCharacterSize(24);
	FloatingWordsText.move(15.f, -0);


	//UserText
	wordEntered = "";
	UserEnteredText.setFont(userEnteredFont);
	UserEnteredText.setCharacterSize(18);
	UserEnteredText.setPosition(25.f, window.getSize().y - 25.f);
	UserEnteredText.setFillColor(Color::Black);

	//GUIText
	TitleText.setFont(guiFont);
	TitleText.setCharacterSize(40);
	TitleText.setFillColor(Color(127, 0, 255));
	TitleText.setString("TYPY");
	TitleText.setPosition(window.getSize().x - TitleText.getGlobalBounds().width - 10.f, window.getSize().y - 40);
}

void Game::initSound()
{
	// initialize Buffers
	if (!correctAnswerBuffer.loadFromFile("Sound/pop.wav"))
		cout << "Could not load the pop buffer!!!!\n";
	if (!wrongAnswerBuffer.loadFromFile("Sound/wrong.wav"))
		cout << "Could not load the wrong buffer!!!!\n";

	CorrectAnswer.setBuffer(correctAnswerBuffer);
	WrongAnswer.setBuffer(wrongAnswerBuffer);
}

void Game::initUI()
{
	//Seperation Line
	SeperationLine.setFillColor(Color::Black);
	SeperationLine.setSize(Vector2f(window.getSize().x, 3.f));
	SeperationLine.setPosition(0, window.getSize().y - 30);

	//Pointing Triangle
	TextStartSymbol.setRadius(10.f);
	TextStartSymbol.setFillColor(Color::Black);
	TextStartSymbol.setPointCount(3);
	TextStartSymbol.setPosition(20.f, window.getSize().y - TextStartSymbol.getRadius() * 2.3f);
	TextStartSymbol.setRotation(90.f);

	//Game Bar & Its Frame
	GameBarFrame.setSize(Vector2f(0.6f * window.getSize().x, 20.f));
	GameBarFrame.setFillColor(Color::White);
	GameBarFrame.setOutlineColor(Color(127, 0, 255));
	GameBarFrame.setOutlineThickness(2.f);
	GameBarFrame.setPosition(0.2f * window.getSize().x, 5.f);

	GameBar.setSize((Vector2f(0.06f * matchedWords * window.getSize().x, 20.f)));
	GameBar.setFillColor(Color::Black);
	GameBar.setPosition(0.2f * window.getSize().x, 5.f);
}

Game::Game(vector<string> RandomWords)
{
	// Window
	window.create(VideoMode(WINDOWWIDTH, WINDOWHEIGHT), "TypingSpeed");
	window.setFramerateLimit(60);
	
	//Words
	this->Words = RandomWords;
	wordMatched = false;
	spacePressed = false;
	matchedWords = 0;

	//Sound
	initSound();

	//GUI
	initUI();

	//Text
	initText();

}

Game::~Game()
{
}

const bool Game::isrunning() const
{
	return this->window.isOpen();
}

const bool Game::gameover() const
{
	return false;
}

void Game::updatefloatingwords()
{
	// Move words and remove outofbound ones
	for (int i = 0; i < WordsOnScreen.size(); i++) {
		string currentword = static_cast<string>(WordsOnScreen[i].getString());

		WordsOnScreen[i].move(1.2f, 0);
		if (WordsOnScreen[i].getPosition().x > WINDOWWIDTH)
			WordsOnScreen.erase(WordsOnScreen.begin() + i);
		else if (spacePressed) {
			if (wordEntered == currentword) {
				WordsOnScreen.erase(WordsOnScreen.begin() + i);
				matchedWords++;
				wordMatched = true;
			}
		}
	}

	//Choose a random word from the list
	int wordSpacing = 40;
	int wordsSoFar = WordsOnScreen.size();
	if (wordsSoFar == 0) {
		while (wordsSoFar < MAXWORDSONSCREEN) {
			int prevWordIndex = -1;
			int wordIndex = rand() % MAXWORDS;
			while (prevWordIndex == wordIndex) {
				wordIndex = rand() % MAXWORDS;
			}
			FloatingWordsText.setString(Words[wordIndex]);

			// Set a color
			int color = rand() % 3;
			Color wordColor;
			switch (color)
			{
			case 0:
				wordColor = Color::Red;
				break;
			case 1:
				wordColor = Color::Blue;
				break;
			case 2:
				wordColor = Color(75,0,130);
				break;
			default:
				wordColor = Color::Blue;
				break;
			}
			FloatingWordsText.setFillColor(wordColor);

			int xoffset = 150;
			FloatingWordsText.setPosition(-FloatingWordsText.getGlobalBounds().width - (rand() % xoffset), (wordsSoFar + 1) * wordSpacing);
			WordsOnScreen.push_back(FloatingWordsText);

			wordsSoFar++;
		}
	}
}

void Game::updateUI()
{
	if (!wordMatched)
		UserEnteredText.setString(wordEntered);
	else {
		wordEntered = "";
		UserEnteredText.setString(wordEntered);
	}

	//Game Bar
	GameBar.setSize(Vector2f(0.06 * matchedWords * window.getSize().x, GameBar.getSize().y));
}

void Game::updatesound()
{
	if (spacePressed) {
		if (wordMatched)
			CorrectAnswer.play();
		else
			WrongAnswer.play();
	}
}

void Game::pollevents()
{
	while (window.pollEvent(ev))
	{
		if(ev.type == Event::Closed)
			window.close();
		else if (ev.type == Event::TextEntered) {
			if (ev.text.unicode < 128 && ev.text.unicode != '\b' && ev.text.unicode != ' ') { // not a backspace or a space
				wordEntered += static_cast<char>(ev.text.unicode);
			}
		}
		else if (ev.type == Event::KeyPressed) {
			if (ev.key.code == Keyboard::Escape) {
				window.close();
			}
			else if (ev.key.code == Keyboard::Backspace || ev.key.code == Keyboard::Delete) {
				if (wordEntered.length() != 0)
					wordEntered.erase(wordEntered.end() - 1);
			}
			else if (ev.key.code == Keyboard::Space)
				spacePressed = true;
		}
	}
}

void Game::update()
{	
	updatefloatingwords();
	updatesound();
	updateUI();
	spacePressed = false;
	wordMatched = false;
}

void Game::render()
{
	window.clear(Color::White);

	//Draw new content & play sound
	for (auto& tx : WordsOnScreen)
		window.draw(tx);
	window.draw(UserEnteredText);
	renderUI();

	// Display
	window.display();
}

void Game::renderUI()
{
	window.draw(TitleText);
	window.draw(SeperationLine);
	window.draw(TextStartSymbol);
	window.draw(GameBarFrame);
	window.draw(GameBar);
}

