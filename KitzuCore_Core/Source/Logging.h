//
// Created by lucac on 08/06/2024.
//

#ifndef LOGGING_H
#define LOGGING_H
#include <spdlog/spdlog.h>

#ifdef _WIN32
#define DBG_BREAK() __debugbreak()
#else
#include <csignal>
#define DBG_BREAK() raise(SIGTRAP)
#endif

#ifdef NDEBUG
#define LOG_INFO(message,...)
#else
#define LOG_INFO(message,...) spdlog::info(message,##__VA_ARGS__)
#endif

#define LOG_WARN(message,...) spdlog::warn(message,##__VA_ARGS__)
#define LOG_ERROR(message,...) spdlog::error(message,##__VA_ARGS__)
#define LOG_CRITICAL(message,...) spdlog::critical(message,##__VA_ARGS__)
#define ASSERT(cond,message,...) if(!(cond)) {spdlog::critical(message,##__VA_ARGS__); DBG_BREAK();}
#endif //LOGGING_H
