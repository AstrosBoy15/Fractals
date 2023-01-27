#version 330 core

uniform vec2 u_position;
uniform vec2 u_windowScale;
uniform float u_scale;
uniform vec2 u_c;
uniform bool u_mandelbrot;
uniform int u_iterations;

out vec4 color;


vec3 calcColor() {
	vec2 pos;
	vec2 z;

	if(u_mandelbrot) {
		pos = ((gl_FragCoord.xy - 0.5 - u_windowScale / 2) * exp(u_scale) + u_position) / 200;
		z =  vec2(0, 0);
	} else {
		pos = u_c;
		z =  ((gl_FragCoord.xy - 0.5 - u_windowScale / 2) * exp(u_scale) + u_position) / 200;
	}

	float zr = sqrt(pow(z.x, 2) + pow(z.y, 2));

	float zt;
	if(z.x == 0 && z.y == 0) {
		zt = 0;
	} else {
		zt = atan(z.x/zr, z.y/zr);
	}

	for(int i = 0; i < u_iterations; i++) {
		z = pow(zr, 2)*vec2(cos(-2*zt), sin(-2*zt)) - pos;
		zr = sqrt(pow(z.x, 2) + pow(z.y, 2));
		zt = atan(z.x/zr, z.y/zr);

		if(zr > 2) {
			return vec3(0, 0.75 - float(i) / u_iterations, 1 - float(i) / u_iterations);
		}
	}

	return vec3(0);
}

void main(){
	color = vec4(calcColor(), 1);
}