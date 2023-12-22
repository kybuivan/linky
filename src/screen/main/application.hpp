#pragma once

namespace linky {

class Application {
public:
    Application() = default;
    virtual ~Application() = default;
    static void Init();
    virtual void Run() = 0;
private:
    static Application* Create();
};

}