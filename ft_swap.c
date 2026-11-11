/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchern-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 13:50:24 by tchern-h          #+#    #+#             */
/*   Updated: 2026/11/07 14:07:25 by tchern-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "push_swap.h"

static void	swap_top(int *stack)
{
	int	temp;

	temp = stack[0];
	stack[0] = stack[1];
	stack[1] = temp;
}

void	sa(int *stack)
{
	swap_top(stack);
	g_ops[SA]++;
	write(1, "sa\n", 3);
}

void	sb(int *stack)
{
	swap_top(stack);
	g_ops[SB]++;
	write(1, "sb\n", 3);
}

void	ss(int *stack_a, int *stack_b)
{
	swap_top(stack_a);
	swap_top(stack_b);
	g_ops[SS]++;
	write(1, "ss\n", 3);
}
