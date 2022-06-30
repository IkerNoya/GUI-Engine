#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "debug.h"

void Debug::DrawLine(float x, float y) {

	glDrawArrays(GL_LINE_STRIP, 0, 5);
}

void Debug::DrawSphere(float radius, float center) {
}

void Debug::DrawCube(float center, float width, float height, float lenght) {
}
