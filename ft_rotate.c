/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchern-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 13:49:25 by tchern-h          #+#    #+#             */
/*   Updated: 2026/11/07 13:49:43 by tchern-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "push_swap.h"

void	rotate_a(int stack_a[], int size_a)
{
	int	first;
	int	i;

	if (!stack_a || size_a < 2)
		return ;
	first = stack_a[0];
	i = 0;
	while (i < size_a - 1)
	{
		stack_a[i] = stack_a[i + 1];
		i++;
	}
	stack_a[size_a - 1] = first;
	g_ops[RA]++;
	write(1, "ra\n", 3);
}

void	rotate_b(int stack_b[], int size_b)
{
	int	first;
	int	i;

	if (!stack_b || size_b < 2)
		return ;
	first = stack_b[0];
	i = 0;
	while (i < size_b - 1)
	{
		stack_b[i] = stack_b[i + 1];
		i++;
	}
	stack_b[size_b - 1] = first;
	g_ops[RB]++;
	write(1, "rb\n", 3);
}


void	reverse_rotate_a(int stack_a[], int size_a)
{
	int	last;
	int	i;

	if (!stack_a || size_a < 2)
		return ;
	last = stack_a[size_a - 1];
	i = size_a - 1;
	while (i > 0)
	{
		stack_a[i] = stack_a[i - 1];
		i--;
	}
	stack_a[0] = last;
	g_ops[RRA]++;
	write(1, "rra\n", 4);
}

void	reverse_rotate_b(int stack_b[], int size_b)
{
	int	last;
	int	i;

	if (!stack_b || size_b < 2)
		return ;
	last = stack_b[size_b - 1];
	i = size_b - 1;
	while (i > 0)
	{
		stack_b[i] = stack_b[i - 1];
		i--;
	}
	stack_b[0] = last;
	g_ops[RRB]++;
	write(1, "rrb\n", 4);
}
