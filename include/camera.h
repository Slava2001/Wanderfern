#pragma once

#include "gl.h"
#include "result.h"
#include "vec.h"

typedef struct Camera {
    Vec3d position;
    Vec3d angles;
} Camera;

typedef struct CameraOptions {
    Vec3d position;
    Vec3d angles;
    GLdouble fov;
    GLdouble aspect;
    GLdouble near_z;
    GLdouble far_z;
} CameraOptions;

decl_result(Camera, Camera);

/**
 * @param position position (x, y, z)
 * @param angles Euler angles (yaw, pitch, roll)
 */
ResultCamera camera_new(CameraOptions ops);
void camera_set_view(Camera *this);
void camera_movevd(Camera *this, Vec3d delta);
void camera_rotated(Camera *this, Vec3d angles);
Vec3d camera_get_position(Camera *this);
Vec3d camera_get_angles(Camera *this);
void camera_set_position(Camera *this, Vec3d position);
void camera_set_angles(Camera *this, Vec3d angles);
