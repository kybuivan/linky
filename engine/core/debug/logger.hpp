// Copyright (c) 2023-2024 Ky Bui Van
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once
#include <exception>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace linky::debug {

template<typename ...Args>
inline std::string serialize(Args &&...args) noexcept {
    std::ostringstream ss;
    static_cast<void>((ss << ... << std::forward<Args>(args)));
    return ss.str();
}

spdlog::logger &logger() noexcept;

inline void set_log_level(spdlog::level::level_enum lvl) noexcept {
    logger().set_level(lvl);
}

template<typename... Args>
inline void debug(Args &&... args) noexcept {
    logger().debug(serialize(std::forward<Args>(args)...));
}

template<typename... Args>
inline void info(Args &&... args) noexcept {
    logger().info(serialize(std::forward<Args>(args)...));
}

template<typename... Args>
inline void warning(Args &&... args) noexcept {
    logger().warn(serialize(std::forward<Args>(args)...));
}

template<typename... Args>
inline void warning_if(bool predicate, Args &&... args) noexcept {
    if (predicate) { warning(std::forward<Args>(args)...); }
}

template<typename... Args>
inline void warning_if_not(bool predicate, Args &&... args) noexcept {
    warning_if(!predicate, std::forward<Args>(args)...);
}

template<typename... Args>
[[noreturn]] inline void exception(Args &&... args) {
    throw std::runtime_error{ serialize(std::forward<Args>(args)...) };
}

template<typename... Args>
inline void exception_if(bool predicate, Args &&... args) {
    if (predicate) { exception(std::forward<Args>(args)...); }
}

template<typename... Args>
inline void exception_if_not(bool predicate, Args &&... args) {
    exception_if(!predicate, std::forward<Args>(args)...);
}

template<typename... Args>
[[noreturn]] inline void error(Args &&... args) {
    logger().error(serialize(std::forward<Args>(args)...));
    exit(-1);
}

template<typename... Args>
inline void error_if(bool predicate, Args &&... args) {
    if (predicate) { error(std::forward<Args>(args)...); }
}

template<typename... Args>
inline void error_if_not(bool predicate, Args &&... args) {
    error_if(!predicate, std::forward<Args>(args)...);
}

}

#define LINKY_SOURCE_LOCATION __FILE__ , ":", __LINE__

#define LINKY_DEBUG(...) \
    ::linky::debug::debug(__VA_ARGS__);

#define LINKY_SET_LOG_LEVEL(lv) \
    ::linky::debug::set_log_level(spdlog::level::level_enum::lv);

#define LINKY_INFO(...) \
    ::linky::debug::info(__VA_ARGS__);

#define LINKY_WARNING(...) \
    ::linky::debug::warning(__VA_ARGS__, "\n    Source: ", LINKY_SOURCE_LOCATION);
#define LINKY_WARNING_IF(...) \
    ::linky::debug::warning_if(__VA_ARGS__, "\n    Source: ", LINKY_SOURCE_LOCATION);
#define LINKY_WARNING_IF_NOT(...) \
    ::linky::debug::warning_if_not(__VA_ARGS__, "\n    Source: ", LINKY_SOURCE_LOCATION);

#define LINKY_EXCEPTION(...) \
    ::linky::debug::exception(__VA_ARGS__, "\n    Source: ", LINKY_SOURCE_LOCATION);
#define LINKY_EXCEPTION_IF(...) \
    ::linky::debug::exception_if(__VA_ARGS__, "\n    Source: ", LINKY_SOURCE_LOCATION);
#define LINKY_EXCEPTION_IF_NOT(...) \
    ::linky::debug::exception_if_not(__VA_ARGS__, "\n    Source: ", LINKY_SOURCE_LOCATION);

#define LINKY_ERROR(...) \
    ::linky::debug::error(__VA_ARGS__, "\n    Source: ", LINKY_SOURCE_LOCATION);
#define LINKY_ERROR_IF(...) \
    ::linky::debug::error_if(__VA_ARGS__, "\n    Source: ", LINKY_SOURCE_LOCATION);
#define LINKY_ERROR_IF_NOT(...) \
    ::linky::debug::error_if_not(__VA_ARGS__, "\n    Source: ", LINKY_SOURCE_LOCATION);