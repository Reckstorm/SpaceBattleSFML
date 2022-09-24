#pragma once
#include "Ship.h"

namespace ProtoShip
{
    namespace Ships
    {
		class attackShip final :
			public Ship
		{
		public:
			attackShip() : Ship(1, 2, 25, 25, "attack", 200, 25000) {};
		};
    }
}