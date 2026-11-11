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

typedef struct s_st
{
	int	*a;
	int	*b;
	int	sa;
	int	sb;
}	t_st;

static int	ft_chunk(int size)
{
	if (size > 100)
		return (size / 14 + 1);
	return (size / 7 + 1);
}

static void	push_one(t_st *s, int *pend, int pushed, int chunk)
{
	if (*pend)
		rotate_b(s->b, s->sb);
	*pend = 0;
	pb(s->a, s->b, &s->sa, &s->sb);
	if (s->b[0] < pushed + chunk / 8 && s->sb > 1)
		*pend = 1;
}

/*
** Phase 1: push a to b chunk by chunk (by rank). The lowest values of the
** chunk (below chunk / 8) are rotated to the bottom of b. A pending rb is
** merged with the next ra into a single rr when possible.
*/
static void	push_chunks(t_st *s, int chunk)
{
	int	pushed;
	int	pend;

	pushed = 0;
	pend = 0;
	while (s->sa > 0)
	{
		if (s->a[0] < pushed + chunk)
			push_one(s, &pend, pushed++, chunk);
		else if (pend && s->sa > 1)
		{
			rotate_both(s->a, s->b, s->sa, s->sb);
			pend = 0;
		}
		else
			rotate_a(s->a, s->sa);
	}
	if (pend)
		rotate_b(s->b, s->sb);
}

static int	idx_of(int *b, int v)
{
	int	i;

	i = 0;
	while (b[i] != v)
		i++;
	return (i);
}

static int	dist(int idx, int size)
{
	if (idx <= size / 2)
		return (idx);
	return (size - idx);
}

static void	bring_to_top_b(t_st *s, int idx)
{
	if (idx <= s->sb / 2)
		while (idx-- > 0)
			rotate_b(s->b, s->sb);
	else
		while (idx++ < s->sb)
			reverse_rotate_b(s->b, s->sb);
}

/*
** Phase 2: b holds ranks 0..sb-1. Take the max (rank sb-1), or when the
** second max is clearly closer take it first, then the max, then sa.
*/
static void	pull_back(t_st *s)
{
	int	i1;
	int	i2;

	while (s->sb > 0)
	{
		i1 = idx_of(s->b, s->sb - 1);
		i2 = -1;
		if (s->sb > 1)
			i2 = idx_of(s->b, s->sb - 2);
		if (i2 >= 0 && dist(i2, s->sb) + 1 < dist(i1, s->sb))
		{
			bring_to_top_b(s, i2);
			pa(s->a, s->b, &s->sa, &s->sb);
			bring_to_top_b(s, idx_of(s->b, s->sb));
			pa(s->a, s->b, &s->sa, &s->sb);
			sa(s->a);
		}
		else
		{
			bring_to_top_b(s, i1);
			pa(s->a, s->b, &s->sa, &s->sb);
		}
	}
}

void	ft_medium_sort(int *a, int *b, int size)
{
	t_st	s;

	if (!rank_values(a, size))
		return ;
	s.a = a;
	s.b = b;
	s.sa = size;
	s.sb = 0;
	push_chunks(&s, ft_chunk(size));
	pull_back(&s);
}
