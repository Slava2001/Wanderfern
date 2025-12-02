#include "plant.h"

#define _USE_MATH_DEFINES
#include <math.h>

ResultPlant plant_new(Vec2 pos) {
    Plant plant;
    Transform t = transform_new();
    plant.transform = transform_translate(&t, vec3(pos.x, 0.5, pos.y));
    plant.texture = try(texture_load("assets/flower.png"),
                        (ResultPlant)Err(), "Failed to load texture");
    plant.sprite = tryc(sprite_new(plant.texture, rect_new(0, 0, 1, 1)), (ResultPlant)Err(),
                        { texture_drop(plant.texture); }, "Failed to create sprite");
    return (ResultPlant)Ok(plant);
}

void plant_draw(Plant *this, const SceneDrawCtx *dctx, const Transform *transform) {
    Transform t = transform_apply(transform, &this->transform);
        sprite_draw(&this->sprite, dctx, &t);
        t = transform_rotate(&t, (float)M_PI_2, vec3(0, 1, 0));
        sprite_draw(&this->sprite, dctx, &t);
}

void plant_drop(Plant *this) {
    sprite_drop(&this->sprite);
    texture_drop(this->texture);
    this->texture = NULL;
}
