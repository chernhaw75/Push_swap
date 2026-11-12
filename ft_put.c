/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchern-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 13:50:24 by tchern-h          #+#    #+#             */
/*   Updated: 2026/11/07 14:07:25 by tchern-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "push_swap.h"

void	ft_putstr_err(const char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	write(2, s, len);
}

void	ft_putnbr_err(int n)
{
	char	c;

	if (n >= 10)
		ft_putnbr_err(n / 10);
	c = '0' + n % 10;
	write(2, &c, 1);
}
