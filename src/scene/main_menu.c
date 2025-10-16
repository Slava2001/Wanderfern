#include "main_menu.h"
#include "gl.h"

#include <math.h>

int update(void *ctx, SceneUpdateCtx *uctx);
int draw(void *ctx);

ResultMainMenu main_menu_new() {
    return (ResultMainMenu) Ok(((MainMenu) {
        .base = (Scene) {
            .update = update,
            .draw = draw,
            .destroy = NULL
        },
        .angle_rad = 0
    }));
}

int update(void *ctx, SceneUpdateCtx *uctx) {
    MainMenu *this = (MainMenu *)ctx;
    const float ROTATION_SPEED_RAD_PER_S = 2.0f * (float)M_PI;
    if (glfwGetKey(uctx->window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        this->angle_rad = this->angle_rad + ROTATION_SPEED_RAD_PER_S * uctx->delta_time;
    }
    return 0;
}

int draw(void *ctx) {
    MainMenu *this = (MainMenu *)ctx;
    glPushMatrix();
    glRotatef(this->angle_rad, 0, 0, 1);
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(-0.5f, -0.5f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f( 0.5f, -0.5f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f( 0.0f,  0.5f);
    glEnd();
    glPopMatrix();
    return 0;
}
