#include "camera.h"

ResultCamera camera_new(CameraOptions ops) {
    gluPerspective(ops.fov, ops.aspect, ops.near_z, ops.far_z);
    return (ResultCamera)Ok(((Camera){ .position = ops.position, .angles = ops.angles }));
}

void camera_set_view(Camera *camera) {
    logd("x: %.2f, y: %.2f, z: %.2f, yaw: %.2f, pitch: %.2f, roll: %.2f\n",
         camera->position.x, camera->position.y, camera->position.z,
         camera->angles.x, camera->angles.y, camera->angles.z);
    glRotated(camera->angles.y, 1.0f, 0.0f, 0.0f);
    glRotated(camera->angles.x, 0.0f, 1.0f, 0.0f);
    glRotated(camera->angles.z, 0.0f, 0.0f, 1.0f);
    glTranslated(-camera->position.x, -camera->position.y, -camera->position.z);
}

void camera_movevd(Camera *camera, Vec3d delta) {
    camera->position = vec3d_add(camera->position, delta);
}

void camera_rotated(Camera *camera, Vec3d angles) {
    camera->angles = vec3d_add(camera->angles, angles);
}

Vec3d camera_get_position(Camera *camera) {
    return camera->position;
}

Vec3d camera_get_angles(Camera *camera) {
    return camera->angles;
}

void camera_set_position(Camera *camera, Vec3d position) {
    camera->position = position;
}

void camera_set_angles(Camera *camera, Vec3d angles) {
    camera->angles = angles;
}
