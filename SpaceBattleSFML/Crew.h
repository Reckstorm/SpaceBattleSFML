#pragma once

namespace ProtoCrew
{
	class Crew
	{
	protected:
		int type;
		int damage;
		int price;
	public:
		Crew(int price, int type = 0);
		int getDamage();
		int getType();
		int getPrice();
	};
}

