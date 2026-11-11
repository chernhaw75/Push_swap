/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchern-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 13:46:35 by tchern-h          #+#    #+#             */
/*   Updated: 2026/11/07 14:50:38 by tchern-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "push_swap.h"

void	push(int *from, int *to, int *size_from, int *size_to)
{
	int	i;

	if (*size_from < 1)
		return ;
	i = *size_to;
	while (i > 0)
	{
		to[i] = to[i - 1];
		i--;
	}
	to[0] = from[0];
	i = 0;
	while (i < *size_from - 1)
	{
		from[i] = from[i + 1];
		i++;
	}
	(*size_from)--;
	(*size_to)++;
}

void	pa(int *a, int *b, int *size_a, int *size_b)
{
	if (*size_b < 1)
		return ;
	push(b, a, size_b, size_a);
	write(1, "pa\n", 3);
}

void	pb(int *a, int *b, int *size_a, int *size_b)
{
	if (*size_a < 1)
		return ;
	push(a, b, size_a, size_b);
	write(1, "pb\n", 3);
}