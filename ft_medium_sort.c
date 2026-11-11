/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_medium_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchern-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 09:12:41 by tchern-h          #+#    #+#             */
/*   Updated: 2026/11/11 09:20:30 by tchern-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	ft_isqrt(int n)
{
	int	r;

	r = 1;
	while ((r + 1) * (r + 1) <= n)
		r++;
	return (r);
}

/*
** Phase 1: move everything from a to b, one rank-chunk at a time.
** If a[0] is inside the current window [0, pushed + chunk), push it.
** Values in the lower half of the window go to the bottom of b (rotate_b),
** so the bigger ones stay near the top of b.
** Otherwise rotate a to look at the next element.
*/
static void	push_chunks(int *a, int *b, int size)
{
	int	size_a;
	int	size_b;
	int	chunk;
	int	pushed;

	size_a = size;
	size_b = 0;
	chunk = ft_isqrt(size);
	pushed = 0;
	while (size_a > 0)
	{
		if (a[0] < pushed + chunk)
		{
			pb(a, b, &size_a, &size_b);
			if (b[0] < pushed + chunk / 2 && size_b > 1)
				rotate_b(b, size_b);
			pushed++;
		}
		else
			rotate_a(a, size_a);
	}
}

static int	max_index(int *b, int size_b)
{
	int	i;

	i = 0;
	while (b[i] != size_b - 1)
		i++;
	return (i);
}

static void	bring_max_to_top(int *b, int size_b, int idx)
{
	if (idx <= size_b / 2)
		while (idx-- > 0)
			rotate_b(b, size_b);
	else
		while (idx++ < size_b)
			reverse_rotate_b(b, size_b);
}

/*
** Phase 2: b holds ranks 0..size-1, so the current maximum is always the
** rank size_b - 1. Bring it to the top the short way and pa it.
*/
static void	pull_back(int *a, int *b, int size)
{
	int	size_a;
	int	size_b;

	size_a = 0;
	size_b = size;
	while (size_b > 0)
	{
		bring_max_to_top(b, size_b, max_index(b, size_b));
		pa(a, b, &size_a, &size_b);
	}
}

void	ft_medium_sort(int *a, int *b, int size)
{
	if (!rank_values(a, size))
		return ;
	push_chunks(a, b, size);
	pull_back(a, b, size);
}
