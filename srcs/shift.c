/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanykei <kanykei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:25:33 by kanykei           #+#    #+#             */
/*   Updated: 2024/04/07 17:28:12 by kanykei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

inline void	*forward_shift_heap_metadata(void *ptr)
{
	return ((void *)(ptr + sizeof(t_hdata)));
}

inline void	*forward_shift_block_metadata(void *ptr)
{
	return ((void *)(ptr + sizeof(t_bdata)));
}

inline void	*backward_shift_block_metadata(void *ptr)
{
	return ((void *)(ptr - sizeof(t_bdata)));
}
