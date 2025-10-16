#pragma once

#include "stdio.h"

#define DBG 0
#define INFO 1
#define ERR 2
#define DISABLE 4

#ifndef LOG_LVL
#define LOG_LVL INFO
#endif

#define generic_log(lvl, ...) do {                                         \
    (void)fprintf(stderr, __FILE__":%d %s ["lvl"]: ", __LINE__, __func__); \
    (void)fprintf(stderr, ##__VA_ARGS__);                                  \
    (void)fprintf(stderr, "\n");                                           \
} while(0)

#if DBG >= LOG_LVL
#define logd(...) generic_log("Dbg ", ##__VA_ARGS__)
#else
#define logd(...)
#endif

#if INFO >= LOG_LVL
#define logi(...) generic_log("Info", ##__VA_ARGS__)
#else
#define logi(...)
#endif

#if ERR >= LOG_LVL
#define loge(...) generic_log("Err ", ##__VA_ARGS__)
#else
#define loge(...)
#endif
