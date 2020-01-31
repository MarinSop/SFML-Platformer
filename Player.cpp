#include "Player.h"



Player::Player(sf::RenderWindow& window)
{
	_texture = sf::Texture();
	_texture.loadFromFile(TEX_PATH "megabottileset.png");
	_rect = sf::IntRect(0, 0, 28.0f, 28.0f);
	_sprite = sf::Sprite(_texture,_rect);
	_collision = sf::RectangleShape(sf::Vector2f(16.0f, 28.0f));
	_collision.setFillColor(sf::Color::Red);
	_collision.setPosition(_startingPos);
	_sprite.setPosition(_collision.getPosition().x + (_collision.getLocalBounds().width / 2.f) - (_sprite.getLocalBounds().width / 2.f), _collision.getPosition().y + _collision.getLocalBounds().height - _sprite.getLocalBounds().height);
	_health = new Health(100);
}

Player::Player()
{
}


Player::~Player()
{
	delete _health;
}

void Player::update()
{
	movement();
	if (_cannonBalls.empty() == false)
	{
		for (int i = 0; i < _cannonBalls.size(); i++)
		{
			_cannonBalls[i]->update();
		}
	}
	if (_animateClock.getElapsedTime().asSeconds() > 0.07f)
	{
	animate();
	}
	if (_invicibleClock.getElapsedTime().asSeconds() >= 2.0f)
	{
	invincibleFunc();
	_invicibleClock.restart();
	}
}

void Player::movement()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (_vel.x > -_maxVel)
		{
			_vel.x += _acceleration * -1.f;
	    }
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (_vel.x < _maxVel)
		{
			_vel.x += _acceleration * 1.f;
		}
	}
	
	if (_vel.x > 0)
	{
		_vel.x -= _drag;
		if (_vel.x < 0)
		{
			_vel.x = 0.0f;
		}
	}
	else if (_vel.x < 0)
	{
		_vel.x += _drag;
		if (_vel.x > 0)
		{
			_vel.x = 0.0f;
		}
	}
	if (_isOnGround == false)
	{
		if (_vel.y >= _maxGravity)
		{
			_vel.y = _maxGravity;
		}
		else
		{
			_vel.y += _gravity;
		}
	}
	playerMove(_vel.x, _vel.y);
	
}

void Player::animate()
{
	if (_isOnGround == false)
	{
			if (_vel.x > 0)
			{
				_rect.width = 28.0f;
			    _rect.left = 0;
			}
			else if (_vel.x < 0)
			{
				_rect.left = 28.0f;
				_rect.width = -28.0f;
			}
			_rect.top = 28.0f;
			_running = false;
	}
	else
	{
		if (_vel.x > 0.0f && _running == false)
		{
			_running = true;
			_rect.left = 0.0f;
			_rect.top = 28.0f*2.f;
		}
		else if (_vel.x < 0.0f && _running == false)
		{
			_running = true;
			_rect.left = 28.0f;
			_rect.top = 28.0f*2.0f;
		}
		if (_vel.x > 0.0f && _running == true)
		{
			_rect.width = 28.0f;
			if (_rect.left < 112.0f-28.0f)
			{
				_rect.left += 28.0f;
			}
			else
			{
				_rect.left = 0.0f;
				_rect.top = 28.0f*2.0f;
			}
		}
		else if (_vel.x < 0.0f && _running == true)
		{
			_rect.width = -28.0f;
			if (_rect.left < 112.0f)
			{
				_rect.left += 28.0f;
			}
			else
			{
				_rect.left = 28.0f;
				_rect.top = 28.0f*2.0f;
			}
		}
		else if (_vel.x == 0)
		{
			if (_rect.width > 0)
			{
				_rect.left = 0;
			}
			else
			{
				_rect.left = 28.0f;
			}
			_rect.top = 0.0f;
			_running = false;
		}
	}
	_sprite.setTextureRect(_rect);
	_animateClock.restart();
}

void Player::invincibleFunc()
{
	if (_invincible == true)
	{
			_invincible = false;
			_invicibleClock.restart();
	}
}

