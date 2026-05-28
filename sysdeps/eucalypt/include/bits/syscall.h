#pragma once

#include <stdint.h>

#define SYS_READ    0
#define SYS_WRITE   1
#define SYS_OPEN    2
#define SYS_CLOSE   3
#define SYS_SEEK    4
#define SYS_STAT    5
#define SYS_MKDIR   6
#define SYS_RMDIR   7
#define SYS_UNLINK  8
#define SYS_READDIR 9
#define SYS_DUP     10
#define SYS_DUP2    11
#define SYS_TELL    12
#define SYS_FSTAT   13
#define SYS_GETPID  14
#define SYS_FORK    15
#define SYS_EXEC    16
#define SYS_EXIT    17
#define SYS_WAITPID 18

static inline uint64_t syscall(uint64_t num, uint64_t arg0, uint64_t arg1, uint64_t arg2) {
    uint64_t ret;
    __asm__ volatile (
        "int $0x80\n"
        : "=a" (ret)
        : "a" (num), "D" (arg0), "S" (arg1), "d" (arg2)
        : "memory"
    );
    return ret;
}