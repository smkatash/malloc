/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanykei <kanykei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 16:25:52 by kanykei           #+#    #+#             */
/*   Updated: 2024/04/19 17:09:59 by kanykei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	show_ptr_address(void *ptr)
{
	ft_putstr_fd("0x", STDOUT_FILENO);
	ft_itoa_base((unsigned long)ptr, HEXIDECIMAL);
}

static size_t	show_blocks(t_bdata *head)
{
	t_bdata	*tmp;
	void	*start_addr;
	void	*end_addr;
	size_t	total_size;

	tmp = head;
	total_size = 0;
	while (tmp)
	{
		if (!tmp->free)
		{
			start_addr = forward_shift_block_metadata(tmp);
			end_addr = (void *)start_addr + tmp->data_size;
			show_ptr_address(start_addr);
			ft_putstr_fd(" - ", STDOUT_FILENO);
			show_ptr_address(end_addr);
			ft_putstr_fd(" : ", STDOUT_FILENO);
			ft_itoa_base((unsigned long)tmp->data_size, DECIMAL);
			ft_putstr_fd(" bytes\n", STDOUT_FILENO);
			total_size += tmp->data_size;
		}
		tmp = tmp->next;
	}
	return (total_size);
}

static size_t	show_zone(t_hdata *head)
{
	t_hdata	*tmp;
	t_bdata	*blocks;
	size_t	total_size;

	tmp = head;
	total_size = 0;
	while (tmp)
	{
		blocks = forward_shift_heap_metadata(tmp);
		total_size += show_blocks(blocks);
		tmp = tmp->next;
	}
	return (total_size);
}

void	show_alloc_mem(void)
{
	size_t	size;

	size = 0;
	ft_putstr_fd("TINY : ", STDOUT_FILENO);
	show_ptr_address(g_zone[TINY]);
	ft_putstr_fd("\n", STDOUT_FILENO);
	size += show_zone(g_zone[TINY]);
	ft_putstr_fd("SMALL : ", STDOUT_FILENO);
	show_ptr_address(g_zone[SMALL]);
	ft_putstr_fd("\n", STDOUT_FILENO);
	size += show_zone(g_zone[SMALL]);
	ft_putstr_fd("LARGE : ", STDOUT_FILENO);
	show_ptr_address(g_zone[LARGE]);
	ft_putstr_fd("\n", STDOUT_FILENO);
	size += show_zone(g_zone[LARGE]);
	ft_putstr_fd("Total : ", STDOUT_FILENO);
	ft_itoa_base((unsigned long)size, DECIMAL);
	ft_putstr_fd(" bytes\n", STDOUT_FILENO);
}
