#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>
#include "Game.h"
using namespace std;

int main()
{
	srand(time(NULL));

	//Init the words vector
	ifstream randomwordsFILE(RESOURCES_LOCATION + "RandomWords.txt");
	if (!randomwordsFILE.is_open()){
		cout << "Could not find the Words file";
		return EXIT_FAILURE;
	}

	vector<string> RandomWords;
	RandomWords.reserve(3000);
	string word;
	int lines = 0;
	float total = 0;
	while (!randomwordsFILE.eof()) {
		randomwordsFILE >> word;
		RandomWords.push_back(word);
		total += word.length();
		lines++;
	}
	// cout << "Words Average Length is: " << total / lines << '\n';

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
