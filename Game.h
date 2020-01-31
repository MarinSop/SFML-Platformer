#pragma once
#include "Player.h"
#include "TileMap.h"
#include "Traps.h"
#include "Enemy.h"
#include "Levels.h"
#include <vector>
class Game
{
public:
	Game(sf::RenderWindow& window);
	~Game();
	void update(sf::RenderWindow &window);
	void draw(sf::RenderTarget& window);
	void eventFunc(std::string action);
	bool menuStatus();
	void setMenuStatus(bool boolean);
private:
	std::vector<int> _groundVector;
	std::vector<int> _backgroundVector;
	Traps* _traps;
	std::vector<Enemy*> _enemys;
	Player* _player;
	TileMap* _ground;
	TileMap* _background;
	Levels _level;
	bool _playerDead = false;
	int _currentLevel = 1;
	bool _inMenu = false;

	void resetLevel(sf::RenderWindow& window);
	void nextLevel(int levelNum,sf::RenderWindow& window, TileMap& ground);

	sf::Texture _flagTexture;
	sf::Sprite _flag;

};

