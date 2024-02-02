#include "malloc.h"

t_hdata *g_heap[3] = { NULL };

void *malloc(size_t size) {
    (void)size;
    void *ptr;
    ptr = mmalloc(size + sizeof(t_bdata));
    printf("heap %zu", g_heap[0]->free_size);
    return ptr;
}