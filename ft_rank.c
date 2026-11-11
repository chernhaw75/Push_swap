/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rank.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchern-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 09:11:43 by tchern-h          #+#    #+#             */
/*   Updated: 2026/11/11 09:12:05 by tchern-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>

static int	count_smaller(int *a, int size, int val)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < size)
	{
		if (a[i] < val)
			count++;
		i++;
	}
	return (count);
}

int	rank_values(int *a, int size)
{
	int	*r;
	int	i;

	r = malloc(sizeof(int) * size);
	if (!r)
		return (0);
	i = 0;
	while (i < size)
	{
		r[i] = count_smaller(a, size, a[i]);
		i++;
	}
	i = 0;
	while (i < size)
	{
		a[i] = r[i];
		i++;
	}
	free(r);
	return (1);
}