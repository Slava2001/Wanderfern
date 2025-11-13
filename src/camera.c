#define LOG_LVL DBG
#include "camera.h"

ResultCamera camera_new(CameraOptions ops) {
    gluPerspective(ops.fov, ops.aspect, ops.near_z, ops.far_z);
    return (ResultCamera)Ok(((Camera){ .position = ops.position, .angles = ops.angles }));
}

void camera_set_view(Camera *this) {
    logd("x: %.2f, y: %.2f, z: %.2f, yaw: %.2f, pitch: %.2f, roll: %.2f",
         this->position.x, this->position.y, this->position.z,
         this->angles.x, this->angles.y, this->angles.z);
    glRotated(this->angles.y, 1.0f, 0.0f, 0.0f);
    glRotated(this->angles.x, 0.0f, 1.0f, 0.0f);
    glRotated(this->angles.z, 0.0f, 0.0f, 1.0f);
    glTranslated(-this->position.x, -this->position.y, -this->position.z);
}

void camera_movevd(Camera *this, Vec3d delta) {
    this->position = vec3d_add(this->position, delta);
}

void camera_rotated(Camera *this, Vec3d angles) {
    this->angles = vec3d_add(this->angles, angles);
}

Vec3d camera_get_position(Camera *this) {
    return this->position;
}

Vec3d camera_get_angles(Camera *this) {
    return this->angles;
}

void camera_set_position(Camera *this, Vec3d position) {
    this->position = position;
}

void camera_set_angles(Camera *this, Vec3d angles) {
    this->angles = angles;
}
