#pragma once
#include "SFML/Graphics.hpp"
#include "Health.h"
#include "TileMap.h"

#define TEX_PATH "textures\\"

class Enemy
{
public:
	Enemy(sf::Vector2f position,sf::RenderWindow& window);
	~Enemy();

	void update(TileMap& ground);
	sf::RectangleShape collider();
	void draw(sf::RenderTarget& window);
	void damage(float damage);
	float currentHealth();
private:
	sf::Texture _tex;
	sf::Sprite _sprite;
	sf::RectangleShape _collision;
	sf::IntRect _rect;
	bool _goingLeft = true;
	Health* _health;
	sf::Clock _animClock;
	float _speed = 1.0f;

	void animate();
};

