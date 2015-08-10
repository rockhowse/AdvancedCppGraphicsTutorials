#version 130
//The fragment shader operats on each pixel in a given polygon

flat in vec4 fragmentColor;

// This is the 3 component float vector that gets output to the screen for each pixel
out vec4 color;

void main() {
	// Just hardcode the color to red
	color = fragmentColor;
}