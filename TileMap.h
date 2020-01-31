#pragma once
#include <vector>
#define TEX_PATH "textures\\"
#include "SFML/Graphics.hpp"
#include "Tile.h"
class TileMap
{
public:
	TileMap(std::vector<int> level,std::string texName);
	~TileMap();
	void draw(sf::RenderTarget& target);
	int tileSize();
	void loadTile();
	sf::RectangleShape checkCollision(int i);
	sf::RectangleShape setCollisionPos(sf::Vector2f pos);
	int tileID(int i);
	void changeLvel(std::vector<int> level);
private:
	std::vector<int> _level;
	std::vector<Tile> _tile;
	sf::Texture _texture;
	sf::Sprite _sprite;
	sf::RectangleShape _collision;
	sf::IntRect _intRect;
	float widthI = 0.0f;
	float heightI = 0.0f;
};

