#pragma once
#include "Crew.h"

namespace ProtoCrew
{
	namespace Lieutenants
	{
		class commandLieutenant final :
			public Crew
		{
		public:
			commandLieutenant() : Crew(5000, 1) {};
		};
	}
}
