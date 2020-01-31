#include "Collision.h"



Collision::Collision()
{
}


Collision::~Collision()
{
}

void Collision::groundCollision(Player & player, TileMap & ground)
{
	for (unsigned int i = 0; i < ground.tileSize(); i++)
	{
		int diffUp = (ground.checkCollision(i).getPosition().y - player.collider().getPosition().y - player.collider().getLocalBounds().height);
		int diffRight = -((ground.checkCollision(i).getPosition().x + ground .checkCollision(i).getLocalBounds().width) - player.collider().getPosition().x);
		int diffLeft = (ground.checkCollision(i).getPosition().x - (player.collider().getPosition().x + player.collider().getLocalBounds().width));
		int diffDown = -((ground.checkCollision(i).getPosition().y + ground.checkCollision(i).getLocalBounds().height) - player.collider().getPosition().y);
		sf::Vector2f playerCenter(player.collider().getPosition().x + player.collider().getLocalBounds().width / 2.f, player.collider().getPosition().y + player.collider().getLocalBounds().height / 2);
		if (player.collider().getGlobalBounds().intersects(ground.checkCollision(i).getGlobalBounds()))
		{
			sf::Vector2f tileCenter(ground.checkCollision(i).getPosition().x + ground.checkCollision(i).getLocalBounds().width / 2, ground.checkCollision(i).getPosition().y + ground.checkCollision(i).getLocalBounds().height / 2);
			if (diffUp > diffLeft && diffUp > diffRight && diffUp > diffDown && playerCenter.y < tileCenter.y)
			{
				player.isOnGround(true);
				player.resetVel(1);
				player.playerMove(0.0f, diffUp);
				break;
			}
			else if (diffDown > diffLeft && diffDown > diffRight && diffDown > diffUp && playerCenter.y > tileCenter.y)
			{
				player.resetVel(1);
				player.playerMove(0.0f, -diffDown + 1);
			}
			else if (diffLeft > diffUp && playerCenter.x < tileCenter.x)
			{
				player.resetVel(0);
				player.playerMove(diffLeft, 0.0f);
			}
			else if (diffRight > diffUp && playerCenter.x > tileCenter.x)
			{
				player.resetVel(0);
				player.playerMove(-diffRight, 0.0f);
			}
			//std::cout << "up" << diffUp << std::endl;
			//std::cout << "Left" << diffLeft << std::endl;
			//std::cout << "right" << diffRight << std::endl;
			//std::cout << "down" << diffDown << std::endl;
		}
		else
		{
			player.isOnGround(false);
		}
	}
}
