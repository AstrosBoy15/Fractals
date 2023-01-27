#include "Global.h"

#include "RenderManager.h"

RenderManager::RenderManager(WindowManager* win_mgr) {
	this->win_mgr = win_mgr;
	fractalShader = new FractalShader("fractal");

	gui = new Gui();

	loadModel(quad);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
}

RenderManager::~RenderManager() {
	delete fractalShader;
	delete gui;
}

void RenderManager::loadModel(const float* quad) {
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), quad, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void RenderManager::prepare() {
	fractalShader->start();
}

void RenderManager::finish() {
	fractalShader->stop();
}

void RenderManager::loadUniforms(const glm::vec2& position, const glm::vec2& windowScale, const float scale, const glm::vec2& c, const bool mandelbrot, const int iterations) {
	fractalShader->loadPosition(position);
	fractalShader->loadWindowScale(windowScale);
	fractalShader->loadScale(scale);
	fractalShader->loadC(c);
	fractalShader->loadMandelbrot(mandelbrot);
	fractalShader->loadIterations(iterations);
}

void RenderManager::render(const glm::vec2& position, const glm::vec2& windowScale, const float scale, const glm::vec2& c, const bool mandelbrot, const int iterations) {
	loadUniforms(position, windowScale, scale, c, mandelbrot, iterations);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}