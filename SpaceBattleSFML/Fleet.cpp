#include "Fleet.h"

Fleet::Fleet(int i)
{
	this->resources = 50 + rand() % 100;
	int lvl = 1 + rand() % 10;
	int x = 0;
	int y = 0;
	int num = 0;
	for (int i = 0; i < 5; i++)
	{
		int j = 1 + rand() % 3;
		if (i == 0)
		{
			commandShip command;
			for (int i = 0; i < lvl; i++)
			{
				command.lvlup();
			}
			this->emplace_back(command);
			shared_ptr<commandLieutenant> commandL = std::make_shared<commandLieutenant>();
			this->at(0).setCrew(commandL);
			shared_ptr<Laser> laserW = std::make_shared<Laser>();
			this->at(0).setWeapon(laserW);
			this->at(0).setPosition(500, 220);
			this->at(0).paint(255, 0, 0, 255);
		}
		else
		{
			num = this->size();
			x = this->at(0).getPosition().x - 10;
			y = this->at(num - 1).getPosition().y + this->at(num - 1).getSize().y + 10;
			switch (j)
			{
			case 1:
			{
				attackShip attack;
				for (int i = 0; i < lvl; i++)
				{
					attack.lvlup();
				}
				this->emplace_back(attack);
				shared_ptr<attackLieutenant> attackL = std::make_shared<attackLieutenant>();
				this->at(num).setCrew(attackL);
				shared_ptr<Missile> missileW = std::make_shared<Missile>();
				this->at(num).setWeapon(missileW);
				if (num >= 2)
				{
					this->at(num).setPosition(x - this->at(num).getSize().x, y);
				}
				else
				{
					this->at(num).setPosition(x - this->at(num).getSize().x, 160);
				}
				this->at(num).paint(255, 0, 0, 255);
				break;
			}
			case 2:
			{
				defenceShip defence;
				for (int i = 0; i < lvl; i++)
				{
					defence.lvlup();
				}
				this->emplace_back(defence);
				shared_ptr<defenceLieutenant> defenceL = std::make_shared<defenceLieutenant>();
				this->at(num).setCrew(defenceL);
				shared_ptr<Missile> missileW = std::make_shared<Missile>();
				this->at(num).setWeapon(missileW);
				if (num >= 2)
				{
					this->at(num).setPosition(x - this->at(num).getSize().x, y);
				}
				else
				{
					this->at(num).setPosition(x - this->at(num).getSize().x, 160);
				}
				this->at(num).paint(0, 220, 0, 255);
				break;
			}
			case 3:
			{
				supportShip support;
				for (int i = 0; i < lvl; i++)
				{
					support.lvlup();
				}
				this->emplace_back(support);
				shared_ptr<supportLieutenant> supportL = std::make_shared<supportLieutenant>();
				this->at(num).setCrew(supportL);
				shared_ptr<Turret> turretW = std::make_shared<Turret>();
				this->at(num).setWeapon(turretW);
				if (num >= 2)
				{
					this->at(num).setPosition(x - this->at(num).getSize().x, y);
				}
				else
				{
					this->at(num).setPosition(x - this->at(num).getSize().x, 160);
				}
				this->at(num).paint(255, 255, 0, 255);
				break;
			}
			}
		}
	}

}

Fleet::Fleet(RenderWindow& window)
{
	this->money = 200000;
	Font font;
	font.loadFromFile("Fonts\\arial.ttf");
	Text start("Make command ship - 30000", font, 25);
	Text quit("Quit", font, 25);


	start.setPosition(50, 50);
	quit.setPosition(50, 75);


	bool flag = 1;
	int menu_num = 0;
	while (flag)
	{
		start.setFillColor(Color(255, 255, 255, 255));
		quit.setFillColor(Color(255, 255, 255, 255));
		window.clear(Color(30, 30, 30, 0));

		if (IntRect(50, 50, 400, 25).contains(Mouse::getPosition(window)))
		{
			start.setFillColor(Color::Blue);
			menu_num = 1;
		}
		if (IntRect(50, 75, 100, 25).contains(Mouse::getPosition(window)))
		{
			quit.setFillColor(Color::Blue);
			menu_num = 2;
		}

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			switch (menu_num)
			{
			case 1:
			{
				makeCommandShip(window);
				this->money -= this->at(0).getPrice();
				flag = 0;
				for (int i = 0; i < 4; i++)
				{
					makeShip(window);
				}
				break;
			}
			case 2:
				flag = 0;
				if (!this->empty())
				{
					this->save();
				}
				window.close();
				exit(0);
			}
		}
		window.draw(start);
		window.draw(quit);
		this->printCurrency(window);
		window.display();
	}
}

