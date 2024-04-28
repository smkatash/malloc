/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanykei <kanykei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 16:25:52 by kanykei           #+#    #+#             */
/*   Updated: 2024/04/29 00:56:10 by kanykei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_bdata	*merge_next_free_block(t_bdata *current_block)
{
	size_t	free_size;

	if (current_block->next && current_block->next->free)
	{
		free_size = current_block->next->total_size + sizeof(t_bdata);
		current_block->total_size += free_size;
		current_block->data_size += free_size;
		current_block->zone->free_size += free_size;
		current_block->zone->block_count -= 1;
		current_block->next = current_block->next->next;
		if (current_block->next)
		{
			current_block->next->prev = current_block;
		}
	}
	return (current_block);
}

static void	merge_free_blocks(t_bdata *current_block)
{
	current_block = merge_next_free_block(current_block);
	if (current_block->prev && current_block->prev->free)
	{
		current_block = merge_next_free_block(current_block->prev);
	}
	if (!current_block->prev && !current_block->next && current_block->free)
	{
		free_page(current_block->zone);
	}
}

bool	valid_block(void *ptr, t_hdata *zone)
{
	t_bdata	*block;
	void	*temp_ptr;

	block = (t_bdata *)forward_shift_heap_metadata(zone);
	temp_ptr = NULL;
	while (block)
	{
		temp_ptr = (forward_shift_block_metadata(block));
		if (ptr == temp_ptr)
		{
			return (true);
		}
		block = block->next;
	}
	return (false);
}

void	free(void *ptr)
{
	t_bdata	*block;

	if (!ptr)
	{
		return ;
	}
	block = (t_bdata *)backward_shift_block_metadata(ptr);
	if (!block->free && block->zone && valid_block(ptr, block->zone))
	{
		block->free = true;
		block->zone->free_size += block->total_size + sizeof(t_bdata);
		merge_free_blocks(block);
	}
}
