/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_medium_pull.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchern-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 09:12:41 by tchern-h          #+#    #+#             */
/*   Updated: 2026/11/11 09:20:30 by tchern-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_idx_of(int *b, int v)
{
	int	i;

	i = 0;
	while (b[i] != v)
		i++;
	return (i);
}

int	ft_dist(int idx, int size)
{
	if (idx <= size / 2)
		return (idx);
	return (size - idx);
}

void	ft_bring_to_top_b(t_st *s, int idx)
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
void	ft_pull_back(t_st *s)
{
	int	i1;
	int	i2;

	while (s->sb > 0)
	{
		i1 = ft_idx_of(s->b, s->sb - 1);
		i2 = -1;
		if (s->sb > 1)
			i2 = ft_idx_of(s->b, s->sb - 2);
		if (i2 >= 0 && ft_dist(i2, s->sb) + 1 < ft_dist(i1, s->sb))
		{
			ft_bring_to_top_b(s, i2);
			pa(s->a, s->b, &s->sa, &s->sb);
			ft_bring_to_top_b(s, ft_idx_of(s->b, s->sb));
			pa(s->a, s->b, &s->sa, &s->sb);
			sa(s->a);
		}
		else
		{
			ft_bring_to_top_b(s, i1);
			pa(s->a, s->b, &s->sa, &s->sb);
		}
	}
}
