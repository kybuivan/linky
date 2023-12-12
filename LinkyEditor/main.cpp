#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <screen/graphics/camera.hpp>
#include <screen/graphics/shader.hpp>
#include <screen/graphics/model.hpp>
#include <core/core.hpp>
#include <GLFW/glfw3.h> // Will drag system OpenGL headers
#include <iostream>

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

// This example can also compile and run with Emscripten! See 'Makefile.emscripten' for details.
#ifdef __EMSCRIPTEN__
#include "../libs/emscripten/emscripten_mainloop_stub.h"
#endif

using namespace Linky;

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 700;

// camera
Camera camera(Vec3f(0.0f, 15.0f, 75.0f));
float lastX = (float)SCR_WIDTH / 2.0;
float lastY = (float)SCR_HEIGHT / 2.0;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

#include <map>
#include <set>
#include <functional>
#include <string>

#include <entt/entt.hpp>
#include <imgui.h>

#ifndef MM_IEEE_ASSERT
    #define MM_IEEE_ASSERT(x) assert(x)
#endif

#define MM_IEEE_IMGUI_PAYLOAD_TYPE_ENTITY "MM_IEEE_ENTITY"

#ifndef MM_IEEE_ENTITY_WIDGET
    #define MM_IEEE_ENTITY_WIDGET ::EntityWidget
#endif

template <class EntityType>
inline void EntityWidget(EntityType& e, entt::basic_registry<EntityType>& reg, bool dropTarget = false)
{
    ImGui::PushID(static_cast<int>(entt::to_integral(e)));

    if (reg.valid(e)) {
        ImGui::Text("ID: %d", entt::to_integral(e));
    } else {
        ImGui::Text("Invalid Entity");
    }

    if (reg.valid(e)) {
        if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID)) {
            ImGui::SetDragDropPayload(MM_IEEE_IMGUI_PAYLOAD_TYPE_ENTITY, &e, sizeof(e));
            ImGui::Text("ID: %d", entt::to_integral(e));
            ImGui::EndDragDropSource();
        }
    }

    if (dropTarget && ImGui::BeginDragDropTarget()) {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(MM_IEEE_IMGUI_PAYLOAD_TYPE_ENTITY)) {
            e = *(EntityType*)payload->Data;
        }

        ImGui::EndDragDropTarget();
    }

    ImGui::PopID();
}

template <class Component, class EntityType>
void ComponentEditorWidget([[maybe_unused]] entt::basic_registry<EntityType>& registry, [[maybe_unused]] EntityType entity) {}

template <class Component, class EntityType>
void ComponentAddAction(entt::basic_registry<EntityType>& registry, EntityType entity)
{
    registry.template emplace<Component>(entity);
}

template <class Component, class EntityType>
void ComponentRemoveAction(entt::basic_registry<EntityType>& registry, EntityType entity)
{
    registry.template remove<Component>(entity);
}

template <class EntityType>
class EntityEditor {
public:
    using Registry = entt::basic_registry<EntityType>;
    using ComponentTypeID = entt::id_type;

    struct ComponentInfo {
        using Callback = std::function<void(Registry&, EntityType)>;
        std::string name;
        Callback widget, create, destroy;
    };

    bool show_window = true;

private:
    std::map<ComponentTypeID, ComponentInfo> component_infos;

    bool entityHasComponent(Registry& registry, EntityType& entity, ComponentTypeID type_id)
    {
        const auto* storage_ptr = registry.storage(type_id);
        return storage_ptr != nullptr && storage_ptr->contains(entity);
    }

public:
    template <class Component>
    ComponentInfo& registerComponent(const ComponentInfo& component_info)
    {
        auto index = entt::type_hash<Component>::value();
        auto insert_info = component_infos.insert_or_assign(index, component_info);
        MM_IEEE_ASSERT(insert_info.second);
        return std::get<ComponentInfo>(*insert_info.first);
    }

    template <class Component>
    ComponentInfo& registerComponent(const std::string& name, typename ComponentInfo::Callback widget)
    {
        return registerComponent<Component>(ComponentInfo{
            name,
            widget,
            ComponentAddAction<Component, EntityType>,
            ComponentRemoveAction<Component, EntityType>,
        });
    }

    template <class Component>
    ComponentInfo& registerComponent(const std::string& name)
    {
        return registerComponent<Component>(name, ComponentEditorWidget<Component, EntityType>);
    }

