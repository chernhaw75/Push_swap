/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bubble_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchern-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 10:29:33 by tchern-h          #+#    #+#             */
/*   Updated: 2026/11/09 10:29:56 by tchern-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	is_sorted(int *a, int size)
{
	int	i;

	i = 0;
	while (i < size - 1)
	{
		if (a[i] > a[i + 1])
			return (0);
		i++;
	}
	return (1);
}

static int	min_index(int *a, int size)
{
	int	i;
	int	min;

	i = 1;
	min = 0;
	while (i < size)
	{
		if (a[i] < a[min])
			min = i;
		i++;
	}
	return (min);
}

static void	bring_to_top(int *a, int size_a, int idx)
{
	if (idx <= size_a / 2)
		while (idx-- > 0)
			rotate_a(a, size_a);
	else
		while (idx++ < size_a)
			reverse_rotate_a(a, size_a);   /* your rra; name assumed */
}

void	ft_simple_sort(int *a, int *b, int size)
{
	int	size_a;
	int	size_b;

	if (is_sorted(a, size))
		return ;
	size_a = size;
	size_b = 0;
	while (size_a > 0)
	{
		bring_to_top(a, size_a, min_index(a, size_a));
		pb(a, b, &size_a, &size_b);
	}
	while (size_b > 0)
		pa(a, b, &size_a, &size_b);
}