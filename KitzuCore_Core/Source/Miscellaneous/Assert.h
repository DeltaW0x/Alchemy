//
// Created by lucac on 03/06/2024.
//

#ifndef ASSERT_H
#define ASSERT_H
#include <spdlog/spdlog.h>

#ifdef _WIN32
#define DBG_BREAK() __debugbreak()
#elif __linux__
#include <signal.h>
#define DBG_BREAK() raise(SIGTRAP)
#endif

#define ASSERT(x,message,...) if(!(x)){spdlog::critical(message,__VA_ARGS__); DBG_BREAK();}

#ifdef _DEBUG
#define INFO(message,...) spdlog::info(message,__VA_ARGS__)
#else
#define INFO(message,...)
#endif
#endif //ASSERT_H
