#include "Traps.h"


Traps::Traps(std::vector<int> level, TileMap& ground)
{
	_tex = new TileMap(level,"traps.png");
	_tex->loadTile();
	detectTileHit(ground);
}


Traps::~Traps()
{
}

void Traps::update(Player & player, TileMap& ground, sf::RenderWindow& window)
{
	if (_shotTime.getElapsedTime().asSeconds() > 2.0f)
	{
		for (int i = 0; i < _tex->tileSize(); i++)
		{
		sf::Vector2f tileCenter(_tex->checkCollision(i).getPosition().x + _tex->checkCollision(i).getLocalBounds().width / 2,
					_tex->checkCollision(i).getPosition().y + _tex->checkCollision(i).getLocalBounds().height / 2);
			if (_tex->tileID(i) == 1)
			{
				_cannonBalls.push_back(new CannonBalls(sf::Vector2f(_tex->checkCollision(i).getPosition().x, tileCenter.y), -1.0f));
			}
			else if (_tex->tileID(i) == 2)
			{
				_cannonBalls.push_back(new CannonBalls(sf::Vector2f(_tex->checkCollision(i).getPosition().x +
					_tex->checkCollision(i).getLocalBounds().width, tileCenter.y), 1.0f));
			}
				
		}
		_shotTime.restart();
	}
	if (_cannonBalls.empty() == false)
	{
		for (int i = 0; i < _cannonBalls.size(); i++)
		{
			_cannonBalls[i]->update();
		}
	}
	collisionHandler(player,ground,window);
}

void Traps::collisionHandler(Player & player, TileMap& ground,sf::RenderWindow& window)
{
	sf::Vector2f playerCenter(player.collider().getPosition().x + player.collider().getLocalBounds().width / 2.0f,
		player.collider().getPosition().y + player.collider().getLocalBounds().height / 2);
	if (player.invincibility() == false)
	{
		for (int i = 0; i < _tex->tileSize(); i++)
		{
			if (_tex->checkCollision(i).getGlobalBounds().intersects(player.collider().getGlobalBounds()))
			{
				if (_tex->tileID(i) == 0)
				{
					sf::Vector2f tileCenter(_tex->checkCollision(i).getPosition().x + _tex->checkCollision(i).getLocalBounds().width / 2,
						_tex->checkCollision(i).getPosition().y + _tex->checkCollision(i).getLocalBounds().height / 2);
					if (player.collider().getPosition().y + (player.collider().getLocalBounds().height) >
						tileCenter.y)
					{
						player.changeInvicibility(true);
						player.damage(20);
						player.resetVel(2);
						if (playerCenter.x > tileCenter.x)
						{
							player.playerMove(32, -32);
						}
						else
						{
							player.playerMove(-32, -32);
						}
						break;
					}
				}

			}
		}
	}
	if (_cannonBalls.empty() == false)
	{
		for (int j = 0; j < _cannonBalls.size(); j++)
		{
			if (player.collider().getGlobalBounds().intersects(_cannonBalls[j]->_ball().getGlobalBounds()))
			{
				player.changeInvicibility(true);
				delete _cannonBalls[j];
				_cannonBalls.erase(std::remove(_cannonBalls.begin(), _cannonBalls.end(), _cannonBalls[j]), _cannonBalls.end());
				player.damage(10);
				break;
			}
			else if (_cannonBalls[j]->_ball().getPosition().x < 0.0f || _cannonBalls[j]->_ball().getPosition().x > window.getSize().x)
			{
				delete _cannonBalls[j];
				_cannonBalls.erase(std::remove(_cannonBalls.begin(), _cannonBalls.end(), _cannonBalls[j]), _cannonBalls.end());
				break;
			}
			else
			{
				for (int i = 0; i <_tileToHit.size(); ++i)
				{
					if (ground.setCollisionPos(_tileToHit[i]).getGlobalBounds().intersects(_cannonBalls[j]->_ball().getGlobalBounds()))
					{
						delete _cannonBalls[j];
						_cannonBalls.erase(std::remove(_cannonBalls.begin(), _cannonBalls.end(), _cannonBalls[j]), _cannonBalls.end());
						break;
					}
				}
			}
		}
	}
}

void Traps::detectTileHit(TileMap& ground)
{
	_tileToHit.clear();
	for (int i = 0; i < ground.tileSize(); ++i)
	{
		for (int j = 0; j < _tex->tileSize(); ++j)
		{
			if (_tex->tileID(j) >= 1)
			{
				if (ground.checkCollision(i).getPosition().y == _tex->checkCollision(j).getPosition().y)
				{
					_tileToHit.push_back(ground.checkCollision(i).getPosition());
				}
			}
		}
	}
}

void Traps::draw(sf::RenderTarget & window)
{
	_tex->draw(window);
	if (_cannonBalls.empty() == false)
	{
		for (int i = 0; i < _cannonBalls.size(); i++)
		{
			_cannonBalls[i]->draw(window);
		}
	}
}

void Traps::levelReset()
{
	for (int i = 0; i < _cannonBalls.size(); i++)
	{
		delete _cannonBalls[i];
	}
	_cannonBalls.clear();

}

void Traps::changeLevel(std::vector<int> level,TileMap& ground)
{
	for (int i = 0; i < _cannonBalls.size(); i++)
	{
		delete _cannonBalls[i];
	}
	_cannonBalls.clear();
	_tex->changeLvel(level);
	detectTileHit(ground);
}

