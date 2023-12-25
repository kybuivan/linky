#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/stdout_color_sinks.h"

// Client Logging Macros
#define TRACE(...)    spdlog::trace(__VA_ARGS__)
#define INFO(...)     spdlog::info(__VA_ARGS__)
#define WARN(...)     spdlog::warn(__VA_ARGS__)
#define ERROR(...)    spdlog::error(__VA_ARGS__)
#define CRITICAL(...) spdlog::critical(__VA_ARGS__)