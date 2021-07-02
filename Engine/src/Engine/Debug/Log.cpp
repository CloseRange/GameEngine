#include "enpch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Engine {

	std::shared_ptr<spdlog::logger> Log::coreLogger;

	void Log::Init() {
		spdlog::set_pattern("%^%v%$");
		coreLogger = spdlog::stdout_color_mt("Console");
		coreLogger->set_level(spdlog::level::trace);
	}
}
