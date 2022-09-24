#pragma once
#include "Crew.h"

namespace ProtoCrew
{
	namespace Lieutenants
	{
		class supportLieutenant final :
			public Crew
		{
		public:
			supportLieutenant() : Crew(5000, 4) {};
		};
	}
}