void Fleet::setMoney(int i)
{
	this->money += i;
}

void Fleet::setResources(int i)
{
	this->resources += i;
}

void Fleet::makeCommandShip(RenderWindow& window)
{
	commandShip command;
	this->emplace_back(command);
	makeWeapon(this->at(0), window);
	makeCrew(this->at(0), window);
	this->at(0).setPosition(100, 220);
	this->at(0).paint(255, 0, 0, 255);
}

void Fleet::makeShip(RenderWindow& window)
{
	Font font;
	font.loadFromFile("Fonts\\arial.ttf");
	Text title("Choose ship type", font, 25);
	Text attack("Attack - 25000", font, 25);
	Text defence("Defence - 25000", font, 25);
	Text support("Support - 20000", font, 25);
	Text quit("Quit", font, 25);

	title.setPosition(50, 50);
	attack.setPosition(50, 75);
	defence.setPosition(50, 100);
	support.setPosition(50, 125);
	quit.setPosition(50, 150);

	bool flag = 1;
	int menu_num = 0;
	int num = this->size();
	int x = this->at(0).getPosition().x + this->at(0).getSize().x + 10;
	int y = this->at(num - 1).getPosition().y + this->at(num - 1).getSize().y + 10;

	while (flag)
	{
		title.setFillColor(Color(255, 255, 255, 255));
		attack.setFillColor(Color(255, 255, 255, 255));
		defence.setFillColor(Color(255, 255, 255, 255));
		support.setFillColor(Color(255, 255, 255, 255));
		quit.setFillColor(Color(255, 255, 255, 255));
		window.clear(Color(30, 30, 30, 0));

		if (IntRect(50, 75, 200, 25).contains(Mouse::getPosition(window)))
		{
			attack.setFillColor(Color::Blue);
			menu_num = 1;
		}
		if (IntRect(50, 100, 200, 25).contains(Mouse::getPosition(window)))
		{
			defence.setFillColor(Color::Blue);
			menu_num = 2;
		}
		if (IntRect(50, 125, 200, 25).contains(Mouse::getPosition(window)))
		{
			support.setFillColor(Color::Blue);
			menu_num = 3;
		}
		if (IntRect(50, 150, 200, 25).contains(Mouse::getPosition(window)))
		{
			quit.setFillColor(Color::Blue);
			menu_num = 4;
		}

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			switch (menu_num)
			{
			case 1:
			{
				attackShip attack;
				if (this->money <= attack.getPrice())
				{
					this->insufficientMoney(window);
					break;
				}
				else
				{
					this->money -= attack.getPrice();
					this->emplace_back(attack);
					sleep(Time(milliseconds(menuDelay())));
					makeWeapon(this->at(num), window);
					makeCrew(this->at(num), window);

					if (num >= 2)
					{
						this->at(num).setPosition(x, y);
					}
					else
					{
						this->at(num).setPosition(x, 160);
					}
					this->at(num).paint(255, 0, 0, 255);
					flag = 0;
					break;
				}
			}
			case 2:
			{
				defenceShip defence;
				if (this->money <= defence.getPrice())
				{
					this->insufficientMoney(window);
					break;
				}
				else
				{
					this->money -= defence.getPrice();
					this->emplace_back(defence);
					sleep(Time(milliseconds(menuDelay())));
					makeWeapon(this->at(num), window);
					makeCrew(this->at(num), window);
					if (num >= 2)
					{
						this->at(num).setPosition(x, y);
					}
					else
					{
						this->at(num).setPosition(x, 160);
					}
					this->at(num).paint(0, 220, 0, 255);
					flag = 0;
					break;
				}
			}
			case 3:
			{
				supportShip support;
				if (this->money <= support.getPrice())
				{
					this->insufficientMoney(window);
					break;
				}
				else
				{
					this->money -= support.getPrice();
					this->emplace_back(support);
					sleep(Time(milliseconds(menuDelay())));
					makeWeapon(this->at(num), window);
					makeCrew(this->at(num), window);
					if (num >= 2)
					{
						this->at(num).setPosition(x, y);
					}
					else
					{
						this->at(num).setPosition(x, 160);
					}
					this->at(num).paint(255, 255, 0, 255);
					flag = 0;
					break;
				}
			}
			case 4:
				flag = 0;
				if (!this->empty())
				{
					this->save();
				}
				window.close();
				exit(0);
			}
		}

		window.draw(title);
		window.draw(attack);
		window.draw(defence);
		window.draw(support);
		window.draw(quit);
		this->printCurrency(window);

		window.display();
	}
}

