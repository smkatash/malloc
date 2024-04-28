/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanykei <kanykei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 16:25:52 by kanykei           #+#    #+#             */
/*   Updated: 2024/04/28 23:05:11 by kanykei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_hdata	*g_zone[3] = {NULL, NULL, NULL};

void	*malloc(size_t size)
{
	void	*ptr;

	if (size >= SIZE_MAX)
	{
		return (NULL);
	}
	ptr = alloc(size + sizeof(t_bdata));
	return (ptr);
}
