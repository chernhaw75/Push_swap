/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchern-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 13:50:24 by tchern-h          #+#    #+#             */
/*   Updated: 2026/11/07 14:07:25 by tchern-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "push_swap.h"

int	g_ops[OP_COUNT];

static int	ft_error(int *a, int *b)
{
	free(a);
	free(b);
	write(2, "Error\n", 6);
	return (1);
}

static t_strat	ft_pick(t_strat s, double d)
{
	if (s != ADAPTIVE)
		return (s);
	if (d < 0.2)
		return (SIMPLE);
	if (d < 0.5)
		return (MEDIUM);
	return (COMPLEX);
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
	if (!a || !b || !ft_load(argv + i, n, a))
		return (ft_error(a, b));
	ft_run(a, b, n, &cfg);
	free(a);
	free(b);
	return (0);
}
