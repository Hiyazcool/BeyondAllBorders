#pragma once
#include "CatalystAPI.h"
namespace Auxilium {
	struct CATALYST_API  EventParams {
		bool IsHandled;
		EventParams() :
			IsHandled(false)
		{

		}
	};
}
