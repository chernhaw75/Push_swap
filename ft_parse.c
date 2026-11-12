/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchern-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 13:50:24 by tchern-h          #+#    #+#             */
/*   Updated: 2026/11/07 14:07:25 by tchern-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "push_swap.h"

static int	ft_parse_int(const char *s, int *out)
{
	long	n;
	int		sign;

	sign = 1;
	n = 0;
	if (*s == '-' || *s == '+')
		if (*s++ == '-')
			sign = -1;
	if (!*s)
		return (0);
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (0);
		n = n * 10 + (*s++ - '0');
		if (n * sign > INT_MAX || n * sign < INT_MIN)
			return (0);
	}
	*out = (int)(n * sign);
	return (1);
}

static int	ft_streq(const char *a, const char *b)
{
	while (*a && *a == *b)
	{
		a++;
		b++;
	}
	return (*a == *b);
}

int	ft_parse_flag(const char *s, t_cfg *cfg)
{
	if (ft_streq(s, "--simple"))
		cfg->strat = SIMPLE;
	else if (ft_streq(s, "--medium"))
		cfg->strat = MEDIUM;
	else if (ft_streq(s, "--complex"))
		cfg->strat = COMPLEX;
	else if (ft_streq(s, "--adaptive"))
		cfg->strat = ADAPTIVE;
	else if (ft_streq(s, "--bench"))
		cfg->bench = 1;
	else
		return (0);
	return (1);
}

static int	ft_has_dup(int *a, int n)
{
	int	i;
	int	j;

	i = 0;
	while (i < n)
	{
		j = i + 1;
		while (j < n)
			if (a[i] == a[j++])
				return (1);
		i++;
	}
	return (0);
}

int	ft_load(char **argv, int count, int *a)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (!ft_parse_int(argv[i], &a[i]))
			return (0);
		i++;
	}
	return (!ft_has_dup(a, count));
}
