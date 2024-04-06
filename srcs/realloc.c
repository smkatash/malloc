#include "malloc.h"

void *realloc(void *ptr, size_t size) {
    if (!ptr || !size || size >= SIZE_MAX) {
        return (NULL);
    }

    void *new_address = mmalloc(size + sizeof(t_bdata));
    ft_memcpy(new_address, ptr, size);
    free(ptr);
    return new_address;
}