    void renderEditor(Registry& registry, EntityType& e)
    {
        ImGui::TextUnformatted("Editing:");
        ImGui::SameLine();

        MM_IEEE_ENTITY_WIDGET(e, registry, true);

        if (ImGui::Button("New")) {
            e = registry.create();
        }
        if (registry.valid(e)) {
            ImGui::SameLine();

            if (ImGui::Button("Clone")) {
                auto old_e = e;
                e = registry.create();

                // create a copy of an entity component by component
                for (auto &&curr: registry.storage()) {
                    if (auto &storage = curr.second; storage.contains(old_e)) {
                        // TODO: do something with the return value. returns false on failure.
                        storage.push(e, storage.value(old_e));
                    }
                }
            }
            ImGui::SameLine();

            ImGui::Dummy({10, 0}); // space destroy a bit, to not accidentally click it
            ImGui::SameLine();

            // red button
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.65f, 0.15f, 0.15f, 1.f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.8f, 0.3f, 0.3f, 1.f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.f, 0.2f, 0.2f, 1.f));
            if (ImGui::Button("Destroy")) {
                registry.destroy(e);
                e = entt::null;
            }
            ImGui::PopStyleColor(3);
        }

        ImGui::Separator();

        if (registry.valid(e)) {
            ImGui::PushID(static_cast<int>(entt::to_integral(e)));
            std::map<ComponentTypeID, ComponentInfo> has_not;
            for (auto& [component_type_id, ci] : component_infos) {
                if (entityHasComponent(registry, e, component_type_id)) {
                    ImGui::PushID(component_type_id);
                    if (ImGui::Button("-")) {
                        ci.destroy(registry, e);
                        ImGui::PopID();
                        continue; // early out to prevent access to deleted data
                    } else {
                        ImGui::SameLine();
                    }

                    if (ImGui::CollapsingHeader(ci.name.c_str())) {
                        ImGui::Indent(30.f);
                        ImGui::PushID("Widget");
                        ci.widget(registry, e);
                        ImGui::PopID();
                        ImGui::Unindent(30.f);
                    }
                    ImGui::PopID();
                } else {
                    has_not[component_type_id] = ci;
                }
            }

            if (!has_not.empty()) {
                if (ImGui::Button("+ Add Component")) {
                    ImGui::OpenPopup("Add Component");
                }

                if (ImGui::BeginPopup("Add Component")) {
                    ImGui::TextUnformatted("Available:");
                    ImGui::Separator();

                    for (auto& [component_type_id, ci] : has_not) {
                        ImGui::PushID(component_type_id);
                        if (ImGui::Selectable(ci.name.c_str())) {
                            ci.create(registry, e);
                        }
                        ImGui::PopID();
                    }
                    ImGui::EndPopup();
                }
            }
            ImGui::PopID();
        }
    }

    void renderEntityList(Registry& registry, std::set<ComponentTypeID>& comp_list)
    {
        ImGui::Text("Components Filter:");
        ImGui::SameLine();
        if (ImGui::SmallButton("clear")) {
            comp_list.clear();
        }

        ImGui::Indent();

        for (const auto& [component_type_id, ci] : component_infos) {
            bool is_in_list = comp_list.count(component_type_id);
            bool active = is_in_list;

            ImGui::Checkbox(ci.name.c_str(), &active);

            if (is_in_list && !active) { // remove
                comp_list.erase(component_type_id);
            } else if (!is_in_list && active) { // add
                comp_list.emplace(component_type_id);
            }
        }

        ImGui::Unindent();
        ImGui::Separator();

        if (comp_list.empty()) {
            ImGui::Text("Orphans:");
            for (EntityType e : registry.template storage<EntityType>()) {
                if (registry.orphan(e)) {
                    MM_IEEE_ENTITY_WIDGET(e, registry, false);
                }
            }
        } else {
            entt::runtime_view view{};
            for (const auto type : comp_list) {
                auto* storage_ptr = registry.storage(type);
                if (storage_ptr != nullptr) {
                    view.iterate(*storage_ptr);
                }
            }

            // TODO: add support for exclude

            ImGui::Text("%lu Entities Matching:", view.size_hint());

            if (ImGui::BeginChild("entity list")) {
                for (auto e : view) {
                    MM_IEEE_ENTITY_WIDGET(e, registry, false);
                }
            }
            ImGui::EndChild();
        }
    }

    // displays both, editor and list
    // uses static internally, use only as a quick way to get going!
    void renderSimpleCombo(Registry& registry, EntityType& e)
    {
        if (show_window) {
            ImGui::SetNextWindowSize(ImVec2(550, 400), ImGuiCond_FirstUseEver);
            if (ImGui::Begin("Entity Editor", &show_window)) {
                if (ImGui::BeginChild("list", {200, 0}, true)) {
                    static std::set<ComponentTypeID> comp_list;
                    renderEntityList(registry, comp_list);
                }
                ImGui::EndChild();

                ImGui::SameLine();

                if (ImGui::BeginChild("editor")) {
                    renderEditor(registry, e);
                }
                ImGui::EndChild();

            }
            ImGui::End();
        }
    }
};

