/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchern-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 12:07:19 by tchern-h          #+#    #+#             */
/*   Updated: 2026/11/10 12:07:48 by tchern-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* main.c */
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include "push_swap.h"

typedef enum e_strat { ADAPTIVE, SIMPLE, MEDIUM, COMPLEX } t_strat;

typedef struct s_cfg
{
	t_strat	strat;
	int		bench;
}	t_cfg;

int		g_ops[OP_COUNT];

static int	ft_error(int *a, int *b)
{
	free(a);
	free(b);
	write(2, "Error\n", 6);
	return (1);
}

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

static int	ft_parse_flag(const char *s, t_cfg *cfg)
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

static t_strat	ft_pick(t_strat s, double d)
{
	if (s != ADAPTIVE)
		return (s);
	if (d < 0.2)
		return (SIMPLE);
	if (d < 0.7)
		return (MEDIUM);
	return (COMPLEX);
}

static void	ft_bench(t_strat used, t_cfg *cfg, double d)
{
	static const char	*name[] = {"Adaptive", "Simple", "Medium", "Complex"};
	static const char	*cplx[] = {"", "O(n^2)", "O(n sqrt(n))", "O(n log n)"};
	int					total;
	int					i;
	int					pct;

	total = 0;
	i = 0;
	while (i < OP_COUNT)
		total += g_ops[i++];
	pct = (int)(d * 10000);
	dprintf(2, "[bench] disorder: %d.%02d%%\n", pct / 100, pct % 100);
	dprintf(2, "[bench] strategy: %s / %s\n", name[cfg->strat], cplx[used]);
	dprintf(2, "[bench] total_ops: %d\n", total);
	dprintf(2, "[bench] sa: %d  sb: %d  ss: %d  pa: %d  pb: %d\n",
		g_ops[SA], g_ops[SB], g_ops[SS], g_ops[PA], g_ops[PB]);
	dprintf(2, "[bench] ra: %d  rb: %d  rr: %d  rra: %d  rrb: %d  rrr: %d\n",
		g_ops[RA], g_ops[RB], g_ops[RR], g_ops[RRA], g_ops[RRB], g_ops[RRR]);
}

static void	ft_run(int *a, int *b, int n, t_cfg *cfg)
{
	double	d;
	t_strat	s;

	d = ft_compute_disorder(a, n);
	s = ft_pick(cfg->strat, d);
	if (d > 0.0)
	{
		if (cfg->strat == ADAPTIVE && n <= 5)
			ft_small_sort(a, b, n);
		else if (s == SIMPLE)
			ft_simple_sort(a, b, n);
		else if (s == MEDIUM)
			ft_medium_sort(a, b, n);
		else
			ft_complex_sort(a, b, n);
	}
	if (cfg->bench)
		ft_bench(s, cfg, d);
}

int	main(int argc, char **argv)
{
	t_cfg	cfg;
	int		*a;
	int		*b;
	int		i;
	int		n;

	cfg.strat = ADAPTIVE;
	cfg.bench = 0;
	i = 1;
	while (i < argc && ft_parse_flag(argv[i], &cfg))
		i++;
	n = argc - i;
	if (n <= 0)
		return (0);
	a = malloc(sizeof(int) * n);
	b = malloc(sizeof(int) * n);
	if (!a || !b)
		return (ft_error(a, b));
	n = 0;
	while (i < argc)
		if (!ft_parse_int(argv[i++], &a[n++]))
			return (ft_error(a, b));
	if (ft_has_dup(a, n))
		return (ft_error(a, b));
	ft_run(a, b, n, &cfg);
	free(a);
	free(b);
	return (0);
}