void Player::bulletHit(TileMap& ground)
{
	if (_cannonBalls.empty() == false)
	{
		for (int i = 0; i < ground.tileSize(); ++i)
		{
			for (int j = 0; j < _cannonBalls.size(); ++j)
			{
				if (ground.checkCollision(i).getGlobalBounds().intersects(_cannonBalls[j]->_ball().getGlobalBounds()))
				{
					delete _cannonBalls[j];
					_cannonBalls.erase(std::remove(_cannonBalls.begin(), _cannonBalls.end(), _cannonBalls[j]), _cannonBalls.end());
				}
				
			}
		}
	}
}

void Player::bulletEnemyHit(Enemy& enemy)
{
	if (_invincible == false)
	{
		if (_collision.getGlobalBounds().intersects(enemy.collider().getGlobalBounds()))
		{
			_health->damage(30.0f);
			_invincible = true;
		}
	}
	if (_cannonBalls.empty() == false)
	{
		for (int i = 0; i < _cannonBalls.size(); i++)
		{
			if (enemy.collider().getGlobalBounds().intersects(_cannonBalls[i]->_ball().getGlobalBounds()))
			{
				enemy.damage(50.0f);
				delete _cannonBalls[i];
				_cannonBalls.erase(std::remove(_cannonBalls.begin(), _cannonBalls.end(), _cannonBalls[i]), _cannonBalls.end());
			}

		}
	}
}

void Player::playerMove(float x, float y)
{
	_collision.move(x, y);
	_sprite.move(x, y);
}

void Player::damage(int damage)
{
	_health->damage(damage);
}

void Player::shoot()
{
	if (_shotTime.getElapsedTime().asSeconds() >= 1.0f)
	{
		if (_rect.width < 0.0f)
		{
			_cannonBalls.push_back(new CannonBalls(sf::Vector2f(_collision.getPosition().x, _collision.getPosition().y + (_collision.getLocalBounds().height / 2)), -1.0f));
		}
		else if (_rect.width > 0.0f)
		{
			_cannonBalls.push_back(new CannonBalls(sf::Vector2f(_collision.getPosition().x + _collision.getLocalBounds().width, _collision.getPosition().y + (_collision.getLocalBounds().height / 2)), 1.0f));
		}
		_shotTime.restart();
	}
}

bool Player::invincibility()
{
	return _invincible;
}

void Player::changeInvicibility(bool state)
{
	_invincible = state;
}

sf::Vector2f Player::playerVel()
{
	return _vel;
}

void Player::levelReset()
{
	_collision.setPosition(_startingPos);
	_sprite.setPosition(_collision.getPosition().x + (_collision.getLocalBounds().width / 2.f) - (_sprite.getLocalBounds().width / 2.f), _collision.getPosition().y + _collision.getLocalBounds().height - _sprite.getLocalBounds().height);
	_health->setHealth(100.0f);
	resetVel(2);
	if (!_cannonBalls.empty())
	{
		for (int i = 0; i < _cannonBalls.size(); i++)
		{
			delete _cannonBalls[i];
			_cannonBalls.erase(std::remove(_cannonBalls.begin(), _cannonBalls.end(), _cannonBalls[i]), _cannonBalls.end());
		}
	}
}

void Player::nextLevel()
{
	_collision.setPosition(_startingPos);
	_sprite.setPosition(_collision.getPosition().x + (_collision.getLocalBounds().width / 2.f) - (_sprite.getLocalBounds().width / 2.f), _collision.getPosition().y + _collision.getLocalBounds().height - _sprite.getLocalBounds().height);
	resetVel(2);
}

