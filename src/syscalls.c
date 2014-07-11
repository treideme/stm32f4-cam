/**
 * @file syscalls.c System call implementations.
 * @author Thomas Reidemeister <treideme@gmail.com>
 * @addtogroup SYSCALLS
 * @{
 */

#include <sys/stat.h>
#include "stm32f4xx.h"

#include <errno.h>
#undef errno
//extern int errno;

int _getpid() {
    return 1;
}

/*
 kill
 Send a signal. Minimal implementation:
 */
int _kill(int pid, int sig) {
//    errno = EINVAL;
    return (-1);
}

int _close(int file) {
    return 0;
}

int _fstat(int file, struct stat *st) {
    return 0;
}

int _isatty(int file) {
    return 1;
}

int _lseek(int file, int ptr, int dir) {
    return 0;
}

int _open(const char *name, int flags, int mode) {
    return -1;
}

static int crlf_state = 0;

void syscalls_crlf_fix(int state) {
    crlf_state = state;
}

static int echo_state = 0;
void syscalls_echo(int state) {
    echo_state = state;
}

int _read(int file, char *ptr, int len) {
    if (file != 0) {
        return 0;
    }

    // Use USB CDC Port for stdin
//    while (!VCP_get_char((uint8_t*) ptr));

//    if (echo_state) {
//        VCP_put_char(*ptr);
//    }

    if (crlf_state && *ptr == '\r') {
        *ptr = '\n';
    }

    return 1;
}

/* Register name faking - works in collusion with the linker.  */
register char * stack_ptr asm ("sp");

caddr_t _sbrk_r(struct _reent *r, int incr) {
    extern char end asm ("end"); /* Defined by the linker.  */
    static char * heap_end;
    char * prev_heap_end;

    if (heap_end == NULL)
        heap_end = &end;

    prev_heap_end = heap_end;

    if (heap_end + incr > stack_ptr) {
        //errno = ENOMEM;
        return (caddr_t) -1;
    }

    heap_end += incr;

    return (caddr_t) prev_heap_end;
}

int _write(int file, char *ptr, int len) {
//    while (VCP_send_buffer((uint8_t*) ptr, len) != 0)
//        ;
    return len;
}

/** @} */