namespace Components {

    struct Transform {
        float x = 0.f;
        float y = 0.f;
        float z = 0.f;
        float scale = 0.f;
        float rotate = 0.f;
    };

    struct Velocity {
        float x = 0.f;
        float y = 0.f;
        float z = 0.f;
    };

} // Components


template <>
void ComponentEditorWidget<Components::Transform>(entt::registry& reg, entt::registry::entity_type e)
{
    auto& t = reg.get<Components::Transform>(e);
    // the "##Transform" ensures that you can use the name "x" in multiple lables
    ImGui::DragFloat("x##Transform", &t.x, 0.1f);
    ImGui::DragFloat("y##Transform", &t.y, 0.1f);
    ImGui::DragFloat("z##Transform", &t.z, 0.1f);
    ImGui::DragFloat("scale##Transform", &t.scale, 0.1f);
    ImGui::DragFloat("rotate##Transform", &t.rotate, 0.1f);
}

template <>
void ComponentEditorWidget<Components::Velocity>(entt::registry& reg, entt::registry::entity_type e)
{
    auto& v = reg.get<Components::Velocity>(e);
    ImGui::DragFloat("x##Velocity", &v.x, 0.1f);
    ImGui::DragFloat("y##Velocity", &v.y, 0.1f);
    ImGui::DragFloat("z##Velocity", &v.z, 0.1f);
}

namespace Systems {

void Velocity(entt::registry& reg, float delta) {
    reg.view<Components::Transform, Components::Velocity>().each(
    [&](Components::Transform& trans, Components::Velocity& vel) {
        // Update rotation based on velocity
        trans.rotate += vel.y * deltaTime;

        // Keep the rotation angle within the range [0, 360)
        trans.rotate = fmod(trans.rotate, 360.0f);

        // Calculate new position based on rotation around the Y-axis
        float angleRad = glm::radians(trans.rotate);
        float radius = glm::sqrt(trans.x*trans.x + trans.y*trans.y + trans.z*trans.z);;  // You can adjust this radius as needed

        trans.x = radius * sin(angleRad);
        trans.z = radius * cos(angleRad);
    });
}

} // Systems

// Main code
int main(int, char**)
{
    TRACE("Init project");
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Linky Engine - Editor", nullptr, nullptr);
    if (window == nullptr)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSwapInterval(1); // Enable vsync

    if (gladLoadGL(glfwGetProcAddress) == 0)
    {
        return -1;
    }
    
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    // - Our Emscripten build process allows embedding fonts to be accessible at runtime from the "fonts/" folder. See Makefile.emscripten for details.
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != nullptr);

    // build and compile shaders
    // -------------------------
    Shader shader("./LinkyEditor/assets/shaders/belt.vert", "./LinkyEditor/assets/shaders/belt.frag");
    Shader instanceShader("./LinkyEditor/assets/shaders/belt_instance.vert", "./LinkyEditor/assets/shaders/belt_instance.frag");
    // load models
    // -----------
    Model rock("./LinkyEditor/assets/models/rock/rock.obj");
    Model planet("./LinkyEditor/assets/models/planet/planet.obj");

    entt::registry reg;

    EntityEditor<entt::entity> editor;

    editor.registerComponent<Components::Transform>("Transform");
    editor.registerComponent<Components::Velocity>("Velocity");

    entt::entity e;
    // generate a large list of semi-random model transformation matrices
    // ------------------------------------------------------------------
    unsigned int amount = 10000;
    std::vector<Mat4f> modelMatrices(amount);
    srand(static_cast<unsigned int>(glfwGetTime())); // initialize random seed
    float radius = 50.0;
    float offset = 10.0f;
    for (unsigned int i = 0; i < amount; i++)
    {
        Mat4f model = Mat4f(1.0f);
        // 1. translation: displace along circle with 'radius' in range [-offset, offset]
        float angle = (float)i / (float)amount * 360.0f;
        float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float x = sin(angle) * radius + displacement;
        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float y = displacement * 0.4f; // keep height of asteroid field smaller compared to width of x and z
        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float z = cos(angle) * radius + displacement;
        model = glm::translate(model, Vec3f(x, y, z));

        // 2. scale: Scale between 0.05 and 0.25f
        float scale = static_cast<float>((rand() % 20) / 100.0 + 0.05);
        model = glm::scale(model, Vec3f(scale));

        // 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
        float rotAngle = static_cast<float>((rand() % 360));
        model = glm::rotate(model, rotAngle, Vec3f(0.4f, 0.6f, 0.8f));

        // 4. now add to list of matrices
        modelMatrices[i] = model;

        e = reg.create();
        // setup nice initial entity
        {
            //reg.emplace<Components::Transform>(e, 500.f, 500.f);
            //reg.emplace<Components::Velocity>(e, 500.f, 500.f);
            reg.emplace<Components::Transform>(e, x, y, z, scale, rotAngle);
            reg.emplace<Components::Velocity>(e, float((rand()%500) - 250)/10, float((rand()%500) - 250)/10, float((rand()%500) - 250)/10);
        }
    }

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, amount * sizeof(Mat4f), &modelMatrices[0], GL_STATIC_DRAW);

    // set transformation matrices as an instance vertex attribute (with divisor 1)
    // note: we're cheating a little by taking the, now publicly declared, VAO of the model's mesh(es) and adding new vertexAttribPointers
    // normally you'd want to do this in a more organized fashion, but for learning purposes this will do.
    // -----------------------------------------------------------------------------------------------------------------------------------
    for (unsigned int i = 0; i < rock.meshes.size(); i++)
    {
        unsigned int VAO = rock.meshes[i].VAO;
        glBindVertexArray(VAO);
        // set attribute pointers for matrix (4 times vec4)
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Mat4f), (void*)0);
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(Mat4f), (void*)(sizeof(glm::vec4)));
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(Mat4f), (void*)(2 * sizeof(glm::vec4)));
        glEnableVertexAttribArray(6);
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Mat4f), (void*)(3 * sizeof(glm::vec4)));

        glVertexAttribDivisor(3, 1);
        glVertexAttribDivisor(4, 1);
        glVertexAttribDivisor(5, 1);
        glVertexAttribDivisor(6, 1);

        glBindVertexArray(0);
    }

    // Our state
    bool show_demo_window = false;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
