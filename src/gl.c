#include "gl.h"
#include "log.h"

ResultWindow gl_init(const char* title) {
    logi("Initing OpenGl");
    glfwInit();

    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    GLFWvidmode mode = *glfwGetVideoMode(monitor);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(mode.width, mode.height, title, monitor, NULL);
    rci(!window, (ResultWindow)Err(), "Failed to init window");
    glfwMakeContextCurrent(window);
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glewExperimental = GL_TRUE;
    glewInit();
    glViewport(0, 0, mode.width, mode.height);

    logi("OpenGL version: %s", glGetString(GL_VERSION));
    return (ResultWindow)Ok(((Window) {
        .gl_window = window,
        .monitor = monitor,
        .video = mode
    }));
}

void gl_deinit(Window *window) {
    glfwSetInputMode(window->gl_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwDestroyWindow(window->gl_window);
    glfwTerminate();
}
