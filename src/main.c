#include <stdio.h>
#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

#define LOG_LVL DBG
#include <utils.h>

#define WINDOW_W 800
#define WINDOW_H 600
#define WINDOW_TITLE "Wanderfern"

/// @brief Draw rectangle.
void draw_rectangle(void);

int main(void) {
    rci(!glfwInit(), EXIT_FAILURE, "Failed to initialize GLFW");
    GLFWwindow* window = glfwCreateWindow(WINDOW_W, WINDOW_H, WINDOW_TITLE, NULL, NULL);
    rci(!window, EXIT_FAILURE, "Failed to create GLFW window");

    glfwMakeContextCurrent(window);
    glViewport(0, 0, WINDOW_W, WINDOW_H);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        draw_rectangle();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return EXIT_SUCCESS;
}

void draw_rectangle(void) {
    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f( 0.5f, -0.5f);
        glVertex2f( 0.5f,  0.5f);
        glVertex2f(-0.5f,  0.5f);
    glEnd();
}
