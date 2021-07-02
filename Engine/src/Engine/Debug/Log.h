#pragma once
#include "Engine/Core.h"
#include "spdlog/spdlog.h"

namespace Engine {
	class Log {
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return coreLogger; };
	private:
		static std::shared_ptr<spdlog::logger> coreLogger;
	};
}

#ifndef LOGGING
#	define LOG_INFO(...)        
#	define LOG_WARN(...)        
#	define LOG_ERROR(...)     
#	define LOG_CRITICAL(...)
#else
#	define LOG_INFO(...)            ::Engine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#	define LOG_WARN(...)            ::Engine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#	define LOG_ERROR(...)           ::Engine::Log::GetCoreLogger()->error(__VA_ARGS__)
#	define LOG_CRITICAL(...)        ::Engine::Log::GetCoreLogger()->critical(__VA_ARGS__)
#endif	

#ifdef ENGINE_ENABLE_FATAL
#	ifdef ENGINE_PLATFORM_WINDOWS
#		define LOG_FATAL(x, ...)    { if(!(x)) { LOG_ERROR(__VA_ARGS__); __debugbreak(); } }
#		define ASSERT(x)			{ if(!(x)) { __debugbreak(); }}
#	else
#		define LOG_FATAL(x, ...)    { if(!(x)) { LOG_ERROR(__VA_ARGS__); } }
#		define ASSERT(x)			x
#	endif
#else
#	define LOG_FATAL(x, ...)        { if(!(x)) { LOG_ERROR(__VA_ARGS__); } }
#	define ASSERT(x)			    x
#endif
