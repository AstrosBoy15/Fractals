#include "FractalShader.h"

FractalShader::FractalShader(const std::string& key) : Shader(key) {
	getAllUniformLocations();
}

void FractalShader::getAllUniformLocations() {
	location_position = glGetUniformLocation(programID, "u_position");
	location_windowScale = glGetUniformLocation(programID, "u_windowScale");
	location_scale = glGetUniformLocation(programID, "u_scale");
	location_c = glGetUniformLocation(programID, "u_c");
	location_mandelbrot = glGetUniformLocation(programID, "u_mandelbrot");
	location_iterations = glGetUniformLocation(programID, "u_iterations");
}

void FractalShader::loadPosition(const glm::vec2& position) {
	loadVec2f(location_position, position);
}

void FractalShader::loadWindowScale(const glm::vec2& windowScale) {
	loadVec2f(location_windowScale, windowScale);
}

void FractalShader::loadScale(const float scale) {
	loadFloat(location_scale, scale);
}

void FractalShader::loadC(const glm::vec2& c) {
	loadVec2f(location_c, c);
}

void FractalShader::loadMandelbrot(const bool mandelbrot) {
	loadBool(location_mandelbrot, mandelbrot);
}

void FractalShader::loadIterations(const int iterations) {
	loadInt(location_iterations, iterations);
}