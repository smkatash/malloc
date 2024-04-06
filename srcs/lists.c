#include "malloc.h"

void    reset_heap_head(t_hdata *curr_page, t_hdata *new_page, int htype) {
    new_page->next = curr_page;
    if (curr_page != NULL) {
        new_page->next->prev = new_page;
    }
    g_zone[htype] = new_page;
}
