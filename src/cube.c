#include "cube.h"
#include "mat.h"

#define _USE_MATH_DEFINES
#include <math.h>

ResultCube cube_new(const Texture *textures[], Rect rects[]) {
    Cube cube;
    cube.transform = transform_new();

    struct FaceTransform {
        GLfloat angle;
        Vec3 axis;
    } face_transform[6] = {
        { .angle = 0.0f,
          .axis = vec3(1, 1, 1) },
        { .angle =  (float)M_PI_2,
          .axis = vec3(0, 1, 0) },
        { .angle =  (float)M_PI,
          .axis = vec3(0, 1, 0) },
        { .angle = -(float)M_PI_2,
          .axis = vec3(0, 1, 0) },
        { .angle = -(float)M_PI_2,
          .axis = vec3(1, 0, 0) },
        { .angle =  (float)M_PI_2,
          .axis = vec3(1, 0, 0) }
    };
    for (int i = 0; i < 6; i++) {
        cube.face[i] = try(sprite_new(textures[i], rects[i]),
                           (ResultCube)Err(), "Failed to init cube face");
        cube.face[i].transform = transform_rotate(&cube.face[i].transform,
                                                  face_transform[i].angle, face_transform[i].axis);
        cube.face[i].transform = transform_translate(&cube.face[i].transform, vec3(0, 0, 0.499f));
    }
    return (ResultCube)Ok(cube);
}

void cube_draw(Cube *this, const SceneDrawCtx *dctx, const Transform *transform) {
    Transform t = transform_apply(transform, &this->transform);
    for (int i = 0; i < 6; i++) {
        sprite_draw(&this->face[i], dctx, &t);
    }
}

void cube_drop(Cube *this) {
    for (int i = 0; i < 6; i++) {
        sprite_drop(&this->face[i]);
    }
}
