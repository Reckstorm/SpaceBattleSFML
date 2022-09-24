#pragma once
#include "Crew.h"

namespace ProtoCrew
{
	namespace Lieutenants
	{
		class defenceLieutenant final :
			public Crew
		{
		public:
			defenceLieutenant() : Crew(5000, 3) {};
		};
	}
}
