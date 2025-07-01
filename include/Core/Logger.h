#pragma once
/**
 * @file Core/Logger.h
 * @author Noah G. Wood (@NoahGWood)
 * @brief Logging utilies and macros using spdlog.
 * @note Use CORE_ macros for internal logs only, make life easier
 * @version 0.1
 * @date 2025-07-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "Core/Base.h"
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)


class Logger {
    public:
        static void Init();
        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger()  { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger()  { return s_ClientLogger; }

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
};
// Core logging macros (internal engine logs)
#define CORE_TRACE(...) Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define CORE_INFO(...) Logger::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_WARN(...) Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_ERROR(...) Logger::GetCoreLogger()->error(__VA_ARGS__)
#define CORE_CRITICAL(...) Logger::GetCoreLogger()->critical(__VA_ARGS__)
// Client logging macros (user logs)
#define TRACE(...) Logger::GetClientLogger()->trace(__VA_ARGS__)
#define INFO(...) Logger::GetClientLogger()->info(__VA_ARGS__)
#define WARN(...) Logger::GetClientLogger()->warn(__VA_ARGS__)
#define ERROR(...) Logger::GetClientLogger()->error(__VA_ARGS__)
#define CRITICAL(...) Logger::GetClientLogger()->critical(__VA_ARGS__)
