#include "Tile.h"



Tile::Tile(sf::Vector2f position, int tileID, sf::Vector2i texWH)
{
	_position = position;
	_tileID = tileID;
	_texWH = texWH;
	for (int i = 0; i < _tileID;++i)
	{
		if (_widthI * 32 >= _texWH.x-32)
		{
			_widthI = 0;
			++_heightI;

		}
		else
		{
		++_widthI;
		}
	}
	_intRect = sf::IntRect(_widthI*32.0f,_heightI*32.0f,32.0f,32.0f);

}

Tile::~Tile() 
{
}

sf::IntRect Tile::intRect()
{
	return _intRect;
}

sf::Vector2f Tile::position()
{
	return sf::Vector2f(_position);
}

int Tile::tileID()
{
	return _tileID;
}
