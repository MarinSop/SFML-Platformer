#include "MainMenu.h"

MainMenu::MainMenu(sf::RenderWindow& window)
{
	_startImg = new sf::Texture();
	_exitImg = new sf::Texture();
	_startImg->loadFromFile("textures\\start.jpg");
	_exitImg->loadFromFile("textures\\exit.jpg");
	_start = sf::Sprite(*_startImg);
	_exit = sf::Sprite(*_exitImg);
	_start.setPosition(sf::Vector2f((window.getSize().x/2)-(_start.getLocalBounds().width/2),
		(window.getSize().y /2) - 100.0f));
	_exit.setPosition(sf::Vector2f((window.getSize().x / 2) - (_exit.getLocalBounds().width / 2),
		(window.getSize().y / 2) + 100.0f));

}

MainMenu::~MainMenu()
{
}

void MainMenu::draw(sf::RenderTarget& window)
{
	window.draw(_start);
	window.draw(_exit);
}

void MainMenu::update(sf::RenderWindow& window)
{
	sf::Mouse mouse;
	if (mouse.getPosition(window).x >= _start.getPosition().x && mouse.getPosition(window).x <= _start.getPosition().x + _start.getLocalBounds().width
		&& mouse.getPosition(window).y >= _start.getPosition().y && mouse.getPosition(window).y <= _start.getPosition().y + _start.getLocalBounds().height)
	{
		if (mouse.isButtonPressed(sf::Mouse::Left))
		{
			_inMenu = false;
		}
	}
	else if (mouse.getPosition(window).x >= _exit.getPosition().x && mouse.getPosition(window).x <= _exit.getPosition().x + _exit.getLocalBounds().width
		&& mouse.getPosition(window).y >= _exit.getPosition().y && mouse.getPosition(window).y <= _exit.getPosition().y + _exit.getLocalBounds().height)
	{
		if (mouse.isButtonPressed(sf::Mouse::Left))
		{
			window.close();
		}
	}
}

bool MainMenu::inMenu()
{
	return _inMenu;
}

void MainMenu::setMenuStatus(bool boolean)
{
	_inMenu = boolean;
}
