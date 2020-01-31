#pragma once
#include "SFML/Graphics.hpp"
class Health
{
public:
	Health(float healthAmount);
	~Health();
	void draw(sf::RenderTarget& window,sf::Sprite& sprite);
	void damage(int damage);
	int healthAmount();
	void setHealth(float health);
private:
	float _health;
	float _maxHealth;
	sf::RectangleShape _healthShape;
};

