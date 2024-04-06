#include "malloc.h"


void    debug_blocks(t_bdata *head) {
    t_bdata *current_block;
    size_t     i = 1;

    current_block = head;

    while (current_block) {
        printf("[ Block %zu ] size: %zu\n", i, current_block->data_size);
        printf("[ Block %zu ] total size: %zu\n", i, current_block->total_size);
        printf("[ Block %zu ] free: %s\n", i, current_block->free ? "true" : "false");
        printf("[ Block %zu ] next: %p\n", i, current_block->next);
        printf("[ Block %zu ] prev: %p\n", i, current_block->prev);
        current_block = current_block->next;
        i++;
    }
}


void    debug_zone(t_hdata *head) {
    t_bdata *blocks;
    size_t     i = 1;

    while (head) {
        printf("[ Zone %zu ] size: %zu\n", i, head->total_size);
        printf("[ Zone %zu ] free size: %zu\n", i, head->free_size);
        printf("[ Zone %zu ] blocks: %zu\n", i, head->block_count);
        blocks = FORWARD_SHIFT_HEAP_METADATA(head);
        debug_blocks(blocks);
        head = head->next;
        i++;
    }
}

// TINY : 0xA0000
// 0xA0020 - 0xA004A : 42 bytes
// 0xA006A - 0xA00BE : 84 bytes
// SMALL : 0xAD000
// 0xAD020 - 0xADEAD : 3725 bytes
// LARGE : 0xB0000
// 0xB0020 - 0xBBEEF : 48847 bytes
// Total : 52698 bytes

void     show_alloc_mem() {
    printf("TINY: %p\n", g_zone[TINY]);
    debug_zone(g_zone[TINY]);
    printf("SMALL: %p\n", g_zone[SMALL]);
    debug_zone(g_zone[SMALL]);
    printf("LARGE: %p\n", g_zone[LARGE]);
    debug_zone(g_zone[LARGE]);
}