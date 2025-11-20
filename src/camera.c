#define LOG_LVL INFO
#include "camera.h"
#define _USE_MATH_DEFINES
#include <math.h>

ResultCamera camera_new(CameraOptions ops) {
    return (ResultCamera)Ok(((Camera) {
        .pos = ops.position,
        .angles = ops.angles,
        .fov = ops.fov,
        .aspect_ration = ops.aspect_ration,
        .near_z = ops.near_z,
        .far_z = ops.far_z
    }));
}

void camera_movevd(Camera *this, Vec3 delta) {
    this->pos = vec3_add(this->pos, delta);
}

void camera_rotated(Camera *this, Vec3 angles) {
    this->pos = vec3_add(this->angles, angles);
}

Vec3 camera_get_position(const Camera *this) {
    return this->pos;
}

Vec3 camera_get_angles(const Camera *this) {
    return this->angles;
}

void camera_set_position(Camera *this, Vec3 position) {
    this->pos = position;
}

void camera_set_angles(Camera *this, Vec3 angles) {
    this->angles = angles;
}

Vec3 camera_get_dir(const Camera *this) {
    return vec3_normalize(vec3(cosf(this->angles.x) * cosf(this->angles.y),
                               sinf(this->angles.x),
                               cosf(this->angles.x) * sinf(this->angles.y)));
}

Transform camera_get_transform(const Camera *this) {
    logd("Camera: pos: (%+0.2f; %+0.2f; %+0.2f) angles: (%+0.2f; %+0.2f; %+0.2f)",
         this->pos.x, this->pos.y, this->pos.z,
         this->angles.x, this->angles.y, this->angles.z);
    Vec3 target = vec3_add(this->pos, camera_get_dir(this));
    Vec3 up = vec3(0,1,0);
    Transform t = transform_view_look_at(&t, this->pos, target, up);
    return transform_view_perspective(&t, this->fov, this->aspect_ration,
                                      this->near_z, this->far_z);
}

GLfloat camera_get_fov(const Camera *this) {
    return this->fov;
}

void camera_set_fov(Camera *this, GLfloat fov) {
    this->fov = fov;
}
