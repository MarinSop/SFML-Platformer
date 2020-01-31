#include "Game.h"



Game::Game(sf::RenderWindow& window)
{
	_level = Levels();
	_player = new Player(window);
	_ground = new TileMap(_level.ground(_currentLevel),"tilemap.png");
	_background = new TileMap(_level.background(_currentLevel),"tilemap.png");
	_background->loadTile();
	_ground->loadTile();
	_traps = new Traps(_level.traps(_currentLevel),*_ground);
	std::vector<sf::Vector2f> tempPosEnemyHolder = _level.enemys(_currentLevel);
	for (int i = 0; i < tempPosEnemyHolder.size(); i++)
	{
		_enemys.push_back(new Enemy(tempPosEnemyHolder[i], window));
	}
	_flagTexture = sf::Texture();
	_flagTexture.loadFromFile("textures\\flag.png");
	_flag = sf::Sprite(_flagTexture);
	_flag.setPosition(_level.endPos(_currentLevel));
}


Game::~Game()
{
	delete _player;
	delete _background;
	delete _ground;
	for (int i = 0; i < _enemys.size(); i++)
	{
		delete _enemys[i];
	}
}

void Game::update(sf::RenderWindow& window)
{
	_player->update();
	_player->collisionHandler(*_ground);
	_player->bulletHit(*_ground);
	if (_enemys.empty() == false)
	{
		for (int i = 0; i < _enemys.size(); i++)
		{
			_enemys[i]->update(*_ground);
		}

	}
	if (_enemys.empty() == false)
	{
		for (int i = 0; i < _enemys.size(); i++)
		{
			_player->bulletEnemyHit(*_enemys[i]);
			if (_enemys[i]->currentHealth() <= 0.0f)
			{
				delete _enemys[i];
				_enemys.erase(std::remove(_enemys.begin(), _enemys.end(), _enemys[i]), _enemys.end());
			}
		}
	}
	//_collision.groundCollision(*_player,*_ground);
	_traps->update(*_player, *_ground,window);
	if (_player->currentHealth() <= 0.0f || _player->collider().getPosition().y > window.getSize().y)
	{
		_currentLevel = 1;
		nextLevel(_currentLevel,window,*_ground);
		resetLevel(window);
	}
	else if (_currentLevel > 4)
	{
		_currentLevel = 1;
		nextLevel(_currentLevel, window,*_ground);
		resetLevel(window);
		_inMenu = true;
	}
	if (_player->collider().getGlobalBounds().intersects(_flag.getGlobalBounds()) && _enemys.empty())
	{
		++_currentLevel;
		nextLevel(_currentLevel,window,*_ground);
	}

}

void Game::draw(sf::RenderTarget& window)
{
	_background->draw(window);
	_ground->draw(window);
	_traps->draw(window);
	if (_playerDead == false)
	_player->draw(window);
	if(_enemys.empty() == false)
	{
		for (int i = 0; i < _enemys.size(); i++)
		{
			_enemys[i]->draw(window);
		}
	}
	if(_enemys.empty())
	window.draw(_flag);

}

void Game::resetLevel(sf::RenderWindow& window)
{
	_player->levelReset();
	for (int i = 0; i < _enemys.size(); i++)
	{
		delete _enemys[i];
	}
	_enemys.clear();
	std::vector<sf::Vector2f> tempPosEnemyHolder = _level.enemys(_currentLevel);
	for (int i = 0; i < tempPosEnemyHolder.size(); i++)
	{
		_enemys.push_back(new Enemy(tempPosEnemyHolder[i], window));
	}
	_traps->levelReset();
}

void Game::nextLevel(int levelNum,sf::RenderWindow& window,TileMap& ground)
{
	_ground->changeLvel(_level.ground(levelNum));
	_background->changeLvel(_level.background(levelNum));
	_traps->changeLevel(_level.traps(levelNum),ground);
	_traps->levelReset();
	_flag.setPosition(_level.endPos(levelNum));
	_player->nextLevel();
	for (int i = 0; i < _enemys.size(); i++)
	{
		delete _enemys[i];
	}
	_enemys.clear();
	std::vector<sf::Vector2f> tempPosEnemyHolder = _level.enemys(levelNum);
	for (int i = 0; i < tempPosEnemyHolder.size(); i++)
	{
		_enemys.push_back(new Enemy(tempPosEnemyHolder[i], window));
	}


}

void Game::eventFunc(std::string action)
{
	if (action == "jump")
	{
		if (_playerDead == false)
			_player->jump();
	}
	if (action == "dash")
	{
		if (_playerDead == false)
			_player->dash();
	}
	if (action == "shoot")
	{
		if (_playerDead == false)
			_player->shoot();
	}
}

bool Game::menuStatus()
{
	return _inMenu;
}

void Game::setMenuStatus(bool boolean)
{
	_inMenu = boolean;
}


