#pragma once

#include "log.h"

#include <stdbool.h>

#define rci(cond, code, ...) if (cond) { loge(__VA_ARGS__); return (code); }
#define rcic(cond, code, code_block, ...) \
    if (cond) { loge(__VA_ARGS__); code_block; return (code); }
#define reci(cond, ...) rci(cond, -1, ##__VA_ARGS__)

#define decl_result(name_suffix, val_type) \
    typedef struct Result ##name_suffix { bool is_err; val_type val; } Result ##name_suffix

#define Ok(value) { .is_err = false, .val = (value) }

#define Err() { .is_err = true }

#define try(result, rc, ...) ({          \
    __typeof__(result) res = (result);   \
    rci(res.is_err, rc, ##__VA_ARGS__);  \
    res.val;                             \
})

#define tryc(result, rc, code_block, ...) ({          \
    __typeof__(result) res = (result);                \
    rcic(res.is_err, rc, code_block, ##__VA_ARGS__);  \
    res.val;                                          \
})
