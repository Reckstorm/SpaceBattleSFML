#pragma once
#include "Ship.h"

namespace ProtoShip
{
    namespace Ships
    {
		class supportShip final :
			public Ship
		{
		public:
			supportShip() : Ship(2, 4, 20, 20, "support", 200, 20000) {};
		};
    }
}
