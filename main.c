# include "include/malloc.h"
# include <stdio.h>
# include <string.h>


int main() {
    show_alloc_mem();
    ft_putstr_fd("\n", STDOUT_FILENO);
    char *str1 = malloc(10);
    show_alloc_mem();
    ft_putstr_fd("\n", STDOUT_FILENO);
    free(str1);
    show_alloc_mem();
    ft_putstr_fd("\n", STDOUT_FILENO);
    char *str2 = malloc(10000000000);
    show_alloc_mem();
    ft_putstr_fd("\n", STDOUT_FILENO);
    free(str2);
    show_alloc_mem();
}
