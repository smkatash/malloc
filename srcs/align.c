/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   align.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanykei <kanykei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:19:46 by kanykei           #+#    #+#             */
/*   Updated: 2024/04/29 00:03:44 by kanykei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

inline size_t	align_heap_size(size_t size)
{
	if (size <= TINY_BLOCK_SIZE)
	{
		return (TINY_HEAP_SIZE);
	}
	if (size <= SMALL_BLOCK_SIZE)
	{
		return (SMALL_HEAP_SIZE);
	}
	return (LARGE_HEAP_SIZE);
}

inline size_t	align_heap_type(size_t size)
{
	if (size <= TINY_HEAP_SIZE)
	{
		return (TINY);
	}
	if (size <= SMALL_HEAP_SIZE)
	{
		return (SMALL);
	}
	return (LARGE);
}

inline size_t	align_block_size(size_t size)
{
	if (size <= TINY)
	{
		return (TINY_BLOCK_SIZE);
	}
	if (size <= SMALL)
	{
		return (SMALL_BLOCK_SIZE);
	}
	return (LARGE_HEAP_SIZE);
}

inline size_t	align_block_type(size_t size)
{
	if (size <= TINY_BLOCK_SIZE)
	{
		return (TINY);
	}
	if (size <= SMALL_BLOCK_SIZE)
	{
		return (SMALL);
	}
	return (LARGE);
}
