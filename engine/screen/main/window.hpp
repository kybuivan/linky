#pragma once
#include <functional>
#include <array>
#include <core/math/math.hpp>
#include <core/string/string.hpp>

struct GLFWwindow;

namespace linky
{
class Window
{
public:
    using MouseButtonCallback = std::function<void(int /* button */, int /* action */, float /* x */, float /* y */)>;
    using CursorPositionCallback = std::function<void(int /* x*/, int /* y */)>;
    using WindowSizeCallback = std::function<void(int /* width*/, int /* height */)>;
    using KeyCallback = std::function<void(int /* key */, int /* action */)>;
    using ScrollCallback = std::function<void(int /* dx */, int /* dy */)>;
public:
    Window() noexcept;
    ~Window() noexcept;

    [[nodiscard]] int width() const noexcept;
    [[nodiscard]] int height() const noexcept;
    [[nodiscard]] bool should_close() const noexcept;
    [[nodiscard]] auto get_handle() const noexcept { return m_handle; }
    [[nodiscard]] explicit operator bool() const noexcept { return !should_close(); }

    Window &set_mouse_callback(MouseButtonCallback cb) noexcept;
    Window &set_cursor_position_callback(CursorPositionCallback cb) noexcept;
    Window &set_window_size_callback(WindowSizeCallback cb) noexcept;
    Window &set_key_callback(KeyCallback cb) noexcept;
    Window &set_scroll_callback(ScrollCallback cb) noexcept;

    void set_background(const std::array<uint8_t, 4u> *pixels, int width, int height, bool bilerp = true) noexcept;

    void set_should_close() noexcept;
    void set_size(int _width, int _height) noexcept;
private:
    void _begin_frame() noexcept;
    void _end_frame() noexcept;
    void _imgui_dock() noexcept;

private:
    std::string m_title;
    core::point m_position;
    core::size m_size;
    bool m_resizable;
    GLFWwindow* m_handle;

    MouseButtonCallback m_mouse_button_callback;
    CursorPositionCallback m_cursor_position_callback;
    WindowSizeCallback m_window_size_callback;
    KeyCallback m_key_callback;
    ScrollCallback m_scroll_callback;
};
}