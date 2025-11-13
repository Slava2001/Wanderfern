#include "gl.h"
#include "log.h"

ResultWindow gl_init(int width, int height, const char* title) {
    logi("Initing OpenGl");
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    rci(!window, (ResultWindow)Err(), "Failed to init window");
    glfwMakeContextCurrent(window);
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glewExperimental = GL_TRUE;
    glewInit();
    glViewport(0, 0, width, height);

    logi("OpenGL version: %s", glGetString(GL_VERSION));
    return (ResultWindow)Ok((Window) {
        .gl_window = window
    });
}

void gl_deinit(Window *window) {
    glfwSetInputMode(window->gl_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwDestroyWindow(window->gl_window);
    glfwTerminate();
}
