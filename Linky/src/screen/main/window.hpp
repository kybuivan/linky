#pragma once
#include <functional>
#include <string>
#include <array>
#include <core/math/math.hpp>

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
    [[nodiscard]] auto get_handle() const noexcept { return handle; }
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
    std::string title;
    Vec2f position;
    Vec2f size;
    bool resizable;
    GLFWwindow* handle;

    MouseButtonCallback mouse_button_callback;
    CursorPositionCallback cursor_position_callback;
    WindowSizeCallback window_size_callback;
    KeyCallback key_callback;
    ScrollCallback scroll_callback;
};
}