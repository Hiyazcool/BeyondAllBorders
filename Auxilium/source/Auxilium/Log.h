#pragma once
#include "Define.h"
#include <spdlog/spdlog.h>
#include "axpch.h"
// I know not all includes are necessary
namespace Auxilium {
	class Logger {
	public:
		static void Initialize();
		static std::shared_ptr<spdlog::logger>& GetLogger() { return mlogger; }
	private:
		static std::shared_ptr<spdlog::logger> mlogger;	
	};

}
#define LOG_INFO(...)  ::Auxilium::Logger::GetLogger()->info(__VA_ARGS__)
#define LOG_TRACE(...)  ::Auxilium::Logger::GetLogger()->trace(__VA_ARGS__)
#define LOG_WARN(...)  ::Auxilium::Logger::GetLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) ::Auxilium::Logger::GetLogger()->error(__VA_ARGS__)
#define LOG_CRIT(...)  ::Auxilium::Logger::GetLogger()->critical(__VA_ARGS__)
#define LOG_DEBUG(...)  ::Auxilium::Logger::GetLogger()->debug(__VA_ARGS__)

