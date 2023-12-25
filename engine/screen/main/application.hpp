#pragma once

namespace linky {

class application {
public:
    application() = default;
    virtual ~application() = default;
    static void init();
    virtual void run() = 0;
private:
    static application* create();
};

}