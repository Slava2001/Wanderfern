#include "player_ctl.h"
#include "util.h"

#define _USE_MATH_DEFINES
#include <math.h>

void get_cursor_moving(GLFWwindow* window, float* xpos, float* ypos);

ResultPlayerCtl playerctl_new(CameraOptions ops) {
    ops.angles.z = 0;
    return (ResultPlayerCtl)Ok((PlayerCtl) {
        .camera = try(camera_new(ops), (ResultPlayerCtl)Err(),
                      "Failed to init player camera")
    });
}

void playerctl_update(PlayerCtl *this, const SceneUpdateCtx *uctx) {
    const float ROTATING_SPEED_RAD_PER_S = 0.5f;
    Vec3 cam_angles = camera_get_angles(&this->camera);
    if (glfwGetKey(uctx->window->gl_window, GLFW_KEY_UP) == GLFW_PRESS) {
        cam_angles.x += ROTATING_SPEED_RAD_PER_S * uctx->delta_time;
    }
    if (glfwGetKey(uctx->window->gl_window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        cam_angles.x -= ROTATING_SPEED_RAD_PER_S * uctx->delta_time;
    }
    if (glfwGetKey(uctx->window->gl_window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        cam_angles.y += ROTATING_SPEED_RAD_PER_S * uctx->delta_time;
    }
    if (glfwGetKey(uctx->window->gl_window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        cam_angles.y -= ROTATING_SPEED_RAD_PER_S * uctx->delta_time;
    }
    // #define ENABLE_CURSOR_SUPPORT
    #ifdef ENABLE_CURSOR_SUPPORT
    GLfloat cursor_dx, cursor_dy;
    get_cursor_moving(uctx->window->gl_window, &cursor_dx, &cursor_dy);
    const float CURSOR_SENSITIVITY = 0.005f;
    cam_angles = vec3_add(cam_angles, vec3(CURSOR_SENSITIVITY * -cursor_dy,
                                             CURSOR_SENSITIVITY * cursor_dx, 0));
    #endif
    cam_angles.y = fmodf(cam_angles.y, 360);
    const float x_angle_range = 0.95f * (float)M_PI_2;
    cam_angles.x = CLAMP(cam_angles.x, -x_angle_range, x_angle_range);
    camera_set_angles(&this->camera, cam_angles);

    const float MOVING_SPEED_M_PER_S = 0.03f;
    Vec3 cam_pos_delta = vec3(0, 0, 0);
    Vec3 cam_dir = camera_get_dir(&this->camera);
    cam_dir.y = 0;
    cam_dir = vec3_normalize(cam_dir);
    Vec2 cam_2d_dir = vec2_normalize(vec2(cam_dir.x, cam_dir.z));
    Vec2 cam_2d_right = vec2_rotate(cam_2d_dir, (float)M_PI_2);
    Vec3 cam_right = vec3(cam_2d_right.x, 0, cam_2d_right.y);
    if (glfwGetKey(uctx->window->gl_window, GLFW_KEY_W) == GLFW_PRESS) {
        cam_pos_delta = vec3_add(cam_pos_delta, cam_dir);
    }
    if (glfwGetKey(uctx->window->gl_window, GLFW_KEY_S) == GLFW_PRESS) {
        cam_pos_delta = vec3_add(cam_pos_delta, vec3_neg(cam_dir));
    }
    if (glfwGetKey(uctx->window->gl_window, GLFW_KEY_A) == GLFW_PRESS) {
        cam_pos_delta = vec3_add(cam_pos_delta, vec3_neg(cam_right));
    }
    if (glfwGetKey(uctx->window->gl_window, GLFW_KEY_D) == GLFW_PRESS) {
        cam_pos_delta = vec3_add(cam_pos_delta, cam_right);
    }
    cam_pos_delta = vec3_muls(cam_pos_delta, MOVING_SPEED_M_PER_S);
    camera_movevd(&this->camera, cam_pos_delta);
}

Transform playerctl_get_transform(PlayerCtl *this) {
    return camera_get_transform(&this->camera);
}

void get_cursor_moving(GLFWwindow* window, float* xpos, float* ypos) {
    static bool is_first = true;
    static double old_x, old_y;
    double cursor_x, cursor_y;
    glfwGetCursorPos(window, &cursor_x, &cursor_y);
    if (is_first) {
        *xpos = 0;
        *ypos = 0;
        is_first = false;
    } else {
        *xpos = (float)(cursor_x - old_x);
        *ypos = (float)(cursor_y - old_y);
    }
    old_x = cursor_x;
    old_y = cursor_y;
}

Vec3 playerctl_get_position(PlayerCtl *this) {
    return camera_get_position(&this->camera);
}
