/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanykei <kanykei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 16:25:52 by kanykei           #+#    #+#             */
/*   Updated: 2024/04/07 17:15:56 by kanykei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	reset_zone_head(t_hdata *curr_page, t_hdata *new_page, int htype)
{
	new_page->next = curr_page;
	if (curr_page != NULL)
	{
		new_page->next->prev = new_page;
	}
	g_zone[htype] = new_page;
}

void	*alloc(size_t size)
{
	int		htype;
	t_hdata	*head;
	t_hdata	*page;
	t_bdata	*block;

	htype = align_block_type(size);
	head = g_zone[htype];
	page = get_valid_page(head, size);
	if (!page)
	{
		page = get_new_page(size);
		if (!page)
		{
			return (NULL);
		}
		block = init_block(page, size);
		reset_zone_head(head, page, htype);
	}
	else
	{
		block = get_page_block(page, size);
	}
	if (block)
	{
		return (forward_shift_block_metadata(block));
	}
	return (NULL);
}
