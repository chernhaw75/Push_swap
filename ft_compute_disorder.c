/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_compute_disorder.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchern-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 13:44:45 by tchern-h          #+#    #+#             */
/*   Updated: 2026/11/07 14:27:11 by tchern-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float	ft_compute_disorder(int *stack, int size)
{
	int	mistakes;
	int	total_pairs;
	int	i;
	int	j;

	mistakes = 0;
	i = 0;
	j = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (stack[i] > stack[j])
				mistakes++;
			j++;
		}
		i++;
	}
	return ((float)mistakes / (float)(size - 1));
}
