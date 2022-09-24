#include "Weapon.h"

ProtoWeapon::Weapon::Weapon(int range, int damage, int price, int type)
{
    this->type = type;
    this->range = range;
    this->damage = damage;
    this->price = price;
}

int ProtoWeapon::Weapon::getDamage()
{
    if (this == nullptr)
    {
        return 0;
    }
    return this->damage;
}

int ProtoWeapon::Weapon::getRange()
{
    if (this == nullptr)
    {
        return 0;
    }
    return this->range;
}

int ProtoWeapon::Weapon::getPrice()
{
    return this->price;
}

int ProtoWeapon::Weapon::getType()
{
    return this->type;
}

void ProtoWeapon::Weapon::setZero()
{
    this->damage = 0;
}