void Fleet::makeWeapon(Ship& ship, RenderWindow& window)
{
	Font font;
	font.loadFromFile("Fonts\\arial.ttf");
	Text title("Choose weapon", font, 25);
	Text laser("Laser - 5000", font, 25);
	Text missile("Missile - 5000", font, 25);
	Text turret("Turret - 5000", font, 25);

	title.setPosition(50, 50);
	laser.setPosition(50, 75);
	missile.setPosition(50, 100);
	turret.setPosition(50, 125);

	bool flag = 1;
	int menu_num = 0;


	while (flag)
	{
		title.setFillColor(Color(255, 255, 255, 255));
		laser.setFillColor(Color(255, 255, 255, 255));
		missile.setFillColor(Color(255, 255, 255, 255));
		turret.setFillColor(Color(255, 255, 255, 255));
		window.clear(Color(30, 30, 30, 0));

		if (IntRect(50, 75, 150, 25).contains(Mouse::getPosition(window)))
		{
			laser.setFillColor(Color::Blue);
			menu_num = 1;
		}
		if (IntRect(50, 100, 150, 25).contains(Mouse::getPosition(window)))
		{
			missile.setFillColor(Color::Blue);
			menu_num = 2;
		}
		if (IntRect(50, 125, 150, 25).contains(Mouse::getPosition(window)))
		{
			turret.setFillColor(Color::Blue);
			menu_num = 3;
		}

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			switch (menu_num)
			{
			case 1:
			{
				shared_ptr<Laser> laserW = std::make_shared<Laser>();
				if (this->money < laserW->getPrice())
				{
					this->insufficientMoney(window);
					laserW.~shared_ptr();
					break;
				}
				else
				{
					this->money -= laserW->getPrice();
					ship.setWeapon(laserW);
					flag = 0;
					sleep(Time(milliseconds(menuDelay())));
					break;
				}
			}
			case 2:
			{
				shared_ptr<Missile> missileW = std::make_shared<Missile>();
				if (this->money < missileW->getPrice())
				{
					this->insufficientMoney(window);
					missileW.~shared_ptr();
					break;
				}
				else
				{
					this->money -= missileW->getPrice();
					ship.setWeapon(missileW);
					flag = 0;
					sleep(Time(milliseconds(menuDelay())));
					break;
				}
			}
			case 3:
			{
				shared_ptr<Turret> turretW = std::make_shared<Turret>();
				if (this->money < turretW->getPrice())
				{
					this->insufficientMoney(window);
					turretW.~shared_ptr();
					break;
				}
				else
				{
					this->money -= turretW->getPrice();
					ship.setWeapon(turretW);
					flag = 0;
					sleep(Time(milliseconds(menuDelay())));
					break;
				}
			}
			}
		}

		window.draw(title);
		window.draw(laser);
		window.draw(missile);
		window.draw(turret);
		this->printCurrency(window);

		window.display();
	}
}

