#ifndef _ABIBITS_FD_SET_H
#define _ABIBITS_FD_SET_H

#define FD_SETSIZE 1024

typedef struct {
	unsigned long fds_bits[FD_SETSIZE / (8 * sizeof(unsigned long))];
} fd_set;

#define FD_ZERO(s) do { int __i; for (__i = 0; __i < (int)(FD_SETSIZE/(8*sizeof(unsigned long))); __i++) (s)->fds_bits[__i] = 0; } while (0)
#define FD_SET(d, s) ((s)->fds_bits[(d)/(8*sizeof(unsigned long))] |= (1UL << ((d)%(8*sizeof(unsigned long)))))
#define FD_CLR(d, s) ((s)->fds_bits[(d)/(8*sizeof(unsigned long))] &= ~(1UL << ((d)%(8*sizeof(unsigned long)))))
#define FD_ISSET(d, s) !!((s)->fds_bits[(d)/(8*sizeof(unsigned long))] & (1UL << ((d)%(8*sizeof(unsigned long)))))

#endif
