#include <stdio.h>
#include "Log.h"
namespace HiyazUtils {

	Log::Logger::Logger() {

	}
	Log::LogPriority Log::Logger::CurrentPriority = Info;
	void Log::Logger::SetPriority(Log::LogPriority _priority) {
		CurrentPriority = _priority;
	}
};