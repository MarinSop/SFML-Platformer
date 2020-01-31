#include "SFML/Graphics.hpp"
#include "Game.h"
#include "MainMenu.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1024, 768), "Demo");
	window.setFramerateLimit(60);
	MainMenu mainmenu = MainMenu(window);
	Game game = Game(window);


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Space:
					game.eventFunc("jump");
					break;
				case sf::Keyboard::LShift:
					game.eventFunc("dash");
					break;
				case sf::Keyboard::F:
					game.eventFunc("shoot");
					break;
				default:
					break;
				}
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				default:
					break;
				}
			default:
				break;
			}

		}
		if (game.menuStatus() == true)
		{
			game.setMenuStatus(false);
			mainmenu.setMenuStatus(true);
		}
		if (mainmenu.inMenu() == true)
		{
			mainmenu.update(window);
		    window.clear();
		    mainmenu.draw(window);
		}
		else
		{
		game.update(window);
		window.clear();
		game.draw(window);
		}
		window.display();
	}

}