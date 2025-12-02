#pragma once

#include <stddef.h>
#include "result.h"

decl_result(VoidPtr, void *);

ResultVoidPtr mem_alloc(size_t size);
void mem_free(void *ptr);
size_t mem_used(void);
