#include "axpch.h"
#include "Log.h"
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
namespace Auxilium {
	std::shared_ptr<spdlog::logger> Logger::mlogger;

	void Logger::Initialize() {
		if (mlogger != nullptr) {
			LOG_DEBUG("Log already Initialized");
		}
		std::vector<spdlog::sink_ptr> logSinks;

		logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("Auxilium.log", true));

		spdlog::set_pattern("%^[%T] %n: %v%$");

		mlogger = std::make_shared<spdlog::logger>("AUXILIUM", begin(logSinks), end(logSinks));

		spdlog::register_logger(mlogger);

		Logger::mlogger = spdlog::stdout_color_mt("AXLM");
		Logger::mlogger->set_level(spdlog::level::trace);
		Logger::mlogger->flush_on(spdlog::level::trace);
		LOG_INFO("Logger Initialized");
	}
}