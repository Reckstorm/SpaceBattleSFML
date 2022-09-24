#pragma once
#include "Weapon.h"
#include "Crew.h"
#include <vector>
#include <iostream>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace ProtoWeapon;
using namespace ProtoCrew;
using std::vector;
using std::cout;
using std::cin;
using std::shared_ptr;

namespace ProtoShip
{
	class Ship : public RectangleShape
	{
	protected:
		Color color;
		std::string typeName;
		int type;
		int maxHP;
		int hp;
		int damage;
		int armor;
		int maxStorage;
		int storage;
		int experience;
		int level;
		int price;
		shared_ptr<Weapon> weapon;
		shared_ptr<Crew> crew;
	public:
		Ship(int armor = 0, int type = 0, int width = 25, int height = 25, std::string typeName = "", int hp = 200, int price = 0);
		void shoot(Ship& ship);
		void setHP(int i);
		void setWeapon(const shared_ptr<Weapon>& weapon);
		void setCrew(const shared_ptr<Crew>& crew);
		void setExp(int i);
		void setStorage(int i);
		void setTypeName(std::string name = "dead");
		void setType(int i = 0);
		void lvlup(int* table);
		void lvlup();
		int getRange() const;
		int getMaxHP() const;
		int getHP() const;
		int getXP() const;
		int getLevel() const;
		int getArmor() const;
		int getDamage() const;
		int getMaxStorage() const;
		int getStorage() const;
		int getType() const;
		int getPrice() const;
		int getWeaponType() const;
		int getCrewType() const;
		std::string getTypeName() const;
		void checkType();
		void paint(int r, int g, int b, int o);
		void paint(int i);
		void printStats(RenderWindow& window, int &y);
		void printEnemyStats(RenderWindow& window, int& y);
		void setDead();
		void supplyAmmo(Ship& ship);
		~Ship() = default;
	};
}