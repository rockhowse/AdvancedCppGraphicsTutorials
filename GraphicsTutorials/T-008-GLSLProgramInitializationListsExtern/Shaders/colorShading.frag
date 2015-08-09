#version 130
//The fragment shader operats on each pixel in a given polygon

// This is the 3 component float vector that gets output to the screen for each pixel
out vec3 color;

void main() {

	// Just hardcode the color to red
	color = vec3(1.0, 0.0, 0.0);
}