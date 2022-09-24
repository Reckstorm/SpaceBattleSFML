#include <SFML/Graphics.hpp>
#include "Ship.h";
#include "Fleet.h"
#include <thread>;
#include <functional>
#include <algorithm>

using namespace sf;
using namespace ProtoShip;

int main()
{
	srand(time(0));
	RenderWindow window(VideoMode(640, 480), "Space Battle");
	Fleet player;
	load(player);
	while (true)
	{
		player.sellResources();
		player.repairShips();
		player.refillAmmo();
		player.replaceShip(window);
		if (player.empty())
		{
			player = Fleet(window);
		}
		
		Fleet enemy(1);
		std::thread battle(&Fleet::battle, std::ref(player), std::ref(enemy));
		battle.detach();
		while (window.isOpen())
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
				{
					if (!player.empty())
					{
						player.save();
					}
					window.close();
					exit(0);
				}
			}

			window.clear(Color(30, 30, 30, 0));


			if (!player.empty())
			{
				for (Ship& i : player)
				{
					window.draw(i);
				}
				player.printFleet(window);
				player.printCurrency(window);
			}
			if (!enemy.empty())
			{
				for (Ship& i : enemy)
				{
					window.draw(i);
				}
				enemy.printEnemyFleet(window);
			}


			window.display();


			if (player[0].getType() == 0)
			{
				player.clear();
				break;
			}
			if (enemy[0].getType() == 0)
			{
				enemy.clear();
				break;
			}
		}
	}
	

}
