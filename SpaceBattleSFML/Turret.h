#pragma once
#include "Weapon.h"

namespace ProtoWeapon
{
	namespace Weapons
	{

		class Turret final :
			public Weapon
		{
		public:
			Turret() : Weapon(200, 7, 5000, 3) {};
		};
	}
}
