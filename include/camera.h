#pragma once

#include "gl.h"
#include "result.h"
#include "vecn.h"
#include "transform.h"
#include "scene.h"

typedef struct Camera {
    Vec3 pos;
    Vec3 angles;
    GLfloat fov;
    GLfloat aspect_ration;
    GLfloat near_z;
    GLfloat far_z;
} Camera;

typedef struct CameraOptions {
    Vec3 position;
    Vec3 angles; // (pitch, yaw, roll)
    GLfloat fov;
    GLfloat aspect_ration;
    GLfloat near_z;
    GLfloat far_z;
} CameraOptions;

decl_result(Camera, Camera);

ResultCamera camera_new(CameraOptions ops);
Transform camera_get_transform(const Camera *this);
void camera_movevd(Camera *this, Vec3 delta);
void camera_rotated(Camera *this, Vec3 angles);
Vec3 camera_get_position(const Camera *this);
Vec3 camera_get_angles(const Camera *this);
Vec3 camera_get_dir(const Camera *this);
void camera_set_position(Camera *this, Vec3 position);
void camera_set_angles(Camera *this, Vec3 angles);
GLfloat camera_get_fov(const Camera *this);
void camera_set_fov(Camera *this, GLfloat fov);
