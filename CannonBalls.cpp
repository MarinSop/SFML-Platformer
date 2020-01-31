#include "CannonBalls.h"


CannonBalls::CannonBalls(sf::Vector2f position,float direction)
{
	_shape = sf::RectangleShape(sf::Vector2f(5.0f, 5.0f));
	_shape.setPosition(position);
	_direction = direction;
}



CannonBalls::~CannonBalls()
{
}

void CannonBalls::update()
{
	if (_vel.x >= 10.0f*_direction)
	{
		_vel.x = 10.0f*_direction;
	}
	else
	{
	_vel.x += 2.f*_direction;
	}
	_shape.move(_vel.x, _vel.y);
}

void CannonBalls::draw(sf::RenderTarget & window)
{
	window.draw(_shape);
}

sf::RectangleShape CannonBalls::_ball()
{
	return _shape;
}

