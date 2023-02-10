#include "Game.h"

void Game::initText()
{
	// initialize fonts
	if (!arialFont.loadFromFile(RESOURCES_LOCATION + "Fonts/arial.ttf"))
		cout << "Could not load the floating words font!!!!\n";
	if(!guiFont.loadFromFile(RESOURCES_LOCATION + "Fonts/Sunny Spells.ttf"))
		cout << "Could not load the GUI font!!!!\n";

	// initialize texts
	 
	//FloatingText
	FloatingWordsText.setFont(arialFont);
	FloatingWordsText.setCharacterSize(24);
	FloatingWordsText.move(5.f, -0);


	//UserText
	wordEntered = "";
	UserEnteredText.setFont(arialFont);
	UserEnteredText.setCharacterSize(18);
	UserEnteredText.setPosition(25.f, window.getSize().y - 25.f);
	UserEnteredText.setFillColor(Color::Black);

	SuggestedWordText.setFont(arialFont);
	SuggestedWordText.setCharacterSize(18);
	SuggestedWordText.setPosition(UserEnteredText.getPosition());
	SuggestedWordText.setFillColor(Color(0,0,0,128));

	//GUIText
	TitleText.setFont(guiFont);
	TitleText.setCharacterSize(40);
	TitleText.setFillColor(Color(127, 0, 255));
	TitleText.setString("TYPY");
	TitleText.setPosition(window.getSize().x - TitleText.getGlobalBounds().width - 10.f, window.getSize().y - 40);

	SpeedText.setFont(guiFont);
	SpeedText.setCharacterSize(20);
	SpeedText.setFillColor(Color::Black);
	SpeedText.setString("Speed(WPM): " + to_string(speed));
	SpeedText.setPosition(0.f,0.f);
	
	RankText.setFont(guiFont);
	RankText.setCharacterSize(20);
	RankText.setFillColor(Color::Black);
	RankText.setString("Rank: " + rank);
	RankText.setPosition(window.getSize().x - RankText.getGlobalBounds().width - 10.f, 0.f);

	ErrorsText.setFont(guiFont);
	ErrorsText.setCharacterSize(20);
	ErrorsText.setFillColor(Color::Black);
	ErrorsText.setString("Errors: " + to_string(wrongAnswers));
	ErrorsText.setPosition(0.5 * window.getSize().x - ErrorsText.getGlobalBounds().width, 0.f);

	GameOverText.setFont(guiFont);
	GameOverText.setCharacterSize(56);
	GameOverText.setFillColor(Color::Red);
	GameOverText.setString("Game Over!!!\n");
	GameOverText.setPosition(window.getSize().x/2 - GameOverText.getGlobalBounds().width/2, window.getSize().y / 2 - GameOverText.getGlobalBounds().height);

	ResetInstructionsText.setFont(guiFont);
	ResetInstructionsText.setCharacterSize(20);
	ResetInstructionsText.setFillColor(Color::Black);
	ResetInstructionsText.setString("Press R to play again");
	ResetInstructionsText.setPosition(GameOverText.getPosition() + Vector2f(25.f, GameOverText.getGlobalBounds().height/2 + 5.f));
}

void Game::initSound()
{
	// initialize Buffers
	if (!correctAnswerBuffer.loadFromFile(RESOURCES_LOCATION + "Sound/pop.wav"))
		cout << "Could not load the pop buffer!!!!\n";
	if (!wrongAnswerBuffer.loadFromFile(RESOURCES_LOCATION + "Sound/wrong.wav"))
		cout << "Could not load the wrong buffer!!!!\n";

	CorrectAnswer.setBuffer(correctAnswerBuffer);
	WrongAnswer.setBuffer(wrongAnswerBuffer);

	CorrectAnswer.setPlayingOffset(seconds(0.25f));
	WrongAnswer.setPlayingOffset(seconds(0.25f));
}

void Game::initUI()
{
										/*Text and Shapes*/
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

	//Text
	initText();
}

bool Game::gameover()
{
	return wrongAnswers > MAX_Errors;
}

bool Game::checkMatching(string src, string dst)
{
	if (src.length() == 0) {
		return false;
	}

	for (int i = 0; i < src.length() && i < dst.length(); i++) {
		if (src[i] != dst[i])
			return false;
	}
	return true;
}

void Game::reset()
{
	GameTime = Time();
	GameClock->restart();

	//Words
	WordsOnScreen.clear();
	UncorrectedErrors.clear();
	wordMatched = false;
	spacePressed = false;

	// User's Info
	wrongAnswers = 0;
	speed = 0;
	matchedWordCharacterLength = 0;
	rank = "newbie";
	wordEntered = "";

	ErrorsText.setString("Errors: " + to_string(wrongAnswers));
	SpeedText.setString("Speed(WPM): " + to_string(speed));
	RankText.setString("Rank: " + rank);
}

Game::Game(vector<string> RandomWords)
{
	// Window
	window.create(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "TypingSpeed");
	window.setFramerateLimit(60);

	GameTime = Time();
	GameClock = new Clock;
	
	//Words
	this->Words = RandomWords;
	wordMatched = false;
	spacePressed = false;

	// User's Info
	wrongAnswers = 0;
	speed = 0;
	matchedWordCharacterLength = 0;
	rank = "newbie";


	//Sound
	initSound();

	//UI
	initUI();

}

