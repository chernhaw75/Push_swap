/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_small_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchern-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 09:12:41 by tchern-h          #+#    #+#             */
/*   Updated: 2026/11/11 09:20:30 by tchern-h         ###   ########.fr       */
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

static void	sort_three(int *a)
{
	if (a[0] > a[1] && a[1] < a[2] && a[0] < a[2])
		sa(a);
	else if (a[0] > a[1] && a[1] > a[2])
	{
		sa(a);
		reverse_rotate_a(a, 3);
	}
	else if (a[0] > a[1] && a[1] < a[2])
		rotate_a(a, 3);
	else if (a[0] < a[1] && a[1] > a[2] && a[0] < a[2])
	{
		sa(a);
		rotate_a(a, 3);
	}
	else if (a[0] < a[1] && a[1] > a[2])
		reverse_rotate_a(a, 3);
}

static void	push_min(int *a, int *b, int *size_a, int *size_b)
{
	int	i;
	int	min;

	i = 1;
	min = 0;
	while (i < *size_a)
	{
		if (a[i] < a[min])
			min = i;
		i++;
	}
	if (min <= *size_a / 2)
		while (min-- > 0)
			rotate_a(a, *size_a);
	else
		while (min++ < *size_a)
			reverse_rotate_a(a, *size_a);
	pb(a, b, size_a, size_b);
}

void	ft_small_sort(int *a, int *b, int size)
{
	int	size_a;
	int	size_b;

	if (is_sorted(a, size))
		return ;
	size_a = size;
	size_b = 0;
	if (size == 2)
		sa(a);
	while (size_a > 3)
		push_min(a, b, &size_a, &size_b);
	if (size_a == 3 && !is_sorted(a, 3))
		sort_three(a);
	while (size_b > 0)
		pa(a, b, &size_a, &size_b);
}
