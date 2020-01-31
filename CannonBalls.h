#pragma once
#include "SFML/Graphics.hpp"
class CannonBalls
{
public:
	CannonBalls(sf::Vector2f position,float direction);
	~CannonBalls();
	void update();
	void draw(sf::RenderTarget& window);
	sf::RectangleShape _ball();
private:
	sf::Vector2f _vel;
	sf::RectangleShape _shape;
	float _direction;
};

