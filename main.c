# include "include/malloc.h"
#include <stdio.h>



int main() {
    void *ptr = malloc(5);
    printf("Pointer %p\n", ptr);
}
