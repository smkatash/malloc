/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanykei <kanykei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 16:25:52 by kanykei           #+#    #+#             */
/*   Updated: 2024/04/07 16:50:38 by kanykei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_bdata	*init_block(t_hdata *page, size_t size)
{
	t_bdata	*head;

	head = (t_bdata *)forward_shift_heap_metadata(page);
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

static t_bdata	*add_new_block(t_bdata *head)
{
	t_bdata	*last;
	t_bdata	*new_block;

	last = head;
	new_block = NULL;
	while (last->next)
	{
		last = last->next;
	}
	new_block = (t_bdata *)(forward_shift_block_metadata(last) \
	+ last->total_size);
	if (new_block)
	{
		memset(new_block, 0, sizeof(t_bdata));
		new_block->prev = last;
		new_block->next = last->next;
		last->next = new_block;
	}
	return (new_block);
}

static t_bdata	*get_free_block(t_bdata *head, size_t size)
{
	t_bdata	*last;

	if (head->free && head->total_size >= size)
	{
		if (!head->next)
		{
			head->total_size = size;
		}
		return (head);
	}
	last = head;
	while (last->next)
	{
		if (last->free == true && last->total_size >= size)
		{
			return (last);
		}
		if (last->next)
		{
			last = last->next;
		}
	}
	return (NULL);
}

t_bdata	*get_page_block(t_hdata *page, size_t size)
{
	t_bdata	*head;
	t_bdata	*valid_block;
	size_t	data_size;

	head = (t_bdata *)forward_shift_heap_metadata(page);
	data_size = size - sizeof(t_bdata);
	valid_block = NULL;
	if (page->block_count && page->free_size > size)
	{
		valid_block = get_free_block(head, data_size);
		if (!valid_block)
		{
			valid_block = add_new_block(head);
			valid_block->total_size = data_size;
			valid_block->zone = page;
			valid_block->zone->free_size -= size;
			valid_block->zone->block_count += 1;
		}
	}
	valid_block->free = false;
	valid_block->data_size = data_size;
	return (valid_block);
}
