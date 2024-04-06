#ifndef MALLOC_H
#define MALLOC_H

# include "../libs/libft/libft.h"
# include <sys/mman.h>
# include <stdio.h>
#include <string.h> 
#include <stdbool.h>

# define TINY 0
# define SMALL 1
# define LARGE 2

# define TINY_HEAP_SIZE (size_t)getpagesize() // 16384
# define TINY_BLOCK_SIZE (size_t)(TINY_HEAP_SIZE / 128) // 128 KB
# define SMALL_HEAP_SIZE (size_t)(16 * getpagesize()) // 262144
# define SMALL_BLOCK_SIZE (size_t)(SMALL_HEAP_SIZE / 1024) // 256 KB
# define LARGE_HEAP_SIZE (size_t)(32 * getpagesize()) // 524288

# define ALIGN_HEAP_SIZE(type) \
    ((type) <= TINY_BLOCK_SIZE ? TINY_HEAP_SIZE : \
    ((type) <= SMALL_BLOCK_SIZE ? SMALL_HEAP_SIZE : \
    LARGE_HEAP_SIZE))

# define ALIGN_HEAP_TYPE(size) \
    ((size) <= TINY_HEAP_SIZE ? TINY: \
    ((size) <= SMALL_HEAP_SIZE ? SMALL : \
    LARGE))

# define ALIGN_BLOCK_SIZE(type) \
    ((type) <= TINY ? TINY_BLOCK_SIZE : \
    ((type) <= SMALL ? SMALL_BLOCK_SIZE : \
    LARGE_HEAP_SIZE))

# define ALIGN_BLOCK_TYPE(size) \
    ((size) <= TINY_BLOCK_SIZE ? TINY : \
    ((size) <= SMALL_BLOCK_SIZE ? SMALL : \
    LARGE))

# define FORWARD_SHIFT_HEAP_METADATA(ptr) ((void *)ptr + sizeof(t_hdata))
# define FORWARD_SHIFT_BLOCK_METADATA(ptr) ((void *)ptr + sizeof(t_bdata))
# define BACKWARD_SHIFT_BLOCK_METADATA(ptr) ((void *)ptr - sizeof(t_bdata))

/*
** For a pagesize of 16384 bytes
**
** TINY  - block < 128 bytes  - heap 16 KB
** SMALL - block < 1024 bytes - heap 128 KB
** LARGE - block > 1024 bytes
*/

typedef struct s_hdata {
    struct s_hdata       *next;
    struct s_hdata       *prev;
    size_t               block_count;
    size_t               total_size;
    size_t               free_size;
}                        t_hdata;

typedef struct s_bdata {
    struct s_bdata      *next;
    struct s_bdata      *prev;
    t_hdata             *zone;
    bool                free;
    size_t              total_size;
    size_t              data_size;
}                       t_bdata;

extern t_hdata  *g_zone[3];

void    *malloc(size_t size);
void    *realloc(void *ptr, size_t size);
void    free(void *ptr);
void    reset_heap_head(t_hdata *curr_page, t_hdata *new_page, int htype);
void    *mmalloc(size_t size);
void    free_page(t_hdata *page);
void    show_alloc_mem();

#endif