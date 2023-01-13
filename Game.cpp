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
	floatingWordsText.setFont(floatingWordsFont);
	floatingWordsText.setCharacterSize(24);
	floatingWordsText.move(15.f, -0);


	//UserText
	wordEntered = "";
	userEnteredText.setFont(userEnteredFont);
	userEnteredText.setCharacterSize(18);
	userEnteredText.setPosition(25.f, window.getSize().y - 25.f);
	userEnteredText.setFillColor(Color::Black);

	//GUIText
	titleText.setFont(guiFont);
	titleText.setCharacterSize(40);
	titleText.setFillColor(Color(127, 0, 255));
	titleText.setString("TYPY");
	titleText.setPosition(window.getSize().x - titleText.getGlobalBounds().width - 10.f, window.getSize().y - 40);
}

void Game::initGUI()
{
	//Seperation Line
	seperationline.setFillColor(Color::Black);
	seperationline.setSize(Vector2f(window.getSize().x, 3.f));
	seperationline.setPosition(0, window.getSize().y - 30);

	//Pointing Triangle
	pointingtraingle.setRadius(10.f);
	pointingtraingle.setFillColor(Color::Black);
	pointingtraingle.setPointCount(3);
	pointingtraingle.setPosition(20.f, window.getSize().y - pointingtraingle.getRadius() * 2.3f);
	pointingtraingle.setRotation(90.f);
}

Game::Game(vector<string> RandomWords)
{
	// Window
	window.create(VideoMode(WINDOWWIDTH, WINDOWHEIGHT), "TypingSpeed");
	window.setFramerateLimit(60);
	
	//Words
	this->Words = RandomWords;

	spacePressed = false;
	wordMatched = false;
	//Text
	initText();

	//GUI
	initGUI();

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

		WordsOnScreen[i].move(1.3f, 0);
		if (WordsOnScreen[i].getPosition().x > WINDOWWIDTH)
			WordsOnScreen.erase(WordsOnScreen.begin() + i);
		else if (spacePressed && wordEntered == currentword) {
			WordsOnScreen.erase(WordsOnScreen.begin() + i);
			spacePressed = false;
			wordMatched = true;
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
			floatingWordsText.setString(Words[wordIndex]);

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
			floatingWordsText.setFillColor(wordColor);

			int xoffset = 150;
			floatingWordsText.setPosition(-floatingWordsText.getGlobalBounds().width - (rand() % xoffset), (wordsSoFar + 1) * wordSpacing);
			WordsOnScreen.push_back(floatingWordsText);

			wordsSoFar++;
		}
	}


}

void Game::updategui()
{
	if (!wordMatched)
		userEnteredText.setString(wordEntered);
	else {
		wordEntered = "";
		userEnteredText.setString(wordEntered);
		wordMatched = false;
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
	updategui();
}

void Game::render()
{
	window.clear(Color::White);

	//Draw new content
	for (auto& tx : WordsOnScreen)
		window.draw(tx);
	window.draw(userEnteredText);
	window.draw(titleText);
	window.draw(seperationline);
	window.draw(pointingtraingle);

	// Display
	window.display();
}

void Game::renderGUI()
{

}
