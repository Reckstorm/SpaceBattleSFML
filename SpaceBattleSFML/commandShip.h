#pragma once
#include "Ship.h"

namespace ProtoShip
{
	namespace Ships
	{
		class commandShip final :
			public Ship
		{
		public:
			commandShip() : Ship(3, 1, 40, 40, "command", 200, 30000) {};
		};
	}
}