void Fleet::makeCrew(Ship& ship, RenderWindow& window)
{

	Font font;
	font.loadFromFile("Fonts\\arial.ttf");
	Text title("Choose Lieutenant", font, 25);
	Text command("Command - 5000", font, 25);
	Text attack("Attack - 5000", font, 25);
	Text defence("Defence - 5000", font, 25);
	Text support("Support - 5000", font, 25);

	title.setPosition(50, 50);
	command.setPosition(50, 75);
	attack.setPosition(50, 100);
	defence.setPosition(50, 125);
	support.setPosition(50, 150);

	bool flag = 1;
	int menu_num = 0;

	while (flag)
	{
		title.setFillColor(Color(255, 255, 255, 255));
		command.setFillColor(Color(255, 255, 255, 255));
		attack.setFillColor(Color(255, 255, 255, 255));
		defence.setFillColor(Color(255, 255, 255, 255));
		support.setFillColor(Color(255, 255, 255, 255));
		window.clear(Color(30, 30, 30, 0));

		if (IntRect(50, 75, 150, 25).contains(Mouse::getPosition(window)))
		{
			command.setFillColor(Color::Blue);
			menu_num = 1;
		}
		if (IntRect(50, 100, 150, 25).contains(Mouse::getPosition(window)))
		{
			attack.setFillColor(Color::Blue);
			menu_num = 2;
		}
		if (IntRect(50, 125, 150, 25).contains(Mouse::getPosition(window)))
		{
			defence.setFillColor(Color::Blue);
			menu_num = 3;
		}
		if (IntRect(50, 150, 150, 25).contains(Mouse::getPosition(window)))
		{
			support.setFillColor(Color::Blue);
			menu_num = 4;
		}

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			switch (menu_num)
			{
			case 1:
			{
				shared_ptr<commandLieutenant> commandL = std::make_shared<commandLieutenant>();
				if (this->money < commandL->getPrice())
				{
					this->insufficientMoney(window);
					commandL.~shared_ptr();
					break;
				}
				else
				{
					this->money -= commandL->getPrice();
					ship.setCrew(commandL);
					flag = 0;
					sleep(Time(milliseconds(menuDelay())));
					break;
				}
			}
			case 2:
			{
				shared_ptr<attackLieutenant> attackL = std::make_shared<attackLieutenant>();
				if (this->money < attackL->getPrice())
				{
					this->insufficientMoney(window);
					attackL.~shared_ptr();
					break;
				}
				else
				{
					this->money -= attackL->getPrice();
					ship.setCrew(attackL);
					flag = 0;
					sleep(Time(milliseconds(menuDelay())));
					break;
				}
			}
			case 3:
			{
				shared_ptr<defenceLieutenant> defenceL = std::make_shared<defenceLieutenant>();
				if (this->money < defenceL->getPrice())
				{
					this->insufficientMoney(window);
					defenceL.~shared_ptr();
					break;
				}
				else
				{
					this->money -= defenceL->getPrice();
					ship.setCrew(defenceL);
					flag = 0;
					sleep(Time(milliseconds(menuDelay())));
					break;
				}
			}
			case 4:
			{
				shared_ptr<supportLieutenant> supportL = std::make_shared<supportLieutenant>();
				if (this->money < supportL->getPrice())
				{
					this->insufficientMoney(window);
					supportL.~shared_ptr();
					break;
				}
				else
				{
					this->money -= supportL->getPrice();
					ship.setCrew(supportL);
					flag = 0;
					sleep(Time(milliseconds(menuDelay())));
					break;
				}
			}
			}
		}

		window.draw(title);
		window.draw(command);
		window.draw(attack);
		window.draw(defence);
		window.draw(support);
		this->printCurrency(window);

		window.display();
	}
}

