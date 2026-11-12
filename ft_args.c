/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchern-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 13:50:24 by tchern-h          #+#    #+#             */
/*   Updated: 2026/11/07 14:07:25 by tchern-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

static int	ft_count_tokens(const char *s)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s && ft_is_sep(*s))
			s++;
		if (*s)
			count++;
		while (*s && !ft_is_sep(*s))
			s++;
	}
	return (count);
}

/*
** Number of integers in all arguments (an argument may hold several,
** separated by spaces). -1 if an argument is empty while others exist.
*/
int	ft_count(char **argv, int count)
{
	int	i;
	int	total;
	int	tok;

	i = 0;
	total = 0;
	while (i < count)
	{
		tok = ft_count_tokens(argv[i++]);
		if (tok == 0 && count > 1)
			return (-1);
		total += tok;
	}
	return (total);
}
