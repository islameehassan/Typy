#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
using namespace std;
using namespace sf;


int main()
{
	srand(time(NULL));
	// Window
	RenderWindow newWindow(VideoMode(1024, 900), "FirstGame", Style::Titlebar | Style::Close);
	newWindow.setFramerateLimit(60);

	Texture backgroundTexture;
	// Game Loop
	while (newWindow.isOpen())
	{
		Event ev;
		// Event Polling 
		while (newWindow.pollEvent(ev)) {

			switch (ev.type)
			{
			case Event::Closed: 
				newWindow.close();
				break;
			case Event::KeyPressed:
				if (ev.key.code == Keyboard::Escape)
					newWindow.close();
				break;
			default:
				break;
			}
		}
		//Update
		newWindow.clear(); // clear the old frame


		//Display
		newWindow.display(); // display the new frame
	}

	// End of Game
	return 0;
}