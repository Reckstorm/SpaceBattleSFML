#pragma once
#include "Weapon.h"

namespace ProtoWeapon
{
	namespace Weapons
	{
		class Missile final :
			public Weapon
		{
		public:
			Missile() : Weapon(240, 25, 5000, 2) {};
		};
	}
}

