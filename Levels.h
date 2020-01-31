#pragma once

#include <vector>
#include "SFML/Graphics.hpp"
class Levels
{
public:
	Levels();
	~Levels();

	std::vector<int> ground(int levelNum);
	std::vector<int> background(int levelNum);
	std::vector<int> traps(int levelNum);
	std::vector<sf::Vector2f> enemys(int levelNum);
	sf::Vector2f endPos(int levelNum);

private:
	std::vector<int> _ground;
	std::vector<int> _background;
	std::vector<int> _traps;

};

