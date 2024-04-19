/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanykei <kanykei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 07:53:56 by ktashbae          #+#    #+#             */
/*   Updated: 2024/04/19 17:06:06 by kanykei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_sizeofnum(unsigned long num, size_t base)
{
	size_t	b;

	if ((num / base) == 0)
		b = 1;
	else
		b = 1 + ft_sizeofnum(num / base, base);
	return (b);
}

static void	ft_base_set(char *base, unsigned long num, size_t n)
{
	size_t	b;

	b = ft_strlen(base);
	if (num >= (unsigned long int)b)
		ft_base_set(base, num / b, n - 1);
	ft_putchar_fd(base[num % b], STDOUT_FILENO);
}

void	ft_itoa_base(unsigned long num, char *base)
{
	size_t	n;
	size_t	b;

	b = ft_strlen(base);
	n = ft_sizeofnum(num, b);
	ft_base_set(base, num, n);
}
