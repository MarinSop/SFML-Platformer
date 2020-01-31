#pragma once
#include "TileMap.h"
#include "CannonBalls.h"
#include <vector>
#include <algorithm>
#include "Player.h"
class Traps
{
public:
	Traps(std::vector<int> level, TileMap& ground);
	~Traps();
	void update(Player& player,TileMap& ground, sf::RenderWindow& window);
	void draw(sf::RenderTarget& window);
	void levelReset();
	void changeLevel(std::vector<int> level, TileMap& ground);
private:
	std::vector<CannonBalls*> _cannonBalls;
	std::vector<sf::Vector2f> _tileToHit;
	sf::Clock _shotTime;
	TileMap* _tex;

	void collisionHandler(Player& player, TileMap& ground,sf::RenderWindow& window);
	void detectTileHit(TileMap& ground);

};

