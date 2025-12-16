#include "vec.h"
#include "result.h"

#include <string.h>

Vec vec_from_static(size_t elem_size, void *buff, size_t buff_len_elems) {
    return (Vec) {
        .data = buff,
        .capacity = buff_len_elems,
        .elem_size = elem_size,
        .len = 0,
        .is_static = true
    };
}

int vec_push(Vec *this, const void *elem) {
    reci(this->is_static && this->len >= this->capacity, "Static vector overflow");
    memcpy(&this->data[this->len * this->elem_size], elem, this->elem_size);
    this->len++;
    return 0;
}

void* vec_get(Vec *this, size_t index) {
    return (void*)&this->data[index * this->elem_size];
}

size_t vec_len(Vec *this) {
    return this->len;
}

size_t vec_elem_size(Vec *this) {
    return this->elem_size;
}

size_t vec_size_bytes(Vec *this) {
    return this->elem_size * this->len;
}

void vec_drop(Vec *this) {
    if (!this->is_static) {
        loge("Unexpected vec type");
    }
    this->capacity = 0;
    this->data = NULL;
    this->elem_size = 0;
    this->is_static = false;
    this->len = 0;
}
