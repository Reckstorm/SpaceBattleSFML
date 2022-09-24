#pragma once
#include "Ship.h"

namespace ProtoShip
{
    namespace Ships
    {
		class defenceShip final :
			public Ship
		{
		public:
			defenceShip() : Ship(5, 3, 35, 35, "defence", 200, 25000) {};
		};
    }
}
