#include "malloc.h"

int head_page_type(t_hdata *page) {
    if (g_zone[TINY] == page) {
        return TINY;
    }
    if (g_zone[SMALL] == page) {
        return SMALL;
    }
    if (g_zone[LARGE] == page) {
        return LARGE;
    }
    return -1;
}

void    free_page(t_hdata *page) {
    if (!page->prev && !page->next) {
        return;
    }

    if (page->prev) {
        page->prev->next = page->next;
        if (page->next) {
            page->next->prev = page->prev;
        }
    } else if (!page->prev && page->next) {
        g_zone[head_page_type(page)] = page->next;
        page->next->prev = NULL;
    }
    munmap((void*)page, page->total_size);
}



t_hdata    *get_new_page(size_t size) {
    t_hdata *ptr;
    size_t  hsize;

    hsize = ALIGN_HEAP_SIZE(size);
    ptr = (t_hdata *)mmap(NULL, hsize + sizeof(t_hdata),
		PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (ptr == MAP_FAILED)
		return (NULL);
    memset(ptr, 0, sizeof(t_hdata));
    ptr->total_size = hsize;
    ptr->free_size = hsize - sizeof(t_hdata);
    return (ptr);
}

t_hdata   *get_valid_page(const t_hdata *head, size_t size) {
    t_hdata *temp;

    temp = (t_hdata *)head;
    while (temp) {
        if (temp->free_size > size) {
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
	return (t_bdata *)(FORWARD_SHIFT_BLOCK_METADATA(last) + last->data_size);
}

t_bdata  *get_valid_block(t_bdata *head) {
    t_bdata *last = head;
    t_bdata *new_block;
    printf("current block\n");
    printf("%zu\n", last->data_size);
    printf("%d\n", last->free);
    printf("%p\n", last->next);
    if (last->free) {
        return (last);
    }

    while (last->next) {
        if (last->free == true) {
            return (last);
        }
        if (last->next) {
		    last = last->next;
        }
    }
    new_block = (t_bdata *)(FORWARD_SHIFT_BLOCK_METADATA(last) + last->data_size);
    last->next = new_block;
    new_block->prev = last;
    new_block->next = NULL;
    new_block->zone->block_count += 1;
    return new_block;
}

t_bdata  *init_block(t_hdata *page, size_t size) {
    t_bdata *head;

    head = (t_bdata *)FORWARD_SHIFT_HEAP_METADATA(page);
    memset(head, 0, sizeof(t_bdata));
    head->zone = page;
    head->zone->block_count += 1;
    head->zone->free_size -= size;
    head->next = NULL;
    head->prev = NULL;
    head->free = false;
    head->data_size = size - sizeof(t_bdata);
    head->total_size = head->data_size;
    return (head);
}

t_bdata *add_new_block(t_bdata *head) {
    t_bdata *last = head;
    t_bdata *new_block = NULL;

    while (last->next) {
		last = last->next;
    }
    new_block = (t_bdata *)(FORWARD_SHIFT_BLOCK_METADATA(last) + last->total_size);
    memset(new_block, 0, sizeof(t_bdata));
    new_block->prev = last;
    new_block->next = last->next;
    last->next = new_block;
    return new_block;
}

t_bdata *get_free_block(t_bdata *head, size_t size) {
    if (head->free && head->total_size >= size) {
        if (!head->next) {
            head->total_size = size;
        }
        return (head);
    }

    t_bdata *last = head;
    while (last->next) {
        if (last->free == true && last->total_size >= size) {
            return (last);
        }
        if (last->next) {
		    last = last->next;
        }
    }
    return (NULL);
}


t_bdata *get_page_block(t_hdata *page, size_t size) {
    t_bdata *head;
    t_bdata *valid_block = NULL;
    size_t data_size;

    head = (t_bdata *)FORWARD_SHIFT_HEAP_METADATA(page);
    data_size = size - sizeof(t_bdata);
    if (page->block_count && page->free_size > size) {
        valid_block = get_free_block(head, data_size);
        if (!valid_block) {
            valid_block = add_new_block(head);
            valid_block->total_size = data_size;
            valid_block->zone = page;
            valid_block->zone->free_size -= size;
            valid_block->zone->block_count += 1;
        }
    }
    valid_block->free = false;
    valid_block->data_size = data_size;
    printf("new block\n");
    printf("%d\n", valid_block->free);
    printf("%zu\n", valid_block->data_size);
    printf("%p\n", valid_block->prev);
    printf("%p\n", valid_block->next);
    return (valid_block);
}

void   *mmalloc(size_t size) {
    t_hdata *head;
    t_hdata *page;
    t_bdata *block;
    int     htype;


    htype = ALIGN_BLOCK_TYPE(size);
    head = g_zone[htype];
    page = get_valid_page(head, size);
    if (!page) {
        page = get_new_page(size);
        if (!page) {
            return (NULL);
        }
        block = init_block(page, size);
        reset_heap_head(head, page, htype); 
    } else {
        block = get_page_block(page, size);
    }
    if (block) {
        printf("Block address %p\n", block);
        return (FORWARD_SHIFT_BLOCK_METADATA(block));
    }
    return (NULL);
}