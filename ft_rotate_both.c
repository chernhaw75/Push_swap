/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate_both.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchern-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 09:12:41 by tchern-h          #+#    #+#             */
/*   Updated: 2026/11/11 09:20:30 by tchern-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "push_swap.h"

static void	rot_one(int *s, int size)
{
	int	first;
	int	i;

	first = s[0];
	i = 0;
	while (i < size - 1)
	{
		s[i] = s[i + 1];
		i++;
	}
	s[size - 1] = first;
}

void	rotate_both(int *a, int *b, int size_a, int size_b)
{
	if (size_a < 2 || size_b < 2)
		return ;
	rot_one(a, size_a);
	rot_one(b, size_b);
	g_ops[RR]++;
	write(1, "rr\n", 3);
}
