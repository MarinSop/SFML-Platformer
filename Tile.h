#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
class Tile
{
public:
	Tile(sf::Vector2f position,int tileID, sf::Vector2i texWH);
	~Tile();
	sf::IntRect intRect();
	sf::Vector2f position();
	int tileID();
private:
	int _tileID;
	int _widthI = 0;
	int _heightI = 0;
	sf::Vector2i _texWH;
	sf::IntRect _intRect;
	sf::Vector2f _position;

};

