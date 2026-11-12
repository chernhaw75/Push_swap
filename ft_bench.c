/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bench.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchern-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 13:50:24 by tchern-h          #+#    #+#             */
/*   Updated: 2026/11/07 14:07:25 by tchern-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	put_row(int first, int last)
{
	static const char	*names[] = {"sa", "sb", "ss", "pa", "pb", "ra",
		"rb", "rr", "rra", "rrb", "rrr"};

	ft_putstr_err("[bench] ");
	while (first <= last)
	{
		ft_putstr_err(names[first]);
		ft_putstr_err(": ");
		ft_putnbr_err(g_ops[first]);
		if (first < last)
			ft_putstr_err("  ");
		first++;
	}
	ft_putstr_err("\n");
}

static void	put_disorder(double d)
{
	int	pct;

	pct = (int)(d * 10000 + 0.5);
	ft_putstr_err("[bench] disorder: ");
	ft_putnbr_err(pct / 100);
	ft_putstr_err(".");
	ft_putnbr_err(pct % 100 / 10);
	ft_putnbr_err(pct % 10);
	ft_putstr_err("%\n");
}

static void	put_strategy(t_strat used, t_cfg *cfg)
{
	static const char	*name[] = {"Adaptive", "Simple", "Medium", "Complex"};
	static const char	*cplx[] = {"", "O(n^2)", "O(n sqrt(n))", "O(n log n)"};

	ft_putstr_err("[bench] strategy: ");
	ft_putstr_err(name[cfg->strat]);
	ft_putstr_err(" / ");
	ft_putstr_err(cplx[used]);
	ft_putstr_err("\n");
}

void	ft_bench(t_strat used, t_cfg *cfg, double d)
{
	int	total;
	int	i;

	total = 0;
	i = 0;
	while (i < OP_COUNT)
		total += g_ops[i++];
	put_disorder(d);
	put_strategy(used, cfg);
	ft_putstr_err("[bench] total_ops: ");
	ft_putnbr_err(total);
	ft_putstr_err("\n");
	put_row(SA, PB);
	put_row(RA, RRR);
}
