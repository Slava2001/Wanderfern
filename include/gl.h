#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "result.h"

typedef struct Window {
    GLFWwindow *gl_window;
    GLFWmonitor *monitor;
    GLFWvidmode video;
} Window;

decl_result(Window, Window);

ResultWindow gl_init(const char* title);
void gl_deinit(Window *window);
