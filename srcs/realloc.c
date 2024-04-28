/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanykei <kanykei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 16:25:52 by kanykei           #+#    #+#             */
/*   Updated: 2024/04/29 01:01:46 by kanykei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*realloc(void *ptr, size_t size)
{
	t_bdata	*block;
	void	*new_address;

	if (!ptr || !size || size >= SIZE_MAX)
	{
		return (NULL);
	}
	block = (t_bdata *)backward_shift_block_metadata(ptr);
	if (block->zone && valid_block(ptr, block->zone)) {
		new_address = alloc(size + sizeof(t_bdata));
		ft_memcpy(new_address, ptr, size);
		free(ptr);
		return (new_address);
	}
	return (NULL);
}
