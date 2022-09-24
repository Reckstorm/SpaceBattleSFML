#include "Crew.h"

ProtoCrew::Crew::Crew(int price, int type)
{
	this->damage = 5;
	this->type = type;
	this->price = price;
}

int ProtoCrew::Crew::getDamage()
{
	return this->damage;
}

int ProtoCrew::Crew::getType()
{
	return this->type;
}

int ProtoCrew::Crew::getPrice()
{
	return this->price;
}
