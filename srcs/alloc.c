/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanykei <kanykei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 16:25:52 by kanykei           #+#    #+#             */
/*   Updated: 2024/04/11 10:35:00 by kanykei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	reset_zone_head(t_hdata *curr_page, t_hdata *new_page, int htype)
{
	new_page->next = curr_page;
	if (curr_page)
	{
		new_page->next->prev = new_page;
	}
	g_zone[htype] = new_page;
}

static t_bdata	*alloc_new_page_block(t_hdata *head, size_t size, int htype)
{
	t_hdata	*page;
	t_bdata	*block;

	page = get_new_page(size);
	if (page)
	{
		block = init_block(page, size);
		reset_zone_head(head, page, htype);
		return (block);
	}
	return (NULL);
}

static t_bdata	*get_valid_page_block(t_hdata *head, size_t size)
{
	t_hdata	*page;
	t_bdata	*block;

	page = get_valid_page(head, size);
	if (page)
	{
		block = get_page_block(page, size);
		return (block);
	}
	return (NULL);
}

void	*alloc(size_t size)
{
	int		htype;
	t_hdata	*head;
	t_bdata	*block;

	htype = align_block_type(size);
	head = g_zone[htype];
	block = get_valid_page_block(head, size);
	if (!block)
	{
		block = alloc_new_page_block(head, size, htype);
	}
	if (block)
	{
		return (forward_shift_block_metadata(block));
	}
	return (NULL);
}
