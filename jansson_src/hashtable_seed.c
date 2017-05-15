/* Generate sizeof(uint32_t) bytes of as random data as possible to seed
   the hash function.
*/

#ifdef HAVE_CONFIG_H
#include "jasson_private_config.h"
#endif

#include <stdint.h>
#include <stdio.h>
#include <time.h>

#ifdef HAVE_STDINT_H
#include <stdint.h>
#endif

#ifdef HAVE_FCNTL_H
#include <fcntl.h>
#endif

#ifdef HAVE_SCHED_H
#include <sched.h>
#endif

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#ifdef HAVE_SYS_STAT_H
#include <sys/stat.h>
#endif

#ifdef HAVE_SYS_TIME_H
#include <sys/time.h>
#endif

#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif

#if defined(_WIN32)
/* For GetModuleHandle(), GetProcAddress() and GetCurrentProcessId() */
#include <windows.h>
#endif

#include "jansson.h"


static uint32_t buf_to_uint32(char *data) {
    size_t i;
    uint32_t result = 0;

    for (i = 0; i < sizeof(uint32_t); i++)
        result = (result << 8) | (unsigned char)data[i];

    return result;
}


uint32_t hashtable_seed = 0x12345;



