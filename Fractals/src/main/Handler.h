#pragma once

#include "util/WindowManager.h"
#include "render/RenderManager.h"

class Handler{
private:
    glm::vec2 position;
    float scale;

    WindowManager* win_mgr;
    RenderManager* renderer;
public:
    Handler(WindowManager* win_mgr, RenderManager* renderer);
    void render();
    void tick();
};

