# Linky Engine

## About
This is my hobby project that I work on in my spare time to learn more about graphics programming and engine architectures. Especially OpenGL and C++. Also to produce some games including my dream game in the future.

## Building
Currently supported and tested compilers are only: MSVC
- Run the root CMake script with this command to generate for MSVC:       
`cmake -S . -B ./build/ -G "Visual Studio 17 2022" -A x64`      
- Then run this command to build it with CMake:   
`cmake --build ./build --config Release`

## Dependencies
- [GLFW](https://github.com/glfw/glfw)
- [entt](https://github.com/skypjack/entt)
- [Dear ImGui](https://github.com/ocornut/imgui)
- [GLM](https://github.com/g-truc/glm)
- [NFD](https://github.com/btzy/nativefiledialog-extended)