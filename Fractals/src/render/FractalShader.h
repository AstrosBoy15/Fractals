#pragma once

#include "Global.h"
#include "render/shader.h"

class FractalShader: public Shader {
private:
	unsigned int location_mvp = 0;
	unsigned int location_position = 0;
	unsigned int location_windowScale = 0;
	unsigned int location_scale = 0;
	unsigned int location_c = 0;
	unsigned int location_mandelbrot = 0;
	unsigned int location_iterations = 0;
public:
	FractalShader(const std::string& key);
	void getAllUniformLocations() override;
	void loadPosition(const glm::vec2& position);
	void loadWindowScale(const glm::vec2& windowScale);
	void loadScale(const float scale);
	void loadC(const glm::vec2& c);
	void loadMandelbrot(const bool mandelbrot);
	void loadIterations(const int iterations);
};