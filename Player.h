#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include "Health.h"
#include "TileMap.h"
#include <vector>
#include "CannonBalls.h"
#include "Enemy.h"

#define TEX_PATH "textures\\"

class Player
{
public:
	Player(sf::RenderWindow& window);
	Player();
	~Player();
	void update();
	void draw(sf::RenderTarget& window);
	void isOnGround(bool boolean);
	sf::RectangleShape collider();
	void collisionHandler(TileMap& tilemap);
	void bulletHit(TileMap& ground);
	void bulletEnemyHit(Enemy& enemy);
	void jump();
	void dash();
	float currentHealth();
	void resetVel(int i);
	void playerMove(float x, float y);
	void damage(int damage);
	void shoot();
	bool invincibility();
	void changeInvicibility(bool state);
	sf::Vector2f playerVel();
	void levelReset();
	void nextLevel();

private:
	sf::Clock _shotTime;
	std::vector<CannonBalls*> _cannonBalls;
	Health* _health;
	sf::Event _event;
	sf::Clock _animateClock;
	sf::Texture _texture;
	sf::IntRect _rect;
	sf::Sprite _sprite;
	sf::RectangleShape _collision;
	void movement();
	void animate();
	void invincibleFunc();
	bool _running = false;
	bool _doubleJump = true;
	float _acceleration = 2.f;
	float _jumpHeight = -10.0f;
	float _maxVel = 5.f;
	float _drag = 0.8f;
	float _gravity = 0.8f;
	float _maxGravity = 15.0f;
	bool _isOnGround = false;
	bool _invincible = false;
	bool _flashing = false;
	sf::Clock _flashClock;
	sf::Clock _invicibleClock;
	sf::Vector2f _vel;
	sf::Vector2f _startingPos = sf::Vector2f(32.0f * 5.0f, 32.0f*20.0f);

};

