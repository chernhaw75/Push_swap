/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchern-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 13:46:35 by tchern-h          #+#    #+#             */
/*   Updated: 2026/11/07 14:22:34 by tchern-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	push(int *stack_from, int *stack_to, int *size_from, int *size_to)
{
	int	i;

	if (*size_from > 0)
	{
		i = 0;
		while (i > 0)
		{
			stack_to[i] = stack_to[i - 1];
			i--;
		}
		stack_to[0] = stack_from[0];
		i = 0;
		while (i < size_from)
		{
			stack_from[i] = stack_from[i + 1];
			i++;
		}
		(*size_from)--;
		(*size_to)++;
	}
}
