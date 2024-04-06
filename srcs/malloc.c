#include "malloc.h"

t_hdata *g_zone[3] = { NULL };

void *malloc(size_t size) {
    if (size >= SIZE_MAX) {
        return (NULL);
    }
    void *ptr = mmalloc(size + sizeof(t_bdata));
    return ptr;
}