#include "malloc.h"


t_hdata    *get_new_page(size_t size) {
    t_hdata *ptr;
    size_t  hsize;

    hsize = ALIGN_HEAP_SIZE(size);
    ptr =(t_hdata *)mmap(NULL, hsize,
		PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (ptr == MAP_FAILED)
		return (NULL);
    ft_memset(ptr, 0, sizeof(t_hdata));
    ptr->total_size = hsize;
    ptr->free_size = hsize - sizeof(t_hdata);
    return (ptr);
}

t_hdata   *get_valid_page(const t_hdata *head, size_t size) {
    t_hdata *temp;

    temp = (t_hdata *)head;
    while (temp) {
        if (temp->free_size >= size) {
            return (temp);
        }
        temp = temp->next;
    }
    return (NULL);
}

t_bdata    *get_end_of_last_block(t_bdata *head) {
    t_bdata *last = head;

    while (last->next) {
		last = last->next;
    }
	return (t_bdata *)SHIFT_BLOCK_METADATA(last) + last->data_size;
}

t_bdata  *get_valid_block(t_bdata *head) {
    t_bdata *last = head;
    t_bdata *new_block;

    while (last->next) {
        if (last->free == true) {
            return (last);
        }
		last = last->next;
    }
    new_block = (t_bdata *)SHIFT_BLOCK_METADATA(last) + last->data_size;
    new_block->prev = last;
    new_block->next = NULL;
    return new_block;
}

t_bdata  *init_block(t_bdata *head) {
    head->next = NULL;
    head->prev = NULL;
    return (head);
}


t_bdata *get_page_block(t_hdata *page, size_t size) {
    t_bdata *current_block;

    current_block = (t_bdata *)SHIFT_HEAP_METADATA(page);
    if (page->block_count && page->free_size <= size) {
        current_block = get_valid_block(current_block);
    } else {
        current_block = init_block(current_block);
    }
    current_block->free = false;
    current_block->data_size = size - sizeof(t_bdata);
    page->free_size -= size;
    return (current_block);
}

void   *mmalloc(size_t size) {
    t_hdata *head;
    t_hdata *page;
    t_bdata *block;
    int     htype;

    htype = ALIGN_HEAP_TYPE(size);
    head = g_heap[htype];
    page = get_valid_page(head, size);
    if (!page) {
        page = get_new_page(size + sizeof(t_hdata));
        reset_heap_head(head, page, htype); 
    }
    block = get_page_block(page, size);
    printf("block status %d\n", block->free);
    printf("block size %zu\n", block->data_size);
    return (SHIFT_BLOCK_METADATA(block));

}