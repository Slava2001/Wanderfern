#include <stdio.h>
#include <stdlib.h>

#define LOG_LVL DBG
#include "utils.h"
#include "gl.h"
#include "scene.h"
#include "main_menu.h"

#define WINDOW_W 800
#define WINDOW_H 600
#define WINDOW_TITLE "Wanderfern"

int main(void) {
    logi("Starting app");
    rci(!glfwInit(), EXIT_FAILURE, "Failed to initialize GLFW");
    GLFWwindow* window = glfwCreateWindow(WINDOW_W, WINDOW_H, WINDOW_TITLE, NULL, NULL);
    rci(!window, EXIT_FAILURE, "Failed to create GLFW window");

    glfwMakeContextCurrent(window);
    glViewport(0, 0, WINDOW_W, WINDOW_H);

    MainMenu menu;
    main_menu_new(&menu);
    Scene *scene = (Scene *)&menu;

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        scene->update(scene, 1.0f/60);
        scene->draw(scene);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return EXIT_SUCCESS;
}
