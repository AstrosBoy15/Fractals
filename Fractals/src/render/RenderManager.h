#pragma once

#include "Global.h"
#include "util/WindowManager.h"
#include "render/FractalShader.h"
#include "gui/Gui.h"

class RenderManager {
private:
	WindowManager* win_mgr;

	FractalShader* fractalShader;

	float quad[8] = { -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f };

	void loadModel(const float* quad);

public:
	Gui* gui;

	RenderManager(WindowManager* win_mgr);
	~RenderManager();
	void render(const glm::vec2& position, const glm::vec2& windowScale, const float scale, const glm::vec2& c, const bool mandelbrot, const int iterations);
	void prepare();
	void finish();
	void loadUniforms(const glm::vec2& position, const glm::vec2& windowScale, const float scale, const glm::vec2& c, const bool mandelbrot, const int iterations);
};