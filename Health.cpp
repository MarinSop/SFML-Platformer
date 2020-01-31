#include "Health.h"
#include <iostream>



Health::Health(float healthAmount):
	_health(healthAmount),_maxHealth(healthAmount)
{
	_healthShape = sf::RectangleShape(sf::Vector2f(32, 5));
	_healthShape.setFillColor(sf::Color::Green);
}


Health::~Health()
{
}

void Health::draw(sf::RenderTarget& window,sf::Sprite& sprite)
{
	float healthCenterX = (_healthShape.getLocalBounds().width / 2);
	float spriteCenterX = (sprite.getLocalBounds().width / 2);
	_healthShape.setPosition(sf::Vector2f(sprite.getPosition().x+spriteCenterX-healthCenterX, sprite.getPosition().y - 10.0f));
	window.draw(_healthShape);
}

void Health::damage(int damage)
{
	_health -= damage;
	float newSize = (_health / _maxHealth)* 32.0f;
	_healthShape.setSize(sf::Vector2f(newSize, 5));
	if (_health > 70.0f)
	{
		_healthShape.setFillColor(sf::Color::Green);
	}
	else if (_health <= 70.0f && _health >= 40.0f)
	{
		_healthShape.setFillColor(sf::Color::Yellow);
	}
	else if (_health < 40.0f)
	{
		_healthShape.setFillColor(sf::Color::Red);
	}
	std::cout << _health << "   " << _healthShape.getSize().x << std::endl;
}

int Health::healthAmount()
{
	return _health;
}

void Health::setHealth(float health)
{
	_health = health;
	_healthShape.setSize(sf::Vector2f(32, 5));
	_healthShape.setFillColor(sf::Color::Green);
}
