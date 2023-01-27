#include "Handler.h"

Handler::Handler(WindowManager* win_mgr, RenderManager* renderer) : win_mgr(win_mgr), renderer(renderer) {
    position = glm::vec2(0, 0);
    scale = 0;
}

void Handler::render() {
    renderer->render(position, glm::vec2(win_mgr->getWindowWidth(), win_mgr->getWindowHeight()), scale, renderer->gui->c, renderer->gui->mode, renderer->gui->iterations);
}

void Handler::tick() {
    if (win_mgr->isKeyDown(GLFW_KEY_W)) {
        position.y += 5 * exp(scale);
    }

    if (win_mgr->isKeyDown(GLFW_KEY_S)) {
        position.y -= 5 * exp(scale);
    }

    if (win_mgr->isKeyDown(GLFW_KEY_D)) {
        position.x += 5 * exp(scale);
    }

    if (win_mgr->isKeyDown(GLFW_KEY_A)) {
        position.x -= 5 * exp(scale);
    }

    if (win_mgr->isKeyDown(GLFW_KEY_E)) {
        scale += 0.01f;
    }

    if (win_mgr->isKeyDown(GLFW_KEY_Q)) {
        scale -= 0.01f;
    }

    if (win_mgr->isKeyPressed(GLFW_KEY_R)) {
        position = glm::vec2(0, 0);
        scale = 0;
    }
}