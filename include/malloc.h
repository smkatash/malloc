#ifndef MALLOC_H
#define MALLOC_H

# include "../libs/libft/libft.h"
# include <sys/mman.h>
# include <stdio.h>

# define TINY 0
# define SMALL 1
# define LARGE 2

# define TINY_HEAP_SIZE (size_t)getpagesize()
# define TINY_BLOCK_SIZE (size_t)(TINY_HEAP_SIZE / 128)
# define SMALL_HEAP_SIZE (size_t)(16 * getpagesize())
# define SMALL_BLOCK_SIZE (size_t)(SMALL_HEAP_SIZE / 1024)
# define LARGE_HEAP_SIZE (size_t)(32 * getpagesize())

# define ALIGN_HEAP_SIZE(size) \
    ((size) <= TINY_BLOCK_SIZE ? TINY_HEAP_SIZE : \
    ((size) <= SMALL_BLOCK_SIZE ? SMALL_HEAP_SIZE : \
    LARGE_HEAP_SIZE))

# define ALIGN_HEAP_TYPE(size) \
    ((size) <= TINY_HEAP_SIZE ? TINY: \
    ((size) <= SMALL_HEAP_SIZE ? SMALL : \
    LARGE))

# define ALIGN_BLOCK_SIZE(type) \
    ((type) <= TINY ? TINY_BLOCK_SIZE : \
    ((type) <= SMALL ? SMALL_BLOCK_SIZE : \
    LARGE_HEAP_SIZE))

# define SHIFT_HEAP_METADATA(ptr) ((void *)ptr + sizeof(t_hdata))
# define SHIFT_BLOCK_METADATA(ptr) ((void *)ptr + sizeof(t_bdata))

typedef enum e_bool {
    false,
    true
} t_bool;

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
    t_bool              free;
    size_t              data_size;
}                       t_bdata;

extern t_hdata  *g_heap[3];

void    *malloc(size_t size);
void    reset_heap_head(t_hdata *curr_page, t_hdata *new_page, int htype);
void    *mmalloc(size_t size);

#endif