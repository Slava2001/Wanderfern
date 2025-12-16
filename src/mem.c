// #define LOG_LVL DBG
#include "mem.h"

#include <stdlib.h>

static size_t allocated_blocks = 0;

ResultVoidPtr mem_alloc(size_t size) {
    void *ptr = malloc(size);
    rci(!ptr, (ResultVoidPtr)Err(), "Failed to allocate %zu bytes", size);
    logd("Allocate %zu bytes, addres: 0x%p", size, ptr);
    allocated_blocks++;
    return (ResultVoidPtr)Ok(ptr);
}

void mem_free(void *ptr) {
    free(ptr);
    allocated_blocks--;
    logd("Free addres: 0x%p", ptr);
}

size_t mem_used() {
    return allocated_blocks++;
}
