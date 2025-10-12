#pragma once

#include "stdio.h"

#define DBG 0
#define INFO 1
#define ERR 2
#define DISABLE 4

#ifndef LOG_LVL
#define LOG_LVL INFO
#endif

#define __log(lvl, ...) do { \
    (void)fprintf(stderr, __FILE__":%d ["lvl"]: ", __LINE__); \
    (void)fprintf(stderr, ##__VA_ARGS__); \
} while(0)

#if DBG >= LOG_LVL
#define logd(msg) __log("Dbg ", msg)
#else
#define logd(msg)
#endif

#if INFO >= LOG_LVL
#define logi(msg) __log("Info", msg)
#else
#define logi(msg)
#endif

#if ERR >= LOG_LVL
#define loge(msg) __log("Err ", msg)
#else
#define loge(msg)
#endif

#define rci(cond, code, msg) if (cond) { loge(msg); return code; }
#define reci(cond, msg) rci(cond, -1, msg)

