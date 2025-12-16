#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct Vec {
    size_t len;
    size_t capacity;
    size_t elem_size;
    uint8_t *data;
    bool is_static;
} Vec;

Vec vec_from_static(size_t elem_size, void *buff, size_t buff_len_elems);
int vec_push(Vec *this, const void *elem);
void* vec_get(Vec *this, size_t index);
size_t vec_len(Vec *this);
size_t vec_elem_size(Vec *this);
/* vec_len(...)*vec_elem_size(...) */
size_t vec_size_bytes(Vec *this);
void vec_drop(Vec *this);
