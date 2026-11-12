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

int	ft_is_sep(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

static int	ft_parse_tok(const char **p, int *out)
{
	const char	*s;
	long		n;
	int			sign;

	s = *p;
	sign = 1;
	n = 0;
	if (*s == '-' || *s == '+')
		if (*s++ == '-')
			sign = -1;
	if (!*s || ft_is_sep(*s))
		return (0);
	while (*s && !ft_is_sep(*s))
	{
		if (*s < '0' || *s > '9')
			return (0);
		n = n * 10 + (*s++ - '0');
		if (n * sign > INT_MAX || n * sign < INT_MIN)
			return (0);
	}
	*p = s;
	*out = (int)(n * sign);
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
	int			i;
	int			n;
	const char	*s;

	i = 0;
	n = 0;
	while (i < count)
	{
		s = argv[i++];
		while (*s)
		{
			while (ft_is_sep(*s))
				s++;
			if (*s && !ft_parse_tok(&s, &a[n++]))
				return (0);
		}
	}
	return (!ft_has_dup(a, n));
}