int* table()
{
	int* table(new int[10]{ 20,40,80,160,320,640,1280,2560,5210,10420 });
	return table;
}

int menuDelay()
{
	return 200;
}

bool findDef(Ship& ship)
{
	return ship.getType() == 3;
}

bool findDead(Ship& ship)
{
	return ship.getType() == 0;
}

bool findLowAmmo(Ship& ship)
{
	return ship.getStorage() < ship.getMaxStorage();
}

bool findLowHP(Ship& ship)
{
	return ship.getHP() < ship.getMaxHP();
}

void load(Fleet& fleet)
{
	ifstream read("C:\\Users\\Admin\\Desktop\\save.txt");
	std::string temp_str;
	if (read.is_open())
	{
		//temp integer
		unsigned int temp = 0;
		//ship number within a fleet
		int s = 0;
		while (true)
		{
			for (int i = 0; i < 8; i++)
			{
				std::getline(read, temp_str, '\n');
				if (temp_str.substr(0,5) == "Money")
				{
					break;
				}
				temp_str = temp_str.substr(temp_str.find(":")+1);
				switch (i)
				{
				case 0:
				{
					int k = std::stoi(temp_str);
					switch (k)
					{
					case 1:
					{
						commandShip command;
						fleet.push_back(command);
						break;
					}
					case 2:
					{
						attackShip attack;
						fleet.push_back(attack);
						break;
					}
					case 3:
					{
						defenceShip defence;
						fleet.push_back(defence);
						break;
					}
					case 4:
					{
						supportShip support;
						fleet.push_back(support);
						break;
					}
					default:
					{
						supportShip dead;
						dead.setType(0);
						fleet.push_back(dead);
						break;
					}
					}
					break;
				}
				case 1:
					temp = std::stoul(temp_str);
					fleet[s].paint(temp);
					break;
				case 2:
					temp = std::stoi(temp_str);
					fleet[s].setHP(temp);
					break;
				case 3:
					temp = std::stoi(temp_str);
					fleet[s].setStorage(temp);
					break;
				case 4:
					temp = std::stoi(temp_str);
					fleet[s].setExp(temp);
					break;
				case 5:
					temp = std::stoi(temp_str);
					for (int j = 0; j < temp; j++)
					{
						fleet[s].lvlup();
					}
					break;
				case 6:
					temp = std::stoi(temp_str);
					switch (temp)
					{
					case 1:
					{
						shared_ptr<Laser> laserW = std::make_shared<Laser>();
						fleet[s].setWeapon(laserW);
						break;
					}
					case 2:
					{
						shared_ptr<Missile> missileW = std::make_shared<Missile>();
						fleet[s].setWeapon(missileW);
						break;
					}
					case 3:
					{
						shared_ptr<Turret> turretW = std::make_shared<Turret>();
						fleet[s].setWeapon(turretW);
						break;
					}
					}
					break;
				case 7:
					temp = std::stoi(temp_str);
					switch (temp)
					{
					case 1:
					{
						shared_ptr<commandLieutenant> commandL = std::make_shared<commandLieutenant>();
						fleet[s].setCrew(commandL);
						break;
					}
					case 2:
					{
						shared_ptr<attackLieutenant> attackL = std::make_shared<attackLieutenant>();
						fleet[s].setCrew(attackL);
						break;
					}
					case 3:
					{
						shared_ptr<defenceLieutenant> defenceL = std::make_shared<defenceLieutenant>();
						fleet[s].setCrew(defenceL);
						break;
					}
					case 4:
					{
						shared_ptr<supportLieutenant> supportL = std::make_shared<supportLieutenant>();
						fleet[s].setCrew(supportL);
						break;
					}
					}
					break;
				}
			}
			s++;
			if (temp_str.substr(0, 5) == "Money")
			{
				break;
			}
		}
		
		temp_str = temp_str.substr(temp_str.find(":") + 1);
		temp = std::stoi(temp_str);
		fleet.setMoney(temp);

		std::getline(read, temp_str, '\n');
		temp_str = temp_str.substr(temp_str.find(":") + 1);
		temp = std::stoi(temp_str);
		fleet.setResources(temp);

		read.close();
		fleet.resetPos();
	}
	else
	{
		read.close();
		return;
	}
}


