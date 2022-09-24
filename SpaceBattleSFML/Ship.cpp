#include "Ship.h"

ProtoShip::Ship::Ship(int armor, int type, int width, int height, std::string typeName, int hp, int price)
{
	this->setSize(sf::Vector2f(width, height));
	this->type = type;
	this->typeName = typeName;
	this->maxHP = hp;
	this->hp = hp;
	this->damage = 0;
	this->maxStorage = 15;
	this->armor = armor;
	this->storage = 15;
	this->experience = 0;
	this->level = 1;
	this->price = price;
}

void ProtoShip::Ship::shoot(Ship& ship)
{
	this->storage--;
	ship.setHP(-(this->weapon->getDamage() + this->damage) - ship.getArmor());
}

void ProtoShip::Ship::setHP(int i)
{
	this->hp += i;
}

void ProtoShip::Ship::setWeapon(const shared_ptr<Weapon>& weapon)
{
	this->weapon = weapon;
	this->damage += this->weapon->getDamage();
}

void ProtoShip::Ship::setCrew(const shared_ptr<Crew>& crew)
{
	this->crew = crew;
	checkType();
}

void ProtoShip::Ship::setExp(int i)
{
	this->experience += i;
}

void ProtoShip::Ship::setStorage(int i)
{
	this->storage += i;
}

void ProtoShip::Ship::setTypeName(std::string name)
{
	this->typeName = name;
}

void ProtoShip::Ship::setType(int i)
{
	this->type = i;
}

void ProtoShip::Ship::lvlup(int* table)
{
	for (size_t i = this->level; i < 10; i++)
	{
		if (this->experience >= table[i])
		{
			this->level++;
			this->maxHP += 20;
			this->hp = this->maxHP;
			this->armor += 2;
			this->maxStorage += 2;
			this->storage = this->maxStorage;
			this->damage += 2;
			this->color.r += 10;
		}
		else return;
	}
}

void ProtoShip::Ship::lvlup()
{
	this->level++;
	this->maxHP += 20;
	this->hp = this->maxHP;
	this->armor += 2;
	this->maxStorage += 2;
	this->storage = this->maxStorage;
	this->damage += 2;
	this->color.r += 10;
}

int ProtoShip::Ship::getRange() const
{
	return this->weapon->getRange();
}

int ProtoShip::Ship::getMaxHP() const
{
	return this->maxHP;
}

int ProtoShip::Ship::getHP() const
{
	return this->hp;
}

int ProtoShip::Ship::getXP() const
{
	return this->experience;
}

int ProtoShip::Ship::getLevel() const
{
	return this->level;
}

int ProtoShip::Ship::getArmor() const
{
	return this->armor;
}

int ProtoShip::Ship::getDamage() const
{
	return this->damage;
}

int ProtoShip::Ship::getMaxStorage() const
{
	return this->maxStorage;
}

int ProtoShip::Ship::getStorage() const
{
	return this->storage;
}

int ProtoShip::Ship::getType() const
{
	return this->type;
}

int ProtoShip::Ship::getPrice() const
{
	return this->price;
}

int ProtoShip::Ship::getWeaponType() const
{
	return this->weapon->getType();
}

int ProtoShip::Ship::getCrewType() const
{
	return this->crew->getType();
}

std::string ProtoShip::Ship::getTypeName() const
{
	return this->typeName;
}

void ProtoShip::Ship::printStats(RenderWindow& window, int& y)
{
	Font font;
	font.loadFromFile("Fonts\\arial.ttf");

	std::string typeS("Type: " + this->getTypeName());
	std::string hpS("HP: " + std::to_string(this->getHP()));
	std::string dmgS("Damage: " + std::to_string(this->getDamage()));
	std::string stgS("Ammo: " + std::to_string(this->getStorage()));

	Text type(typeS, font, 12);
	Text hp(hpS, font, 12);
	Text dmg(dmgS, font, 12);
	Text stg(stgS, font, 12);

	type.setPosition(5, y); y += 15;
	hp.setPosition(5, y); y += 15;
	dmg.setPosition(5, y); y += 15;
	stg.setPosition(5, y); y += 30;

	type.setFillColor(Color(255, 255, 255, 255));
	hp.setFillColor(Color(255, 255, 255, 255));
	dmg.setFillColor(Color(255, 255, 255, 255));
	stg.setFillColor(Color(255, 255, 255, 255));

	window.draw(type);
	window.draw(hp);
	window.draw(dmg);
	window.draw(stg);

}

void ProtoShip::Ship::printEnemyStats(RenderWindow& window, int& y)
{
	Font font;
	font.loadFromFile("Fonts\\arial.ttf");

	std::string typeS("Type: " + this->typeName);
	std::string hpS("HP: " + std::to_string(this->hp));
	std::string dmgS("Damage: " + std::to_string(this->damage));
	std::string stgS("Ammo: " + std::to_string(this->storage));

	Text type(typeS, font, 12);
	Text hp(hpS, font, 12);
	Text dmg(dmgS, font, 12);
	Text stg(stgS, font, 12);

	type.setPosition(545, y); y += 15;
	hp.setPosition(545, y); y += 15;
	dmg.setPosition(545, y); y += 15;
	stg.setPosition(545, y); y += 30;

	type.setFillColor(Color(255, 255, 255, 255));
	hp.setFillColor(Color(255, 255, 255, 255));
	dmg.setFillColor(Color(255, 255, 255, 255));
	stg.setFillColor(Color(255, 255, 255, 255));

	window.draw(type);
	window.draw(hp);
	window.draw(dmg);
	window.draw(stg);
}

void ProtoShip::Ship::setDead()
{
	this->setType();
	this->setTypeName();
	this->setSize(sf::Vector2f(0, 0));
	this->damage = 0;
	this->weapon->setZero();
}

void ProtoShip::Ship::supplyAmmo(Ship& ship)
{
	if (this->storage > 0)
	{
		this->storage--;
		ship.setStorage(1);
	}
	else return;
}

void ProtoShip::Ship::checkType()
{
	if (this->crew->getType() == this->type)
	{
		this->damage += this->crew->getDamage();
	}
}

void ProtoShip::Ship::paint(int r, int g, int b, int o)
{
	this->color = Color(r, g, b, o);
	this->setFillColor(color);
	this->setOutlineThickness(1);
	this->setOutlineColor(Color::Black);
}

void ProtoShip::Ship::paint(int i)
{
	this->color = Color(i);
	this->setFillColor(color);
	this->setOutlineThickness(1);
	this->setOutlineColor(Color::Black);
}