void Player::collisionHandler(TileMap& tilemap)
{
	for (unsigned int i = 0; i < tilemap.tileSize(); i++)
	{
		int diffUp = (tilemap.checkCollision(i).getPosition().y - _collision.getPosition().y - _collision.getLocalBounds().height);
		int diffRight = -((tilemap.checkCollision(i).getPosition().x + tilemap.checkCollision(i).getLocalBounds().width) - _collision.getPosition().x);
		int diffLeft = (tilemap.checkCollision(i).getPosition().x - (_collision.getPosition().x + _collision.getLocalBounds().width));
		int diffDown = -((tilemap.checkCollision(i).getPosition().y + tilemap.checkCollision(i).getLocalBounds().height) - _collision.getPosition().y);
		sf::Vector2f playerCenter(_collision.getPosition().x + _collision.getLocalBounds().width / 2.f, _collision.getPosition().y + _collision.getLocalBounds().height / 2);
		if (_collision.getGlobalBounds().intersects(tilemap.checkCollision(i).getGlobalBounds()))
		{
			sf::Vector2f tileCenter(tilemap.checkCollision(i).getPosition().x + tilemap.checkCollision(i).getLocalBounds().width / 2, tilemap.checkCollision(i).getPosition().y + tilemap.checkCollision(i).getLocalBounds().height / 2);
			if (diffUp > diffLeft && diffUp > diffRight && diffUp > diffDown && playerCenter.y < tileCenter.y)
			{
				_isOnGround = true;
				_doubleJump = true;
				_vel.y = 0.0f;
				playerMove(0.0f, diffUp);
				break;
			}
			else if (diffDown > diffLeft && diffDown > diffRight && diffDown > diffUp && playerCenter.y > tileCenter.y)
			{
				_vel.y = 0.0f;
				playerMove(0.0f, -diffDown + 1);
			}
			else if (diffLeft > diffUp && playerCenter.x < tileCenter.x)
			{
				_vel.x = 0.0f;
				playerMove(diffLeft, 0.0f);
			}
			else if (diffRight > diffUp && playerCenter.x > tileCenter.x)
			{
				_vel.x = 0.0f;
				playerMove(-diffRight, 0.0f);
			}
			//std::cout << "up" << diffUp << std::endl;
			//std::cout << "Left" << diffLeft << std::endl;
			//std::cout << "right" << diffRight << std::endl;
			//std::cout << "down" << diffDown << std::endl;
		}
		else
		{
			_isOnGround = false;
		}
	}
	//_collision.move(0.0f, _vel.y);
	//std::cout << _vel.y << std::endl;
	//std::cout << _vel.x << std::endl;
}

void Player::jump()
{
	if (_isOnGround == true)
	{
	_vel.y += _jumpHeight;
	}
	if (_isOnGround == false && _doubleJump == true)
	{
		_doubleJump = false;
		_vel.y = 0.0f;
		_vel.y += _jumpHeight;
	}
}

void Player::dash()
{
	if (_vel.x > 0.0f)
	{
		_vel.y = 0.0f;
		_vel.x = 20.0f;
	}
	else if (_vel.x < 0.0f)
	{
		_vel.y = 0.0f;
		_vel.x = -20.0f;
	}
}

float Player::currentHealth()
{
	return _health->healthAmount();
}

void Player::resetVel(int i)
{
	if (i == 0)
	{
		_vel.x = 0;
	}
	else if (i == 1)
	{
		_vel.y = 0;
	}
	else
	{
		_vel.x = 0;
		_vel.y = 0;
	}
}

void Player::draw(sf::RenderTarget& window)
{
	//window.draw(_collision);
	if (_invincible == true)
	{
		if (_flashClock.getElapsedTime().asSeconds() >= 0.1f)
		{
			if (_flashing == true)
				_flashing = false;
			else
				_flashing = true;
			_flashClock.restart();
		}
		else
		{
			if(_flashing == true)
			window.draw(_sprite);
		}
	}
	else
	{
	window.draw(_sprite);
	}
	if (_cannonBalls.empty() == false)
	{
		for (int i = 0; i < _cannonBalls.size(); i++)
		{
			_cannonBalls[i]->draw(window);
		}
	}
	_health->draw(window,_sprite);
	//window.draw(_collision);
}

void Player::isOnGround(bool boolean)
{
	_isOnGround = boolean;
	if (boolean == true)
	{
		_doubleJump = boolean;
	}
}

sf::RectangleShape Player::collider()
{
	return _collision;
}