Game::~Game()
{
	cout << "TYPY " << PROJECT_VERSION_MAJOR << "." << PROJECT_VERSION_MINOR << '\n';
}

const bool Game::isrunning() const
{
	return this->window.isOpen();
}

void Game::updatefloatingwords()
{
								/*Handling new words pushed into the screen and organizes the logic based upon entering 
														a correct or wrong word by the user*/

	// Move words and remove outofbound ones
	for (int i = 0; i < WordsOnScreen.size(); i++) {
		string currentword = static_cast<string>(WordsOnScreen[i].getString());

		WordsOnScreen[i].move(0.5f, 0);
		if (WordsOnScreen[i].getPosition().x > WINDOW_WIDTH)
			WordsOnScreen.erase(WordsOnScreen.begin() + i);
		else if (spacePressed) {
			// word matched
			if (wordEntered == currentword) {
				WordsOnScreen.erase(WordsOnScreen.begin() + i);
				matchedWordCharacterLength += wordEntered.length(); // to calculate the speed
				UncorrectedErrors.erase(currentword);
				wordMatched = true;
			}
		}
	}

	// No matching has occured
	string suggested = static_cast<string>(SuggestedWordText.getString());
	if (spacePressed && !wordMatched) {
		if (suggested == "" && wordEntered.length() != 0) // the user has entered a non-existant word
			UncorrectedErrors.insert(wordEntered);
		else if (suggested.length() != 0)
			UncorrectedErrors.insert(suggested);
	}

	//Choose a random word from the list
	int wordSpacing = 40;
	int wordsSoFar = WordsOnScreen.size();
	if (wordsSoFar == 0) {
		while (wordsSoFar < MAX_WORDS_ONSCREEN) {
			int prevWordIndex = -1;
			int wordIndex = rand() % MAX_WORDS;
			while (prevWordIndex == wordIndex) {
				wordIndex = rand() % MAX_WORDS;
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
			//-FloatingWordsText.getGlobalBounds().width - (rand() % xoffset)
			FloatingWordsText.setPosition(0, (wordsSoFar + 1) * wordSpacing);
			WordsOnScreen.push_back(FloatingWordsText);

			wordsSoFar++;
		}
	}
}

void Game::updateUI()
{
	//Word Entry Box
	if (!wordMatched) {
		UserEnteredText.setString(wordEntered);
	}
	else {
		// Clearing the text
		wordEntered = "";
		UserEnteredText.setString(wordEntered);
		SuggestedWordText.setString(wordEntered);
	}

	for (Text& word : WordsOnScreen)
	{
		if (checkMatching(wordEntered, static_cast<string>(word.getString()))) {
			SuggestedWordText.setString(word.getString());
			break;
		}
		else {
			SuggestedWordText.setString("");
		}
	}


	//Speed
	//Update iff a space is pressed to avoid continuous change
	if (spacePressed) {
		GameTime = GameClock->getElapsedTime();
		speed = 60 * ((matchedWordCharacterLength / AVERAGEWORD_LENGTH) - (int)UncorrectedErrors.size()) / (GameTime.asSeconds());
		if (speed < 0)
			speed = 0;
		SpeedText.setString("Speed(WPM): " + to_string(speed));
	}

	//rank
	if (speed <= 20) {
		rank = "newbie";
	}
	else if (speed <= 40) {
		rank = "pubil";
	}
	else if (speed <= 60) {
		rank = "specialist";
	}
	else if (speed <= 70) {
		rank = "expert";
	}
	else if (speed <= 80) {
		rank = "master";
	}
	else
		rank = "grandmaseter";
	RankText.setString("Rank: " + rank);
	RankText.setPosition(Vector2f(window.getSize().x - RankText.getGlobalBounds().width - 10.f, 0));

	//ErrorsText
	if (spacePressed && !wordMatched) {
		wrongAnswers++;
		ErrorsText.setString("Errors: " + to_string(wrongAnswers));
	}

	// negate
	if (spacePressed)
		spacePressed = false;
	if (wordMatched)
		wordMatched = false;
}

void Game::updatesound()
{
	if (CorrectAnswer.getStatus() != 2) {
		CorrectAnswer.setPlayingOffset(seconds(0.25f));
	}
	if (WrongAnswer.getStatus() != 2) {
		WrongAnswer.setPlayingOffset(seconds(0.25f));
	}

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
			if (ev.text.unicode < 128 && ev.text.unicode != '\b' && ev.text.unicode != ' ' && wordEntered.size() <= 40) { // not a backspace or a space and max chars to avoid outofbound text
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
			else if (ev.key.code == Keyboard::Space && wordEntered != "")
				spacePressed = true;
		}
	}
}

void Game::update()
{	
	if (!gameover()) {
		updatefloatingwords();
		updatesound();
		updateUI();
	}
	else {
		if (Keyboard::isKeyPressed(Keyboard::R))
			reset();
	}
}

void Game::render()
{
	window.clear(Color::White);

	//Draw new content & play sound
	for (auto& tx : WordsOnScreen)
		window.draw(tx);

	window.draw(UserEnteredText);
	window.draw(SuggestedWordText);
	window.draw(TitleText);
	window.draw(SpeedText);
	window.draw(RankText);
	window.draw(ErrorsText);
	window.draw(SeperationLine);
	window.draw(TextStartSymbol);
	if (gameover()) {
		window.draw(GameOverText);
		window.draw(ResetInstructionsText);
	}

	// Display
	window.display();
}


