#pragma once

#include "log.h"

#include <stdbool.h>

#define rci(cond, code, msg) if (cond) { loge(msg); return (code); }

#define reci(cond, msg) rci(cond, -1, msg)


#define decl_result(name_suffix, val_type) \
    typedef struct Result ##name_suffix { bool is_err; val_type val; } Result ##name_suffix

#define Ok(value) { .is_err = false, .val = (value) }

#define Err() { .is_err = true }

#define try(result, rc, ...) ({          \
    __typeof__(result) res = (result);   \
    rci(res.is_err, rc, ##__VA_ARGS__);  \
    res.val;                             \
})
