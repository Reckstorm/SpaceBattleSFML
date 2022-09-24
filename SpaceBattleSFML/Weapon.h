#pragma once

namespace ProtoWeapon
{
	class Weapon
	{
	protected:
		int range;
		int damage;
		int price;
		int type;
	public:
		Weapon(int, int, int, int);
		int getDamage();
		int getRange();
		int getPrice();
		int getType();
		void setZero();
	};
}

