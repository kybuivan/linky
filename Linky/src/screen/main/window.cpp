#include "screen/main/window.hpp"
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace linky
{

Window::Window() noexcept
{
}

Window::~Window() noexcept {
    glfwMakeContextCurrent(handle);
    //_texture.reset();
    //ImNodes::DestroyContext();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(handle);
}

int Window::width() const noexcept {
    auto width = 0;
    auto height = 0;
    glfwGetWindowSize(handle, &width, &height);
    return static_cast<int>(width);
}

int Window::height() const noexcept {
    auto width = 0;
    auto height = 0;
    glfwGetWindowSize(handle, &width, &height);
    return static_cast<int>(height);
}

bool Window::should_close() const noexcept {
    return glfwWindowShouldClose(handle);
}

Window &Window::set_mouse_callback(Window::MouseButtonCallback cb) noexcept {
    mouse_button_callback = std::move(cb);
    return *this;
}

Window &Window::set_cursor_position_callback(Window::CursorPositionCallback cb) noexcept {
    cursor_position_callback = std::move(cb);
    return *this;
}

Window &Window::set_window_size_callback(Window::WindowSizeCallback cb) noexcept {
    window_size_callback = std::move(cb);
    return *this;
}

Window &Window::set_key_callback(Window::KeyCallback cb) noexcept {
    key_callback = std::move(cb);
    return *this;
}

Window &Window::set_scroll_callback(Window::ScrollCallback cb) noexcept {
    scroll_callback = std::move(cb);
    return *this;
}

void Window::set_background(const std::array<uint8_t, 4u> *pixels, int width, int height, bool bilerp) noexcept {
    // if (_texture == nullptr) { _texture = luisa::make_unique<GLTexture>(); }
    // _texture->load(pixels, size, bilerp);
}

void Window::set_should_close() noexcept {
    glfwSetWindowShouldClose(handle, true);
}

void Window::_imgui_dock() noexcept {
    static bool dockspaceOpen = true;
    static bool opt_fullscreen_persistant = true;
    bool opt_fullscreen = opt_fullscreen_persistant;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.1f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
    ImGui::PopStyleVar();
    if (opt_fullscreen) {
        ImGui::PopStyleVar(2);
    }
    // DockSpace
    ImGuiIO& io = ImGui::GetIO();
    ImGuiStyle& style = ImGui::GetStyle();
    float minWinSizeX = style.WindowMinSize.x;
    style.WindowMinSize.x = 370.0f;
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }
    style.WindowMinSize.x = minWinSizeX;
    ImGui::End();
}

void Window::_begin_frame() noexcept {
    if (!should_close()) {
        glfwMakeContextCurrent(handle);
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        //_imgui_dock();
    }
}

void Window::_end_frame() noexcept {
    if (!should_close()) {
        // background
        // if (_texture != nullptr) {
        //     auto s = make_float2(size());
        //     auto t = make_float2(_texture->size());
        //     // aspect fit
        //     auto scale = std::min(s.x / t.x, s.y / t.y);
        //     auto tl = (s - t * scale) * 0.5f;
        //     auto br = tl + t * scale;
        //     ImGui::GetBackgroundDrawList()->AddImage(
        //         _texture->handle(), {tl.x, tl.y}, {br.x, br.y});
        // }

        // rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(handle, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(.15f, .15f, .15f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}

        glfwSwapBuffers(handle);
    }
}

void Window::set_size(int _width, int _height) noexcept {
    if (resizable) {
        glfwSetWindowSize(handle, static_cast<int>(_width), static_cast<int>(_height));
    } else {
        //logger("Ignoring resize on non-resizable window.");
    }
}
}