void Fleet::save()
{
	ofstream write;
	write.open("C:\\Users\\Admin\\Desktop\\save.txt");
	if (write.is_open())
	{
		for (Ship& i : *this)
		{
			write << "Type:" << i.getType() << "\n";
			write << "Color:" << i.getFillColor().toInteger() << "\n";
			write << "HP:" << i.getHP() << "\n";
			write << "Storage:" << i.getStorage() << "\n";
			write << "Exp:" << i.getXP() << "\n";
			write << "Lvl:" << i.getLevel() << "\n";
			write << "Weapon:" << i.getWeaponType() << "\n";
			write << "Crew:" << i.getCrewType() << "\n";
		}
		write << "Money:" << this->getMoney() << "\n";
		write << "Res:" << this->getResources() << "\n";
	}
	write.close();
}

void Fleet::battle(Fleet& enemy)
{
	int distance = abs(enemy[0].getPosition().x - enemy[0].getSize().x - this->at(0).getPosition().x + this->at(0).getSize().x);
	int shootRange = enemy[0].getRange() > this->at(0).getRange() ? enemy[0].getRange() : this->at(0).getRange();
	while (distance > shootRange)
	{
		for (int i = 0; i < 5; i++)
		{
			enemy[i].move(Vector2f(-5, 0));
			this->at(i).move(Vector2f(5, 0));
			sleep(Time(milliseconds(menuDelay())));
		}
		distance -= 10;
	}
	srand(time(0));
	int turn = rand() % 2;
	while (this->at(0).getType() == 1 && distance <= shootRange)
	{
		if (turn)
		{
			int size = this->size();
			auto targetI = std::find_if(enemy.begin(), enemy.end(), findDef);
			int target = targetI - enemy.begin();
			for (int i = 0; i < size; i++)
			{
				if (this->at(i).getType() == 4)
				{
					for (size_t j = 0; j < 4; j++)
					{
						if (this->at(j).getStorage() < this->at(j).getMaxStorage() && this->at(j).getType() != 4 && this->at(j).getType() != 0)
						{
							this->at(i).supplyAmmo(this->at(j));
						}
					}
				}
				if (targetI != enemy.end())
				{
					this->at(i).shoot(enemy[target]);
					if (enemy[target].getHP() < 1)
					{
						enemy[target].setDead();
						targetI = std::find_if(enemy.begin(), enemy.end(), findDef);
						target = targetI - enemy.begin();
					}
					sleep(Time(milliseconds(menuDelay() * 2)));
				}
				else
				{
					this->at(i).shoot(enemy[0]);
					if (enemy[0].getHP() < 1)
					{
						enemy[0].setDead();
						this->setResources(enemy.getResources());
						for (Ship& i : *this)
						{
							if (i.getType())
							{
								i.setExp(50);
								i.lvlup(table());
							}
						}
						this->resetPos();
						return;
					}
					sleep(Time(milliseconds(menuDelay() * 2)));
				}
			}
			turn = 0;
		}
		else
		{
			int size = enemy.size();
			auto targetI = std::find_if(this->begin(), this->end(), findDef);
			int target = targetI - this->begin();
			for (int i = 0; i < size; i++)
			{
				if (enemy[i].getType() == 4)
				{
					for (int j = 0; j < 4; j++)
					{
						if (enemy[j].getStorage() < enemy[j].getMaxStorage() && enemy[j].getType() != 4 && enemy[j].getType() != 0)
						{
							enemy[i].supplyAmmo(enemy[j]);
						}
					}
				}
				if (targetI != this->end())
				{
					enemy[i].shoot(this->at(target));
					if (this->at(target).getHP() < 1)
					{
						this->at(target).setDead();
						targetI = std::find_if(this->begin(), this->end(), findDef);
						target = targetI - this->begin();
					}
					sleep(Time(milliseconds(menuDelay() * 2)));
				}
				else
				{
					enemy[i].shoot(this->at(0));
					if (this->at(0).getHP() < 1)
					{
						this->at(0).setDead();
						return;
					}
					sleep(Time(milliseconds(menuDelay() * 2)));
				}
			}
			turn = 1;
		}

	}
}

