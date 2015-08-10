#pragma once
#include <GL/glew.h>

struct Vertex {
	struct Position {
		GLfloat x;
		GLfloat y;
	} position;

	struct Color {
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
	} color;
};