#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include "Game.h"


using namespace std;

int main()
{
	srand(time(NULL));

	//Init the words vector
	ifstream randomwordsFILE("randomwords.txt");
	if (!randomwordsFILE.is_open())
		return EXIT_FAILURE;

	vector<string> RandomWords;
	RandomWords.reserve(3000);
	string word;
	while (!randomwordsFILE.eof()) {
		randomwordsFILE >> word;
		RandomWords.push_back(word);
	}

	// Game Object
	Game game(RandomWords);

	// Game Loop
	while (game.isrunning()) {
		game.pollevents();
		game.update();
		game.render();
	}


	// End of Game
	return 0;
}