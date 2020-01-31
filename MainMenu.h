#pragma once
#include "SFML/Graphics.hpp"
class MainMenu
{
public:
	MainMenu(sf::RenderWindow& window);
	~MainMenu();
	void draw(sf::RenderTarget& window);
	void update(sf::RenderWindow& window);
	bool inMenu();
	void setMenuStatus(bool boolean);

private:
	bool _inMenu = true;
	sf::Texture* _startImg;
	sf::Texture* _exitImg;
	sf::Sprite _start;
	sf::Sprite _exit;

};