#ifdef __EMSCRIPTEN__
    // For an Emscripten build we are disabling file-system access, so let's not attempt to do a fopen() of the imgui.ini file.
    // You may manually call LoadIniSettingsFromMemory() to load settings from your own storage.
    io.IniFilename = nullptr;
    EMSCRIPTEN_MAINLOOP_BEGIN
#else
    while (!glfwWindowShouldClose(window))
#endif
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();

        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);
        
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

        Systems::Velocity(reg, 1.f/60.f);

        // render editor
        editor.renderSimpleCombo(reg, e);

        // Update transformations in ECS components
        auto view = reg.view<Components::Transform, Components::Velocity>();
        for (auto entity : view)
        {
            auto &transform = view.get<Components::Transform>(entity);
            auto &velocity = view.get<Components::Velocity>(entity);

            // Get the entity's ID
            entt::entity entityId = entity;

            // Convert the entity ID to an integral type for streaming
            auto entityIdIntegral = entt::to_integral(entityId);
            auto& model = modelMatrices[entityIdIntegral];
            model = glm::mat4(1.0f); // Initialize as identity matrix
            model = glm::translate(model, Vec3f(transform.x, transform.y, transform.z));
            // 2. scale: Scale between 0.05 and 0.25f
            model = glm::scale(model, Vec3f(transform.scale));

            model = glm::rotate(model, transform.rotate, Vec3f(0.4f, 0.6f, 0.8f));
        }

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Update buffer data with the modified modelMatrices
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, amount * sizeof(Mat4f), &modelMatrices[0], GL_STATIC_DRAW);

        // configure transformation matrices
        Mat4f projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
        Mat4f view1 = camera.GetViewMatrix();;

        // draw meteorites
        instanceShader.use();
        instanceShader.setMat4("projection", projection);
        instanceShader.setMat4("view", view1);
        instanceShader.setInt("texture_diffuse1", 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, rock.textures_loaded[0].id);
        for (unsigned int i = 0; i < rock.meshes.size(); i++)
        {
            glBindVertexArray(rock.meshes[i].VAO);
            glDrawElementsInstanced(
                GL_TRIANGLES, rock.meshes[i].indices.size(), GL_UNSIGNED_INT, 0, amount
            );
        }

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
        //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        glfwSwapBuffers(window);
    }
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_MAINLOOP_END;
#endif

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(kForward, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(kBackward, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(kLeft, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(kRight, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.ProcessKeyboard(kUp, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
        camera.ProcessKeyboard(kDown, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    // (1) ALWAYS forward mouse data to ImGui! This is automatic with default backends. With your own backend:
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    //camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}