#include "TileMap.h"



TileMap::TileMap(std::vector<int> level, std::string texName)
{
	_texture = sf::Texture();
	_texture.loadFromFile(TEX_PATH + texName);
	_sprite = sf::Sprite(_texture);
	_collision = sf::RectangleShape(sf::Vector2f(32.f,32.f));
	_level = level;
}


TileMap::~TileMap()
{
}


void TileMap::draw(sf::RenderTarget & window)
{
	for (unsigned int i = 0; i < _tile.size(); i++)
	{
		_sprite.setTextureRect(_tile[i].intRect());
		_sprite.setPosition(_tile[i].position());
 	    window.draw(_sprite);
	}
}

int TileMap::tileSize()
{
	return _tile.size();
}

void TileMap::loadTile()
{
	for (int i = 0; i < _level.size(); i++)
	{
		if (widthI * 32.0f < 992.0f)
		{
			if (_level[i] > -1)
			{
				_tile.push_back(Tile(sf::Vector2f(widthI*32.0f, heightI*32.0f), _level[i], sf::Vector2i(_texture.getSize().x, _texture.getSize().y)));
			}

		++widthI;
		}
		else
		{
			if (_level[i] > -1)
			{
			_tile.push_back(Tile(sf::Vector2f(widthI*32.0f, heightI*32.0f), _level[i], sf::Vector2i(_texture.getSize().x, _texture.getSize().y)));
			}
			widthI = 0;
			++heightI;
		}

	}
}

sf::RectangleShape TileMap::checkCollision(int i)
{
	_collision.setPosition(_tile[i].position());
	return _collision;
}

sf::RectangleShape TileMap::setCollisionPos(sf::Vector2f pos)
{
	_collision.setPosition(pos);
	return _collision;
}

int TileMap::tileID(int i)
{
	return _tile[i].tileID();
}

void TileMap::changeLvel(std::vector<int> level)
{
	_level.clear();
	_level = level;
	_tile.clear();
	widthI = 0;
	heightI = 0;
	loadTile();
}


