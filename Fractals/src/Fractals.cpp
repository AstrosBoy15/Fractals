#include "Global.h"

#include "util/WindowManager.h"
#include "render/RenderManager.h"
#include "main/FPSManager.h"
#include "main/Handler.h"

#ifdef _DEBUG
size_t allocated = 0;
bool showFPS = true;

void* operator new(size_t size) { 
    allocated += size;
    return malloc(size);
}

void operator delete(void* memory, size_t size) {
    allocated -= size;
    free(memory);
}

#define _CHECKLEAKS if (allocated) { std::cout << "[MEMORY LEAK!]: " << allocated << " bytes of allocated memory still remain!" << std::endl; }

#else

bool showFPS = false;
#define _CHECKLEAKS

#endif

void cycle(WindowManager* win_mgr, RenderManager* renderer, Handler* handler) {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    //render
    handler->tick();
    handler->render();
    win_mgr->updateWindow();

    renderer->gui->renderGUI();

    glfwSwapBuffers(win_mgr->getWindow());
    glfwPollEvents();
}

int main(void) {
    WindowManager* win_mgr = new WindowManager();

    if (!win_mgr->getWindow()) {
        delete win_mgr;
        std::cout << "Window Failed to Load!" << std::endl;
        return -1;
    }

    RenderManager* renderer = new RenderManager(win_mgr);
    FPSManager* fps_mgr = new FPSManager(60, showFPS);
    Handler* handler = new Handler(win_mgr, renderer);

    renderer->gui->initGUI(win_mgr->getWindow());

    renderer->prepare();

    while (!glfwWindowShouldClose(win_mgr->getWindow())) {
        if (fps_mgr->runCycle()) {
            cycle(win_mgr, renderer, handler);
        }
    }

    renderer->gui->cleanup();
    renderer->finish();

    glfwTerminate();

    delete win_mgr;
    delete renderer;
    delete fps_mgr;
    delete handler;

    _CHECKLEAKS

    return 0;
}