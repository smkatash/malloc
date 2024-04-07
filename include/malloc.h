/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanykei <kanykei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 16:25:52 by kanykei           #+#    #+#             */
/*   Updated: 2024/04/07 17:26:02 by kanykei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include "../libs/libft/libft.h"
# include <sys/mman.h>
# include <stdio.h>
# include <string.h> 
#include <stdbool.h>

# define TINY 0
# define SMALL 1
# define LARGE 2

# define TINY_HEAP_SIZE (size_t)getpagesize() // 16384
# define TINY_BLOCK_SIZE (size_t)(TINY_HEAP_SIZE / 128) // 128 KB
# define SMALL_HEAP_SIZE (size_t)(16 * getpagesize()) // 262144
# define SMALL_BLOCK_SIZE (size_t)(SMALL_HEAP_SIZE / 1024) // 256 KB
# define LARGE_HEAP_SIZE (size_t)(32 * getpagesize()) // 524288

/*
** For a pagesize of 16384 bytes
**
** TINY  - block < 128 bytes  - heap 16 KB
** SMALL - block < 1024 bytes - heap 128 KB
** LARGE - block > 1024 bytes
*/

typedef struct s_hdata
{
	struct s_hdata	*next;
	struct s_hdata	*prev;
	size_t			block_count;
	size_t			total_size;
	size_t			free_size;
}					t_hdata;

typedef struct s_bdata
{
	struct s_bdata	*next;
	struct s_bdata	*prev;
	t_hdata			*zone;
	bool			free;
	size_t			total_size;
	size_t			data_size;
}					t_bdata;

extern t_hdata		*g_zone[3];
void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);
void				free(void *ptr);
void				show_alloc_mem(void);
void				*alloc(size_t size);
void				free_page(t_hdata *page);
t_hdata				*get_new_page(size_t size);
t_hdata				*get_valid_page(const t_hdata *head, size_t size);
t_bdata				*get_page_block(t_hdata *page, size_t size);
t_bdata				*init_block(t_hdata *page, size_t size);
size_t				align_heap_size(size_t type);
size_t				align_heap_type(size_t size);
size_t				align_block_size(size_t type);
size_t				align_block_type(size_t size);
void				*forward_shift_heap_metadata(void *ptr);
void				*forward_shift_block_metadata(void *ptr);
void				*backward_shift_block_metadata(void *ptr);
#endif
