#include "Enemy.h"

Enemy::Enemy(sf::Vector2f position,sf::RenderWindow& window)
{
	_tex = sf::Texture();
	_tex.loadFromFile(TEX_PATH "enemy.png");
	_rect = sf::IntRect(22.0f*10, 0.0f, -22.0f, 33.0f);
	_sprite = sf::Sprite(_tex,_rect);
	_collision = sf::RectangleShape(sf::Vector2f(16.0f, 32.0f));
	_sprite.setPosition(position);
	_collision.setPosition(_sprite.getPosition());
	_health = new Health(100);
}

Enemy::~Enemy()
{
	delete _health;
}

void Enemy::update(TileMap& ground)
{
	for (int i = 0; i < ground.tileSize(); i++)
	{
		if (_collision.getGlobalBounds().intersects(ground.checkCollision(i).getGlobalBounds()))
		{
			if (_goingLeft == true)
			{
				_rect.width = 22.0f;
				_sprite.setTextureRect(_rect);
				_goingLeft = false;
			}
			else if(_goingLeft == false)
			{
				_rect.width = -22.0f;
				_sprite.setTextureRect(_rect);
				_goingLeft = true;
			}
		}
		
	}
	if (_goingLeft == true)
	{
		_sprite.move(-_speed, 0.0f);
		_collision.move(-_speed, 0.0f);
	}
	else
	{
		_sprite.move(_speed, 0.0f);
		_collision.move(_speed, 0.0f);
	}
	animate();
}

sf::RectangleShape Enemy::collider()
{
	return _collision;
}

void Enemy::draw(sf::RenderTarget& window)
{
	_health->draw(window,_sprite);
	//window.draw(_collision);
	window.draw(_sprite);
}

void Enemy::damage(float damage)
{
	_health->damage(damage);
}

float Enemy::currentHealth()
{
	return _health->healthAmount();
}

void Enemy::animate()
{
	if (_animClock.getElapsedTime().asSeconds() >= 0.25f)
	{
		if (_goingLeft == true)
		{
			if (_rect.left > 286.0f-22.0f)
			{
				_rect.left = 22.0f;
			}
			else
			{
				_rect.left += 22.0f;
			}
		}
		else
		{
			if (_rect.left >= 286.0f-22.0f)
			{
				_rect.left = 22.0f;
			}
			else
			{
				_rect.left += 22.0f;
			}
		}
		_sprite.setTextureRect(_rect);
		_animClock.restart();
	}
}
