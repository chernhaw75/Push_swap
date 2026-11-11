/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_complex_sort.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchern-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 08:54:32 by tchern-h          #+#    #+#             */
/*   Updated: 2026/11/11 08:55:09 by tchern-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>

static int	bits_needed(int size)
{
	int	bits;

	bits = 0;
	while (((size - 1) >> bits) != 0)
		bits++;
	return (bits);
}

/*
** One radix pass on `bit`: bit 0 -> pb, bit 1 -> rotate_a. Then everything
** in b goes back to a. Stable, so lower bits stay ordered inside each group.
*/
static void	radix_pass(int *a, int *b, int size, int bit)
{
	int	size_a;
	int	size_b;
	int	i;

	size_a = size;
	size_b = 0;
	i = 0;
	while (i < size)
	{
		if ((a[0] >> bit) & 1)
			rotate_a(a, size_a);
		else
			pb(a, b, &size_a, &size_b);
		i++;
	}
	while (size_b > 0)
		pa(a, b, &size_a, &size_b);
}

void	ft_complex_sort(int *a, int *b, int size)
{
	int	bit;
	int	max_bits;

	if (!rank_values(a, size))
		return ;
	max_bits = bits_needed(size);
	bit = 0;
	while (bit < max_bits)
	{
		radix_pass(a, b, size, bit);
		bit++;
	}
}
