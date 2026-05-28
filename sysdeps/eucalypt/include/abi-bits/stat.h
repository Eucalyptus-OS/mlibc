#pragma once

#include <stdint.h>
#include "mode_t.h"

struct stat {
    char     st_name[256];  // matches MAX_NAME_LEN
    uint32_t st_type;
    uint32_t st_size;
    uint32_t st_flags;
};