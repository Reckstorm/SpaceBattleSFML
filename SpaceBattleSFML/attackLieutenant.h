#pragma once
#include "Crew.h"

namespace ProtoCrew
{
	namespace Lieutenants
	{
		class attackLieutenant final :
			public Crew
		{
		public:
			attackLieutenant() : Crew(5000, 2) {};
		};
	}
}
