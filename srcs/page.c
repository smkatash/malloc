/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanykei <kanykei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 16:25:52 by kanykei           #+#    #+#             */
/*   Updated: 2024/04/29 01:05:55 by kanykei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int	head_page_type(t_hdata *page)
{
	if (g_zone[TINY] == page)
	{
		return (TINY);
	}
	if (g_zone[SMALL] == page)
	{
		return (SMALL);
	}
	if (g_zone[LARGE] == page)
	{
		return (LARGE);
	}
	return (-1);
}

void	free_page(t_hdata *page)
{
	if (!page->prev && !page->next)
	{
		return ;
	}
	if (page->prev)
	{
		page->prev->next = page->next;
		if (page->next)
		{
			page->next->prev = page->prev;
		}
	}
	else if (!page->prev && page->next)
	{
		g_zone[head_page_type(page)] = page->next;
		page->next->prev = NULL;
	}
	munmap((void *)page, page->total_size);
}

t_hdata	*get_valid_page(t_hdata *head, size_t size)
{
	t_hdata	*temp;
	
	temp = head;
	while (temp)
	{
		if (temp->free_size > size)
		{
			return (temp);
		}
		temp = temp->next;
	}
	return (NULL);
}

t_hdata	*get_new_page(size_t size)
{
	void	*ptr;
	t_hdata	*head;
	size_t	hsize;

	hsize = align_heap_size(size);
	if (hsize < size) {
		hsize = size;
	}
	ptr = mmap(NULL, hsize + sizeof(t_hdata), \
	PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (ptr == MAP_FAILED)
	{
		return (NULL);
	}
	head = (t_hdata *)ptr;
	memset(head, 0, sizeof(t_hdata));
	head->total_size = hsize + sizeof(t_hdata);
	head->free_size = hsize;
	return (head);
}
