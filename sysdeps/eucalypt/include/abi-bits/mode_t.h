#pragma once
#include <stdint.h>

typedef uint32_t mode_t;

#define S_IFREG  0  // regular file
#define S_IFDIR  1  // directory
#define S_IFBLK  2  // block device
#define S_IFMNT  3  // mountpoint
#define S_IFLNK  4  // symbolic link
#define S_IFIFO  5  // pipe/FIFO

#define S_ISREG(m)  ((m) == S_IFREG)
#define S_ISDIR(m)  ((m) == S_IFDIR)
#define S_ISBLK(m)  ((m) == S_IFBLK)
#define S_ISLNK(m)  ((m) == S_IFLNK)
#define S_ISFIFO(m) ((m) == S_IFIFO)