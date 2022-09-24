#pragma once
#include "Weapon.h"

namespace ProtoWeapon 
{
	namespace Weapons
	{
		class Laser final :
			public Weapon
		{
		public:
			Laser() : Weapon(300, 15, 5000, 1) {};
		};
	}
}



