#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "result.h"

typedef struct Window {
    GLFWwindow *gl_window;
} Window;

decl_result(Window, Window);

ResultWindow gl_init(int width, int height, const char* title);
void gl_deinit(Window *window);
