#include <abi-bits/errno.h>
#include <bits/ensure.h>
#include <bits/syscall.h>
#include <mlibc/all-sysdeps.hpp>
#include <mlibc/tcb.hpp>
#include <string.h>

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
#define SYS_MMAP    19
#define SYS_MUNMAP  20

#define STUB() \
    ({ \
        __ensure(!"STUB function was called"); \
        __builtin_unreachable(); \
    })

namespace mlibc {

void Sysdeps<LibcPanic>::operator()() {
    sysdep<LibcLog>("!!! mlibc panic !!!");
    sysdep<Exit>(-1);
    __builtin_trap();
}

void Sysdeps<LibcLog>::operator()(const char *msg) {
    ssize_t unused;
    sysdep<Write>(2, msg, strlen(msg), &unused);
}

void Sysdeps<Exit>::operator()(int status) {
    syscall(SYS_EXIT, status);
    __builtin_unreachable();
}

int Sysdeps<TcbSet>::operator()(void *pointer) {
    uintptr_t thread_data = reinterpret_cast<uintptr_t>(pointer) + sizeof(Tcb);
    asm volatile("wrfsbase %0" :: "r"(thread_data));
    return 0;
}

int Sysdeps<Isatty>::operator()(int fd) {
    if (fd == 0 || fd == 1 || fd == 2)
        return 0;
    errno = ENOTTY;
    return ENOTTY;
}

int Sysdeps<Write>::operator()(int fd, const void *buf, size_t size, ssize_t *ret) {
    auto r = syscall(SYS_WRITE, fd, buf, size);
    if (r < 0) { errno = (int)-r; return -1; }
    *ret = (ssize_t)r;
    return 0;
}

int Sysdeps<Read>::operator()(int fd, void *buf, size_t size, ssize_t *ret) {
    auto r = syscall(SYS_READ, fd, buf, size);
    if (r < 0) { errno = (int)-r; return -1; }
    *ret = (ssize_t)r;
    return 0;
}

int Sysdeps<Open>::operator()(const char *path, int flags, mode_t mode, int *fd) {
    (void)mode;
    auto r = syscall(SYS_OPEN, path, flags);
    if (r < 0) { errno = (int)-r; return -1; }
    *fd = (int)r;
    return 0;
}

int Sysdeps<Close>::operator()(int fd) {
    auto r = syscall(SYS_CLOSE, fd);
    if (r < 0) { errno = (int)-r; return -1; }
    return 0;
}

int Sysdeps<Seek>::operator()(int fd, off_t offset, int whence, off_t *new_offset) {
    auto r = syscall(SYS_SEEK, fd, offset, whence);
    if (r < 0) { errno = (int)-r; return -1; }
    *new_offset = (off_t)r;
    return 0;
}

int Sysdeps<AnonAllocate>::operator()(size_t size, void **pointer) {
    auto r = syscall(SYS_MMAP, (uint64_t)0, (uint64_t)size, (uint64_t)0);
    if ((int64_t)r < 0) {
        errno = ENOMEM;
        return ENOMEM;
    }
    *pointer = (void *)r;
    return 0;
}

int Sysdeps<AnonFree>::operator()(void *pointer, size_t size) {
    syscall(SYS_MUNMAP, (uint64_t)pointer, (uint64_t)size);
    return 0;
}

int Sysdeps<VmMap>::operator()(void *hint, size_t size, int prot, int flags,
                                int fd, off_t offset, void **window) {
    (void)prot; (void)flags; (void)fd; (void)offset;
    auto r = syscall(SYS_MMAP, (uint64_t)hint, (uint64_t)size, (uint64_t)0);
    if ((int64_t)r < 0) { errno = ENOMEM; return -1; }
    *window = (void *)r;
    return 0;
}

int Sysdeps<VmUnmap>::operator()(void *addr, size_t size) {
    syscall(SYS_MUNMAP, (uint64_t)addr, (uint64_t)size);
    return 0;
}

int Sysdeps<FutexWake>::operator()(int *, bool) { STUB(); }
int Sysdeps<FutexWait>::operator()(int *, int, timespec const *) { STUB(); }
int Sysdeps<ClockGet>::operator()(int, time_t *, long *) { STUB(); }

}