void Fleet::printFleet(RenderWindow& window)
{
	int y = 5;
	for (Ship& i : *this)
	{
		i.printStats(window, y);
	}
}

void Fleet::printEnemyFleet(RenderWindow& window)
{
	int y = 5;
	for (Ship& i : *this)
	{
		i.printEnemyStats(window, y);
	}
}

int Fleet::getMoney()
{
	return this->money;
}

int Fleet::getResources()
{
	return this->resources;
}

void Fleet::printCurrency(RenderWindow& window)
{
	Font font;
	font.loadFromFile("Fonts\\arial.ttf");
	Text money("Money: " + std::to_string(this->money), font, 22);
	Text resources("Resources: " + std::to_string(this->resources), font, 22);
	money.setPosition(5, 450);
	resources.setPosition(220, 450);
	money.setFillColor(Color(255, 255, 255, 255));
	resources.setFillColor(Color(255, 255, 255, 255));
	window.draw(money);
	window.draw(resources);
}

void Fleet::insufficientMoney(RenderWindow& window)
{
	Font font;
	font.loadFromFile("Fonts\\arial.ttf");
	Text error("Money are insufficient. You have: " + std::to_string(this->money), font, 25);
	error.setPosition(5, 450);
	error.setFillColor(Color(255, 255, 255, 255));
	window.draw(error);
}

void Fleet::replaceShip(RenderWindow& window)
{
	int countDead = std::count_if(this->begin(), this->end(), findDead);
	if (countDead)
	{
		for (size_t i = 0; i < countDead; i++)
		{
			auto pos = std::find_if(this->begin(), this->end(), findDead);
			this->erase(pos);
			this->makeShip(window);
		}
		this->resetPos();
	}
	int size = this->size();
	if (size < 5 && !this->empty())
	{
		while (size != 5)
		{
			this->makeShip(window);
			size++;
		}
		this->resetPos();
	}
	sleep(milliseconds(menuDelay()));
}

void Fleet::refillAmmo()
{
	int ammoRefill = std::count_if(this->begin(), this->end(), findLowAmmo);
	if (ammoRefill)
	{
		for (size_t i = 0; i < ammoRefill; i++)
		{
			auto posIt = std::find_if(this->begin(), this->end(), findLowAmmo);
			int pos = posIt - this->begin();
			this->at(pos).setStorage(this->at(pos).getMaxStorage());
			this->setMoney(-(2500));
		}
	}
	sleep(milliseconds(menuDelay()));
}

void Fleet::repairShips()
{
	int repairCount = std::count_if(this->begin(), this->end(), findLowAmmo);
	if (repairCount)
	{
		for (size_t i = 0; i < repairCount; i++)
		{
			auto posIt = std::find_if(this->begin(), this->end(), findLowHP);
			int pos = posIt - this->begin();
			this->at(pos).setHP(this->at(pos).getMaxHP());
			this->setMoney(-(5000));
		}
	}
	sleep(milliseconds(menuDelay()));
}

void Fleet::sellResources()
{
	if (this->resources > 0)
	{
		this->money += this->resources * 2000;
	}
	this->resources = 0;
	sleep(milliseconds(menuDelay()));
}

void Fleet::resetPos()
{
	this->at(0).setPosition(100, 220);
	int x = 100 + this->at(0).getSize().x + 10;
	int y = 160;
	int size = this->size();
	for (size_t i = 1; i < size; i++)
	{
		this->at(i).setPosition(x, y);
		y = this->at(i).getPosition().y + this->at(i).getSize().y + 10;
	}
}
