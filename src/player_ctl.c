#include "player_ctl.h"
#include "util.h"

#include <math.h>

ResultPlayerCtl playerctl_new(CameraOptions ops) {
    return (ResultPlayerCtl)Ok((PlayerCtl) {
        .camera = try(camera_new(ops), (ResultPlayerCtl)Err(),
                      "Failed to init player camera")
    });
}

void get_cursor_moving(GLFWwindow* window, double* xpos, double* ypos);

void get_cursor_moving(GLFWwindow* window, double* xpos, double* ypos) {
    static bool is_first = true;
    static double old_x, old_y;
    double cursor_x, cursor_y;
    glfwGetCursorPos(window, &cursor_x, &cursor_y);
    if (is_first) {
        *xpos = 0;
        *ypos = 0;
        is_first = false;
    } else {
        *xpos = cursor_x - old_x;
        *ypos = cursor_y - old_y;
    }
    old_x = cursor_x;
    old_y = cursor_y;
}

void playerctl_update(PlayerCtl *ctl, const SceneUpdateCtx *uctx) {
    const float ROTATING_SPEED_DEGREES_PER_S = 45;
    Vec3d cam_angles = camera_get_angles(&ctl->camera);
    if (glfwGetKey(uctx->window, GLFW_KEY_UP) == GLFW_PRESS) {
        cam_angles.y -= ROTATING_SPEED_DEGREES_PER_S * uctx->delta_time;
    }
    if (glfwGetKey(uctx->window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        cam_angles.y += ROTATING_SPEED_DEGREES_PER_S * uctx->delta_time;
    }
    if (glfwGetKey(uctx->window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        cam_angles.x += ROTATING_SPEED_DEGREES_PER_S * uctx->delta_time;
    }
    if (glfwGetKey(uctx->window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        cam_angles.x -= ROTATING_SPEED_DEGREES_PER_S * uctx->delta_time;
    }
    double cursor_dx, cursor_dy;
    get_cursor_moving(uctx->window, &cursor_dx, &cursor_dy);
    const float CURSOR_SENSITIVITY = 0.5f;
    cam_angles = vec3d_add(cam_angles, vec3d(CURSOR_SENSITIVITY * cursor_dx,
                                             CURSOR_SENSITIVITY * cursor_dy, 0));
    cam_angles.x = fmod(cam_angles.x, 360);
    cam_angles.y = CLAMP(cam_angles.y, -89, 89);
    camera_set_angles(&ctl->camera, cam_angles);

    const float MOVING_SPEED_M_PER_S = 0.1f;
    Vec3d cam_pos_delta = vec3d(0, 0, 0);
    double yaw_rad = cam_angles.x * M_PI / 180.0;
    if (glfwGetKey(uctx->window, GLFW_KEY_W) == GLFW_PRESS) {
        cam_pos_delta = vec3d_add(cam_pos_delta,
                                  vec3d(cos(yaw_rad - M_PI_2), 0, sin(yaw_rad - M_PI_2)));
    }
    if (glfwGetKey(uctx->window, GLFW_KEY_S) == GLFW_PRESS) {
        cam_pos_delta = vec3d_add(cam_pos_delta,
                                  vec3d(-cos(yaw_rad - M_PI_2), 0, -sin(yaw_rad - M_PI_2)));
    }
    if (glfwGetKey(uctx->window, GLFW_KEY_A) == GLFW_PRESS) {
        cam_pos_delta = vec3d_add(cam_pos_delta,
                                  vec3d(-cos(yaw_rad), 0, -sin(yaw_rad)));
    }
    if (glfwGetKey(uctx->window, GLFW_KEY_D) == GLFW_PRESS) {
        cam_pos_delta = vec3d_add(cam_pos_delta,
                                  vec3d(cos(yaw_rad), 0, sin(yaw_rad)));
    }
    cam_pos_delta = vec3d_muls(cam_pos_delta, MOVING_SPEED_M_PER_S);
    camera_movevd(&ctl->camera, cam_pos_delta);
}

void playerctl_set_view(PlayerCtl *ctl) {
    camera_set_view(&ctl->camera);
}
